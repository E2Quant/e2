/*
 * =====================================================================================
 *
 *       Filename:  E2PointerFunc.cpp
 *
 *    Description:  E2PointerFunc
 *
 *        Version:  1.0
 *        Created:  2026/01/23 13时57分42秒
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
#include <call_graph/E2PointerFunc.hpp>
#include <cstddef>
#include <vector>

#include "call_graph/E2Graph.hpp"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/Casting.h"
namespace e2 {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2PointerFunc::E2PointerFunc
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
E2PointerFunc::E2PointerFunc() {

} /* -----  end of function E2PointerFunc::E2PointerFunc  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2PointerFunc::pointsTo
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void E2PointerFunc::pointsTo(llvm::Value* from, llvm::Value* to)
{
    if (_pointToList.count(from) == 0) {
        std::vector<llvm::Value*> tos;
        tos.push_back(to);
        _pointToList.insert({from, tos});
    }
    else {
        _pointToList[from].push_back(to);
    }
} /* -----  end of function E2PointerFunc::pointsTo  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2PointerFunc::addToInstrList
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void E2PointerFunc::addToInstrList(llvm::Instruction* inst)
{
    _InstrList.push_back(inst);
} /* -----  end of function E2PointerFunc::addToInstrList  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2PointerFunc::processInstrList
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void E2PointerFunc::processInstrList(E2Graph* graph)
{
    while (!_InstrList.empty()) {
        llvm::Instruction* inst = _InstrList.front();
        if (isa<llvm::CallInst>(inst)) {
            llvm::CallInst* callInst = dyn_cast<llvm::CallInst>(inst);

            std::vector<llvm::Function*> funcSet =
                getPointsToFunc(callInst->getFunction(), graph);

            graph->addFuncAndCall(callInst->getFunction());
            for (auto f : funcSet) {
                graph->addCall(f);
            }
        }

        _InstrList.pop_front();
    }

} /* -----  end of function E2PointerFunc::processInstrList  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2PointerFunc::getInstrListSize
 *  ->  void *
 *  Parameters:

 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::size_t E2PointerFunc::getInstrListSize()
{
    std::size_t ret = _InstrList.size();
    return ret;
} /* -----  end of function E2PointerFunc::getInstrListSize  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2PointerFunc::loopPoints
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Function* E2PointerFunc::loopPoints(
    llvm::Function* val, E2Graph* p, std::vector<llvm::Function*>& functionSet)

{
    if (p->existFunc(val)) {
        return val;
    }

    std::vector<llvm::Value*> values = _pointToList[val];
    for (llvm::Value* v : values) {
        if (v->getType()->isFunctionTy()) {
            llvm::Function* vf = llvm::dyn_cast<llvm::Function>(v);
            llvm::Function* func = loopPoints(vf, p, functionSet);
            if (func != nullptr) {
                functionSet.push_back(func);
            }
        }
    }
    return nullptr;

} /* -----  end of function E2PointerFunc::loopPoints  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  E2PointerFunc::getPointsToFunc
 *  ->  void *, bool existfunc
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::vector<llvm::Function*> E2PointerFunc::getPointsToFunc(llvm::Function* val,
                                                            E2Graph* p)
{
    std::vector<llvm::Function*> funcSet;
    loopPoints(val, p, funcSet);
    return funcSet;
} /* -----  end of function E2PointerFunc::getPointsToFunc  ----- */
}  // namespace e2
