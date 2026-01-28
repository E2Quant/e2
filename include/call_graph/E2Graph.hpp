/*
 * =====================================================================================
 *
 *       Filename:  E2Graph.hpp
 *
 *    Description:  E2Graph
 *
 *        Version:  1.0
 *        Created:  2026/01/23 10时23分11秒
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

#ifndef E2GRAPH_INC
#define E2GRAPH_INC
#include <list>
#include <map>
#include <vector>

#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
namespace e2 {

struct __FuncCall {
    llvm::Function* func;
    std::vector<llvm::Function*> call;
}; /* ----------  end of struct __FuncCall  ---------- */

typedef struct __FuncCall FuncAndCallType;
/*
 * ================================
 *        Class:  E2Graph
 *  Description:
 * ================================
 */
class E2Graph {
public:
    /* =============  LIFECYCLE     =================== */
    E2Graph(); /* constructor */
    /* =============  ACCESSORS     =================== */
    void addFuncAndCall(llvm::Function* func);
    void addCall(llvm::Function* call);
    void printGraph(std::string name);
    void displayBanner(std::string name);
    bool existFunc(llvm::Function* func);
    std::vector<llvm::Function*> getFunc(llvm::Function* func);
    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    std::list<FuncAndCallType> _FuncData;
}; /* -----  end of class E2Graph  ----- */

}  // namespace e2
#endif /* ----- #ifndef E2GRAPH_INC  ----- */
