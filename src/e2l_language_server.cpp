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
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "assembler/BaseType.hpp"
#include "ast/ParserCtx.hpp"
#include "lsp-server/IoEventLoop.hpp"
#include "lsp-server/LspLsif.hpp"
#include "lsp-server/e2lsp.hpp"
using namespace e2;
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  lsp
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void lsp()
{
    std::cout << "Content-Type: application/vscode-jsonrpc; charset=utf-8\r\n";
    std::cout.flush();  // 有些客户SWITCH端需要这个头

    while (true) {
        std::string messageStr = readLSPMessage();
        if (messageStr.empty()) {
            std::ofstream outf("/tmp/lsp.log");
            outf << "Clicked on qqqq empty!" << "\n";
            outf.close();
            break;
        }
        std::cerr << " e2log " << messageStr << std::endl;
        auto message = e2_json::parse(messageStr);

        // 处理请求（有 id 字段）
        if (message.contains("id")) {
            e2_json response = {{"jsonrpc", "2.0"}, {"id", message["id"]}};
            std::ofstream outf("/tmp/lsp.log");
            outf << "Clicked inininitt qqqq!" << "\n";
            outf.close();
            std::string method = message["method"];
            if (method == "initialize") {
                response["result"] = handleInitialize(message["params"]);
            }
            else if (method == "textDocument/didOpen") {
                std::ofstream outf("/tmp/lsp.log");
                outf << "Clicked on qqqq!" << "\n";
                outf.close();
            }
            else if (method == "textDocument/definition") {
                response["result"] = handleDefinition(message["params"]);
            }
            else {
                // 对于不支持的请求，返回错误
                response["error"] = {{"code", -32601},
                                     {"message", "Method not found"}};
            }

            // 发送响应
            sendLSPMessage(response.dump());
        }
        // 处理通知（无 id 字段，如 didOpen）
        else if (message["method"] == "textDocument/didOpen") {
            handleDidOpen(message["params"]);

            std::ofstream outf("/tmp/lsp.log");
            outf << "Clicked inininitt didopen!" << "\n";
            outf.close();
        }
        else if (message["method"] == "initialized") {
            std::ofstream outf("/tmp/lsp.log");
            outf << "Clicked on qqqq init!" << messageStr << "\n";
            outf.close();
            // 客户端在 initialize 后发送 initialized 通知，通常无需特殊处理
        }
    }
} /* -----  end of function lsp  ----- */

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
 *         Name:  mPoll
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void mPoll()
{
    const int BUFFER_SIZE = 256;
    const int TIMEOUT_MS = 10000;  // 3秒超时

    // 1. 创建管道
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 2. 初始化 pollfd 数组——监控两个文件描述符
    struct pollfd fds[2];

    // 第一个元素：标准输入
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[0].revents = 0;

    // 第二个元素：管道读端
    fds[1].fd = pipefd[0];
    fds[1].events = POLLIN;
    fds[1].revents = 0;

    std::cout << "监控标准输入和管道读端，超时 " << TIMEOUT_MS << " 毫秒..."
              << std::endl;
    std::cout << "在另一个终端运行: echo \"hello\" >> /proc/" << getpid()
              << "/fd/" << pipefd[1] << std::endl;

    // 3. 调用 poll()——相比 select()，poll() 无需重建 fd 集合，内核只覆盖
    // revents 字段 [1](@ref)[2](@ref)
    int ret = poll(fds, 2, TIMEOUT_MS);

    // 4. 处理返回值
    if (ret == -1) {
        std::cerr << "poll 错误: " << strerror(errno) << std::endl;
        close(pipefd[0]);
        close(pipefd[1]);
        exit(EXIT_FAILURE);
    }
    else if (ret == 0) {
        std::cout << "超时！" << TIMEOUT_MS << " 毫秒内无数据" << std::endl;
    }
    else {
        std::cout << ret << " 个文件描述符就绪" << std::endl;

        // 5. 遍历数组，检查每个 fd 的 revents
        for (int i = 0; i < 2; ++i) {
            if (fds[i].revents & POLLIN) {
                char buffer[BUFFER_SIZE];
                std::size_t bytes_read =
                    read(fds[i].fd, buffer, BUFFER_SIZE - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    std::cout << "从 fd=" << fds[i].fd << " 读取: " << buffer
                              << std::endl;
                }
            }
            // 检查错误或挂起事件
            if (fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                std::cout << "fd=" << fds[i].fd << " 发生错误或连接关闭"
                          << std::endl;
            }
        }
    }

    // 6. 清理资源
    close(pipefd[0]);
    close(pipefd[1]);

} /* -----  end of function mPoll  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  mPollLoop
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void mPollLoop()
{
    IoEventLoop loop;
    loop.add_read_fd(STDIN_FILENO, [&](int fd) {
        char buffer[1024];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            std::cout << "Read Event Triggered! Data received: " << buffer;

            // Check for exit condition
            if (std::string(buffer).find("exit") != std::string::npos) {
                std::cout << "Exit command detected. Stopping loop...\n";
                loop.stop();
            }
        }
        else if (bytes_read == 0) {
            std::cout << "EOF detected on stdin.\n";
            loop.stop();
        }
    });

    loop.run();

} /* -----  end of function mPollLoop  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  testjson
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void testjson()
{
    LifecycleMsg life;
    // lif.Initialize();

    e2_json response = {{"jsonrpc", "2.0"}, {"id", 1}};

    response["result"] = life.Initialize();
    std::cout << response.dump(4) << std::endl;

} /* -----  end of function testjson  ----- */

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
void yyltoken(const char* fps)
{
    ParserCtx ctx;
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

    // // 查询（回调函数方式）
    // static int callback(void* data, int argc, char** argv, char** colName)
    // {
    //     for (int i = 0; i < argc; i++) {
    //         std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL")
    //                   << std::endl;
    //     }
    //     std::cout << "--------" << std::endl;
    //     return 0;
    // }
    //

    std::deque<LocationType> mods = ctx.imports();

    for (auto mod : mods) {
        llog::info("mod name:", mod.mod_name, " code line:", mod.code_line,
                   " path:", mod.code_path);
        ret = ctx.findPath(mod.mod_name.c_str());
        if (ret == -1) {
            llog::bug("not found file:", mod.mod_name);
        }
    }

    ElementInfoType eit = ctx.element_data();
    LspLsif ll;

    for (auto value : eit) {
        ll.clear(value.first);
        ll.batchInsert(value.second);
    }

    std::vector<ElementInfo> ei;
    auto fun = [](void* data, int argc, char** argv, char** colName) -> int {
        auto* result = static_cast<std::vector<ElementInfo>*>(data);
        ElementInfo _ei;
        for (int i = 0; i < argc; i++) {
            // std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL")
            //           << std::endl;
            std::string col = std::string(colName[i]);
            if (col == "e2lfile") {
                _ei.code_path = (argv[i] ? std::string(argv[i]) : "");
            }
            if (col == "value") {
                _ei.value = (argv[i] ? std::string(argv[i]) : "");
            }
            if (col == "code") {
                _ei.insertText = (argv[i] ? std::string(argv[i]) : "");
            }
        }
        result->push_back(_ei);

        //        std::cout << "--------" << std::endl;
        return 0;
    };  // -----  end lambda  -----
    std::string imports = "imp";
    std::string sql = llog::format(
        "select e2lfile, value,code from e2lsp where value like \"%s%%\" ",
        imports.c_str());
    std::cout << sql << std::endl;

    ll.query(sql, fun, &ei);

    for (auto k : ei) {
        std::cout << "code :" << k.code_path << " value:" << k.value
                  << std::endl;
    }
} /* -----  end of function yyltoken  ----- */

/*
 * ===  FUNCTION  =============================
 *         Name:  main
 *  Description:
 * ============================================
 */
int main(int argc, char* argv[])
{
    if (argc > 1) {
        yyltoken(argv[1]);
        // mPoll();
        // mPollLoop();
    }
    else {
        lspt();
    }

    //    testjson();

    // lsp();
    return EXIT_SUCCESS;
} /* ----------  end of function main  ---------- */
