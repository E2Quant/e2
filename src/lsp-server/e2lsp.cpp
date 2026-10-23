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
#include <string>
#include <vector>

#include "assembler/BaseType.hpp"
#include "ast/ParserCtx.hpp"
#include "lsp-server/Diagnostic/PublishDiagnosticsParams.hpp"
#include "lsp-server/IoEventLoop.hpp"
#include "lsp-server/RequestStruct.hpp"
#include "lsp-server/ResponseStruct.hpp"
#include "lsp-server/dbcache/LspLsif.hpp"
#include "lsp-server/dbcache/dbevent.hpp"
#include "lsp-server/textDocument/CompletionList.hpp"
#include "lsp-server/textDocument/DefinitionParams.hpp"
#include "lsp-server/textDocument/inlineCompletion.hpp"
#include "lsp-server/util.hpp"
#include "utility/Log.hpp"
namespace e2 {

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

    iresult.capabilities.completionProvider.triggerCharacters = {".", "[", "\"",
                                                                 "'"};
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        iresult.capabilities.completionProvider.triggerCharacters.push_back(
            llog::format("%c", ch));
    }
    for (char ch = 'a'; ch <= 'z'; ch++) {
        iresult.capabilities.completionProvider.triggerCharacters.push_back(
            llog::format("%c", ch));
    }
    iresult.capabilities.completionProvider.resolveProvider = true;

    iresult.capabilities.signatureHelpProvider.triggerCharacters = {"(", ",",
                                                                    ")"};
    iresult.capabilities.semanticTokensProvider.legend.tokenTypes = {
        "namespace", "import", "func", "union"};
    iresult.capabilities.codeActionProvider.CodeActionKind = {
        "quickfix", "source.organizeImports"};
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
bool DocumentSync::DidChange(RequestMessage request_msg,
                             std::string& change_text)
{
    std::size_t len = request_msg.params.count("contentChanges");

    if (len == 0) {
        return false;
    }
    if (request_msg.params["contentChanges"][0].count("range")) {
        change_text = request_msg.params["contentChanges"][0]["text"];
    }

    return true;
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
CompletionList LanguageFeatures::Completion(
    const ContentChangesType& search_key, Position pos)
{
    int rc = 0;
    CompletionList clist;
    EJson ejson;
#ifdef E2L_DEBUG
    llog::echo("search key:", search_key.search_key);
#endif

    if (search_key.source.size() == 0) {
        return clist;
    }

    CompletionItem item;

    std::vector<ElementInfo> ei_list;
    // std::string key = search_key.search_key;
    int ret = 0;
    std::size_t import_post = 0;
    if (search_key.source.substr(0, key_import.length()) == key_import) {
        import_post = search_key.source.length();
        if (search_key.search_key.find("<") == std::string::npos) {
            rc = dbevent.search_import_path("", ei_list);
        }
        else {
            rc = dbevent.search_import_path(search_key.search_key.substr(1),
                                            ei_list);
        }
    }
    else {
        // key =
        dbevent.search_key(search_key.search_key, ei_list);
    }

    if (ret == -1) {
        llog::info("key is empty");
        return clist;
    }
    std::string current_path = _current_uri.substr(file_path.length());

    if (search_key.search_pos_start > pos.character) {
        pos.character = search_key.search_pos_start;
    }
    else {
        pos.character -= search_key.search_key.length();
    }
#ifdef E2L_DEBUG

    llog::echo("search len:", search_key.search_key.length(),
               " line:", pos.line, " char:", pos.character,
               " search post:", search_key.search_pos_start,
               " search source:", search_key.source.length(),
               " import  post:", import_post);
#endif

    for (auto it : ei_list) {
        //   自动提示中 列表显示的内容
        item.label = it.value;
        // 多个提示的时候用来排序的
        item.sortText = it.value + "_" + it.insertText;

        // 最终插入的内容,这个可能会更准确点 textEdit, 以后再优化吧
        if (it.insertText.length() == 0) {
            item.textEdit.newText = it.value;
        }
        else {
            item.documentation =
                "path:\n" + it.code_uri + "\ndoc:\n" + it.insertText;
            item.textEdit.newText = it.insertText;
        }

        item.textEdit.range.start = pos;
        // item.textEdit.range.end = pos;

        switch (it.ek) {
            case e2::ElementKind::_ek_fun:
                item.kind = CompletionItemKind::Function;

                break;
            case e2::ElementKind::_ek_var:

                if (it.code_uri != current_path) {
                    // llog::info(it.value, " uri:", it.code_uri,
                    //            " current:", current_path);
                    continue;
                }
                item.kind = CompletionItemKind::Variable;
                break;
            case e2::ElementKind::_ek_ns_this_call:
                item.kind = CompletionItemKind::Function;
                if (it.from_ns.length() == 0) {
                    item.textEdit.newText = "this::" + it.insertText;
                }
                break;
            case e2::ElementKind::_ek_ns_fun:
                item.kind = CompletionItemKind::Function;
                if (it.from_ns.length() == 0) {
                    item.textEdit.newText = "this::" + it.insertText;
                }
                else {
                    item.textEdit.newText = it.from_ns + "<>::" + it.insertText;

                    item.label = it.from_ns + "<>::" + it.value;
                }
                break;
            case e2::ElementKind::_ek_ns_var:
                item.kind = CompletionItemKind::Variable;
                item.textEdit.newText = "this::" + it.value;

                break;

            case e2::ElementKind::_ek_namespace: {
                item.kind = CompletionItemKind::Class;
                std::vector<ElementInfo> ei_ns_func;
                rc = dbevent.search_ns(it.value, ei_ns_func);
                if (rc == 0) {
                    ns_list(clist, ei_ns_func, pos, true);
                    continue;
                }
            } break;
            case e2::ElementKind::_ek_ns_call: {
                item.kind = CompletionItemKind::Function;
                if (it.from_ns.length() > 0) {
                    item.label =
                        it.from_ns + "<" + it.tag + ">::" + it.insertText;
                    item.sortText += it.tag;

                    item.textEdit.newText =
                        it.from_ns + "<" + it.tag + ">::" + it.insertText;
                }

            } break;

            case e2::ElementKind::_ek_keyword: {
                item.kind = CompletionItemKind::snippet;

                if (it.value == "this") {
                    std::vector<ElementInfo> ei_ns_list;
                    rc = dbevent.search_ns_field(pos.line, ei_ns_list);
                    if (rc == 0) {
                        ns_list(clist, ei_ns_list, pos, false);
                        continue;
                    }
                }
                else if (it.value == "import") {
#ifdef E2L_DEBUG

                    llog::echo(it.value, " search:", search_key.search_key);
#endif
                    std::vector<ElementInfo> ei_mod_list;
                    rc = dbevent.search_import_path("", ei_mod_list);
                    if (rc == 0) {
                        mod_list(clist, ei_mod_list, pos);
                        continue;
                    }
                }
                else {
                    // 多行的话，这个VIM 才不会出错
                    item.insertText = it.insertText;
                }
            } break;
            case e2::ElementKind::_ek_mode_path: {
                item.kind = CompletionItemKind::Module;

                std::string imp_path = it.code_uri;

                item.label = item.sortText = imp_path;
                item.textEdit.newText = "<" + imp_path + ">";

                item.documentation = "path:\n" + it.code_uri + "\ndoc:\n" +
                                     "import <" + imp_path + ">";
                item.textEdit.range.start.character =
                    import_post - search_key.search_key.length();

                item.textEdit.range.start.line = pos.line;

                item.textEdit.range.end.character =
                    item.textEdit.range.start.character +
                    item.textEdit.newText.length();

                item.data = ejson.toDict("doc_uri",
                                         file_path + it.code_dir + it.code_uri);
            } break;
            case e2::ElementKind::_ek_call:
                item.kind = CompletionItemKind::Method;
                break;
            case e2::ElementKind::_ek_union: {
                item.kind = CompletionItemKind::Enum;
                std::vector<ElementInfo> ei_un_list;
                rc = dbevent.search_union_fields(it.value, ei_un_list);
                if (rc == 0) {
                    union_list(clist, ei_un_list, pos, true);
                    continue;
                }
            } break;
            case e2::ElementKind::_ek_call_arg:
                item.kind = CompletionItemKind::TypeParameter;
                item.documentation =
                    "path:\n" + it.code_uri + "\ndoc:\n" + it.from_ns;
                break;
            case e2::ElementKind::_ek_globle_un:
                item.kind = CompletionItemKind::Enum;
                item.label = it.from_ns + "." + it.value;
                item.sortText = it.value;

                item.textEdit.newText = it.from_ns + "." + it.value;

                break;
            default:

#ifdef E2L_DEBUG
                llog::echo("default :", int(it.ek), " text:", it.insertText);
#endif
                item.kind = CompletionItemKind::Text;
                break;
        }

        if (it.ek != e2::ElementKind::_ek_mode_path) {
            item.textEdit.range.end.character =
                item.textEdit.range.start.character +
                item.textEdit.newText.length();
            item.documentation =
                "path:\n" + it.code_uri + "\ndoc:\n" + item.textEdit.newText;
        }

        item.textEdit.range.end.line = pos.line;

        if (it.code_uri.length() == 0) {
            item.data = ejson.toDict("doc_uri", _current_uri);
        }
        else {
            item.data =
                ejson.toDict("doc_uri", file_path + it.code_dir + it.code_uri);
        }
        clist.items.push_back(item);
    }
    if (clist.items.size() == 0) {
        llog::info("clist is empty");
    }
    return clist;

} /* -----  end of function LanguageFeatures::Completion  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LanguageFeatures::ns_list
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LanguageFeatures::ns_list(CompletionList& clist,
                               std::vector<ElementInfo>& ei_ns_list,
                               Position pos, bool self_or_call)
{
    CompletionItem item_ns;
    EJson ejson;

    for (auto nit : ei_ns_list) {
        switch (nit.ek) {
            case e2::ElementKind::_ek_ns_fun:
                item_ns.kind = CompletionItemKind::Function;

                break;
            case e2::ElementKind::_ek_ns_var:
                item_ns.kind = CompletionItemKind::Variable;

                break;
            default:
                break;
        }
        if (self_or_call) {
            item_ns.label =
                nit.from_ns + "<" + nit.tag + ">::" + nit.insertText;
            item_ns.sortText = nit.tag;

            item_ns.textEdit.newText =
                nit.from_ns + "<" + nit.tag + ">::" + nit.insertText;
        }
        else {
            item_ns.label = "this::" + nit.value;
            item_ns.sortText = "this::" + nit.value;
            if (nit.insertText.length() == 0) {
                item_ns.textEdit.newText = "this::" + nit.value;
            }
            else {
                item_ns.textEdit.newText = "this::" + nit.insertText;
            }
        }

        item_ns.documentation =
            "path:\n" + nit.code_uri + "\ndoc:\n" + item_ns.textEdit.newText;

        item_ns.textEdit.range.start = pos;

        item_ns.textEdit.range.end = pos;

        item_ns.data =
            ejson.toDict("doc_uri", file_path + nit.code_dir + nit.code_uri);

        clist.items.push_back(item_ns);
    }
} /* -----  end of function LanguageFeatures::ns_list  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LanguageFeatures::union_list
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LanguageFeatures::union_list(CompletionList& clist,
                                  std::vector<ElementInfo>& ei_un_list,
                                  Position pos, bool self_or_call)
{
    CompletionItem item_ns;
    EJson ejson;

    for (auto nit : ei_un_list) {
        switch (nit.ek) {
            case e2::ElementKind::_ek_union:
                item_ns.kind = CompletionItemKind::Enum;
                break;
            case e2::ElementKind::_ek_globle_un:
                item_ns.kind = CompletionItemKind::EnumMember;
                break;
            default:
                break;
        }
        if (self_or_call) {
            item_ns.label = nit.from_ns + "." + nit.value;
            item_ns.sortText = nit.value;

            item_ns.textEdit.newText = nit.from_ns + "." + nit.value;
        }
        else {
            llog::info("value:", nit.value);
        }
        item_ns.documentation =
            "path:\n" + nit.code_uri + "\ndoc:\n" + item_ns.textEdit.newText;
        item_ns.textEdit.range.start = pos;

        item_ns.textEdit.range.end = pos;

        item_ns.data = ejson.toDict("doc_uri", file_path + nit.code_uri);

        clist.items.push_back(item_ns);
    }
} /* -----  end of function LanguageFeatures::union_list  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LanguageFeatures::mod_list
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LanguageFeatures::mod_list(CompletionList& clist,
                                std::vector<ElementInfo>& ei_mod_list,
                                Position pos)
{
    CompletionItem item;
    EJson ejson;

    for (auto nit : ei_mod_list) {
        item.kind = CompletionItemKind::Module;

        std::string imp_path = nit.code_uri;

        item.label = item.sortText = imp_path;
        item.textEdit.newText = "import <" + imp_path + ">";

        item.documentation =
            "path:\n" + nit.code_uri + "\ndoc:\n" + "import <" + imp_path + ">";
        item.textEdit.range.start.character = 0;

        item.textEdit.range.start.line = pos.line;

        item.textEdit.range.end.character = item.textEdit.newText.length();
        item.textEdit.range.end.line = pos.line;

        item.data =
            ejson.toDict("doc_uri", file_path + nit.code_dir + nit.code_uri);

        clist.items.push_back(item);
    }
} /* -----  end of function LanguageFeatures::mod_list  ----- */

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
        if (ds.range.start.line > 0) {
            ds.range.start.line -= 1;
        }
        ds.range.start.character = it.begin_column;
        ds.range.end.line = it.code_line;
        if (ds.range.end.line > 0) {
            ds.range.end.line -= 1;
        }
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
    // llog::echo(dp.textDocument.uri);
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
        //             llog::format("write error len:%ld size:%ld", len,
        //             size);
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
 *         Name:  LSPTransport::init_data
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LSPTransport::init_data()
{
    std::size_t cores = std::thread::hardware_concurrency();
    _pool.run(cores > 0 ? cores : 2);

    auto fun = [this](const std::string& value) {
        this->ctx.project(value);
    };  // -----  end lambda  -----

    LspLsif ll;
    ll.load_lib_json(fun);

    ctx.all_scan(false);

} /* -----  end of function LSPTransport::init_data  ----- */

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
#ifdef E2L_DEBUG
            llog::info("initialize");
#endif
            initialize_response(request_msg);
        }
        else if (request_msg.method == "initialized") {
#ifdef E2L_DEBUG
            llog::info("initialized");
#endif
        }
        else if (request_msg.method == "textDocument/codeAction") {
#ifdef E2L_DEBUG
            llog::info("codeAction");
#endif
        }
        else if (request_msg.method == "textDocument/completion") {
            // 自动提示
#ifdef E2L_DEBUG
            llog::info("completion");
#endif
            if (_change_text.search_key.size() > 0) {
                auto fun = [this](RequestMessage r) {
                    this->complete_response(r);
                };  // -----  end lambda  -----

                _pool.enqueue(fun, request_msg);
            }
        }
        else if (request_msg.method == "textDocument/definition" ||
                 request_msg.method == "textDocument/typeDefinition" ||
                 request_msg.method == "textDocument/declaration") {
            llog::info(request_msg.method);
            // 跳转的
            auto fun = [this](RequestMessage r) {
                std::string rootUri = r.params["textDocument"]["uri"];
                LanguageFeatures lf(rootUri);
                DefinitionParams dps = lf.Definition(r);
                this->location(dps, r.id);
            };  // -----  end lambda  -----

            _pool.enqueue(fun, request_msg);
        }
#ifdef E2L_DEBUG
        else {
            llog::bug("else:" + request_msg.method);
            // CERR("id else:" + request_msg.method);
            //  return false;
        }
#endif
    }
    else {
        DocumentSync ds;

        // Notification
        if (request_msg.method == "textDocument/didOpen" ||
            request_msg.method == "textDocument/didSave") {
            // 打开文件或保存
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
            std::string change_text = "";
            bool is_change = ds.DidChange(request_msg, change_text);
            if (is_change) {
#ifdef E2L_DEBUG

                llog::info("didchange:", change_text,
                           " size:", change_text.length());
#endif
                if (change_text.length() < 2) {
                    _change_text.clean();
                }
                else {
                    int rnum = split(change_text, " ", _change_text);
#ifdef E2L_DEBUG

                    llog::info("didchange:", _change_text.source,
                               " search:", _change_text.search_key,
                               " pos start:", _change_text.search_pos_start);
#endif
                    if (rnum == 0) {
                        _change_text.clean();
                    }
                }
            }
        }
#ifdef E2L_DEBUG
        else {
            llog::bug("else:" + request_msg.method);

            // CERR("else:" + request_msg.method);
            //  return false;
        }
#endif
    }

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
    std::string rootUri = request_msg.params["textDocument"]["uri"];
    Position _complete_position;
    if (request_msg.params.count("position") > 0) {
        _complete_position.character =
            request_msg.params["position"]["character"];
        _complete_position.line = request_msg.params["position"]["line"];
    }
    else {
        _complete_position.character = 0;
        _complete_position.line = 0;
    }

    e2_json response = {{"jsonrpc", "2.0"}, {"id", request_msg.id}};

    LanguageFeatures lf(rootUri);
    CompletionList clist = lf.Completion(_change_text, _complete_position);
    response["result"] = clist;

    for (auto& item : response["result"]["items"]) {
        if (item.count("insertText") > 0) {
            std::string name = item["insertText"].get<std::string>();
            if (name.length() > 0) {
                item.erase("textEdit");
            }
        }
    }

    std::string json_dump = response.dump();

    std::string str_json =
        llog::format(response_fmt, json_dump.size(), json_dump.c_str());

    // llog::echo(str_json);

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
 *  处理代码报错
 * ============================================
 */
void LSPTransport::diagnostics(TextDocumentItem& tdi,
                               RequestMessage request_msg)
{
    std::string uri = tdi.uri.substr(_file_p.length());
    ctx.e2lsp();

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
        ret = ctx.ProjPath(mod.mod_name.c_str());
        if (ret < 0) {
            LocationType loc_mod;
            loc_mod.mod_name = mod.mod_name;
            loc_mod.code_line = mod.code_line;
            loc_mod.code_uri = mod.code_uri;
            loc_mod.begin_line = loc_mod.end_line = mod.code_line - 1;
            loc_mod.begin_column = import_str.length();
            loc_mod.end_column = mod.mod_name.length() + import_str.length();
            loc_mod.msg = "not found mode name:" + mod.mod_name;
            loc_mod.code_type = "mode not found";
            d2dt.push_back(loc_mod);
        }
    }

    ElementInfoType eit = ctx.element_data();
    _dbevent.save_element(eit);

    std::string rootUri = request_msg.params["textDocument"]["uri"];
    LanguageFeatures lf(rootUri);
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
#ifdef E2L_DEBUG
        llog::echo("str empty");
#endif
        return "";
    }
    size_t start = str.find_first_not_of(WHITESPACE);
    if (start == std::string::npos) {
#ifdef E2L_DEBUG
        llog::echo("str empty find first");
#endif
        return "";
    }  // 字符串仅由空白字符组成

    size_t end = str.find_last_not_of(WHITESPACE);
    std::string ret = str.substr(start, end - start + 1);

    return ret;
} /* -----  end of function LSPTransport::trim  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::split
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int LSPTransport::split(const std::string& str, const std::string& split_str,
                        ContentChangesType& dest)
{
    int ret = 0;
    std::string::size_type n;
    std::string node = trim(str);
    // std::string value = "";

    dest.source = node;
    dest.search_pos_start = 0;
    do {
        if (node.length() < 2) {
            return ret;
        }
        n = node.find(split_str);

        if (n != std::string::npos) {
            node = node.substr(n);
            dest.search_pos_start += n;
        }
        node = trim(node);
        ret++;
        dest.search_key = node;

    } while (n != std::string::npos && node.length() > 0);

    return ret;
} /* -----  end of function LSPTransport::split  ----- */

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
    e2_json response = {{"jsonrpc", "2.0"}, {"id", id}};
    std::vector<Location> loc_list;
    std::vector<ElementInfo> ei_list;
    std::string uri = dp.textDocument.uri.substr(_file_p.length());
    int character = dp.position.character;
    // Line position in a document (zero-based).
    int line = dp.position.line + 1;

    std::string value = "";
    int ret = _dbevent.value(uri, line, character, value);
    if (ret != -1 && value.length() > 0) {
        ei_list.clear();

        ret = _dbevent.postion(value, ei_list);
        if (ret != -1) {
            for (auto it : ei_list) {
                Location loc;
                loc.uri = _file_p + it.code_uri;
                loc.range.start.character = it.begin_column;
                loc.range.start.line = it.begin_line - 1;

                loc.range.end.character = it.end_column;
                loc.range.end.line = it.end_line - 1;
                loc_list.push_back(loc);
            }
        }
    }

    response["result"] = loc_list;

    std::string json_dump = response.dump();

    std::string str_json =
        llog::format(response_fmt, json_dump.size(), json_dump.c_str());

    //    llog::echo(str_json);

    _stream.write(str_json.c_str(), str_json.size());

} /* -----  end of function LSPTransport::location  ----- */

}  // namespace e2
