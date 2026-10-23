/*
 * =====================================================================================
 *
 *       Filename:  LspLsif.hpp
 *
 *    Description:  LspLsif
 *
 *        Version:  1.0
 *        Created:  2026/08/03 16时59分15秒
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

#ifndef LSP_LSIF_INC
#define LSP_LSIF_INC
#include <sqlite3.h>

#include <cstring>
#include <string>
#include <vector>

#include "assembler/BaseType.hpp"
#include "utility/Log.hpp"
namespace e2 {

/* Callback function */

using call_back_query = int (*)(void*, int, char**, char**);

using JsonCallback = std::function<void(const std::string&)>;

/*
 * ================================
 *        Class:  LspLsif
 *  Description:
 * ================================
 */
class LspLsif {
public:
    /* =============  LIFECYCLE     =================== */
    LspLsif(); /* constructor */
    ~LspLsif() { close(); }
    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */

    void load_lib_json(JsonCallback);

    bool open(const std::string& filename);
    bool clear(const std::string& e2l_file);
    bool execute(const std::string& sql);
    bool preparedInsert(ElementInfo);
    bool update(ElementInfo);

    bool query(const std::string& sql, call_back_query, void*);
    bool queryWithPrepare(const std::string& sql);
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
    bool batchInsert(const std::vector<ElementInfo>& records);
    bool batchUpdate(const std::vector<ElementInfo>& records);

    void system_keyword(const char*);
    void close();

    // void import_dir(const std::string& code_dir)
    // {
    //     _code_dir = std::move(code_dir);
    // }

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */
    void init();
    void init_db();

    void update();

    void GlobalUnionToE2lsp();

    /* =============  DATA MEMBERS  =================== */
    sqlite3* _db_connect;

    const char* _lldir = ".e2lsp";
    std::string _dbfile = ".e2lsp/e2lsp.db";
    const char* _lib_json_file = ".e2lsp/lib.json";
    //  std::string _code_dir = "";
}; /* -----  end of class LspLsif  ----- */

}  // namespace e2
#endif /* ----- #ifndef LSP_LSIF_INC  ----- */
