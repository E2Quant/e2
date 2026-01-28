/*
 * =====================================================================================
 *
 *       Filename:  E2CallGraph.hpp
 *
 *    Description:  E2CallGraph
 *
 *        Version:  1.0
 *        Created:  2026/01/23 10时11分12秒
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

#ifndef E2CALLGRAPH_INC
#define E2CALLGRAPH_INC
#include "call_graph/E2Graph.hpp"
#include "call_graph/E2PointerFunc.hpp"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Pass.h"
#include "llvm/Target/TargetMachine.h"
namespace e2 {

struct E2CallGraphPass : public llvm::ModulePass {
    static char ID;

    E2Graph* callgraph = new E2Graph();
    E2PointerFunc* pointerFunc = new E2PointerFunc();

    E2CallGraphPass() : ModulePass(ID) {}

    void getAnalysisUsage(llvm::AnalysisUsage& AU) const override
    {
        AU.setPreservesAll();
    }

    virtual bool runOnModule(llvm::Module& M) override
    {
        for (llvm::Function& Func : M) {
            callgraph->addFuncAndCall(&Func);

            for (llvm::BasicBlock& BB : Func) {
                for (llvm::Instruction& Ins : BB) {
                    if (isa<llvm::StoreInst>(Ins)) {
                        llvm::StoreInst* storeInst =
                            llvm::dyn_cast<llvm::StoreInst>(&Ins);

                        llvm::Value* to =
                            storeInst->getValueOperand()->stripPointerCasts();

                        llvm ::Value* from =
                            storeInst->getPointerOperand()->stripPointerCasts();

                        // Add Points-To
                        pointerFunc->pointsTo(from, to);
                        // Add to Worklist
                        pointerFunc->addToInstrList(&Ins);
                        continue;
                    }
                    if (isa<llvm::LoadInst>(Ins)) {
                        llvm::LoadInst* loadInst =
                            llvm::dyn_cast<llvm::LoadInst>(&Ins);

                        llvm::Value* to =
                            loadInst->getPointerOperand()->stripPointerCasts();
                        llvm::Value* from = dyn_cast<llvm::Value>(loadInst);

                        // Add Points-To
                        pointerFunc->pointsTo(from, to);
                        // Add to Worklist
                        pointerFunc->addToInstrList(&Ins);
                        continue;
                    }

                    else if (isa<llvm::CallBase>(Ins)) {
                        llvm::CallBase* callBase =
                            llvm::dyn_cast<llvm::CallBase>(&Ins);

                        if (!callBase) {
                            // Maybe Indirect Call
                            pointerFunc->addToInstrList(&Ins);
                            continue;
                        }

                        // errs()<<*callInst;
                        if (callBase->isIndirectCall()) {
                            pointerFunc->addToInstrList(&Ins);
                            continue;
                        }
                        // Direct Call
                        llvm::Function* calleeFunc =
                            callBase->getCalledFunction();
                        if (calleeFunc->isIntrinsic())
                            continue;  // Ignored Function calls inserted by
                                       // LLVM

                        callgraph->addCall(calleeFunc);
                    }
                }
            }
        }

        return true;
    }

    virtual bool doFinalization(llvm::Module& M) override
    {
        pointerFunc->processInstrList(
            callgraph);  // resolve Pointers and modify the callgraph

        callgraph->printGraph("e2q");

        // Clean up
        delete callgraph;
        delete pointerFunc;
        return true;
    }

}; /* ----------  end of struct __E2CallGraphPass  ---------- */
char E2CallGraphPass::ID = 0;
static llvm::RegisterPass<E2CallGraphPass> X("E2CallGraphPass",
                                             "Call Grap Phass Generation");

}  // namespace e2
#endif /* ----- #ifndef E2CALLGRAPH_INC  ----- */
