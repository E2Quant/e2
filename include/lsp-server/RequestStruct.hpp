/*
 * =====================================================================================
 *
 *       Filename:  RequestStruct.hpp
 *
 *    Description:  RequestStruct
 *
 *        Version:  1.0
 *        Created:  2026/07/27 14时28分14秒
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

#ifndef REQUESTSTRUCT_INC
#define REQUESTSTRUCT_INC

#include "lsp-server/util.hpp"

namespace e2 {

struct __NotificationMessage {
    std::string method;
    e2_json params;  // 参数
}; /* ----------  end of struct __NotificationMessage  ---------- */

typedef struct __NotificationMessage NotificationMessage;

template <ProgressToken T>
struct ProgressParams {
    /**
     * The progress token provided by the client or server.
     */
    T token;
    /**
     * The progress data.
     */
    T value;
}; /* ----------  end of struct ProgressParams  ---------- */

template <ProgressToken T>
struct WorkDoneProgressParams {
    /**
     * An optional token that a server can use to report work done progress.
     */
    T workDoneToken;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(WorkDoneProgressParams, workDoneToken);
}; /* ----------  end of struct WorkDoneProgressParams  ---------- */

struct __ClientInfo {
    /**
     * The name of the client as defined by the client.
     */
    std::string name;
    /**
     * The client's version as defined by the client.
     */
    std::string version;
}; /* ----------  end of struct __ClientInfo  ---------- */

typedef struct __ClientInfo ClientInfo;

enum ResourceOperationKind {
    Create,
    Rename,
    Delete
}; /* ----------  end of enum ResourceOperationKind  ---------- */

enum FailureHandlingKind {
    Abort,
    Transactional,
    Undo,
    TextOnlyTransactional
}; /* ----------  end of enum FailureHandlingKind  ---------- */

struct ChangeAnnotationsSupportOptions {
    /**
     * Whether the client groups edits with equal labels into tree nodes,
     * for instance all edits labelled with "Changes in Strings" would
     * be a tree node.
     */
    bool groupsOnLabel;
}; /* ----------  end of struct ChangeAnnotationsSupportOptions  ---------- */

typedef struct ChangeAnnotationsSupportOptions ChangeAnnotationsSupportOptions;

struct WorkspaceEditClientCapabilities {
    /**
     * The client supports versioned document changes in `WorkspaceEdit`s.
     */
    bool documentChanges;
    /**
     * The resource operations the client supports. Clients should at least
     * support 'create', 'rename', and 'delete' for files and folders.
     *
     * @since 3.13.0
     */

    ResourceOperationKind resourceOperations;
    /**
     * The failure handling strategy of a client if applying the workspace edit
     * fails.
     *
     * @since 3.13.0
     */
    FailureHandlingKind failureHandling;
    /**
     * Whether the client normalizes line endings to the client specific
     * setting.
     * If set to `true`, the client will normalize line ending characters
     * in a workspace edit to the client specific new line character(s).
     *
     * @since 3.16.0
     */

    bool normalizesLineEndings;
    /**
     * Whether the client in general supports change annotations on text edits,
     * create file, rename file, and delete file changes.
     *
     * @since 3.16.0
     */
    ChangeAnnotationsSupportOptions changeAnnotationSupport;

    /**
     * Whether the client supports `WorkspaceEditMetadata` in `WorkspaceEdit`s.
     *
     * @since 3.18.0
     */

    bool metadataSupport;
    /**
     * Whether the client supports snippets as text edits.
     *
     * @since 3.18.0
     */
    bool snippetEditSupport;

}; /* ----------  end of struct WorkspaceEditClientCapabilities  ---------- */

struct TextDocumentSyncClientCapabilities {
    /**
     * Whether text document synchronization supports dynamic registration.
     */

    bool dynamicRegistration;

    /**
     * The client supports sending will save notifications.
     */
    bool willSave;
    /**
     * The client supports sending a will save request and
     * waits for a response providing text edits which will
     * be applied to the document before it is saved.
     */
    bool willSaveWaitUntil;
    /**
     * The client supports did save notifications.
     */
    bool didSave;
}; /* ----------  end of struct TextDocumentSyncClientCapabilities  ----------
    */

struct TextDocumentFilterClientCapabilities {
    /**
     * The client supports Relative Patterns.
     *
     * @since 3.18.0
     */
    bool relativePatternSupport;
}; /* ----------  end of struct TextDocumentFilterClientCapabilities  ----------
    */

enum MarkupKind {
    PlainText,
    Markdown
}; /* ----------  end of enum MarkupKind  ---------- */

struct CompletionItemTagOptions {
    /**
     * The properties that a client can resolve lazily.
     */
    CompletionItemTag valueSet;

}; /* ----------  end of struct CompletionItemTagOptions  ---------- */

struct ClientCompletionItemResolveOptions {
    std::string properties;
}; /* ----------  end of struct ClientCompletionItemResolveOptions  ----------
    */

struct ClientCompletionItemInsertTextModeOptions {
    InsertTextMode valueSet;
}; /* ----------  end of struct ClientCompletionItemInsertTextModeOptions
      ---------- */

struct ClientCompletionItemOptionsKind {
    /**
     * The completion item kind values the client supports. When this
     * property exists the client also guarantees that it will
     * handle values outside its set gracefully and falls back
     * to a default value when unknown.
     *
     * If this property is not present the client only supports
     * the completion items kinds from `Text` to `Reference` as defined in
     * the initial version of the protocol.
     */
    CompletionItemKind valueSet;
}; /* ----------  end of struct ClientCompletionItemOptionsKind  ---------- */

struct ClientCompletionItemOptions {
    /**
     * Client supports snippets as insert text.
     *
     * A snippet can define tab stops and placeholders with `$1`, `$2`
     * and `${3:foo}`. `$0` defines the final tab stop, it defaults to
     * the end of the snippet. Placeholders with equal identifiers are linked,
     * that is typing in one will update others too.
     */
    bool snippetSupport;

    /**
     * Client supports commit characters on a completion item.
     */
    bool commitCharactersSupport;

    /**
     * Client supports the following content formats for the documentation
     * property. The order describes the preferred format of the client.
     */
    MarkupKind documentationFormat;

    /**
     * Client supports the deprecated property on a completion item.
     */
    bool deprecatedSupport;

    /**
     * Client supports the preselect property on a completion item.
     */
    bool preselectSupport;

    /**
     * Client supports the tag property on a completion item. Clients supporting
     * tags have to handle unknown tags gracefully. Clients especially need to
     * preserve unknown tags when sending a completion item back to the server
     * in a resolve call.
     *
     * @since 3.15.0
     */
    CompletionItemTagOptions tagSupport;

    /**
     * Client support insert replace edit to control different behavior if a
     * completion item is inserted in the text or should replace text.
     *
     * @since 3.16.0
     */
    bool insertReplaceSupport;

    /**
     * Indicates which properties a client can resolve lazily on a completion
     * item. Before version 3.16.0 only the predefined properties
     * `documentation` and `details` could be resolved lazily.
     *
     * @since 3.16.0
     */
    ClientCompletionItemResolveOptions resolveSupport;

    /**
     * The client supports the `insertTextMode` property on
     * a completion item to override the whitespace handling mode
     * as defined by the client (see `insertTextMode`).
     *
     * @since 3.16.0
     */
    ClientCompletionItemInsertTextModeOptions insertTextModeSupport;

    /**
     * The client has support for completion item label
     * details (see also `CompletionItemLabelDetails`).
     *
     * @since 3.17.0
     */
    bool labelDetailsSupport;
}; /* ----------  end of struct ClientCompletionItemOptions  ---------- */

struct CompletionListCapabilities {
    /**
     * The client supports the following itemDefaults on
     * a completion list.
     *
     * The value lists the supported property names of the
     * `CompletionList.itemDefaults` object. If omitted
     * no properties are supported.
     *
     * @since 3.17.0
     */
    std::string itemDefaults;

    /**
     * Specifies whether the client supports `CompletionList.applyKind` to
     * indicate how supported values from `completionList.itemDefaults`
     * and `completion` will be combined.
     *
     * If a client supports `applyKind` it must support it for all fields
     * that it supports that are listed in `CompletionList.applyKind`. This
     * means when clients add support for new/future fields in completion
     * items the MUST also support merge for them if those fields are
     * defined in `CompletionList.applyKind`.
     *
     * @since 3.18.0
     */
    bool applyKindSupport;
}; /* ----------  end of struct CompletionListCapabilities  ---------- */

struct CompletionClientCapabilities {
    /**
     * Whether completion supports dynamic registration.
     */
    bool dynamicRegistration;

    /**
     * The client supports the following `CompletionItem` specific
     * capabilities.
     */
    ClientCompletionItemOptions completionItem;

    /**
     * The client supports the following completion item kinds.
     */
    ClientCompletionItemOptionsKind completionItemKind;

    /**
     * The client supports sending additional context information for a
     * `textDocument/completion` request.
     */
    bool contextSupport;

    /**
     * The client's default when the completion item doesn't provide an
     * `insertTextMode` property.
     *
     * @since 3.17.0
     */
    InsertTextMode insertTextMode;

    /**
     * The client supports the following `CompletionList` specific
     * capabilities.
     *
     * @since 3.17.0
     */
    CompletionListCapabilities completionList;
}; /* ----------  end of struct CompletionClientCapabilities  ---------- */

typedef struct CompletionClientCapabilities CompletionClientCapabilities;

struct TextDocumentClientCapabilities {
    /**
     * Defines which synchronization capabilities the client supports.
     */
    TextDocumentSyncClientCapabilities synchronization;

    /**
     * Defines which filters the client supports.
     *
     * @since 3.18.0
     */
    TextDocumentFilterClientCapabilities filters;

    /**
     * Capabilities specific to the `textDocument/completion` request.
     */

    CompletionClientCapabilities completion;

}; /* ----------  end of struct TextDocumentClientCapabilities  ---------- */

struct WorkspaceClientCapabilities {
    /**
     * The client supports applying batch edits
     * to the workspace by supporting the request
     * 'workspace/applyEdit'
     */
    bool applyEdit;
    /**
     * Capabilities specific to `WorkspaceEdit`s
     */
    WorkspaceEditClientCapabilities workspaceEdit;

}; /* ----------  end of struct WorkspaceClientCapabilities  ---------- */

struct ClientCapabilities {
    /**
     * Workspace specific client capabilities.
     */

    WorkspaceClientCapabilities workspace;

}; /* ----------  end of struct ClientCapabilities  ---------- */

enum TraceValue {
    off,
    messages,
    verbose
}; /* ----------  end of enum TraceValue  ---------- */

struct WorkspaceFolder {
    /**
     * The associated URI for this workspace folder.
     */
    URI uri;

    /**
     * The name of the workspace folder. Used to refer to this
     * workspace folder in the user interface.
     */
    std::string name;
}; /* ----------  end of struct WorkspaceFolder  ---------- */

typedef struct WorkspaceFolder WorkspaceFolder;

template <ProgressToken T>
struct InitializeParams : public WorkDoneProgressParams<T> {
    /**
     * The process Id of the parent process that started the server. Is null if
     * the process has not been started by another process. If the parent
     * process is not alive then the server should exit (see exit notification)
     * its process.
     */
    int processId;
    /**
     * Information about the client
     *
     * @since 3.15.0
     */

    ClientInfo clientinfo;

    /**
     * The locale the client is currently showing the user interface
     * in. This must not necessarily be the locale of the operating
     * system.
     *
     * Uses IETF language tags as the value's syntax
     * (See https://en.wikipedia.org/wiki/IETF_language_tag)
     *
     * @since 3.16.0
     */
    std::string locale;

    /**
     * The rootPath of the workspace. Is null
     * if no folder is open.
     *
     * @deprecated in favour of `rootUri`.
     */
    std::string rootPath;

    /**
     * The rootUri of the workspace. Is null if no
     * folder is open. If both `rootPath` and `rootUri` are set
     * `rootUri` wins.
     *initializationOptions
     * @deprecated in favour of `workspaceFolders`
     */
    DocumentUri rootUri;

    /**
     * User provided initialization options.
     */

    LSPAnyObject initializationOptions;

    /**
     * The capabilities provided by the client (editor or tool)
     */
    ClientCapabilities capabilities;

    /**
     * The initial trace setting. If omitted trace is disabled ('off').
     */
    TraceValue trace;

    /**
     * The workspace folders configured in the client when the server starts.
     * This property is only available if the client supports workspace folders.
     * It can be `null` if the client supports workspace folders but none are
     * configured.
     *
     * @since 3.6.0
     */

    WorkspaceFolder workspaceFolders;
}; /* ----------  end of struct InitializeParams  ---------- */

struct Registration {
    /**
     * The id used to register the request. The id can be used to deregister
     * the request again.
     */
    std::string id;

    /**
     * The method / capability to register for.
     */
    std::string method;

    /**
     * Options necessary for the registration.
     */
    LSPAnyObject registerOptions;
}; /* ----------  end of struct Registration  ---------- */

struct RegistrationParams {
    Registration registrations;
}; /* ----------  end of struct RegistrationParams  ---------- */

typedef struct RegistrationParams RegistrationParams;

struct Unregistration {
    /**
     * The id used to unregister the request or notification. Usually an id
     * provided during the register request.
     */
    std::string id;

    /**
     * The method / capability to unregister for.
     */
    std::string method;

}; /* ----------  end of struct Unregistration  ---------- */

typedef struct Unregistration Unregistration;

struct UnregistrationParams {
    // This should correctly be named `unregistrations`. However, changing this
    // is a breaking change and needs to wait until we deliver a 4.x version
    // of the specification.
    Unregistration unregisterations;
}; /* ----------  end of struct UnregistrationParams  ---------- */

typedef struct UnregistrationParams UnregistrationParams;

struct SetTraceParams {
    /**
     * The new value that should be assigned to the trace setting.
     */
    TraceValue value;
}; /* ----------  end of struct SetTraceParams  ---------- */

typedef struct SetTraceParams SetTraceParams;

struct LogTraceParams {
    /**
     * The message to be logged.
     */
    std::string message;
    /**
     * Additional information that can be computed if the `trace` configuration
     * is set to `'verbose'`.
     */
    std::string verbose;
}; /* ----------  end of struct LogTraceParams  ---------- */

typedef struct LogTraceParams LogTraceParams;

struct DidOpenTextDocumentParams {
    /**
     * The document that was opened.
     */
    TextDocumentItem textDocument;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DidOpenTextDocumentParams, textDocument);
}; /* ----------  end of struct DidOpenTextDocumentParams  ---------- */

typedef struct DidOpenTextDocumentParams DidOpenTextDocumentParams;
}  // namespace e2
#endif /* ----- #ifndef REQUESTSTRUCT_INC  ----- */
