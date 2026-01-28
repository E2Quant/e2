/*
 * =====================================================================================
 *
 *       Filename:  E2Graph.cpp
 *
 *    Description: E2Graph
 *
 *        Version:  1.0
 *        Created:  2026/01/23 10时33分48秒
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
#include <algorithm>
#include <call_graph/E2Graph.hpp>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"
#include "utility/Log.hpp"
namespace e2 {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2Graph::E2Graph
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
E2Graph::E2Graph() {} /* -----  end of function E2Graph::E2Graph  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2Graph::addFuncAndCall
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void E2Graph::addFuncAndCall(llvm::Function* func)
{
    std::vector<llvm::Function*> call;
    FuncAndCallType fact;
    fact.func = func;
    _FuncData.push_front(fact);

} /* -----  end of function E2Graph::addFuncAndCall  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2Graph::addCall
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void E2Graph::addCall(llvm::Function* call)
{
    if (_FuncData.front().call.size() == 0) {
        _FuncData.front().call.push_back(call);
        return;
    }
    auto rest = std::find(std::begin(_FuncData.front().call),
                          std::end(_FuncData.front().call), call);
    if (rest != std::end(_FuncData.front().call)) {
        return;
    }

    _FuncData.front().call.push_back(call);
} /* -----  end of function E2Graph::addCall  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2Graph::existFunc
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool E2Graph::existFunc(llvm::Function* func)
{
    for (auto it : _FuncData) {
        if (func == it.func) {
            return true;
        }
    }
    return false;
} /* -----  end of function E2Graph::existFunc  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2Graph::getFunc
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::vector<llvm::Function*> E2Graph::getFunc(llvm::Function* func)
{
    for (auto it : _FuncData) {
        if (func == it.func) {
            return it.call;
        }
    }
    std::vector<llvm::Function*> v;
    return v;
} /* -----  end of function E2Graph::getFunc  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2Graph::printGraph
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void E2Graph::printGraph(std::string name)
{
    std::string graphFileName = e2::llog::format("%s.text", name.c_str());
    std::string graphFileNameDot = e2::llog::format("%s.dot", name.c_str());
    std::ofstream graphFile, graphDot;
    graphFile.open(graphFileName);
    graphDot.open(graphFileNameDot);
    graphDot << "digraph G {"
             << "\n";

    std::string call_name = "";
    std::string func_name = "";
    for (auto const& func_call : _FuncData) {
        graphFile << e2::llog::format("[%s]:",
                                      func_call.func->getName().str().c_str());
        func_name = func_call.func->getName().str();

        while (func_name.find("_") != std::string::npos) {
            std::replace(func_name.begin(), func_name.end(), '_', ':');
        }
        unsigned int count = 0;
        for (auto const callId : func_call.call) {
            call_name = callId->getName().str();

            while (call_name.find("_") != std::string::npos) {
                std::replace(call_name.begin(), call_name.end(), '_', ':');
            }

            if (call_name.find("#") != std::string::npos) {
                graphDot << e2::llog::format(
                    "\"%s\" -> \"%s:self\";\n", func_name.c_str(),
                    call_name.substr(0, call_name.length() - 2).c_str());
            }
            else if (call_name.find("-") != std::string::npos) {
                graphDot << e2::llog::format("\"%s\" -> \"%s\";\n",
                                             func_name.c_str(),
                                             call_name.substr(1).c_str());
            }
            else {
                graphDot << e2::llog::format("\"%s\" -> \"%s\";\n",
                                             func_name.c_str(),
                                             call_name.c_str());
            }

            if (count != func_call.call.size() - 1) {
                graphFile << ",";
            }

            graphFile << e2::llog::format("[%s]\n",
                                          callId->getName().str().c_str());
            count++;
        }
        graphFile << "\n";
    }

    graphDot << "}";

    graphFile.close();
    graphDot.close();
    displayBanner(name);

} /* -----  end of function E2Graph::printGraph  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2Graph::displayBanner
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void E2Graph::displayBanner(std::string name)
{
    llvm::errs() << "Graphical Graph: xdot " << name
                 << ".dot\nText Format: gedit " << name << ".txt\n";

} /* -----  end of function E2Graph::displayBanner  ----- */
}  // namespace e2
