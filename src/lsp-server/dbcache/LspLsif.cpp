/*
 * =====================================================================================
 *
 *       Filename:  LspLsif.cpp
 *
 *    Description:  LspLsif
 *
 *        Version:  1.0
 *        Created:  2026/08/03 17时11分36秒
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
#include "lsp-server/dbcache/LspLsif.hpp"

#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "assembler/BaseType.hpp"
#include "lsp-server/util.hpp"
#include "utility/Log.hpp"
namespace e2 {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::LspLsif
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
LspLsif::LspLsif() : _db_connect(nullptr)
{
    init();
} /* -----  end of function LspLsif::LspLsif  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::init
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LspLsif::init()
{
    struct stat info;
    int init_db_table = -1;

    if (stat(_lldir, &info) != 0) {
        mkdir(_lldir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    else if (info.st_mode & S_IFDIR) {
    }
    else {
        mkdir(_lldir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    init_db_table = access(_dbfile.c_str(), R_OK);
    open(_dbfile);

    if (init_db_table != 0) {
        init_db();
    }

} /* -----  end of function LspLsif::init  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::init_db
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LspLsif::init_db()
{
    std::string sql =
        "CREATE TABLE e2lsp(code_uri, code_dir, value, begin_line, "
        "end_line, "
        "begin_column,  end_column, code_line, ek, code,from_ns,tag, now);";
    execute(sql);
    sql = "CREATE INDEX idx_file ON e2lsp (code_uri);";
    execute(sql);
    sql = "CREATE INDEX idx_value ON e2lsp (value);";
    execute(sql);

    std::string lib = llog::format("%s/lib.json", _lldir);
    int ret = access(lib.c_str(), R_OK);
    if (ret != 0) {
        e2_json j = e2_json::array({"/usr/local/include/e2"});
        std::ofstream(lib) << j;
    }

} /* -----  end of function LspLsif::init_db  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::system_keyword
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LspLsif::system_keyword(const char* e2l_json_file)
{
    std::string enter = "\n";

    std::FILE* f = NULL;
    const char* def_e2l_json_file = "/usr/local/include/e2/lsp-server/e2l.json";
    std::vector<std::string> keywords = {
        "extern", "namespace", "union", "func",     "import", "this",
        "self",   "switch",    "case",  "default",  "if",     "else",
        "for",    "do",        "while", "continue", "break",  "return"};
    ElementInfo ei;
    ei.ek = ElementKind::_ek_keyword;
    if (e2l_json_file != NULL) {
        int is_file = access(e2l_json_file, R_OK);
        llog::echo("is_file:", is_file);
        printf("ptha:%s\n", e2l_json_file);
        if (is_file != 0) {
            return;
        }

        f = std::fopen(e2l_json_file, "r");
        e2_json jdata = e2_json::parse(f);

        for (const auto& [key, value] : jdata.items()) {
            ei.value = key;
            ei.insertText = "";

            std::size_t body_size = jdata[key].count("body");
            if (body_size == 0) {
                continue;
            }
            body_size = jdata[key]["body"].size();
            for (auto it : jdata[key]["body"]) {
                ei.insertText += it;
                ei.insertText += enter;
            }

            preparedInsert(ei);
        }
    }
    else {
        int is_file = access(def_e2l_json_file, R_OK);
        if (is_file != 0) {
            return;
        }

        f = std::fopen(def_e2l_json_file, "r");
        if (f == NULL) {
            llog::bug("file not exist!");
            return;
        }
        try {
            e2_json jdata = e2_json::parse(f);
            for (auto key : keywords) {
                ei.value = key;
                ei.insertText = "";

                if (jdata.count(key)) {
                    std::size_t body_size = jdata[key].count("body");
                    if (body_size == 0) {
                        continue;
                    }
                    body_size = jdata[key]["body"].size();
                    for (auto it : jdata[key]["body"]) {
                        ei.insertText += it;
                        ei.insertText += enter;
                    }
                }

                preparedInsert(ei);
            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        GlobalUnionToE2lsp();
    }

} /* -----  end of function LspLsif::system_keyword  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::GlobalUnionToE2lsp
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  以后再优化吧
 * ============================================
 */
void LspLsif::GlobalUnionToE2lsp()
{
    char* tokens = NULL;
    char* var_tokens = NULL;
    char* pre = NULL;
    char* str;
    char delim[] = ".";
    // long val = 0;
    ElementInfo ei;

    for (auto it = _GlobalVariables.begin(); it != _GlobalVariables.end();
         ++it) {
        // val = it->second / NUMBER_DECI;
        str = strdup(it->first.c_str());

        if (str != NULL) {
            tokens = strtok(str, delim);
            if (pre == NULL) {
                pre = strdup(tokens);
                ei.value = llog::format("%s", tokens);
                ei.insertText = "";
                // 3
                ei.ek = ElementKind::_ek_union;

                preparedInsert(ei);

                // printf("union %s {\n", tokens);
            }
            if (strcmp(tokens, pre) != 0) {
                free(pre);
                pre = NULL;
                ei.value = llog::format("%s", tokens);
                ei.insertText = "";
                // 3
                ei.ek = ElementKind::_ek_union;

                preparedInsert(ei);

                // printf("}\n");
                // printf("union %s {\n", tokens);
                pre = strdup(tokens);
            }

            while ((var_tokens = strtok(NULL, delim))) {
                ei.value = llog::format("%s", var_tokens);
                ei.from_ns = llog::format("%s", tokens);
                // 6
                ei.ek = ElementKind::_ek_globle_un;
                preparedInsert(ei);

                // printf("%s .  %s = %ld;\n", tokens, var_tokens, val);
            }
            free(str);
        }
    }
    if (pre != NULL) {
        free(pre);
        pre = NULL;
    }
} /* -----  end of function LspLsif::GlobalUnionToE2lsp  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::load_lib_json
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LspLsif::load_lib_json(JsonCallback jcb)
{
    int ef = access(_lib_json_file, R_OK);
    if (ef != 0) {
        return;
    }
    std::ifstream fjson(_lib_json_file);
    e2_json data = e2_json::parse(fjson);
    std::string value = "";
    for (auto it : data) {
        value = it.get<std::string>();
        jcb(value);
    }
} /* -----  end of function LspLsif::load_lib_json  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::open
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::open(const std::string& filename)
{
    int rc = sqlite3_open(filename.c_str(), &_db_connect);
    if (rc != SQLITE_OK) {
        llog::bug("无法打开数据库: ", sqlite3_errmsg(_db_connect));
        return false;
    }
    return true;

} /* -----  end of function LspLsif::open  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::clear
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::clear(const std::string& e2l_file)
{
    std::string sql = llog::format("DELETE FROM e2lsp WHERE code_uri =\"%s\"; ",
                                   e2l_file.c_str());

    return execute(sql);
} /* -----  end of function LspLsif::clear  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::execute
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::execute(const std::string& sql)
{
    char* errMsg = nullptr;
    int rc = sqlite3_exec(_db_connect, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        llog::bug("SQL 错误: ", errMsg, " sql:", sql);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
} /* -----  end of function LspLsif::execute  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::preparedInsert
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::preparedInsert(ElementInfo ei)
{
    sqlite3_stmt* stmt;
    const char* sql =
        "INSERT INTO e2lsp(code_uri,code_dir, value, begin_line, "
        "end_line,begin_column,  "
        "end_column,code_line, ek,code,from_ns,tag, now) VALUES (?, "
        "?,?,?,?,?,?,?,?,?,?,?,?)";

    int rc = sqlite3_prepare_v2(_db_connect, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        llog::bug("预处理失败: ", sqlite3_errmsg(_db_connect), " sql:", sql);
        return false;
    }
    auto now = std::chrono::system_clock::now();
    auto seconds =
        std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch())
            .count();
    // 绑定参数
    sqlite3_bind_text(stmt, 1, ei.code_uri.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, ei.code_dir.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, ei.value.c_str(), -1, SQLITE_STATIC);

    sqlite3_bind_int(stmt, 4, ei.begin_line);
    sqlite3_bind_int(stmt, 5, ei.end_line);
    sqlite3_bind_int(stmt, 6, ei.begin_column);
    sqlite3_bind_int(stmt, 7, ei.end_column);
    sqlite3_bind_int(stmt, 8, ei.code_line);
    sqlite3_bind_int(stmt, 9, int(ei.ek));
    sqlite3_bind_text(stmt, 10, ei.insertText.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 11, ei.from_ns.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 12, ei.tag.c_str(), -1, SQLITE_STATIC);

    sqlite3_bind_int(stmt, 13, seconds);
    // 执行
    rc = sqlite3_step(stmt);

    // 清理
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;

} /* -----  end of function LspLsif::preparedInsert  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::update
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::update(ElementInfo ei)
{
    int rc = 0;
    if (ei.ek == ElementKind::_ek_namespace ||
        ei.ek == ElementKind::_ek_union) {
        sqlite3_stmt* ustmt = nullptr;

        const char* usql =
            "UPDATE e2lsp SET from_ns = ? WHERE code_uri=? and  begin_line >= "
            "? and end_line <=? and ek in (?,?,?);";
        rc = sqlite3_prepare_v2(_db_connect, usql, -1, &ustmt, nullptr);
        if (rc != SQLITE_OK) {
            llog::bug("预处理失败: ", sqlite3_errmsg(_db_connect));
            return false;
        }
        sqlite3_bind_text(ustmt, 1, ei.value.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(ustmt, 2, ei.code_uri.c_str(), -1, SQLITE_STATIC);

        sqlite3_bind_int(ustmt, 3, ei.begin_line);
        sqlite3_bind_int(ustmt, 4, ei.end_line);

        if (ei.ek == ElementKind::_ek_namespace) {
            sqlite3_bind_int(ustmt, 5, int(ElementKind::_ek_ns_var));
            sqlite3_bind_int(ustmt, 6, int(ElementKind::_ek_ns_fun));
            sqlite3_bind_int(ustmt, 7, int(ElementKind::_ek_ns_this_call));
        }
        else {
            sqlite3_bind_int(ustmt, 5, int(ElementKind::_ek_var));
            sqlite3_bind_int(ustmt, 6, int(ElementKind::_ek_globle_un));
            sqlite3_bind_int(ustmt, 7, int(ElementKind::_ek_var));
        }

        // 执行

        if (sqlite3_step(ustmt) != SQLITE_DONE) {
            const char* original_sql = sqlite3_expanded_sql(ustmt);
            llog::bug("原始 SQL: ", original_sql);

            llog::bug("执行更新失败: ", sqlite3_errmsg(_db_connect));
        }

        // 清理
        sqlite3_finalize(ustmt);
    }
    return true;
} /* -----  end of function LspLsif::update  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::query
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::query(const std::string& sql, call_back_query callback,
                    void* data)
{
    char* errMsg = nullptr;
    int rc = sqlite3_exec(_db_connect, sql.c_str(), callback, data, &errMsg);
    if (rc != SQLITE_OK) {
        llog::bug("查询错误: ", errMsg, " sql:", sql);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
} /* -----  end of function LspLsif::query  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::queryWithPrepare
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::queryWithPrepare(const std::string& sql)
{
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(_db_connect, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        llog::bug("预处理查询失败: ", sqlite3_errmsg(_db_connect));

        return false;
    }

    // 逐行读取结果
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);
        std::cout << "id: " << id << ", name: " << (name ? name : "NULL")
                  << ", age: " << age << std::endl;
    }

    sqlite3_finalize(stmt);
    return true;
} /* -----  end of function LspLsif::queryWithPrepare  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::beginTransaction
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::beginTransaction()
{
    return execute("BEGIN TRANSACTION");
} /* -----  end of function LspLsif::beginTransaction  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::commitTransaction
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::commitTransaction()
{
    return execute("COMMIT");
} /* -----  end of function LspLsif::commitTransaction  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::rollbackTransaction
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::rollbackTransaction()
{
    return execute("ROLLBACK");
} /* -----  end of function LspLsif::rollbackTransaction  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::batchInsert
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::batchInsert(const std::vector<ElementInfo>& records)
{
    beginTransaction();

    for (const auto& record : records) {
        if (!preparedInsert(record)) {
            rollbackTransaction();
            return false;
        }
    }

    commitTransaction();

    return true;
} /* -----  end of function LspLsif::batchInsert  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::batchUpdate
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool LspLsif::batchUpdate(const std::vector<ElementInfo>& records)
{
    beginTransaction();

    for (const auto& record : records) {
        if (!update(record)) {
            rollbackTransaction();
            return false;
        }
    }

    commitTransaction();

    return true;
} /* -----  end of function LspLsif::batchUpdate  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LspLsif::close
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void LspLsif::close()
{
    if (_db_connect) {
        sqlite3_close(_db_connect);
        _db_connect = nullptr;
    }
} /* -----  end of function LspLsif::close  ----- */

}  // namespace e2
