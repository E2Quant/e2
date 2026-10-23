/*
 * =====================================================================================
 *
 *       Filename:  e2lsp.hpp
 *
 *    Description:  e2lsp
 *
 *        Version:  1.0
 *        Created:  2026/04/24 14时34分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vyouzhi (vz), vyouzhi@gmail.com
 *   Organization:  Etomc2.com
 *        LICENSE:  BSD-3-Clause license
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
 *
 * =====================================================================================
 */

#ifndef E2LSP_INC
#define E2LSP_INC
#include <cstddef>
#include <string>
#include <thread>
#include <vector>

#include "ast/ParserCtx.hpp"
#include "lsp-server/Diagnostic/PublishDiagnosticsParams.hpp"
#include "lsp-server/LspThreadPool.hpp"
#include "lsp-server/ResponseStruct.hpp"
#include "lsp-server/dbcache/dbevent.hpp"
#include "lsp-server/textDocument/CompletionList.hpp"
#include "lsp-server/textDocument/DefinitionParams.hpp"
#include "lsp-server/util.hpp"
namespace e2 {

struct __ContentChangesType {
    std::string source;
    std::string search_key;
    std::size_t search_pos_start;

    void clean()
    {
        source = "";
        search_key = "";
        search_pos_start = 0;
    }
}; /* ----------  end of struct __ContentChangesType  ---------- */

typedef struct __ContentChangesType ContentChangesType;

/*
 * ================================
 *        Class:  LifecycleMsg
 *  Description:
 * ================================
 */
class LifecycleMsg {
public:
    /* =============  LIFECYCLE     =================== */
    LifecycleMsg() {}; /* constructor */

    /* =============  ACCESSORS     =================== */
    InitializeResult Initialize();
    void Initialized();
    void RegisterCap();
    void UnRegisterCap();
    void SetTrace();
    void LogTrace();
    void Shutdown();
    void Exit();
    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

}; /* -----  end of class LifecycleMsg  ----- */

/*
 * ================================
 *        Class:  DocumentSync
 *  Description:
 * ================================
 */
class DocumentSync {
public:
    /* =============  LIFECYCLE     =================== */
    DocumentSync() {}; /* constructor */

    /* =============  ACCESSORS     =================== */
    void ListTextDocument();
    TextDocumentItem DidOpen(RequestMessage);
    bool DidChange(RequestMessage, std::string&);
    void WillSave();
    void WillSaveWaitUntil();
    void DidSave();
    void DidClose();
    void Rename();
    void ListNoteBook();
    void DidOpenNoteBook();
    void DidChangeNoteBook();
    void DidSaveNoteBook();
    void DidCloseNoteBook();

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS
     *==================
     */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

}; /* -----  end of class DocumentSync  ----- */

/*
 * ================================
 *        Class:  LanguageFeatures
 *  Description:
 * ================================
 */
class LanguageFeatures {
public:
    /* =============  LIFECYCLE     =================== */
    LanguageFeatures(std::string uri)
    {
        _current_uri = uri;
        dbevent.set_current_uri(uri);
    }; /* constructor */

    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */
    CompletionList Completion(const ContentChangesType& search_key, Position);
    void inlineCompletion();

    PublishDiagnosticsParams PublishDiagnostics(TextDocumentItem,
                                                std::vector<LocationType>);

    DefinitionParams Definition(RequestMessage);
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */
    void ns_list(CompletionList&, std::vector<ElementInfo>&, Position pos,
                 bool self_or_call);
    void union_list(CompletionList&, std::vector<ElementInfo>&, Position pos,
                    bool self_or_call);
    void mod_list(CompletionList&, std::vector<ElementInfo>&, Position pos);
    /* =============  DATA MEMBERS  =================== */
    std::string _current_uri = "";
    std::string file_path = "file://";

    std::string key_import = "import";

    DBEvent dbevent;
}; /* -----  end of class LanguageFeatures  ----- */

/*
 * ================================
 *        Class:  IOStream
 *  Description:
 * ================================
 */
class IOStream {
public:
    /* =============  LIFECYCLE     =================== */
    IOStream() = default; /* constructor */
    IOStream& operator=(const IOStream&) = delete;
    virtual ~IOStream() = default;
    /* =============  ACCESSORS     =================== */
    virtual int read(char* buffer, std::size_t size, FILE*) = 0;
    virtual int write(const char* buffer, std::size_t size) = 0;
    virtual void HeaderPart() = 0;

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

}; /* -----  end of class IOStream  ----- */

/*
 * ================================
 *        Class:  StdIOStream
 *  Description:
 * ================================
 */
class StdIOStream : public IOStream {
public:
    /* =============  LIFECYCLE     =================== */
    StdIOStream() {}; /* constructor */

    /* =============  ACCESSORS     =================== */
    int read(char* buffer, std::size_t size, FILE* io_read);
    int write(const char* buffer, std::size_t size);
    /* =============  MUTATORS      =================== */
    void HeaderPart();
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    std::string content_type = "application/vscode-jsonrpc; charset=utf-8";
}; /* -----  end of class StdIOStream  ----- */

/*
 * ================================
 *        Class:  LSPTransport
 *  Description:
 * ================================
 */
class LSPTransport {
public:
    /* =============  LIFECYCLE     =================== */
    LSPTransport(IOStream& ios) : _stream(ios)
    {
        init_data();
    }; /* constructor */

    ~LSPTransport() {}
    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */
    void send_response();
    void handle_message();

    void initialize();
    void next();
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    void init_data();
    std::string trim(const std::string& str);
    int split(const std::string& str, const std::string& split_str,
              ContentChangesType&);
    RequestMessage read_message(FILE*);

    bool route(RequestMessage);

    void initialize_response(RequestMessage);
    void complete_response(RequestMessage);

    void diagnostics(TextDocumentItem&, RequestMessage);

    void location(DefinitionParams, int id);

    /* =============  DATA MEMBERS  =================== */

    e2::ParserCtx ctx;

    const char* response_fmt = "Content-Length: %d\r\n\r\n%s";

    std::string _file_p = "file://";

    IOStream& _stream;

    const std::string WHITESPACE = " \n\r\t\f\v";

    ContentChangesType _change_text;

    LspThreadPool _pool;

    DBEvent _dbevent;

}; /* -----  end of class LSPTransport  ----- */

}  // namespace e2
#endif /* ----- #ifndef LSPTransport_INC  ----- */
