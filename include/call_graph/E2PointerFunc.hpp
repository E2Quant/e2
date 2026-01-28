/*
 * =====================================================================================
 *
 *       Filename:  E2PointerFunc.hpp
 *
 *    Description:  E2PointerFunc
 *
 *        Version:  1.0
 *        Created:  2026/01/23 10时18分28秒
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

#ifndef E2PointerFunc_INC
#define E2PointerFunc_INC
#include <cstddef>
#include <list>
#include <map>

#include "call_graph/E2Graph.hpp"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
namespace e2 {

/*
 * ================================
 *        Class:  E2PointerFunc
 *  Description:
 * ================================
 */
class E2PointerFunc {
public:
    /* =============  LIFECYCLE     =================== */
    E2PointerFunc(); /* constructor */

    /* =============  ACCESSORS     =================== */
    void pointsTo(llvm::Value* from, llvm::Value* to);
    void addToInstrList(llvm::Instruction* inst);
    void processInstrList(E2Graph*);
    std::size_t getInstrListSize();

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */
    llvm::Function* loopPoints(llvm::Function* val, E2Graph* p,
                               std::vector<llvm::Function*>& functionSet);

    std::vector<llvm::Function*> getPointsToFunc(llvm::Function* val,
                                                 E2Graph* p);
    /* =============  DATA MEMBERS  =================== */
    std::list<llvm::Instruction*> _InstrList;

    std::map<llvm::Value*, std::vector<llvm::Value*>> _pointToList;

}; /* -----  end of class E2PointerFunc  ----- */

}  // namespace e2
#endif /* ----- #ifndef E2PointerFunc_INC  ----- */
