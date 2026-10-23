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
#include <sys/unistd.h>
#include <unistd.h>

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <filesystem>
#include <string>
#include <vector>

#include "E2L/E2LType.hpp"
#include "assembler/BaseType.hpp"
#include "generated/e2_bison.hpp"
#include "generated/e2_lex.hpp"
#include "location.hh"
#include "utility/Log.hpp"
namespace e2 {

ParserCtx::ParserCtx()
{
    try {
        std::string root_path = std::filesystem::current_path().string() + "/";
        _project_dir.push_back(root_path);
    }
    catch (const std::filesystem::filesystem_error& e) {
        llog::bug("project dir get error:", e.what());
    }
#ifdef SEARCH_PATH
    std::string spath = std::string(SEARCH_PATH);
    _project_dir.push_back(spath);
#endif

    _file_path[0] = '.';

    _RootBlock = MALLOC(Block, "inter", code_line, _file_path);
}

ParserCtx::~ParserCtx()
{
    RELEASE(_RootBlock);
    if (_root_filepath != NULL) {
        free(_root_filepath);
        _root_filepath = NULL;
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
    _trace_scanning = false;
#else
    _trace_scanning = false;
#endif
    yyset_debug(_trace_scanning, lexer);

    if (_file_path[0] == '\0' || _file_path[0] == '-')
        yyset_in(stdin, lexer);
    else {
        _file = fopen(_file_path, "r");
        if (_file == nullptr) {
            e2::llog::bug("cannot open ", std::string(_file_path), ": ",
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

    _file_path[0] = '\0';
} /* -----  end of function ParserCtx::scan_end  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::reset
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ParserCtx::reset()
{
    if (_root_filepath != NULL) {
        free(_root_filepath);
        _root_filepath = NULL;
    }

    if (_RootBlock != nullptr) {
        _RootBlock->clean();
    }
    _cbt = NodeType::_null;
    _current_proj_idx = -1;
    _imp_path = "main";

    _element_map.clear();

} /* -----  end of function ParserCtx::reset  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::toparse
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  f 有可能是完整路径，有可能是 URI
 * ============================================
 */
int ParserCtx::toparse(const char* f)
{
    int ret = 0;
    code_line = 1;
    variable_str_num = 1;

#ifdef E2L_DEBUG
    if (_root_filepath != NULL) {
        llog::info(llog::format("root: %s", _root_filepath));
    }
    else {
        llog::info(llog::format("root initing"));
    }
#endif
    ret = ProjPath(f);

#ifdef E2L_DEBUG
    llog::info(llog::format("file:%s ret:%d", _file_path, ret));
#endif
    if (ret != 0) {
        llog::bug(llog::format("not found import file:%s from root path:%s",
                               _file_path, _root_filepath));
        return ret;
    }

    if (_root_filepath != NULL) {
        free(_root_filepath);
        _root_filepath = NULL;
    }
    _root_filepath = strdup(f);

    yylex_init(&lexer);

    scan_begin();

    int res = parser->parse();
    if (res != 0) {
        ret = -2;
    }

    scan_end();

    if (ret == 0 && _all_scan) {
        ret = HasImport();
    }

    return ret;

} /* -----  end of function ParserCtx::toparse  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::ProjPath
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int ParserCtx::ProjPath(const char* f)
{
    int ret = 0;
    char fmt[] = "%s/%s";
    size_t len = 0;
    _current_proj_idx = -1;
    if (f == NULL) {
        return -1;
    }

    ret = access(f, R_OK);
    if (ret == 0) {
        RESETFILE();
        len = snprintf(NULL, 0, "%s", f) + 1;
        if (len > FILE_SIZE) {
            len = FILE_SIZE;
        }
        snprintf(_file_path, len, "%s", f);

        return ret;
    }

    for (std::string code_dir : _project_dir) {
        if (code_dir.length() == 0) {
            llog::info("search path is empty");
            return -1;
        }
        _current_proj_idx++;

        RESETFILE();

        len = snprintf(NULL, 0, fmt, code_dir.c_str(), f) + 1;
        if (len > FILE_SIZE) {
            len = FILE_SIZE;
        }
        snprintf(_file_path, len, fmt, code_dir.c_str(), f);

        ret = access(_file_path, R_OK);

        // #ifdef E2L_DEBUG
        //         if (ret != 0) {
        //             llog::bug(_file_path);
        //         }
        //         // else {
        //         //     llog::info(_file_path);
        //         // }
        // #endif

        if (ret == 0) {
            break;
        }
    }

    if (ret != 0) {
        _current_proj_idx = -1;
        ret = findPath(f);
    }

    return ret;
} /* -----  end of function ParserCtx::ProjPath  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::findPath
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  转成全路径的 path
 * ============================================
 */
int ParserCtx::findPath(const char* f)
{
    int ef = -1;

    std::string dir_name = root_dirname(_root_filepath);

    ef = loopPath(f, dir_name);
    if (ef != 0) {
        for (auto pdir : _project_dir) {
            dir_name = pdir + "/" + root_dirname(_root_filepath);
            ef = loopPath(f, dir_name);
            if (ef == 0) {
                break;
            }
        }
    }

    return ef;
} /* -----  end of function ParserCtx::findPath  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::loopPath
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int ParserCtx::loopPath(const char* f, std::string& dir_name)
{
    char fmt[] = "%s/%s";
    size_t len = 0;
    int ef = -1;

    size_t dir_is_len = 0;
    do {
        RESETFILE();

        len = snprintf(NULL, 0, fmt, dir_name.c_str(), f) + 1;

        snprintf(_file_path, len, fmt, dir_name.c_str(), f);

        // #ifdef E2L_DEBUG
        //         llog::info(_file_path);
        // #endif

        ef = access(_file_path, R_OK);
        if (ef == 0) {
            _project_dir.push_back(dir_name);
            return ef;
        }

        dir_name = root_dirname(dir_name.c_str());

        dir_is_len = strnlen(dir_name.c_str(), len);
        if (dir_is_len < 2) {
            return ef;
        }

    } while (1);

    return ef;
} /* -----  end of function ParserCtx::loopPath  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::project
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ParserCtx::project(const std::string src_path)
{
    if (src_path.length() == 0) return;
    std::string proj = src_path;
    std::size_t len = proj.length();
    if (proj.substr(len - 1, len) == "/") {
        proj = proj.substr(0, len - 1);
    }
    LongPath(proj, true);

    // llog::info(proj);
    _project_dir.push_back(proj);

} /* -----  end of function ParserCtx::project  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::root_dirname
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  取上一级目录
 * ============================================
 */
std::string ParserCtx::root_dirname(const char* p)
{
    if (p == NULL) {
        return std::filesystem::path(_project_dir.at(0)).parent_path().string();
    }
    return std::filesystem::path(p).parent_path().string();
} /* -----  end of function ParserCtx::root_dirname  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::LongPath
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int ParserCtx::LongPath(std::string& src_path, bool complete)
{
    int ret = 0;
    std::filesystem::path now_path = std::filesystem::current_path();
    if (src_path.substr(0, 2) == "..") {
        ret = 1;
        do {
            src_path = src_path.substr(3, src_path.length());
            now_path = now_path.parent_path();

        } while (src_path.substr(0, 2) == ".." && src_path.length() > 3);

        if (complete) {
            src_path = now_path.string() + "/" + src_path;
        }
    }
    else if (src_path.substr(0, 1) == ".") {
        if (src_path.length() <= 2) {
            src_path = now_path.string();
        }
        else {
            src_path = src_path.substr(2, src_path.length());

            if (complete) {
                src_path = now_path.string() + "/" + src_path;
            }
        }
    }
    else if (src_path.substr(0, 1) != "/") {
        src_path = _project_dir.at(0) + src_path;
    }
    else {
        ret = -1;
    }
    return ret;
} /* -----  end of function ParserCtx::LongPath  ----- */
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
const char* ParserCtx::current_file()
{
    return _file_path;
} /* -----  end of function ParserCtx::current_file  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::grammar_error
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  保存语法错误的数据
 * ============================================
 */
void ParserCtx::grammar_error(const yy::location& locs, std::size_t line,
                              std::string msg)
{
    std::string efile = llog::format("%s", _file_path);

    LocationType e2d;
    e2d.begin_line = locs.begin.line;
    e2d.begin_column = locs.begin.column;
    e2d.end_line = locs.end.line;
    e2d.end_column = locs.end.column;
    e2d.code_line = line;
    e2d.code_uri = efile;
    e2d.msg = msg;

    _error_location.push_back(e2d);

} /* -----  end of function ParserCtx::grammar_error  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::grammar_error
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
const std::vector<LocationType> ParserCtx::grammar_error()
{
    return _error_location;
} /* -----  end of function ParserCtx::grammar_error  ----- */

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
    std::deque<LocationType> imps = _RootBlock->get_import(_imp_path);

    while (!imps.empty()) {
        _imp_path = imps.front().mod_name;
        imps.pop_front();

        _RootBlock->update(_imp_path);
        ret = toparse(_imp_path.c_str());
        if (ret == -1) {
            // 下一步再做 lsp 变量错误的分析
            continue;
        }
    }

    return ret;
} /* -----  end of function ParserCtx::HasImport  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::imports
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::deque<LocationType> ParserCtx::imports()
{
    std::deque<LocationType> imps = _RootBlock->get_import(_imp_path);
    return imps;
} /* -----  end of function ParserCtx::imports  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::element_data
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ParserCtx::element_data(ElementInfo ei, std::size_t line, ElementKind ek)
{
    if (_e2lsp == false) {
        return;
    }
    ei.ek = ek;
    std::string efile = llog::format("%s", _file_path);

    LongPath(efile, true);

    std::size_t len = 0;
    std::string pdir = "";
    for (auto code_dir : _project_dir) {
        len = code_dir.length();
        if (efile.length() < len) {
            continue;
        }
        pdir = efile.substr(0, len);
        if (pdir == code_dir) {
            efile = efile.substr(len, efile.length());
            ei.code_dir = code_dir;
            break;
        }
    }

    ei.code_uri = efile;

    if (_element_map.count(efile) == 0) {
        std::vector<ElementInfo> ei_list;
        ei_list.push_back(ei);
        _element_map.insert({efile, ei_list});
    }
    else {
        _element_map.at(efile).push_back(ei);
    }
} /* -----  end of function ParserCtx::element_data  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::element_update
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  主要是更新 method_call 的参数与  primary_rvalue 的 ek 值
 * ============================================
 */
void ParserCtx::element_update(ElementInfo ei, std::size_t line, ElementKind ek)
{
    if (_e2lsp == false) {
        return;
    }
    std::string efile = llog::format("%s", _file_path);

    if (_element_map.count(efile) == 0) {
        return;
    }
    std::size_t idx = 0;
    for (auto it : _element_map.at(efile)) {
        if (it.value == ei.value && it.code_line == ei.code_line) {
            _element_map.at(efile).at(idx).ek = ek;
            _element_map.at(efile).at(idx).from_ns = ei.from_ns;
        }
        idx++;
    }
} /* -----  end of function ParserCtx::element_update  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ParserCtx::element_data
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
ElementInfoType ParserCtx::element_data()
{
    return _element_map;
} /* -----  end of function ParserCtx::element_data  ----- */

}  // namespace e2
