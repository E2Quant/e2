/*
 * =====================================================================================
 *
 *       Filename:  e2lsp.hpp
 *
 *    Description:  e2lsp
 *
 *        Version:  1.0
 *        Created:  2026/04/24 14时34分33秒
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

#ifndef E2LSP_INC
#define E2LSP_INC
#include <map>
#include <string>

#include "nlohmann/json.hpp"
using json = nlohmann::json;
namespace e2 {

std::string readLSPMessage();
void sendLSPMessage(const std::string& jsonStr);

json handleInitialize(const json& params);

inline std::map<std::string, std::string> openDocuments;  // URI -> 内容

void handleDidOpen(const json& params);

json handleDefinition(const json& params);

struct LSPMessage {
    std::string jsonrpc;    // 固定为 "2.0"
    int id;                 // 请求 ID（可选）
    std::string method;     // 方法名
    nlohmann::json params;  // 参数
};

/*
 * ================================
 *        Class:  LSPTransport
 *  Description:
 * ================================
 */
class LSPTransport {
public:
    /* =============  LIFECYCLE     =================== */
    LSPTransport(); /* constructor */

    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */
    void send_response();
    void handle_message();
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */
    void initialize();
    LSPMessage read_message();

    void initialize_response();
    void complete_response();
    /* =============  DATA MEMBERS  =================== */

}; /* -----  end of class LSPTransport  ----- */

}  // namespace e2
#endif /* ----- #ifndef LSPTransport_INC  ----- */
