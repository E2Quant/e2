/*
 * =====================================================================================
 *
 *       Filename:  ResponseStruct.hpp
 *
 *    Description:  ResponseStruct
 *
 *        Version:  1.0
 *        Created:  2026/07/27 14时19分21秒
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

#ifndef RESPONSESTRUCT_INC
#define RESPONSESTRUCT_INC
#include <string>
#include <vector>

#include "lsp-server/util.hpp"
namespace e2 {

enum TextDocumentSyncKind {
    /**
     * Documents should not be synced at all.
     */
    None = 0,

    /**
     * Documents are synced by always sending the full content
     * of the document.
     */
    Full = 1,

    /**
     * Documents are synced by sending the full content on open.
     * After that only incremental updates to the document are
     * sent.
     */
    Incremental = 2,
}; /* ----------  end of enum TextDocumentSyncKind  ---------- */

typedef enum TextDocumentSyncKind TextDocumentSyncKind;
struct TextDocumentSyncOptions {
    /**
     * Open and close notifications are sent to the server. If omitted open
     * close notifications should not be sent.
     */
    bool openClose = false;

    /**
     * Change notifications are sent to the server. See
     * TextDocumentSyncKind.None, TextDocumentSyncKind.Full and
     * TextDocumentSyncKind.Incremental. If omitted it defaults to
     * TextDocumentSyncKind.None.
     */
    TextDocumentSyncKind change;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextDocumentSyncOptions, change);
}; /* ----------  end of struct TextDocumentSyncOptions  ---------- */

typedef struct TextDocumentSyncOptions TextDocumentSyncOptions;

struct NotebookCellLanguage {
    std::string language;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(NotebookCellLanguage, language);

}; /* ----------  end of struct NotebookCellLanguage  ---------- */

typedef struct NotebookCellLanguage NotebookCellLanguage;

struct NotebookDocumentFilterWithNotebook {
    /**
     * The notebook to be synced. If a string
     * value is provided, it matches against the
     * notebook type. '*' matches every notebook.
     */
    std::string notebook;

    /**
     * The cells of the matching notebook to be synced.
     */
    std::vector<NotebookCellLanguage> cells;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(NotebookDocumentFilterWithNotebook, notebook,
                                   cells);

}; /* ----------  end of struct NotebookDocumentFilterWithNotebook  ----------
    */

typedef struct NotebookDocumentFilterWithNotebook
    NotebookDocumentFilterWithNotebook;
struct NotebookDocumentSyncOptions {
    /**
     * The notebooks to be synced
     *: ( | NotebookDocumentFilterWithCells)[]
     */
    NotebookDocumentFilterWithNotebook notebookSelector;

    /**
     * Whether save notifications should be forwarded to
     * the server. Will only be honored if mode === `notebook`.
     */
    bool save;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(NotebookDocumentSyncOptions,
                                   notebookSelector, save);

}; /* ----------  end of struct NotebookDocumentSyncOptions  ---------- */

typedef struct NotebookDocumentSyncOptions NotebookDocumentSyncOptions;

struct ServerCompletionItemOptions {
    /**
     * The server has support for completion item label
     * details (see also `CompletionItemLabelDetails`) when
     * receiving a completion item in a resolve call.
     *
     * @since 3.17.0
     */
    bool labelDetailsSupport;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ServerCompletionItemOptions,
                                   labelDetailsSupport);

}; /* ----------  end of struct ServerCompletionItemOptions  ---------- */

typedef struct ServerCompletionItemOptions ServerCompletionItemOptions;

struct CompletionOptions {
    /**
     * Most tools trigger completion request automatically without explicitly
     * requesting it using a keyboard shortcut (e.g., Ctrl+Space). Typically
     * they do so when the user starts to type an identifier. For example, if
     * the user types `c` in a JavaScript file, code complete will automatically
     * pop up and present `console` besides others as a completion item.
     * Characters that make up identifiers don't need to be listed here.
     *
     * If code complete should automatically be triggered on characters not
     * being valid inside an identifier (for example, `.` in JavaScript), list
     * them in `triggerCharacters`.
     */
    std::vector<std::string> triggerCharacters;

    /**
     * The list of all possible characters that commit a completion. This field
     * can be used if clients don't support individual commit characters per
     * completion item. See client capability
     * `completion.completionItem.commitCharactersSupport`.
     *
     * If a server provides both `allCommitCharacters` and commit characters on
     * an individual completion item, the ones on the completion item win.
     *
     * @since 3.2.0
     */
    std::vector<std::string> allCommitCharacters;

    /**
     * The server provides support to resolve additional
     * information for a completion item.
     */
    bool resolveProvider = true;

    /**
     * The server supports the following `CompletionItem` specific
     * capabilities.
     *
     * @since 3.17.0
     */
    ServerCompletionItemOptions completionItem;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CompletionOptions, triggerCharacters,
                                   allCommitCharacters, resolveProvider,
                                   completionItem);
}; /* ----------  end of struct CompletionOptions  ---------- */

typedef struct CompletionOptions CompletionOptions;

struct WorkDoneProgressOptions {
    bool workDoneProgress = true;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(WorkDoneProgressOptions, workDoneProgress);
}; /* ----------  end of struct WorkDoneProgressOptions  ---------- */

typedef struct WorkDoneProgressOptions WorkDoneProgressOptions;

struct SignatureHelpOptions : public WorkDoneProgressOptions {
    /**
     * The characters that trigger signature help
     * automatically.
     */
    std::vector<std::string> triggerCharacters;

    /**
     * List of characters that re-trigger signature help.
     *
     * These trigger characters are only active when signature help is already
     * showing. All trigger characters are also counted as re-trigger
     * characters.
     *
     * @since 3.15.0
     */
    std::vector<std::string> retriggerCharacters;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SignatureHelpOptions, triggerCharacters,
                                   retriggerCharacters);
}; /* ----------  end of struct SignatureHelpOptions  ---------- */

struct CodeLensOptions : public WorkDoneProgressOptions {
    /**
     * Code lens has a resolve provider as well.
     */
    bool resolveProvider = false;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CodeLensOptions, resolveProvider);
}; /* ----------  end of struct CodeLensOptions  ---------- */

typedef struct CodeLensOptions CodeLensOptions;

struct ExecuteCommandOptions : public WorkDoneProgressOptions {
    /**
     * The commands to be executed on the server.
     */
    std::vector<std::string> commands;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ExecuteCommandOptions, commands);
}; /* ----------  end of struct ExecuteCommandOptions  ---------- */

typedef struct ExecuteCommandOptions ExecuteCommandOptions;

struct SemanticTokensLegend {
    /**
     * The token types a server uses.
     */
    std::vector<std::string> tokenTypes;

    /**
     * The token modifiers a server uses.
     */
    std::vector<std::string> tokenModifiers;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SemanticTokensLegend, tokenTypes,
                                   tokenModifiers);

}; /* ----------  end of struct SemanticTokensLegend  ---------- */

typedef struct SemanticTokensLegend SemanticTokensLegend;

struct SemanticTokensOptions : public WorkDoneProgressOptions {
    /**
     * The legend used by the server.
     */
    SemanticTokensLegend legend;

    /**
     * Server supports providing semantic tokens for a specific range
     * of a document.
     */
    bool range;

    /**
     * Server supports providing semantic tokens for a full document.
     */
    bool full;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SemanticTokensOptions, legend, range, full);

}; /* ----------  end of struct SemanticTokensOptions  ---------- */

typedef struct SemanticTokensOptions SemanticTokensOptions;

struct TextDocumentContentOptions {
    /**
     * The schemes for which the server provides content.
     */
    std::vector<std::string> schemes;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextDocumentContentOptions, schemes);
}; /* ----------  end of struct TextDocumentContentOptions  ---------- */

typedef struct TextDocumentContentOptions TextDocumentContentOptions;

struct WorkspaceFoldersServerCapabilities {
    /**
     * The server has support for workspace folders.
     */
    bool supported = true;

    /**
     * Whether the server wants to receive workspace folder
     * change notifications.
     *
     * If a string is provided, the string is treated as an ID
     * under which the notification is registered on the client
     * side. The ID can be used to unregister for these events
     * using the `client/unregisterCapability` request.
     */
    bool changeNotifications = true;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(WorkspaceFoldersServerCapabilities,
                                   supported, changeNotifications);
}; /* ----------  end of struct WorkspaceFoldersServerCapabilities  ----------
    */

typedef struct WorkspaceFoldersServerCapabilities
    WorkspaceFoldersServerCapabilities;

struct WorkspaceOptions {
    /**
     * The server supports workspace folder.
     *
     * @since 3.6.0
     */
    WorkspaceFoldersServerCapabilities workspaceFolders;

    /**
     * The server is interested in notifications/requests for operations on
     * files.
     *
     * @since 3.16.0
     */
    //    FileOperationOptions fileOperations;

    /**
     * The server supports the `workspace/textDocumentContent` request.
     *| TextDocumentContentRegistrationOptions
     * @since 3.18.0
     */
    TextDocumentContentOptions textDocumentContent;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(WorkspaceOptions, workspaceFolders,
                                   textDocumentContent);

}; /* ----------  end of struct WorkspaceOptions  ---------- */

typedef struct WorkspaceOptions WorkspaceOptions;

struct ServerCapabilities {
    /**
     * The position encoding the server picked from the encodings offered
     * by the client via the client capability `general.positionEncodings`.
     *
     * If the client didn't provide any position encodings the only valid
     * value that a server can return is 'utf-16'.
     *
     * If omitted it defaults to 'utf-16'.
     *
     * @since 3.17.0
     */
    // PositionEncodingKind positionEncoding;

    /**
     * Defines how text documents are synced. Is either a detailed structure
     * defining each notification or for backwards compatibility the
     * TextDocumentSyncKind number. If omitted it defaults to
     * `TextDocumentSyncKind.None`.
     *| TextDocumentSyncKind
     *    TextDocumentSyncOptions
     */

    TextDocumentSyncKind textDocumentSync;

    /**
     * Defines how notebook documents are synced.
     *|
               NotebookDocumentSyncRegistrationOptions
     * @since 3.17.0
     */
    NotebookDocumentSyncOptions notebookDocumentSync;

    /**
     * The server provides completion support.
     */
    CompletionOptions completionProvider;

    /**
     * The server provides hover support.
     *| HoverOptions
     */
    bool hoverProvider = true;

    /**
     * The server provides signature help support.
     */
    SignatureHelpOptions signatureHelpProvider;

    /**
     * The server provides go to declaration support.
     *| DeclarationOptions | DeclarationRegistrationOptions
     * @since 3.14.0
     */
    bool declarationProvider;

    /**
     * The server provides goto definition support.
     *| DefinitionOptions
     */
    bool definitionProvider = true;

    /**
     * The server provides goto type definition support.
     *| TypeDefinitionOptions |TypeDefinitionRegistrationOptions
     * @since 3.6.0
     */
    bool typeDefinitionProvider;

    /**
     * The server provides goto implementation support.
     *| ImplementationOptions | ImplementationRegistrationOptions
     * @since 3.6.0
     */
    bool implementationProvider;

    /**
     * The server provides find references support.
     *| ReferenceOptions
     */
    bool referencesProvider = true;

    /**
     * The server provides document highlight support.
     *| DocumentHighlightOptions
     */
    bool documentHighlightProvider = true;

    /**
     * The server provides document symbol support.
     *| DocumentSymbolOptions
     */
    bool documentSymbolProvider = true;

    /**
     * The server provides code actions. The `CodeActionOptions` return type is
     * only valid if the client signals code action literal support via the
     * property `textDocument.codeAction.codeActionLiteralSupport`.
     *| CodeActionOptions
     */
    bool codeActionProvider = true;

    /**
     * The server provides code lens.
     */
    CodeLensOptions codeLensProvider;

    /**
     * The server provides document link support.
     */
    //    DocumentLinkOptions documentLinkProvider;

    /**
     * The server provides color provider support.
     *| DocumentColorOptions | DocumentColorRegistrationOptions
     * @since 3.6.0
     */
    bool colorProvider;

    /**
     * The server provides document formatting.
     *| DocumentFormattingOptions
     */
    bool documentFormattingProvider = true;

    /**
     * The server provides document range formatting.
     *| DocumentRangeFormattingOptions
     */
    bool documentRangeFormattingProvider = true;

    /**
     * The server provides document formatting on typing.
     */
    //    DocumentOnTypeFormattingOptions documentOnTypeFormattingProvider;

    /**
     * The server provides rename support. RenameOptions may only be
     * specified if the client states that it supports
     * `prepareSupport` in its initial `initialize` request.
     *| RenameOptions
     */
    bool renameProvider = true;

    /**
     * The server provides folding provider support.
     *| FoldingRangeOptions | FoldingRangeRegistrationOptions
     * @since 3.10.0
     */
    bool foldingRangeProvider = true;

    /**
     * The server provides execute command support.
     */
    ExecuteCommandOptions executeCommandProvider;

    /**
     * The server provides selection range support.
     *| SelectionRangeOptions | SelectionRangeRegistrationOptions
     * @since 3.15.0
     */
    bool selectionRangeProvider;

    /**
     * The server provides linked editing range support.
     *| LinkedEditingRangeOptions |
     *          LinkedEditingRangeRegistrationOptions
     * @since 3.16.0
     */
    bool linkedEditingRangeProvider;

    /**
     * The server provides call hierarchy support.
     *| CallHierarchyOptions | CallHierarchyRegistrationOptions
     * @since 3.16.0
     */
    bool callHierarchyProvider = false;

    /**
     * The server provides semantic tokens support.
     *| SemanticTokensRegistrationOptions
     * @since 3.16.0
     */
    SemanticTokensOptions semanticTokensProvider;

    /**
     * Whether server provides moniker support.
     *| MonikerOptions | MonikerRegistrationOptions
     * @since 3.16.0
     */
    bool monikerProvider;

    /**
     * The server provides type hierarchy support.
     *| TypeHierarchyOptions | TypeHierarchyRegistrationOptions
     * @since 3.17.0
     */
    bool typeHierarchyProvider;

    /**
     * The server provides inline values.
     *| InlineValueOptions | InlineValueRegistrationOptions
     * @since 3.17.0
     */
    bool inlineValueProvider;

    /**
     * The server provides inlay hints.
     *| InlayHintOptions | InlayHintRegistrationOptions
     * @since 3.17.0
     */
    bool inlayHintProvider;

    /**
     * The server has support for pull model diagnostics.
     *
     * @since 3.17.0
     *| DiagnosticRegistrationOptions
     */
    //    DiagnosticOptions diagnosticProvider;

    /**
     * The server provides workspace symbol support.
     *| WorkspaceSymbolOptions
     */
    bool workspaceSymbolProvider;

    /**
     * The server provides inline completions.
     *| InlineCompletionOptions
     *  先不用这个功能这么快
     * @since 3.18.0
     */
    // bool inlineCompletionProvider = false;

    /**
     * Workspace specific server capabilities
     */
    WorkspaceOptions workspace;

    /**
     * Experimental server capabilities.
     */
    LSPAnyObject experimental;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        ServerCapabilities, textDocumentSync, notebookDocumentSync,
        completionProvider, hoverProvider, signatureHelpProvider,
        declarationProvider, definitionProvider, typeDefinitionProvider,
        implementationProvider, referencesProvider, documentHighlightProvider,
        documentSymbolProvider, codeActionProvider, codeLensProvider,
        colorProvider, documentFormattingProvider,
        documentRangeFormattingProvider, renameProvider, foldingRangeProvider,
        executeCommandProvider, selectionRangeProvider,
        linkedEditingRangeProvider, callHierarchyProvider, monikerProvider,
        typeHierarchyProvider, inlineValueProvider, inlayHintProvider,
        workspaceSymbolProvider, workspace);
}; /* ----------  end of struct ServerCapabilities  ---------- */

typedef struct ServerCapabilities ServerCapabilities;

struct InitializeResult {
    /**
     * The capabilities the language server provides.
     */
    ServerCapabilities capabilities;
    /**
     * Information about the server.
     *capabilities,
     * @since 3.15.0
     */
    ServerInfo serverInfo;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(InitializeResult, capabilities, serverInfo);
}; /* ----------  end of struct InitializeResult  ---------- */
}  // namespace e2
#endif /* ----- #ifndef RESPONSESTRUCT_INC  ----- */
