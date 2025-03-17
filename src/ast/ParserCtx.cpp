/*
 * =====================================================================================
 *
 *       Filename:  ParserCtx.cpp
 *
 *    Description:  ParserCtx
 *
 *        Version:  1.0
 *        Created:  2023年10月24日 16时32分19秒
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
 * =====================================================================================
 */

#include "ast/ParserCtx.hpp"

#include <libgen.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>
#include <vector>

#include "generated/e2_bison.hpp"
#include "generated/e2_lex.hpp"
namespace e2 {

ParserCtx::ParserCtx()
{
    _RootBlock = MALLOC(Block, "inter", code_line, _file_path);
}

ParserCtx::~ParserCtx()
{
    RELEASE(_RootBlock);
    if (_dir != nullptr) {
        free(_dir);
        _dir = nullptr;
    }
}

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Parser::scan_begin
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ParserCtx::scan_begin()
{
    loc = new yy::location();
    parser = new yy::Parser(lexer, *loc, *this);

#ifdef E2L_DEBUG
    parser->set_debug_level(false);
    trace_scanning = false;
#else
    trace_scanning = false;
#endif
    yyset_debug(trace_scanning, lexer);

    if (_file_path == nullptr || std::string(_file_path) == "-")
        yyset_in(stdin, lexer);
    else {
        _file = fopen(_file_path, "r");
        if (_file == nullptr) {
            e2::log::bug("cannot open ", std::string(_file_path), ": ",
                         strerror(errno));
            exit(EXIT_FAILURE);
        }
        yyset_in(_file, lexer);
    }
} /* -----  end of function Parser::scan_begin  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::scan_end
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ParserCtx::scan_end()
{
    yylex_destroy(lexer);
    delete loc;
    delete parser;

    if (_file != nullptr) {
        fclose(_file);
    }

    if (_file_path != nullptr) {
        free(_file_path);
        _file_path = nullptr;
    }
} /* -----  end of function ParserCtx::scan_end  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::toparse
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int ParserCtx::toparse(const char* f)
{
    int ret = 0;
    code_line = 1;
    if (_dir == nullptr) {
        size_t dlen = snprintf(NULL, 0, "%s", f) + 1;
        _file_path = (char*)malloc(dlen);
        snprintf(_file_path, dlen, "%s", f);

        char* _dirc = strdup(f);
        if (_dirc != nullptr) {
            char* dir = dirname(_dirc);
            dlen = snprintf(NULL, 0, "%s", dir) + 1;
            _dir = (char*)malloc(dlen);
            snprintf(_dir, dlen, "%s", dir);

            free(_dirc);
            _dirc = nullptr;
        }
    }
    else {
        char fmt[] = "%s/%s";
        size_t len = snprintf(NULL, 0, fmt, _dir, f) + 1;
        _file_path = (char*)malloc(len);
        snprintf(_file_path, len, fmt, _dir, f);
    }

    yylex_init(&lexer);

    scan_begin();

    int res = parser->parse();
    if (res != 0) {
        ret = -1;
    }

    scan_end();
    if (ret == 0) {
        ret = HasImport();
    }

    return ret;

} /* -----  end of function ParserCtx::toparse  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::RootBlock
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
Block* ParserCtx::RootBlock() { return _RootBlock; }
void ParserCtx::RootBlock(Block* block) { _RootBlock = block; }
/* -----  end of function ParserCtx::RootBlock  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::current_file
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ParserCtx::current_file()
{
    printf("file:%s\n", _file_path);
} /* -----  end of function ParserCtx::current_file  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::path
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
const char* ParserCtx::path()
{
    return _file_path;
} /* -----  end of function ParserCtx::path  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::HasImport
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   先这样简单点，之后再优化 相互 import 的功能 
 * ============================================
 */
int ParserCtx::HasImport()
{
    _RootBlock->mod();
    int ret = 0;
    if (_RootBlock->importnull(_imp_path)) {
        return ret;
    }
    std::deque<std::string> imps = _RootBlock->get_import(_imp_path);
    while (!imps.empty()) {
        _imp_path = imps.front();
        imps.pop_front();

        _RootBlock->update(_imp_path);
        ret = toparse(_imp_path.c_str());
        if (ret == -1) {
            return ret;
        }
    }

    return ret;
} /* -----  end of function ParserCtx::HasImport  ----- */

}  // namespace e2
