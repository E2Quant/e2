/*
 * =====================================================================================
 *
 *       Filename:  dbevent.hpp
 *
 *    Description:  dbevent
 *
 *        Version:  1.0
 *        Created:  2026/09/22 09时41分49秒
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

#ifndef DBEVENT_INC
#define DBEVENT_INC
#include <cstdint>
#include <string>
#include <vector>

#include "assembler/BaseType.hpp"
#include "lsp-server/dbcache/LspLsif.hpp"
namespace e2 {

inline auto call_fun = [](void* data, int argc, char** argv,
                          char** colName) -> int {
    auto* result = static_cast<std::vector<ElementInfo>*>(data);
    ElementInfo _ei;
    for (int i = 0; i < argc; i++) {
        std::string col = std::string(colName[i]);
        if (col == "code_uri") {
            _ei.code_uri = (argv[i] ? std::string(argv[i]) : "");
        }
        if (col == "code_dir") {
            _ei.code_dir = (argv[i] ? std::string(argv[i]) : "");
        }
        if (col == "value") {
            _ei.value = (argv[i] ? std::string(argv[i]) : "");
        }
        if (col == "begin_line") {
            _ei.begin_line = (argv[i] ? atoi(argv[i]) : 0);
        }
        if (col == "begin_column") {
            _ei.begin_column = (argv[i] ? atoi(argv[i]) : 0);
        }
        if (col == "end_line") {
            _ei.end_line = (argv[i] ? atoi(argv[i]) : 0);
        }
        if (col == "end_column") {
            _ei.end_column = (argv[i] ? atoi(argv[i]) : 0);
        }
        if (col == "code_line") {
            _ei.code_line = (argv[i] ? atoi(argv[i]) : 0);
        }
        if (col == "ek") {
            int ekd = (argv[i] ? atoi(argv[i]) : 0);
            _ei.ek = (ElementKind)ekd;
        }
        if (col == "code") {
            _ei.insertText = (argv[i] ? std::string(argv[i]) : "");
        }
        if (col == "from_ns") {
            _ei.from_ns = (argv[i] ? std::string(argv[i]) : "");
        }
        if (col == "tag") {
            _ei.tag = (argv[i] ? std::string(argv[i]) : "");
        }
    }
    result->push_back(_ei);
    return 0;
};  // -----  end lambda  -----

#define QUERY(sql, rlist)                              \
    ({                                                 \
        int __ret = 0;                                 \
        do {                                           \
            bool r = _ll.query(sql, call_fun, &rlist); \
            if (r == false) {                          \
                __ret = -1;                            \
            }                                          \
        } while (0);                                   \
        __ret;                                         \
    })

/*
 * ================================
 *        Class:  DBEvent
 *  Description:
 * ================================
 */
class DBEvent {
public:
    /* =============  LIFECYCLE     =================== */
    DBEvent();
    DBEvent(std::string uri); /* constructor */

    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */
    void set_current_uri(std::string uri);
    int value(const std::string& uri, int line, int character, std::string&);
    int postion(std::string&, std::vector<ElementInfo>&);
    int search_key(const std::string&, std::vector<ElementInfo>&);

    int search_ns(const std::string&, std::vector<ElementInfo>&);
    int search_ns_field(std::uint32_t line, std::vector<ElementInfo>&);

    int search_ns_fields(const std::string&, std::vector<ElementInfo>&);

    int search_import_path(const std::string&, std::vector<ElementInfo>&);
    int search_union_fields(const std::string&, std::vector<ElementInfo>&);
    void save_element(ElementInfoType&);
    std::string real_uri(const std::string& uri);
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */
    void init(std::string uri);

    /* =============  DATA MEMBERS  =================== */

    LspLsif _ll;

    std::string _current_uri = "";

    std::vector<std::string> _project_lib;
}; /* -----  end of class DBEvent  ----- */

}  // namespace e2
#endif /* ----- #ifndef DBEVENT_INC  ----- */
