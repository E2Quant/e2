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
#include <vector>

#include "assembler/BaseType.hpp"
#include "assembler/CodeGenStatement.hpp"
#include "assembler/ControlFlow.hpp"
#include "assembler/ExternFunction.hpp"
namespace yy {
class Parser;
class location;

}  // namespace yy

namespace e2 {

#define FILE_SIZE 2046

#define RESETFILE()               \
    ({                            \
        do {                      \
            _file_path[0] = '\0'; \
        } while (0);              \
    })
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

    int toparse(const char* f);
    int ProjPath(const char* f);
    const char* current_file();
    void project(const std::string paths);

    Block* RootBlock();
    void RootBlock(Block* block);
    NodeType current_block_type() { return _cbt; };
    void current_block_type(NodeType nt) { _cbt = nt; };

    void clear_loc() { _error_location.clear(); };
    void grammar_error(const yy::location&, std::size_t line, std::string msg);
    const std::vector<LocationType> grammar_error();
    void all_scan(bool b) { _all_scan = b; }

    void element_data(ElementInfo, std::size_t line, ElementKind);
    void element_update(ElementInfo, std::size_t line, ElementKind);
    ElementInfoType element_data();
    std::deque<LocationType> imports();

    void e2lsp()
    {
        _e2lsp = true;
        reset();
    }

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */
    // Handling the scanner.
    void scan_begin();
    void scan_end();

    void reset();

    int HasImport();

    int LongPath(std::string&, bool complete);
    int findPath(const char* f);

    int loopPath(const char* f, std::string&);
    std::string root_dirname(const char* p);
    /* =============  DATA MEMBERS  =================== */
    void* lexer;
    yy::location* loc;
    yy::Parser* parser;

    Block* _RootBlock{nullptr};

    NodeType _cbt = NodeType::_null;

    // 一个路径的长度，应该够了
    char _file_path[FILE_SIZE] = {0};
    // toparse 的 file path
    char* _root_filepath = NULL;
    FILE* _file = nullptr;

    std::vector<std::string> _project_dir;
    int _current_proj_idx = -1;

    bool _trace_scanning;

    std::string _imp_path = "main";

    std::vector<LocationType> _error_location;

    bool _all_scan = true;

    bool _e2lsp = false;
    //  e2l file path -> element_info list
    ElementInfoType _element_map;
}; /* -----  end of class ParserCtx  ----- */

}  // namespace e2
#endif /* ----- #ifndef PARSERCTX_INC  ----- */
