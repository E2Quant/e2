/*
 * =====================================================================================
 *
 *       Filename:   e2l_language_server.cpp
 *
 *    Description:   e2l_language_server
 *
 *        Version:  1.0
 *        Created:  2026/07/28 16时45分52秒
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

#include <poll.h>
#include <stdlib.h>
#include <unistd.h>

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "assembler/BaseType.hpp"
#include "assembler/CodeGenContext.hpp"
#include "ast/ParserCtx.hpp"
#include "lsp-server/dbcache/LspLsif.hpp"
#include "lsp-server/dbcache/dbevent.hpp"
#include "lsp-server/e2lsp.hpp"
#include "utility/Log.hpp"
using namespace e2;
namespace fs = std::filesystem;

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  lspt
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void lspt()
{
    StdIOStream stdi;
    LSPTransport lsp(stdi);

    lsp.initialize();

    lsp.next();

} /* -----  end of function lspt  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  yyltoken
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
ElementInfoType yyltoken(const char* fps, std::string project)
{
    llog::echo("yyl pro:", project);
    ParserCtx ctx;
    if (project.length() > 0) {
        ctx.project(project);
    }

    auto fun = [&ctx](const std::string& value) {
        ctx.project(value);
    };  // -----  end lambda  -----
    LspLsif ll;
    ll.load_lib_json(fun);

    ctx.e2lsp();

    ctx.all_scan(false);
    int ret = ctx.toparse(fps);
    if (ret < 0) {
        std::cerr << " loc size:" << ctx.grammar_error().size() << std::endl;
        for (auto it : ctx.grammar_error()) {
            std::cerr << " code line:" << it.code_line << "\n"
                      << " begin character:" << it.begin_column
                      << " begin line:" << it.begin_line << "\n"
                      << " end character:" << it.end_column
                      << " end line:" << it.end_line << "\n"
                      << " msg:" << it.msg << std::endl;
        }
    }

    std::deque<LocationType> mods = ctx.imports();

    for (auto mod : mods) {
        llog::echo("----");
        llog::info("mod name:", mod.mod_name, " code line:", mod.code_line,
                   " path:", mod.code_uri);
        ret = ctx.ProjPath(mod.mod_name.c_str());
        if (ret == -1) {
            llog::bug("not found file:", mod.mod_name);
        }
    }
    ElementInfoType eit = ctx.element_data();
    return eit;

} /* -----  end of function yyltoken  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  list_all_files
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int list_all_files(const char* path_str)
{
    fs::path code_dir(path_str);
    std::error_code ec;

    // 1. 检查路径是否存在
    if (!fs::exists(code_dir, ec)) {
        if (ec) {
            std::cerr << "检查路径出错: " << ec.message() << '\n';
        }
        else {
            std::cerr << "路径不存在: " << path_str << '\n';
        }
        return -2;
    }

    // 2. 检查是否为目录
    if (fs::is_directory(code_dir, ec)) {
        ElementInfoType eit;
        DBEvent dbevent(code_dir);
        //        std::string file_path = "";
        std::filesystem::path now_path;
        try {
            for (const auto& entry :
                 fs::recursive_directory_iterator(code_dir)) {
                std::string ext = entry.path().extension().string();
                // file_path = entry.path().string();

                if (ext == ".e2" || ext == ".e2l") {
                    eit = yyltoken(entry.path().c_str(), code_dir.string());

                    dbevent.save_element(eit);
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "遍历失败: " << e.what() << '\n';
        }
        return 0;
    }
    else {
        std::cerr << ec.message() << std::endl;
        return -1;
    }
} /* -----  end of function list_all_files  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  index_event
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void index_event(const char* code_path)
{
    int ret = list_all_files(code_path);
    if (ret == -1) {
        ElementInfoType eit = yyltoken(code_path, "");
        DBEvent dbevent;
        dbevent.save_element(eit);
    }
} /* -----  end of function index_event  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  e2l_json
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void e2l_json(const char* e2_json_path)
{
    CodeGenContext cgct;
    cgct.AddGlobal();

    LspLsif lsio;
    lsio.system_keyword(e2_json_path);

} /* -----  end of function e2l_json  ----- */

/*
 * ===  FUNCTION  =============================
 *         Name:  main
 *  Description:
 * ============================================
 */
int main(int argc, char* argv[])
{
    int h;
    bool bl = false;
    bool create_index = false;
    bool i = false;
    char* f = nullptr;
    char* d = nullptr;
    char* e = nullptr;

    std::string help =
        "%s -h \n \
Usage: \n \
-h help \n \
--- code manager \n \
    -b bison/lex code \n \
    -c create code index \n \
    -d project or lib dirs \n \
    -e e2l json system keyword, \n \
        def:/usr/local/include/e2/lsp-server/e2l.json \n \
    -f code file \n \
--- lsp server \n \
    -i io lsp server \n \
    -n network lsp server \n \
-v show e2lsp version \n \
";

    while ((h = getopt(argc, argv, "hnibcvd:f:e:")) != -1) {
        switch (h) {
            case 'h': {
                printf(help.c_str(), argv[0]);

                exit(-1);
            }
            case 'n':
                printf("network lsp server\n");
                break;
            case 'i':
                i = true;
                break;
            case 'b':
                bl = true;
                break;
            case 'c':
                create_index = true;
                break;
            case 'v':
                printf("version:0.0.1\n");
                break;
            case 'd':
                d = optarg;
                break;
            case 'f':
                f = optarg;
                break;
            case 'e':
                e = optarg;
                break;
            case '?':
            default:
                printf("%s -h\n", argv[0]);
                exit(-1);
        }
    }

    if (argc < 2) {
        printf(help.c_str(), argv[0]);

        exit(-1);
    }

    if (e != nullptr) {
        e2l_json(e);
        return EXIT_SUCCESS;
    }

    if (i) {
        lspt();
        return EXIT_SUCCESS;
    }

    if (bl && f != nullptr) {
        std::string ypath = "";
        if (d != nullptr) {
            ypath = std::string(d);
        }

        yyltoken(f, ypath);
        return EXIT_SUCCESS;
    }

    if (create_index) {
        if (f != nullptr) {
            index_event(f);
        }
        else if (d != nullptr) {
            index_event(d);
        }
    }

    return EXIT_SUCCESS;
} /* ----------  end of function main  ---------- */
