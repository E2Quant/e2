/*
 * =====================================================================================
 *
 *       Filename:  inlineCompletion.hpp
 *
 *    Description:  inlineCompletion
 *
 *        Version:  1.0
 *        Created:  2026/07/27 17时39分55秒
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

#ifndef INLINECOMPLETION_INC
#define INLINECOMPLETION_INC
#include <cstdint>
#include <string>
#include <vector>

#include "lsp-server/RequestStruct.hpp"
#include "lsp-server/util.hpp"
namespace e2 {

struct TextDocumentIdentifier {
    /**
     * The text document's URI.
     */
    DocumentUri uri;
}; /* ----------  end of struct TextDocumentIdentifier  ---------- */

typedef struct TextDocumentIdentifier TextDocumentIdentifier;

struct TextDocumentPositionParams {
    /**
     * The text document.
     */
    TextDocumentIdentifier textDocument;

    /**
     * The position inside the text document.
     */
    Position position;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextDocumentPositionParams, textDocument,
                                   position);
}; /* ----------  end of struct TextDocumentPositionParams  ---------- */

typedef struct TextDocumentPositionParams TextDocumentPositionParams;

enum InlineCompletionTriggerKind {
    /**
     * Completion was triggered explicitly by a user gesture.
     * Return multiple completion items to enable cycling through them.
     */
    Invoked = 1,

    /**
     * Completion was triggered automatically while editing.
     * It is sufficient to return a single completion item in this case.
     */
    Automatic = 2,
}; /* ----------  end of enum InlineCompletionTriggerKind  ---------- */

typedef enum InlineCompletionTriggerKind InlineCompletionTriggerKind;

struct SelectedCompletionInfo {
    /**
     * The range that will be replaced if this completion item is accepted.
     */
    Range range;

    /**
     * The text the range will be replaced with if this completion is
     * accepted.
     */
    std::string text;
}; /* ----------  end of struct SelectedCompletionInfo  ---------- */

typedef struct SelectedCompletionInfo SelectedCompletionInfo;

struct InlineCompletionContext {
    /**
     * Describes how the inline completion was triggered.
     */
    InlineCompletionTriggerKind triggerKind;

    /**
     * Provides information about the currently selected item in the
     * autocomplete widget if it is visible.
     *
     * If set, provided inline completions must extend the text of the
     * selected item and use the same range, otherwise they are not shown as
     * preview.
     * As an example, if the document text is `console.` and the selected item
     * is `.log` replacing the `.` in the document, the inline completion must
     * also replace `.` and start with `.log`, for example `.log()`.
     *
     * Inline completion providers are requested again whenever the selected
     * item changes.
     */
    SelectedCompletionInfo selectedCompletionInfo;
}; /* ----------  end of struct InlineCompletionContext  ---------- */

typedef struct InlineCompletionContext InlineCompletionContext;

template <ProgressToken T>
struct InlineCompletionParams : public TextDocumentPositionParams,
                                WorkDoneProgressParams<T> {
    /**
     * Additional information about the context in which inline completions
     * were requested.
     */
    InlineCompletionContext context;
}; /* ----------  end of struct InlineCompletionParams  ---------- */

// Response:

// result: InlineCompletionItem[] | InlineCompletionList | null defined as
// follows:

struct InlineCompletionItem {
    /**
     * The text to replace the range with. Must be set.
     * Is used both for the preview and the accept operation.
     */
    std::string insertText;

    /**
     * A text that is used to decide if this inline completion should be
     * shown. When `falsy`, the {@link InlineCompletionItem.insertText} is
     * used.
     *
     * An inline completion is shown if the text to replace is a prefix of the
     * filter text.
     */
    std::string filterText;

    /**
     * The range to replace.
     * Must begin and end on the same line.
     *
     * Prefer replacements over insertions to provide a better experience when
     * the user deletes typed text.
     */
    Range range;

    /**
     * An optional {@link Command} that is executed *after* inserting this
     * completion.
     */
    Command command;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(InlineCompletionItem, insertText, filterText,
                                   range, command);
}; /* ----------  end of struct InlineCompletionItem  ---------- */

typedef struct InlineCompletionItem InlineCompletionItem;
struct InlineCompletionList {
    /**
     * The inline completion items.
     */
    InlineCompletionItem items;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(InlineCompletionList, items);
}; /* ----------  end of struct InlineCompletionList  ---------- */

typedef struct InlineCompletionList InlineCompletionList;
}  // namespace e2
#endif /* ----- #ifndef INLINECOMPLETION_INC  ----- */
