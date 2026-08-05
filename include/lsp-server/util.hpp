/*
 * =====================================================================================
 *
 *       Filename:  util.hpp
 *
 *    Description:  util
 *
 *        Version:  1.0
 *        Created:  2026/07/27 14时25分16秒
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

#ifndef UTIL_INC
#define UTIL_INC
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <string>

#include "nlohmann/json.hpp"
using e2_json = nlohmann::json;
namespace e2 {
#define CERR(data)                                                   \
    ({                                                               \
        do {                                                         \
            std::cerr << " e2lsp log:[" << data << "]" << std::endl; \
        } while (0);                                                 \
    })

#define rnrn [ '\n', '\r\n', '\r' ]
#define DocumentUri std::string
#define URI std::string
template <typename T>
concept ProgressToken = std::same_as<T, int> || std::same_as<T, std::string>;

/**
 * The LSP any type.
 *
 * @since 3.17.0
 *LSPObject | LSPArray | string | integer | uinteger |
        decimal | boolean | null;
 */
template <typename T>
concept LSPAny = std::same_as<T, int> || std::same_as<T, std::string> ||
                 std::same_as<T, std::uint32_t> || std::same_as<T, bool> ||
                 std::same_as<T, e2_json>;

using LSPAnyObject = e2_json;

/*
 * ================================
 *        Class:  EJson
 *  Description:
 * ================================
 */

class EJson {
public:
    /* =============  LIFECYCLE     =================== */
    EJson() {}; /* constructor */

    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */
    template <LSPAny T>
    e2_json toDict(std::string key, T t)
    {
        e2_json ret = {{key, t}};
        return ret;
    };
    template <LSPAny T>
    e2_json toDict(std::map<std::string, T> m)
    {
        e2_json ret(m);
        return ret;
    }
    template <LSPAny T>
    e2_json toList(std::vector<T> v)
    {
        e2_json ret = e2_json::parse(v.begin(), v.end());

        return ret;
    };

    void merge(e2_json& src, e2_json& ext) { src.merge_patch(ext); }

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

}; /* -----  end of class EJson  ----- */

struct ServerInfo {
    /**
     * The name of the server as defined by the server.
     */
    std::string name = "e2lsp";

    /**
     * The server's version as defined by the server.
     */
    std::string version = "1.2.3";

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ServerInfo, name, version);

}; /* ----------  end of struct ServerInfo  ---------- */

struct __ErrorCode {
    // Defined by JSON-RPC
    const int ParseError = -32700;
    const int InvalidRequest = -32600;
    const int MethodNotFound = -32601;
    const int InvalidParams = -32602;
    const int InternalError = -32603;

    /**
     * This is the start range of JSON-RPC reserved error codes.
     * It doesn't denote a real error code. No LSP error codes should
     * be defined between the start and end range. For backwards
     * compatibility the `ServerNotInitialized` and the `UnknownErrorCode`
     * are left in the range.
     *
     * @since 3.16.0
     */
    const int jsonrpcReservedErrorRangeStart = -32099;
    /** @deprecated use jsonrpcReservedErrorRangeStart */
    const int serverErrorStart = jsonrpcReservedErrorRangeStart;

    /**
     * Error code indicating that a server received a notification or
     * request before the server received the `initialize` request.
     */
    const int ServerNotInitialized = -32002;
    const int UnknownErrorCode = -32001;

    /**
     * This is the end range of JSON-RPC reserved error codes.
     * It doesn't denote a real error code.
     *
     * @since 3.16.0
     */
    const int jsonrpcReservedErrorRangeEnd = -32000;
    /** @deprecated use jsonrpcReservedErrorRangeEnd */
    const int serverErrorEnd = jsonrpcReservedErrorRangeEnd;

    /**
     * This is the start range of LSP reserved error codes.
     * It doesn't denote a real error code.
     *
     * @since 3.16.0
     */
    const int lspReservedErrorRangeStart = -32899;

    /**
     * A request failed but it was syntactically correct, e.g the
     * method name was known and the parameters were valid. The error
     * message should contain human readable information about why
     * the request failed.
     *
     * @since 3.17.0
     */
    const int RequestFailed = -32803;

    /**
     * The server cancelled the request. This error code should
     * only be used for requests that explicitly support being
     * server cancellable.
     *
     * @since 3.17.0
     */
    const int ServerCancelled = -32802;

    /**
     * The server detected that the content of a document got
     * modified outside normal conditions. A server should
     * NOT send this error code if it detects a content change
     * in its unprocessed messages. The result even computed
     * on an older state might still be useful for the client.
     *
     * If a client decides that a result is not of any use anymore
     * the client should cancel the request.
     */
    const int ContentModified = -32801;

    /**
     * The client has canceled a request and a server has detected
     * the cancel.
     */
    const int RequestCancelled = -32800;

    /**
     * This is the end range of LSP reserved error codes.
     * It doesn't denote a real error code.
     *
     * @since 3.16.0
     */
    const int lspReservedErrorRangeEnd = -32800;
}; /* ----------  end of struct __ErrorCode  ---------- */

typedef struct __ErrorCode ErrorCode;

struct __ResponseError {
    ErrorCode code;
    std::string message;

}; /* ----------  end of struct __ResponseError  ---------- */

typedef struct __ResponseError ResponseError;

struct Position {
    /**
     * Line position in a document (zero-based).
     */
    std::uint32_t line;

    /**
     * Character offset on a line in a document (zero-based). The meaning of
     * this offset is determined by the negotiated `PositionEncodingKind`.
     *
     * If the character value is greater than the line length it defaults back
     * to the line length.
     */
    std::uint32_t character;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Position, line, character);
}; /* ----------  end of struct Position  ---------- */

typedef struct Position Position;
struct Range {
    /**
     * The range's start position.
     */
    Position start;

    /**
     * The range's end position.
     */
    Position end;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Range, start, end);
}; /* ----------  end of struct Range  ---------- */

typedef struct Range Range;

struct Command {
    /**
     * Title of the command, like `save`.
     */
    std::string title;

    /**
     * An optional tooltip.
     *
     * @since 3.18.0
     */
    std::string tooltip;

    /**
     * The identifier of the actual command handler.
     */
    std::string command;

    /**
     * Arguments that the command handler should be
     * invoked with.
     */
    std::vector<std::string> arguments;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Command, title, tooltip, command, arguments);
}; /* ----------  end of struct Command  ---------- */

typedef struct Command Command;

struct TextDocumentItem {
    /**
     * The text document's URI.
     */
    DocumentUri uri;

    /**
     * The text document's language identifier.
     */
    std::string languageId;

    /**
     * The version number of this document (it will increase after each
     * change, including undo/redo).
     */
    int version;

    /**
     * The content of the opened text document.
     */
    std::string text;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextDocumentItem, uri, languageId, version,
                                   text);
}; /* ----------  end of struct TextDocumentItem  ---------- */

typedef struct TextDocumentItem TextDocumentItem;

enum CompletionItemTag {
    /**
     * Render a completion as obsolete, usually using a strike-out.
     */
    Deprecated = 1,
}; /* ----------  end of enum CompletionItemTag  ---------- */

typedef enum CompletionItemTag CompletionItemTag;

enum CompletionItemKind {
    Text = 1,
    Method = 2,
    Function = 3,
    Constructor = 4,
    Field = 5,
    Variable = 6,
    Class = 7,
    Interface = 8,
    Module = 9,
    Property = 10,
    Unit = 11,
    Value = 12,
    Enum = 13,
    Keyword = 14,
    snippet = 15,
    Color = 16,
    File = 17,
    Reference = 18,
    Folder = 19,
    EnumMember = 20,
    Constant = 21,
    Struct = 22,
    Event = 23,
    Operator = 24,
    TypeParameter = 25,
}; /* ----------  end of enum CompletionItemKind  ---------- */

typedef enum CompletionItemKind CompletionItemKind;
enum InsertTextFormat {
    /**
     * The primary text to be inserted is treated as a plain string.
     */
    plainText = 1,

    /**
     * The primary text to be inserted is treated as a snippet.
     *
     * A snippet can define tab stops and placeholders with `$1`, `$2`
     * and `${3:foo}`. `$0` defines the final tab stop, it defaults to
     * the end of the snippet. Placeholders with equal identifiers are linked,
     * that is, typing in one will update others too.
     */
    Snippet = 2,
}; /* ----------  end of enum InsertTextFormat  ---------- */

typedef enum InsertTextFormat InsertTextFormat;

enum InsertTextMode {
    /**
     * The insertion or replace strings are taken as-is. If the
     * value is multiline, the lines below the cursor will be
     * inserted using the indentation defined in the string value.
     * The client will not apply any kind of adjustments to the
     * string.
     */
    asIs = 1,

    /**
     * The editor adjusts leading whitespace of new lines so that
     * they match the indentation up to the cursor of the line for
     * which the item is accepted.
     *
     * Consider a line like this: <2tabs><cursor><3tabs>foo. Accepting a
     * multi line completion item is indented using 2 tabs and all
     * following lines inserted will be indented using 2 tabs as well.
     */
    adjustIndentation = 2,
}; /* ----------  end of enum InsertTextMode  ---------- */

typedef enum InsertTextMode InsertTextMode;

struct LSPMessage {
    std::string jsonrpc;
};

struct __MessageBody {
    int id;  // 请求 ID（可选）

    std::string jsonrpc;  // 固定为 "2.0"
}; /* ----------  end of struct __MessageBody  ---------- */

typedef struct __MessageBody MessageBody;

struct __RequestMessage : public MessageBody {
    std::string method;  // 方法名
    e2_json params;      // 参数
}; /* ----------  end of struct __RequestMessage  ---------- */

typedef struct __RequestMessage RequestMessage;

struct __ResponseMessage {
    e2_json result;
    ResponseError responseError;
}; /* ----------  end of struct __ResponseMessage  ---------- */

typedef struct __ResponseMessage ResponseMessage;

}  // namespace e2
#endif /* ----- #ifndef UTIL_INC  ----- */
