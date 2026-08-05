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
#include "lsp-server/LspLsif.hpp"

#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "assembler/BaseType.hpp"
#include "lsp-server/util.hpp"
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
    ;
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
        "CREATE TABLE e2lsp(e2lfile, value, begin_line, begin_column, "
        "end_line, end_column,code_line, ek, code, now);";
    execute(sql);
    sql = "CREATE INDEX idx_file ON e2lsp (e2lfile);";
    execute(sql);
    sql = "CREATE INDEX idx_value ON e2lsp (value);";
    execute(sql);

    system_keyword();
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
void LspLsif::system_keyword()
{
    const char* e2l_json_file = "/usr/local/include/e2/e2l.json";
    std::vector<std::string> keywords = {
        "extern", "namespace", "union", "func",     "import", "this",
        "self",   "switch",    "case",  "default",  "if",     "else",
        "for",    "do",        "while", "continue", "break",  "return"};
    ElementInfo ei;
    ei.ek = ElementKind::_ek_keyword;
    int is_file = access(e2l_json_file, R_OK);
    if (is_file != 0) {
        return;
    }
    std::FILE* f = std::fopen(e2l_json_file, "r");
    if (f == NULL) {
        llog::bug("file not exist!");
        return;
    }
    try {
        std::string enter = "\n";
        e2_json jdata = e2_json::parse(f);
        for (auto key : keywords) {
            ei.value = key;
            ei.insertText = "";
            if (jdata.count(key)) {
                if (jdata[key].count("body")) {
                    for (auto it : jdata[key]["body"]) {
                        ei.insertText += it;
                        ei.insertText += enter;
                    }
                }
            }

            preparedInsert(ei);
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

} /* -----  end of function LspLsif::system_keyword  ----- */
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
    std::string sql = llog::format("DELETE FROM e2lsp WHERE e2lfile =\"%s\"; ",
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
        llog::bug("SQL 错误: ", errMsg);
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
        "INSERT INTO e2lsp(e2lfile, value, begin_line, begin_column, end_line, "
        "end_column,code_line, ek,code, now) VALUES (?, ?,?,?,?,?,?,?,?,?)";

    int rc = sqlite3_prepare_v2(_db_connect, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        llog::bug("预处理失败: ", sqlite3_errmsg(_db_connect));
        return false;
    }
    auto now = std::chrono::system_clock::now();
    auto seconds =
        std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch())
            .count();
    // 绑定参数
    sqlite3_bind_text(stmt, 1, ei.code_path.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, ei.value.c_str(), -1, SQLITE_STATIC);

    sqlite3_bind_int(stmt, 3, ei.begin_line);
    sqlite3_bind_int(stmt, 4, ei.begin_column);
    sqlite3_bind_int(stmt, 5, ei.end_line);
    sqlite3_bind_int(stmt, 6, ei.end_column);
    sqlite3_bind_int(stmt, 7, ei.code_line);
    sqlite3_bind_int(stmt, 8, int(ei.ek));
    sqlite3_bind_text(stmt, 9, ei.insertText.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 10, seconds);
    // 执行
    rc = sqlite3_step(stmt);

    // 清理
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;

} /* -----  end of function LspLsif::preparedInsert  ----- */

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
        llog::bug("查询错误: ", errMsg);
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
