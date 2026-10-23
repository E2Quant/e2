/*
 * =====================================================================================
 *
 *       Filename:  dbevent.cpp
 *
 *    Description:  dbevent
 *
 *        Version:  1.0
 *        Created:  2026/09/22 09时46分44秒
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
#include "lsp-server/dbcache/dbevent.hpp"

#include <filesystem>
#include <string>

#include "assembler/BaseType.hpp"
#include "utility/Log.hpp"
namespace e2 {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::DBEvent
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
DBEvent::DBEvent()
{
    _current_uri = "";
    init("");
}
DBEvent::DBEvent(std::string uri)
{
    init(uri);
} /* -----  end of function DBEvent::DBEvent  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::set_current_uri
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void DBEvent::set_current_uri(std::string uri)
{
    std::string file_path = "file://";
    if (uri.length() > file_path.length()) {
        _current_uri = uri.substr(file_path.length());
    }
} /* -----  end of function DBEvent::set_current_uri  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::init
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void DBEvent::init(std::string uri)
{
    std::string root_path = std::filesystem::current_path().string() + "/";
    _project_lib.push_back(root_path);

    auto fun = [this](const std::string& value) {
        this->_project_lib.push_back(value);
    };  // -----  end lambda  -----

    _ll.load_lib_json(fun);

    set_current_uri(uri);
} /* -----  end of function DBEvent::init  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::real_uri
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::string DBEvent::real_uri(const std::string& uri)
{
    // std::size_t len = 0;
    // std::string pdir = "";
    std::string import_uri = uri;
    // int m = 0;
    // for (auto search_path : _project_lib) {
    //     len = search_path.length();
    //     m++;
    //     if (import_uri.length() < len) {
    //         continue;
    //     }
    //     pdir = uri.substr(0, len);
    //     if (pdir == search_path) {
    //         if (m > 1) {
    //             len = -1;
    //         }
    //         import_uri = import_uri.substr(len, import_uri.length());
    //         break;
    //     }
    // }
    return import_uri;
} /* -----  end of function DBEvent::real_uri  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::value
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int DBEvent::value(const std::string& uri, int line, int character,
                   std::string& val)
{
    std::vector<ElementInfo> ei_list;
    std::string _uri = uri;

    llog::echo(_uri);

    std::string sql = llog::format(
        "SELECT DISTINCT value,begin_column,end_column,ek  from e2lsp WHERE "
        "(code_dir || code_uri) = "
        "\"%s\" and code_line=%d and begin_column <= %d and end_column >= %d "
        "GROUP BY value ;",
        _uri.c_str(), line, character, character);

#ifdef E2L_DEBUG
    llog::info(sql);
#endif

    int ret = QUERY(sql, ei_list);
    if (ei_list.size() > 0) {
        val = ei_list.at(0).value;
    }
    else {
        ret = -1;
    }
    return ret;

} /* -----  end of function DBEvent::value  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::postion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int DBEvent::postion(std::string& value, std::vector<ElementInfo>& ei_list)
{
    std::string sql = llog::format(
        "SELECT DISTINCT  (code_dir ||  code_uri ) AS code_uri, ek,"
        "value,begin_column,begin_line,end_column,end_line "
        "from e2lsp WHERE value = '%s' GROUP BY code_uri,ek ;",
        value.c_str());

#ifdef E2L_DEBUG
    llog::info(sql);
#endif

    int ret = QUERY(sql, ei_list);
    return ret;

} /* -----  end of function DBEvent::postion  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::search_key
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int DBEvent::search_key(const std::string& key,
                        std::vector<ElementInfo>& ei_list)
{
    std::string::size_type n = key.find("<");
    std::string sql = "";
    if (n != std::string::npos) {
        std::string ns_name = key.substr(0, n);
        std::string ns_tag = "";
        std::string::size_type p = key.find(">");
        if (p != std::string::npos) {
            ns_tag = key.substr(n, p);
        }

        // llog::info("name:", ns_name, " tag:", ns_tag);
        if (ns_tag.length() == 0) {
            sql = llog::format(
                "select (code_dir ||  code_uri ) AS code_uri, value, "
                "code,from_ns,tag, ek from "
                "e2lsp where "
                "from_ns = '%s' AND ek in(%d, %d)  ",
                ns_name.c_str(), int(ElementKind::_ek_ns_fun),
                int(ElementKind::_ek_ns_call));
        }
        else {
            sql = llog::format(
                "select (code_dir ||  code_uri ) AS code_uri, value, "
                "code,from_ns,tag, ek from "
                "e2lsp where "
                "from_ns = '%s' AND ek in(%d, %d) AND tag ='%s' ",
                ns_name.c_str(), int(ElementKind::_ek_ns_fun),
                int(ElementKind::_ek_ns_call), ns_tag.c_str());
        }
    }
    if (sql.length() == 0) {
        n = key.find(":");
        if (n != std::string::npos) {
            sql = llog::format(
                "select (code_dir ||  code_uri ) AS code_uri, value, code, "
                "from_ns,tag,ek from "
                "e2lsp where "
                "value like "
                "\"%s%%\" ",
                key.substr(0, n).c_str());
        }
    }

    if (sql.length() == 0) {
        n = key.find(".");
        if (n != std::string::npos) {
            sql = llog::format(
                "select (code_dir ||  code_uri ) AS code_uri, value, code, "
                "from_ns,tag,ek from "
                "e2lsp where "
                "value like "
                "\"%s%%\"   ",
                key.substr(0, n).c_str());
        }
    }
    if (sql.length() == 0) {
        sql = llog::format(
            "          SELECT DISTINCT value,(code_dir || code_uri) AS "
            "code_uri,ek, code, from_ns, tag FROM e2lsp WHERE value LIKE "
            "\"%s%%\" "
            "AND ek = 1 AND (code_dir || code_uri) = \"%s\""
            " UNION "
            "SELECT DISTINCT    value,(code_dir || code_uri) AS code_uri,ek, "
            "code, from_ns, tag FROM e2lsp WHERE value LIKE \"%s%%\" AND ek != "
            "1 GROUP BY value",
            key.c_str(), _current_uri.c_str(), key.c_str());
    }
#ifdef E2L_DEBUG
    llog::info(sql);
#endif

    int ret = QUERY(sql, ei_list);
    return ret;

} /* -----  end of function DBEvent::search_key  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::search_ns
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int DBEvent::search_ns(const std::string& ns_name,
                       std::vector<ElementInfo>& ei_list)
{
    std::string sql = llog::format(
        "select (code_dir ||  code_uri ) AS code_uri, value, code,from_ns,tag, "
        "ek from e2lsp "
        "where "
        "from_ns = \"%s\" AND ek in(%d, %d) ",
        ns_name.c_str(), int(ElementKind::_ek_ns_fun),
        int(ElementKind::_ek_ns_call));

#ifdef E2L_DEBUG
    llog::info(sql);
#endif

    int ret = QUERY(sql, ei_list);
    return ret;
} /* -----  end of function DBEvent::search_ns  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::search_ns_field
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int DBEvent::search_ns_field(std::uint32_t line,
                             std::vector<ElementInfo>& ei_list)
{
    std::vector<ElementInfo> ns_ei;
    std::string sql = llog::format(
        "select value,begin_line,end_line from e2lsp where begin_line <= %d "
        "AND end_line>=%d AND ek=%d and (code_dir || code_uri)='%s'  ;",
        line, line, int(ElementKind::_ek_namespace), _current_uri.c_str());

#ifdef E2L_DEBUG
    llog::info(sql);
#endif

    int ret = QUERY(sql, ns_ei);
    if (ret == -1) {
        return ret;
    }

    for (auto it : ns_ei) {
        sql = llog::format(
            "SELECT data.code_uri, data.value, data.code, "
            "data.ek, "
            "data.begin_line,data.end_line FROM (select (code_dir ||  code_uri "
            ") AS  code_uri, "
            "value, code, "
            "ek, begin_line,end_line from e2lsp where begin_line >= %d AND "
            "end_line <= %d AND ek in(%d, %d)) data WHERE data.begin_line > %d "
            "or data.end_line < %d ; ",
            it.begin_line, it.end_line, int(ElementKind::_ek_ns_var),
            int(ElementKind::_ek_ns_fun), line, line);
#ifdef E2L_DEBUG
        llog::info(sql);
#endif

        ret = QUERY(sql, ei_list);
    }

    return 0;
} /* -----  end of function DBEvent::search_ns_field  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::search_ns_fields
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int DBEvent::search_ns_fields(const std::string& ns_name,
                              std::vector<ElementInfo>& ei_list)
{
    // llog::info("name:", ns_name);
    std::string sql = llog::format(
        "select (code_dir ||  code_uri ) AS  code_uri, value, "
        "code,from_ns,tag, ek from e2lsp "
        "where "
        "from_ns = \"%s\" AND ek in(%d, %d) ",
        ns_name.c_str(), int(ElementKind::_ek_ns_fun),
        int(ElementKind::_ek_ns_call));
#ifdef E2L_DEBUG
    llog::info(sql);
#endif

    int ret = QUERY(sql, ei_list);
    return ret;
} /* -----  end of function DBEvent::search_ns_fields  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::search_union_fields
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int DBEvent::search_union_fields(const std::string& unin_name,
                                 std::vector<ElementInfo>& ei_list)
{
    std::string sql = llog::format(
        "select DISTINCT value,from_ns,(code_dir ||  code_uri ) AS code_uri,  "
        "code,tag, "
        "ek from e2lsp "
        "where "
        "from_ns = \"%s\" AND ek in(%d, %d) GROUP BY value,from_ns ",
        unin_name.c_str(), int(ElementKind::_ek_union),
        int(ElementKind::_ek_globle_un));

#ifdef E2L_DEBUG
    llog::info(sql);
#endif

    int ret = QUERY(sql, ei_list);

    return ret;
} /* -----  end of function DBEvent::search_union_fields  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::search_import_path
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
int DBEvent::search_import_path(const std::string& imp_path,
                                std::vector<ElementInfo>& ei_list)
{
    std::string limit = " ;";

    std::string efile = "code_uri !=''";
    if (imp_path.length() > 0) {
        efile = llog::format("code_uri like '%%%s%%'", imp_path.c_str());
    }
    std::string sql = llog::format(
        "SELECT DISTINCT code_uri,code_dir, 13 as ek from e2lsp WHERE %s ORDER "
        "BY "
        "code_uri  %s ",
        efile.c_str(), limit.c_str());

#ifdef E2L_DEBUG
    llog::info(sql);
#endif

    int ret = QUERY(sql, ei_list);

    return ret;

} /* -----  end of function DBEvent::search_import_path  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  DBEvent::save_element
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void DBEvent::save_element(ElementInfoType& eit)
{
    // _ll.import_dir(_current_uri);
    for (auto value : eit) {
        _ll.clear(value.first);
        _ll.batchInsert(value.second);
    }

    for (auto value : eit) {
        _ll.batchUpdate(value.second);
    }

} /* -----  end of function DBEvent::save_element  ----- */
}  // namespace e2
