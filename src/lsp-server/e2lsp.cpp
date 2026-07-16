/*
 * =====================================================================================
 *
 *       Filename:  e2lsp.cpp
 *
 *    Description:  e2lsp
 *
 *        Version:  1.0
 *        Created:  2026/04/24 14时36分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vyouzhi (vz), vyouzhi@gmail.com
 *   Organization:  Etomc2.com
 *        LICENSE: BSD-3-Clause license
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
#include "lsp-server/e2lsp.hpp"

#include <iostream>

#include "nlohmann/json.hpp"
namespace e2 {

// 从 stdin 读取一条完整的 LSP 消息
std::string readLSPMessage()
{
    std::string header;
    // 读取直到遇到两个连续的换行符（即空行）
    while (std::getline(std::cin, header) && !header.empty()) {
        std::cout << "header:" << header << std::endl;
        // 解析 Content-Length
        if (header.find("Content-Length:") == 0) {
            size_t contentLength = std::stoi(header.substr(16));
            // 读取两个换行符（\r\n\r\n 中的第二部分）
            std::cin.get();  // 读取一个字符，通常是 '\r' 或 '\n'
            std::cin.get();  // 再读取一个字符
            // 根据长度读取 JSON 主体
            std::string body(contentLength, '\0');
            std::cin.read(&body[0], contentLength);
            return body;
        }
    }
    return "";
}
// 发送 LSP 格式消息到 stdout
void sendLSPMessage(const std::string& jsonStr)
{
    std::cout << "Content-Length: " << jsonStr.size() << "\r\n\r\n" << jsonStr;
    std::cout.flush();
}

json handleInitialize(const json& params)
{
    json response = {{"capabilities",
                      {
                          {"definitionProvider", true},  // 声明支持跳转到定义
                          // 可以在此添加其他支持的能力，如
                          // textDocumentSync、hoverProvider 等
                      }}};
    return response;
}

void handleDidOpen(const json& params)
{
    std::string uri = params["textDocument"]["uri"];
    std::string text = params["textDocument"]["text"];
    openDocuments[uri] = text;

    std::cout << "uri:" << uri << "  text:" << text << std::endl;
    // 此处可以触发初步的语法分析或诊断
}

json handleDefinition(const json& params)
{
    std::string uri = params["textDocument"]["uri"];
    int line = params["position"]["line"];
    int character = params["position"]["character"];
    std::cout << "uri:" << uri << "  line:" << line << " char:" << character
              << std::endl;

    json result = json::array();  // 定义可能返回多个位置，以数组形式

    // 极简示例：如果请求的是 main.cpp 中 loopPrint 的调用，则跳转到
    // loopPrint.cpp
    // if (uri.find("main.cpp") != std::string::npos && line == 2 &&
    //     character == 2) {
    //     json location = {{"uri",
    //     "file:///path/to/your/project/loopPrint.cpp"},
    //                      {"range",
    //                       {{"start", {{"line", 2}, {"character", 5}}},
    //                        {"end", {{"line", 2}, {"character", 14}}}}}};
    //     result.push_back(location);
    // }
    return result;
}

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LSPTransport::read_message
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
LSPMessage LSPTransport::read_message()
{
    LSPMessage msg;

    std::string header;
    std::getline(std::cin, header);  // "Content-Length: X"
    int length = 10;
    //    int length = parseContentLength(header);
    std::cin.ignore(2);  // 忽略 \r\n

    std::string body(length, '\0');
    std::cin.read(&body[0], length);
    return msg;
    //    return nlohmann::json::parse(msg);
} /* -----  end of function LSPTransport::read_message  ----- */

}  // namespace e2
