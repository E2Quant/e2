/*
 * =====================================================================================
 *
 *       Filename:  CompletionList.hpp
 *
 *    Description:  CompletionList
 *
 *        Version:  1.0
 *        Created:  2026/07/28 11时07分37秒
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

#ifndef COMPLETIONLIST_INC
#define COMPLETIONLIST_INC
#include <string>
#include <vector>

#include "lsp-server/util.hpp"

namespace e2 {

struct CompletionItemDefaults {
    /**
     * A default commit character set.
     *
     * @since 3.17.0
     */
    std::vector<std::string> commitCharacters;

    /**
     * A default edit range.
     *| EditRangeWithInsertReplace
     * @since 3.17.0
     */
    Range editRange;

    /**
     * A default insert text format.
     *
     * @since 3.17.0
     */
    InsertTextFormat insertTextFormat;

    /**
     * A default insert text mode.
     *
     * @since 3.17.0
     */
    InsertTextMode insertTextMode;

    /**
     * A default data value.
     *
     * @since 3.17.0
     */
    LSPAnyObject data;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CompletionItemDefaults, commitCharacters,
                                   editRange, insertTextFormat, insertTextMode,
                                   data);
}; /* ----------  end of struct CompletionItemDefaults  ---------- */

typedef struct CompletionItemDefaults CompletionItemDefaults;

enum ApplyKind {
    /**
     * The value from the individual item (if provided and not `null`) will be
     * used instead of the default.
     */
    Replace = 1,

    /**
     * The value from the item will be merged with the default.
     *
     * The specific rules for merging values are defined against each field
     * that supports merging.
     */
    Merge = 2,
}; /* ----------  end of enum ApplyKind  ---------- */

typedef enum ApplyKind ApplyKind;

struct CompletionItemApplyKinds {
    /**
     * Specifies whether commitCharacters on a completion will replace or be
     * merged with those in `completionList.itemDefaults.commitCharacters`.
     *
     * If ApplyKind.Replace, the commit characters from the completion item will
     * always be used unless not provided, in which case those from
     * `completionList.itemDefaults.commitCharacters` will be used. An
     * empty list can be used if a completion item does not have any commit
     * characters and also should not use those from
     * `completionList.itemDefaults.commitCharacters`.
     *
     * If ApplyKind.Merge the commitCharacters for the completion will be the
     * union of all values in both
     * `completionList.itemDefaults.commitCharacters` and the completion's own
     * `commitCharacters`.
     *
     * @since 3.18.0
     */
    ApplyKind commitCharacters;

    /**
     * Specifies whether the `data` field on a completion will replace or
     * be merged with data from `completionList.itemDefaults.data`.
     *
     * If ApplyKind.Replace, the data from the completion item will be used if
     * provided (and not `null`), otherwise
     * `completionList.itemDefaults.data` will be used. An empty object can
     * be used if a completion item does not have any data but also should
     * not use the value from `completionList.itemDefaults.data`.
     *
     * If ApplyKind.Merge, a shallow merge will be performed between
     * `completionList.itemDefaults.data` and the completion's own data
     * using the following rules:
     *
     * - If a completion's `data` field is not provided (or `null`), the
     *   entire `data` field from `completionList.itemDefaults.data` will be
     *   used as-is.
     * - If a completion's `data` field is provided, each field will
     *   overwrite the field of the same name in
     *   `completionList.itemDefaults.data` but no merging of nested fields
     *   within that value will occur.
     *
     * @since 3.18.0
     */
    ApplyKind data;
}; /* ----------  end of struct CompletionItemApplyKinds  ---------- */

typedef struct CompletionItemApplyKinds CompletionItemApplyKinds;

struct CompletionItemLabelDetails {
    /**
     * An optional string which is rendered less prominently directly after
     * {@link CompletionItem.label label}, without any spacing. Should be
     * used for function signatures or type annotations.
     */
    std::string detail;

    /**
     * An optional string which is rendered less prominently after
     * {@link CompletionItemLabelDetails.detail}. Should be used for fully
     * qualified names or file paths.
     */
    std::string description;
}; /* ----------  end of struct CompletionItemLabelDetails  ---------- */

typedef struct CompletionItemLabelDetails CompletionItemLabelDetails;

struct TextEdit {
    /**
     * The range of the text document to be manipulated. To insert
     * text into a document, create a range where start === end.
     */
    Range range;

    /**
     * The string to be inserted. For delete operations, use an
     * empty string.
     */
    std::string newText;
}; /* ----------  end of struct TextEdit  ---------- */

typedef struct TextEdit TextEdit;

struct CompletionItem {
    /**
     * The label of this completion item.
     *
     * The label property is also by default the text that
     * is inserted when selecting this completion.
     *
     * If label details are provided, the label itself should
     * be an unqualified name of the completion item.
     */
    std::string label;

    /**
     * Additional details for the label.
     *
     * @since 3.17.0
     */
    CompletionItemLabelDetails labelDetails;

    /**
     * The kind of this completion item. Based on the kind,
     * an icon is chosen by the editor. The standardized set
     * of available values is defined in `CompletionItemKind`.
     */
    CompletionItemKind kind;

    /**
     * Tags for this completion item.
     *
     * @since 3.15.0
     */
    std::vector<CompletionItemTag> tags;

    /**
     * A human-readable string with additional information
     * about this item, like type or symbol information.
     */
    std::string detail;

    /**
     * A human-readable string that represents a doc-comment.
     *| MarkupContent
     */
    std::string documentation;

    /**
     * Indicates if this item is deprecated.
     *
     * @deprecated Use `tags` instead if supported.
     */
    bool deprecated;

    /**
     * Select this item when showing.
     *
     * *Note* that only one completion item can be selected and that the
     * tool / client decides which item that is. The rule is that the *first*
     * item of those that match best is selected.
     */
    bool preselect;

    /**
     * A string that should be used when comparing this item
     * with other items. When omitted, the label is used
     * as the sort text for this item.
     */
    std::string sortText;

    /**
     * A string that should be used when filtering a set of
     * completion items. When omitted, the label is used as the
     * filter text for this item.
     */
    std::string filterText;

    /**
     * A string that should be inserted into a document when selecting
     * this completion. When omitted, the label is used as the insert text
     * for this item.
     *
     * The `insertText` is subject to interpretation by the client side.
     * Some tools might not take the string literally. For example,
     * when code complete is requested for `con<cursor position>`
     * and a completion item with an `insertText` of `console` is provided,
     * VSCode will only insert `sole`. Therefore, it is
     * recommended to use `textEdit` instead since it avoids additional client
     * side interpretation.
     */
    std::string insertText;

    /**
     * The format of the insert text. The format applies to both the
     * `insertText` property and the `newText` property of a provided
     * `textEdit`. If omitted, defaults to `InsertTextFormat.PlainText`.
     *
     * Please note that the insertTextFormat doesn't apply to
     * `additionalTextEdits`.
     */
    InsertTextFormat insertTextFormat;

    /**
     * How whitespace and indentation is handled during completion
     * item insertion. If not provided, the client's default value depends on
     * the `textDocument.completion.insertTextMode` client capability.
     *
     * @since 3.16.0
     * @since 3.17.0 - support for `textDocument.completion.insertTextMode`
     */
    InsertTextMode insertTextMode;

    /**
     * An edit which is applied to a document when selecting this completion.
     * When an edit is provided, the value of `insertText` is ignored.
     *
     * *Note:* The range of the edit must be a single line range and it must
     * contain the position at which completion has been requested. Despite this
     * limitation, your edit can write multiple lines.
     *
     * Most editors support two different operations when accepting a completion
     * item. One is to insert a completion text and the other is to replace an
     * existing text with a completion text. Since this can usually not be
     * predetermined by a server it can report both ranges. Clients need to
     * signal support for `InsertReplaceEdit`s via the
     * `textDocument.completion.completionItem.insertReplaceSupport` client
     * capability property.
     *
     * *Note 1:* The text edit's range as well as both ranges from an insert
     * replace edit must be a single line and they must contain the position
     * at which completion has been requested. In both cases, the new text can
     * consist of multiple lines.
     * *Note 2:* If an `InsertReplaceEdit` is returned, the edit's insert range
     * must be a prefix of the edit's replace range, meaning it must be
     * contained in and starting at the same position.
     *| InsertReplaceEdit
     * @since 3.16.0 additional type `InsertReplaceEdit`
     */
    TextEdit textEdit;

    /**
     * The edit text used if the completion item is part of a CompletionList and
     * CompletionList defines an item default for the text edit range.
     *
     * Clients will only honor this property if they opt into completion list
     * item defaults using the capability `completionList.itemDefaults`.
     *
     * If not provided and a list's default range is provided, the label
     * property is used as a text.
     *
     * @since 3.17.0
     */
    std::string textEditText;

    /**
     * An optional array of additional text edits that are applied when
     * selecting this completion. Edits must not overlap (including the same
     * insert position) with the main edit nor with themselves.
     *
     * Additional text edits should be used to change text unrelated to the
     * current cursor position (for example adding an import statement at the
     * top of the file if the completion item will insert an unqualified type).
     */
    std::vector<TextEdit> additionalTextEdits;

    /**
     * An optional set of characters that, when pressed while this completion is
     * active, will accept it first and then type that character. *Note* that
     * all commit characters should have `length=1` and that superfluous
     * characters will be ignored.
     */
    std::vector<std::string> commitCharacters;

    /**
     * An optional command that is executed *after* inserting this completion.
     * *Note* that additional modifications to the current document should be
     * described with the additionalTextEdits-property.
     */
    Command command;

    /**
     * A data entry field that is preserved on a completion item between
     * a completion and a completion resolve request.
     */
    LSPAnyObject data;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CompletionItem, label, data, sortText, kind,
                                   insertText);
}; /* ----------  end of struct CompletionItem  ---------- */

typedef struct CompletionItem CompletionItem;

struct CompletionList {
    /**
     * This list is not complete. Further typing should result in recomputing
     * this list.
     *
     * Recomputed lists have all their items replaced (not appended) in the
     * incomplete completion sessions.
     */
    bool isIncomplete = false;

    /**
     * In many cases, the items of an actual completion result share the same
     * value for properties like `commitCharacters` or the range of a text
     * edit. A completion list can therefore define item defaults which will
     * be used if a completion item itself doesn't specify the value.
     *
     * If a completion list specifies a default value and a completion item
     * also specifies a corresponding value, the rules for combining these are
     * defined by `applyKinds` (if the client supports it), defaulting to
     * ApplyKind.Replace.
     *
     * Servers are only allowed to return default values if the client
     * signals support for this via the `completionList.itemDefaults`
     * capability.
     *
     * @since 3.17.0
     */
    CompletionItemDefaults itemDefaults;

    /**
     * Specifies how fields from a completion item should be combined with those
     * from `completionList.itemDefaults`.
     *
     * If unspecified, all fields will be treated as ApplyKind.Replace.
     *
     * If a field's value is ApplyKind.Replace, the value from a completion item
     * (if provided and not `null`) will always be used instead of the value
     * from `completionItem.itemDefaults`.
     *
     * If a field's value is ApplyKind.Merge, the values will be merged using
     * the rules defined against each field below.
     *
     * Servers are only allowed to return `applyKind` if the client
     * signals support for this via the `completionList.applyKindSupport`
     * capability.
     *
     * @since 3.18.0
     */
    CompletionItemApplyKinds applyKind;

    /**
     * The completion items.
     */
    std::vector<CompletionItem> items;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CompletionList, isIncomplete, items);
}; /* ----------  end of struct CompletionList  ---------- */

typedef struct CompletionList CompletionList;
}  // namespace e2
#endif /* ----- #ifndef COMPLETIONLIST_INC  ----- */
