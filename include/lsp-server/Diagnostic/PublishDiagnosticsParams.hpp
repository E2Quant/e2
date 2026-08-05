/*
 * =====================================================================================
 *
 *       Filename:  PublishDiagnosticsParams.hpp
 *
 *    Description:  PublishDiagnosticsParams
 *
 *        Version:  1.0
 *        Created:  2026/07/29 14时15分47秒
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

#ifndef PUBLISHDIAGNOSTICSPARAMS_INC
#define PUBLISHDIAGNOSTICSPARAMS_INC
#include <string>
#include <vector>

#include "lsp-server/util.hpp"

namespace e2 {

enum DiagnosticSeverity {
    /**
     * Reports an error.
     */
    Error = 1,
    /**
     * Reports a warning.
     */
    Warning = 2,
    /**
     * Reports information.
     */
    Information = 3,
    /**
     * Reports a hint.
     */
    Hint = 4,
}; /* ----------  end of enum DiagnosticSeverity  ---------- */

typedef enum DiagnosticSeverity DiagnosticSeverity;

struct Diagnostic {
    /**
     * The range at which the message applies.
     */
    Range range;

    /**
     * The diagnostic's severity. To avoid interpretation mismatches when a
     * server is used with different clients it is highly recommended that
     * servers always provide a severity value. If omitted, it’s recommended
     * for the client to interpret it as an Error severity.
     */
    DiagnosticSeverity severity;

    /**
     * The diagnostic's code, which might appear in the user interface.
     *?: integer | string
     */
    std::string code;

    /**
     * An optional property to describe the error code.
     *
     * @since 3.16.0
     */
    //  CodeDescription codeDescription;

    /**
     * A human-readable string describing the source of this
     * diagnostic, e.g. 'typescript' or 'super lint'.
     */
    std::string source;

    /**
     * The diagnostic's message.
     *
     * @since 3.18.0 - support for MarkupContent. This is guarded by the client
     * capability `textDocument.diagnostic.markupMessageSupport`.
     *: string | MarkupContent
     */
    std::string message;

    /**
     * Additional metadata about the diagnostic.
     *
     * @since 3.15.0
     */
    // std::vector<DiagnosticTag> tags;

    /**
     * An array of related diagnostic information, e.g. when symbol-names within
     * a scope collide all definitions can be marked via this property.
     */
    // std::vector<DiagnosticRelatedInformation> relatedInformation;

    /**
     * A data entry field that is preserved between a
     * `textDocument/publishDiagnostics` notification and
     * `textDocument/codeAction` request.
     *
     * @since 3.16.0
     */
    //  LSPAnyObject data;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Diagnostic, range, severity, code, source,
                                   message);
}; /* ----------  end of struct Diagnostic  ---------- */

typedef struct Diagnostic Diagnostic;

struct PublishDiagnosticsParams {
    /**
     * The URI for which diagnostic information is reported.
     */
    DocumentUri uri;

    /**
     * Optionally, the version number of the document the diagnostics are
     * published for.
     *
     * @since 3.15.0
     */
    int version = 1;

    /**
     * An array of diagnostic information items.
     */
    std::vector<Diagnostic> diagnostics;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PublishDiagnosticsParams, uri, version,
                                   diagnostics);
}; /* ----------  end of struct PublishDiagnosticsParams  ---------- */

typedef struct PublishDiagnosticsParams PublishDiagnosticsParams;
}  // namespace e2
#endif /* ----- #ifndef PUBLISHDIAGNOSTICSPARAMS_INC  ----- */
