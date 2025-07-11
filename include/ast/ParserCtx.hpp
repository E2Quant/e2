/*
 * =====================================================================================
 *
 *       Filename:  ParserCtx.hpp
 *
 *    Description:  ParserCtx
 *
 *        Version:  1.0
 *        Created:  2023年10月24日 16时30分19秒
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
#ifndef PARSERCTX_INC
#define PARSERCTX_INC
#include <libgen.h>

#include <cstddef>
#include <string>

#include "assembler/CodeGenStatement.hpp"
#include "assembler/ControlFlow.hpp"
#include "assembler/ExternFunction.hpp"
namespace yy {
class Parser;
class location;
}  // namespace yy

namespace e2 {

/*
 * ================================
 *        Class:  ParserCtx
 *  Description:
 * ================================
 */
class ParserCtx {
public:
    /* =============  LIFECYCLE     =================== */
    ParserCtx(); /* constructor */
    ~ParserCtx();
    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */

    // Handling the scanner.
    void scan_begin();
    void scan_end();

    int toparse(const char *f);
    void search_path(const char *f);

    Block *RootBlock();
    void RootBlock(Block *block);

    const char *path();
    void current_file();
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */
    int HasImport();

    void rootPath(const char *f);
    int findPath(const char *f);

    int defPath(const char *f);
    /* =============  DATA MEMBERS  =================== */
    void *lexer;
    yy::location *loc;
    yy::Parser *parser;

    Block *_RootBlock{nullptr};

    char *_dir = nullptr;
    char *_file_path = nullptr;
    FILE *_file = nullptr;

    bool trace_scanning;

    std::string _imp_path = "main";

    std::string _search_path = "";

}; /* -----  end of class ParserCtx  ----- */

}  // namespace e2
#endif /* ----- #ifndef PARSERCTX_INC  ----- */
