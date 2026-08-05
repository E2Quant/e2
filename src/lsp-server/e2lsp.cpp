/*
 * =====================================================================================
 *
 *       Filename:  e2lsp.cpp
 *
 *    Description:  e2lsp
 *
 *        Version:  1.0
 *        Created:  2026/04/24 14时36分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vyouzhi (vz), vyouzhi@gmail.com
 *   Organization:  Etomc2.com
 *        LICENSE: BSD-3-Clause license
 *
 *  Copyright (c) 2019-2022, vyouzhi
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  * Neither the name of vyouzhi and/or the DataFrame nor the
 *  names of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL vyouzhi BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * =====================================================================================
 */
#include "lsp-server/e2lsp.hpp"

#include <unistd.h>

#include <cstddef>
#include <cstdio>
#include <future>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <vector>

#include "assembler/BaseNode.hpp"
#include "assembler/BaseType.hpp"
#include "ast/ParserCtx.hpp"
#include "lsp-server/Diagnostic/PublishDiagnosticsParams.hpp"
#include "lsp-server/IoEventLoop.hpp"
#include "lsp-server/LspLsif.hpp"
#include "lsp-server/RequestStruct.hpp"
#include "lsp-server/ResponseStruct.hpp"
#include "lsp-server/textDocument/CompletionList.hpp"
#include "lsp-server/textDocument/DefinitionParams.hpp"
#include "lsp-server/textDocument/inlineCompletion.hpp"
#include "lsp-server/util.hpp"
#include "utility/Log.hpp"
namespace e2 {

// 从 stdin 读取一条完整的 LSP 消息
std::string readLSPMessage()
{
    std::string header;
    // 读取直到遇到两个连续的换行符（即空行）
    while (std::getline(std::cin, header) && !header.empty()) {
        std::cout << "header:" << header << std::endl;
        // 解析 Content-Length
        if (header.find("Content-Length:") == 0) {
            size_t contentLength = std::stoi(header.substr(16));
            // 读取两个换行符（\r\n\r\n 中的第二部分）
            std::cin.get();  // 读取一个字符，通常是 '\r' 或 '\n'
            std::cin.get();  // 再读取一个字符
                             // 根据长度读取 JSON 主体
            std::string body(contentLength, '\0');
            std::cin.read(&body[0], contentLength);
            return body;
        }
    }
    return "";
}
// 发送 LSP 格式消息到 stdout
void sendLSPMessage(const std::string& jsonStr)
{
    std::cout << "Content-Length: " << jsonStr.size() << "\r\n\r\n" << jsonStr;
    std::cout.flush();
}

e2_json handleInitialize(const e2_json& params)
{
    e2_json response = {{"capabilities",
                         {
                             {"definitionProvider",
                              true},  // 声明支持跳转到定义
                                      // 可以在此添加其他支持的能力，如
                                      // textDocumentSync、hoverProvider 等
                         }}};
    return response;
}

void handleDidOpen(const e2_json& params)
{
    std::string uri = params["textDocument"]["uri"];
    std::string text = params["textDocument"]["text"];
    openDocuments[uri] = text;

    std::cout << "uri:" << uri << "  text:" << text << std::endl;
    // 此处可以触发初步的语法分析或诊断
}

e2_json handleDefinition(const e2_json& params)
{
    std::string uri = params["textDocument"]["uri"];
    int line = params["position"]["line"];
    int character = params["position"]["character"];
    std::cout << "uri:" << uri << "  line:" << line << " char:" << character
              << std::endl;

    e2_json result = e2_json::array();  // 定义可能返回多个位置，以数组形式

    // 极简示例：如果请求的是 main.cpp 中 loopPrint 的调用，则跳转到
    // loopPrint.cpp
    // if (uri.find("main.cpp") != std::string::npos && line == 2 &&
    //     character == 2) {
    //     json location = {{"uri",
    //     "file:///path/to/your/project/loopPrint.cpp"},
    //                      {"range",
    //                       {{"start", {{"line", 2}, {"character", 5}}},
    //                        {"end", {{"line", 2}, {"character", 14}}}}}};
    //     result.push_back(location);
    // }
    return result;
}

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LifecycleMsg::Initialize
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
InitializeResult LifecycleMsg::Initialize()
{
    InitializeResult iresult;
    //.change
    iresult.capabilities.textDocumentSync = TextDocumentSyncKind::Incremental;
    //    iresult.capabilities.textDocumentSync.openClose = false;

    iresult.capabilities.completionProvider.triggerCharacters = {"."};
    iresult.capabilities.completionProvider.resolveProvider = true;
    iresult.capabilities.signatureHelpProvider.triggerCharacters = {"(", ",",
                                                                    "="};
    iresult.capabilities.semanticTokensProvider.legend.tokenTypes = {
        "namespace", "import", "func", "union"};
    return iresult;
} /* -----  end of function LifecycleMsg::Initialize  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DocumentSync::DidOpen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  当文档打开的时候，在这儿返回代码有没有错误
 * ============================================
 */
TextDocumentItem DocumentSync::DidOpen(RequestMessage request_msg)
{
    DidOpenTextDocumentParams dotdp;
    if (request_msg.params.count("textDocument") == 0) {
        return dotdp.textDocument;
    }
    if (request_msg.params["textDocument"].count("languageId") == 0) {
        dotdp.textDocument.uri = request_msg.params["textDocument"]["uri"];
        dotdp.textDocument.version = 1;
    }
    else {
        dotdp = request_msg.params.get<DidOpenTextDocumentParams>();
    }

    return dotdp.textDocument;

} /* -----  end of function DocumentSync::DidOpen  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DocumentSync::DidChange
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::string DocumentSync::DidChange(RequestMessage request_msg)
{
    std::string change_text = "";
    std::size_t len = request_msg.params.count("contentChanges");

    if (len == 0) {
        return change_text;
    }
    if (request_msg.params["contentChanges"][0].count("range")) {
        change_text = request_msg.params["contentChanges"][0]["text"];
    }

    return change_text;
} /* -----  end of function DocumentSync::DidChange  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LanguageFeatures::inlineCompletion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LanguageFeatures::inlineCompletion() {

} /* -----  end of function LanguageFeatures::inlineCompletion  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LanguageFeatures::Completion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
CompletionList LanguageFeatures::Completion(std::string search_key,
                                            Position pos)
{
    CompletionList clist;
    std::vector<CompletionItem> items;
    EJson ejson;
    llog::echo("search key:", search_key);
    if (search_key.length() == 0) {
        return clist;
    }

    CompletionItem item;
    LspLsif ll;

    std::vector<ElementInfo> ei_list;

    std::string sql = llog::format(
        "select e2lfile, value,code from e2lsp where value like \"%s%%\" ",
        search_key.c_str());

    ll.query(sql, call_fun, &ei_list);

    llog::info(sql);
    for (auto it : ei_list) {
        item.label = it.value;
        item.sortText = it.value;

        switch (it.ek) {
            case e2::ElementKind::_ek_namespace:
                item.kind = CompletionItemKind::Class;
                break;
            case e2::ElementKind::_ek_fun:
                item.kind = CompletionItemKind::Class;
                break;
            case e2::ElementKind::_ek_var:
                item.kind = CompletionItemKind::Variable;
                break;
            case e2::ElementKind::_ek_keyword:
                item.kind = CompletionItemKind::Keyword;
                break;

            default:
                item.kind = CompletionItemKind::Text;
                break;
        }

        item.insertText = it.insertText;
        std::string uri = it.code_path;
        item.data = ejson.toDict("doc_uri", uri);

        items.push_back(item);
    }

    clist.items = items;

    return clist;

} /* -----  end of function LanguageFeatures::Completion  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LanguageFeatures::PublishDiagnostics
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
PublishDiagnosticsParams LanguageFeatures::PublishDiagnostics(
    TextDocumentItem tdi, std::vector<LocationType> e2d)
{
    PublishDiagnosticsParams pdp;
    pdp.uri = tdi.uri;
    pdp.version = tdi.version;

    for (auto it : e2d) {
        Diagnostic ds;

        ds.range.start.line = it.code_line;
        ds.range.start.character = it.begin_column;
        ds.range.end.line = it.code_line;
        ds.range.end.character = it.end_column;

        ds.severity = DiagnosticSeverity::Error;
        ds.code = it.code_type;
        ds.message = it.msg;
        ds.source = "e2lsp";

        pdp.diagnostics.push_back(ds);
    }

    return pdp;
} /* -----  end of function LanguageFeatures::PublishDiagnostics  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LanguageFeatures::Definition
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
DefinitionParams LanguageFeatures::Definition(RequestMessage request_msg)
{
    DefinitionParams dp;
    dp.textDocument.uri = request_msg.params["textDocument"]["uri"];

    if (request_msg.params.count("position")) {
        dp.position = request_msg.params["position"].get<Position>();
    }

    return dp;
} /* -----  end of function LanguageFeatures::Definition  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  StdIOStream::read
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int StdIOStream::read(char* buffer, std::size_t size, FILE* io_read)
{
    char* ch = buffer;
    std::size_t rsize = 0;
    while ((rsize = fread(ch, sizeof(char), 1, io_read))) {
        if (*ch == '\n' && size == 1) {
            break;
        }  // 行结束
        if (*ch == '\r' || *ch == '\n') {
            continue;
        }  // 忽略 \r

        size -= rsize;

        if (size == 0) {
            break;
        }
        ch++;
    }

    if (std::feof(stdin)) {
#ifdef E2L_DEBUG
        CERR("Successfully reached the End-Of-File");
#endif
        return -1;
    }
    if (std::ferror(stdin)) {
#ifdef E2L_DEBUG
        CERR("A stream error occurred");
#endif
        return -1;
    }

    return size;
} /* -----  end of function StdIOStream::read  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  StdIOStream::write
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int StdIOStream::write(const char* buffer, std::size_t size)
{
    std::size_t len = fwrite(buffer, 1, size, stdout);
    if (len < size) {
        // #ifdef E2L_DEBUG
        //         std::string data =
        //             llog::format("write error len:%ld size:%ld", len, size);
        //         CERR(data);
        // #endif
        return -1;
    }
    // #ifdef E2L_DEBUG
    //     std::string valu = llog::format("write ok len:%ld size:%ld", len,
    //     size); CERR(valu);
    // #endif

    std::fflush(stdout);

    return len;
} /* -----  end of function StdIOStream::write  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  StdIOStream::HeaderPart
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */

void StdIOStream::HeaderPart()
{
    std::string hp = llog::format("Content-Length: 0\r\nContent-Type: %s\r\n",
                                  content_type.c_str());

    write(hp.data(), hp.size());
}

/* -----  end of function StdIOStream::HeaderPart  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::next
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LSPTransport::next()
{
    IoEventLoop loop;

    auto read_fun = [&](int fd) {
        const char* mode = "r";
        FILE* _fd = fdopen(fd, mode);
        RequestMessage request_msg = read_message(_fd);
        bool ret = route(request_msg);
        if (ret == false) {
            loop.stop();
        }
    };  // -----  end lambda  -----

    loop.add_read_fd(STDIN_FILENO, read_fun);

    loop.run();
} /* -----  end of function LSPTransport::next  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::route
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LSPTransport::route(RequestMessage request_msg)
{
    if (request_msg.id) {
        if (request_msg.method == "initialize") {
            initialize_response(request_msg);
        }
        else if (request_msg.method == "initialized") {
            //   CERR("inited");
        }
        else if (request_msg.method == "textDocument/codeAction") {
            // CERR("codeAction");
        }
        else if (request_msg.method == "textDocument/completion") {
            if (_change_text.length() > 0) {
                auto fun = [this](RequestMessage r) {
                    this->complete_response(r);
                };  // -----  end lambda  -----

                _pool.enqueue(fun, request_msg);
            }
        }
        else if (request_msg.method == "textDocument/definition" ||
                 request_msg.method == "textDocument/typeDefinition" ||
                 request_msg.method == "textDocument/declaration") {
            auto fun = [this](RequestMessage r) {
                LanguageFeatures lf;
                DefinitionParams dps = lf.Definition(r);
                this->location(dps, r.id);
            };  // -----  end lambda  -----

            _pool.enqueue(fun, request_msg);
        }
        else {
            // CERR("id else:" + request_msg.method);
            //  return false;
        }
    }
    else {
        DocumentSync ds;

        // Notification
        if (request_msg.method == "textDocument/didOpen" ||
            request_msg.method == "textDocument/didSave") {
            auto dfun = [this, &ds](RequestMessage r) {
                TextDocumentItem td;
                td = ds.DidOpen(r);
                if (td.uri.length() > 0) {
                    this->diagnostics(td, r);
                }
            };  // -----  end lambda  -----

            _pool.enqueue(dfun, request_msg);
        }
        else if (request_msg.method == "textDocument/didChange") {
            _change_text = ds.DidChange(request_msg);
            _change_text = trim(_change_text);
        }

        else {
            // CERR("else:" + request_msg.method);
            //  return false;
        }
    }

    // llog::info("next:", request_msg.method);
    return true;

} /* -----  end of function LSPTransport::route  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::initialize
 *  ->  void *std::fflush(stdout);

 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LSPTransport::initialize()
{
    _stream.HeaderPart();

} /* -----  end of function LSPTransport::initialize  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::read_message
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
RequestMessage LSPTransport::read_message(FILE* io_read)
{
    int contentLength = 0;
    std::string headerLine = "";
    char buf;
    RequestMessage request_msg;

    // 不知道长度的时候
    while (_stream.read(&buf, 1, io_read) == 0) {
        headerLine.push_back(buf);
        std::fflush(stdout);
    }

    if (headerLine.empty()) {
        CERR("headerLine empty!");

        return request_msg;
    }
    // 解析 Content-Length
    if (sscanf(headerLine.c_str(), "Content-Length: %d", &contentLength) != 1) {
        // 解析长度出错
        CERR(contentLength);
    }
    std::fflush(stdout);

    if (contentLength == 0) {
        CERR("cententlength == 0");
        return request_msg;
    }
    // #ifdef E2L_DEBUG
    //     CERR(headerLine);
    //     //    CERR(std::string(buffer.data()));
    // #endif
    // 知道长度的时候
    std::vector<char> buffer(contentLength + 1, 0);
    if (_stream.read(buffer.data(), contentLength, io_read) != 0) {
        CERR("error read content!");
        return request_msg;
    }

    if (buffer.empty()) {
        return request_msg;
    }
    auto request_json = e2_json::parse(buffer);
    if (request_json.size() == 0) {
        return request_msg;
    }

    if (request_json.contains("id")) {
        request_msg.id = request_json["id"];
    }
    else {
        request_msg.id = 0;
    }

    request_msg.jsonrpc = request_json["jsonrpc"];
    request_msg.method = request_json["method"];
    request_msg.params = request_json["params"];

    return request_msg;
    //    return nlohmann::json::parse(msg);
} /* -----  end of function LSPTransport::read_message  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::initialize_response
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LSPTransport::initialize_response(RequestMessage request_msg)
{
    std::string rootUri = request_msg.params["rootUri"];
    std::string rootPath = request_msg.params["rootPath"];
    e2_json response = {{"jsonrpc", "2.0"}, {"id", request_msg.id}};

    LifecycleMsg life;
    response["result"] = life.Initialize();

    std::string json_dump = response.dump();

    std::string str_json =
        llog::format(response_fmt, json_dump.size(), json_dump.c_str());

    // CERR(str_json);

    _stream.write(str_json.c_str(), str_json.size());

} /* -----  end of function LSPTransport::initialize_response  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::complete_response
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LSPTransport::complete_response(RequestMessage request_msg)
{
    // std::string rootUri = request_msg.params["textDocument"]["uri"];
    Position _complete_position;
    _complete_position.character = request_msg.params["position"]["character"];
    _complete_position.line = request_msg.params["position"]["line"];

    e2_json response = {{"jsonrpc", "2.0"}, {"id", request_msg.id}};

    LanguageFeatures lf;
    CompletionList clist = lf.Completion(_change_text, _complete_position);
    response["result"] = clist;

    std::string json_dump = response.dump();

    std::string str_json =
        llog::format(response_fmt, json_dump.size(), json_dump.c_str());

    _change_text = "";

    _stream.write(str_json.c_str(), str_json.size());

} /* -----  end of function LSPTransport::complete_response  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::diagnostics
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LSPTransport::diagnostics(TextDocumentItem& tdi,
                               RequestMessage request_msg)
{
    e2::ParserCtx ctx;

    std::string uri = tdi.uri.substr(_file_p.length());
    ctx.all_scan(false);
    ctx.clear_loc();

    e2_json response = {{"jsonrpc", "2.0"}};

    int ret = ctx.toparse(uri.c_str());
    PublishDiagnosticsParams pdp;
    std::vector<LocationType> d2dt;
    if (ret < 0) {
        d2dt = ctx.grammar_error();
    }
    std::string import_str = "import";
    std::deque<LocationType> mods = ctx.imports();
    for (auto mod : mods) {
        ret = ctx.findPath(mod.mod_name.c_str());
        if (ret < 0) {
            LocationType loc_mod;
            loc_mod.mod_name = mod.mod_name;
            loc_mod.code_line = mod.code_line;
            loc_mod.code_path = mod.code_path;
            loc_mod.begin_line = loc_mod.end_line = mod.code_line - 1;
            loc_mod.begin_column = import_str.length();
            loc_mod.end_column = mod.mod_name.length() + import_str.length();
            loc_mod.msg = "not found mode name:" + mod.mod_name;
            loc_mod.code_type = "mode not found";
            d2dt.push_back(loc_mod);
        }
    }

    ElementInfoType eit = ctx.element_data();
    LspLsif ll;

    for (auto value : eit) {
        ll.clear(value.first);
        ll.batchInsert(value.second);
    }

    LanguageFeatures lf;
    pdp = lf.PublishDiagnostics(tdi, d2dt);

    response["params"] = pdp;
    response["method"] = "textDocument/publishDiagnostics";
    std::string json_dump = response.dump();

    std::string str_json =
        llog::format(response_fmt, json_dump.size(), json_dump.c_str());

    _stream.write(str_json.c_str(), str_json.size());

} /* -----  end of function LSPTransport::diagnostics  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::trim
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::string LSPTransport::trim(const std::string& str)
{
    if (str.length() == 0) {
        return "";
    }
    size_t start = str.find_first_not_of(WHITESPACE);
    if (start == std::string::npos) return "";  // 字符串仅由空白字符组成

    size_t end = str.find_last_not_of(WHITESPACE);
    std::string ret = str.substr(start, end - start + 1);
    if (ret.find(" ") != std::string::npos) {
        return "";
    }

    return ret;
} /* -----  end of function LSPTransport::trim  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::location
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LSPTransport::location(DefinitionParams dp, int id)
{
    std::vector<ElementInfo> ei_list;
    std::string uri = dp.textDocument.uri.substr(_file_p.length());
    int character = dp.position.character;
    int line = dp.position.line + 1;
    std::string sql = llog::format(
        "SELECT value,begin_column,end_column,ek  from e2lsp WHERE e2lfile = "
        "\"%s\" and code_line=%d and begin_column <= %d and end_column >= %d "
        "and ek>3 LIMIT 1;",
        uri.c_str(), line, character, character);

    llog::info(sql);
    LspLsif ll;

    ll.query(sql, call_fun, &ei_list);

    if (ei_list.size() == 0) {
        llog::echo("size == 0");
        return;
    }

    std::string value = ei_list.at(0).value;

    sql = llog::format(
        "SELECT e2lfile, value,begin_column,begin_line,end_column,end_line,ek  "
        "from e2lsp WHERE "
        "value = \"%s\"  and  ek> 0 and ek < %d ;",
        value.c_str(), int(ElementKind::_ek_call));
    llog::info(sql);

    ei_list.clear();

    ll.query(sql, call_fun, &ei_list);

    if (ei_list.size() == 0) {
        llog::echo("size == 0");

        return;
    }

    std::vector<Location> loc_list;
    for (auto it : ei_list) {
        Location loc;
        loc.uri = _file_p + it.code_path;
        loc.range.start.character = it.begin_column;
        loc.range.start.line = it.begin_line - 1;

        loc.range.end.character = it.end_column;
        loc.range.end.line = it.end_line - 1;
        loc_list.push_back(loc);
    }

    e2_json response = {{"jsonrpc", "2.0"}, {"id", id}};
    response["result"] = loc_list;

    std::string json_dump = response.dump();

    std::string str_json =
        llog::format(response_fmt, json_dump.size(), json_dump.c_str());

    llog::echo(str_json);

    _stream.write(str_json.c_str(), str_json.size());

} /* -----  end of function LSPTransport::location  ----- */

}  // namespace e2
