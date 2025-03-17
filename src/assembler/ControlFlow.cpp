/*
 * =====================================================================================
 *
 *       Filename:  ControlFlow.cpp
 *
 *    Description:  ControlFlow
 *
 *        Version:  1.0
 *        Created:  2023年11月08日 11时39分02秒
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

#include "assembler/ControlFlow.hpp"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include <cstddef>

namespace e2 {
#define BBLock(bname, fun)                                                 \
    ({                                                                     \
        llvm::BasicBlock* _bblock;                                         \
        do {                                                               \
            _bblock = llvm::BasicBlock::Create(context.getGlobalContext(), \
                                               bname, fun);                \
        } while (0);                                                       \
        _bblock;                                                           \
    })
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LabledBlock::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* LabledBlock::codeGen(CodeGenContext& context)
{
    return nullptr;
} /* -----  end of function LabledBlock::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  IFStatement::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* IFStatement::codeGen(CodeGenContext& context)
{
    llvm::Value* ret = nullptr;
    llvm::Value* comp = nullptr;

    if (_exp != nullptr) {
        if (_exp->getType() != NodeType::_comp) {
            _Comp = MALLOC(CompOperator, _exp, _codeLine, _path.c_str());
        }
        else {
            _Comp = dynamic_cast<CompOperator*>(_exp);
        }
    }
    if (_Comp == nullptr) {
        context.DontRun();
        e2::log::bug("condition is nullptr");
        return nullptr;
    }
    comp = _Comp->codeGen(context);
    //  解决   _cond2 = arg < _var;  这样会返回大于 0 的值
    //  如果不是 bool 类型就转一下 bool 类型

    if (comp == nullptr) {
        if (_Comp->id() != nullptr) {
            e2::log::bug("comp value is nullptr, comp id:", _Comp->id()->name(),
                         " codeline:", _codeLine, " path:", _path);
        }
        else {
            e2::log::bug("comp values error, codeline:", _codeLine,
                         " path:", _path);
        }

        context.DontRun();
        return nullptr;
    }

    ToBool(comp, context);

    if (_labledBlock == nullptr) {
        e2::log::bug("labed block value is nullptr");

        return nullptr;
    }

    llvm::Function* TheFunction = context.currentBlock()->getParent();

    llvm::BasicBlock* thenBlock = BBLock("then", TheFunction);

    llvm::BasicBlock* elseBlock = BBLock("else", nullptr);

    llvm::BasicBlock* mergeBlock = BBLock("end", nullptr);

    llvm::BasicBlock* breakBB = context.currentBreak();
    bool brk = false;
    context.currentBreak(mergeBlock);

    llvm::BranchInst::Create(thenBlock, elseBlock, comp,
                             context.currentBlock());

    bool needMergeBlock = false;
    Selection se = _labledBlock->selection(0);
    if (se != Selection::_then) {
        e2::log::bug("then error");

        return nullptr;
    }
    Block* Then = _labledBlock->block(0);

    context.pushBlock(thenBlock, ScopeKind::_sk_flow);

    if (Then != nullptr) {
        Then->codeGen(context);

        ret = context.getCurrentReturnValue();
        if (ret != nullptr) {
            llvm::ReturnInst::Create(context.getGlobalContext(), ret,
                                     context.currentBlock());
        }

        brk = context.isBreakPoint();
        if (brk && breakBB != nullptr) {
            llvm::BranchInst::Create(breakBB, context.currentBlock());
            context.setBreakPoint(false);
        }
    }

    if (context.currentBlock()->getTerminator() == nullptr) {
        llvm::BranchInst::Create(mergeBlock, context.currentBlock());
        needMergeBlock = true;
    }

    TheFunction->getBasicBlockList().push_back(elseBlock);
    context.popBlock();

    context.pushBlock(elseBlock, ScopeKind::_sk_flow);
    if (_labledBlock != nullptr && _labledBlock->size() == 2) {
        se = _labledBlock->selection(1);
        if (se == Selection::_else) {
            Block* Else = _labledBlock->block(1);
            if (Else != nullptr) {
                Else->codeGen(context);

                ret = context.getCurrentReturnValue();
                if (ret != nullptr) {
                    llvm::ReturnInst::Create(context.getGlobalContext(), ret,
                                             context.currentBlock());
                }
                brk = context.isBreakPoint();
                if (brk && breakBB != nullptr) {
                    llvm::BranchInst::Create(breakBB, context.currentBlock());
                    context.setBreakPoint(false);
                }
            }
        }
    }

    if (context.currentBlock()->getTerminator() == nullptr) {
        llvm::BranchInst::Create(mergeBlock, context.currentBlock());
        needMergeBlock = true;
    }
    context.popBlock();

    if (needMergeBlock) {
        TheFunction->getBasicBlockList().push_back(mergeBlock);
        context.setInsertPoint(mergeBlock);
    }

    context.popBreak();

    return mergeBlock;

} /* -----  end of function IFStatement::codeGen  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  SwitchStatement::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* SwitchStatement::codeGen(CodeGenContext& context)
{
    return nullptr;
} /* -----  end of function SwitchStatement::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  IterStatement::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* IterStatement::codeGen(CodeGenContext& context)
{
    llvm::Value* ptr = nullptr;
    switch (_it) {
        case IterType::_while:
            ptr = IterWhile(context);
            break;
        case IterType::_forfull:
        case IterType::_for:
            ptr = IterFor(context);
            break;
        default:
            break;
    }
    return ptr;
} /* -----  end of function IterStatement::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  IterStatement::IterWhile
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* IterStatement::IterWhile(CodeGenContext& context)
{
    llvm::Function* function = context.currentBlock()->getParent();

    llvm::BasicBlock* firstCondBlock = BBLock("firstcond", function);
    llvm::BasicBlock* condBB = BBLock("cond", nullptr);
    llvm::BasicBlock* loopBB = BBLock("loop", nullptr);
    llvm::BasicBlock* jumpBB = BBLock("jump", nullptr);
    llvm::BasicBlock* mergeBB = BBLock("merge", nullptr);

    llvm::BranchInst::Create(firstCondBlock, context.currentBlock());

    /// enter while first cond
    context.pushBlock(firstCondBlock, ScopeKind::_sk_flow);
    llvm::Value* firstCondValue = _condition->codeGen(context);
    if (firstCondValue == nullptr) {
        e2::log::bug("Missing condition in while loop.");
        return nullptr;
    }

    ToBool(firstCondValue, context);

    llvm::BranchInst::Create(loopBB, jumpBB, firstCondValue,
                             context.currentBlock());

    function->getBasicBlockList().push_back(condBB);
    context.popBlock();
    ///

    /// while check cond
    context.pushBlock(condBB, ScopeKind::_sk_flow);
    llvm::Value* condValue = _condition->codeGen(context);
    if (condValue == nullptr) {
        e2::log::bug("Code gen for condition expression in while loop failed.");
        return nullptr;
    }
    ToBool(condValue, context);

    llvm::BranchInst::Create(loopBB, mergeBB, condValue,
                             context.currentBlock());

    function->getBasicBlockList().push_back(loopBB);
    context.popBlock();
    ///

    /// block codeGen
    context.pushBlock(loopBB, ScopeKind::_sk_flow);
    llvm::Value* loopValue = _block->codeGen(context);
    if (loopValue == nullptr) {
        e2::log::bug("Code gen for loop value in while loop failed.");
        return nullptr;
    }
    llvm::BranchInst::Create(condBB, context.currentBlock());

    function->getBasicBlockList().push_back(jumpBB);
    context.popBlock();

    /// jump break
    context.pushBlock(jumpBB, ScopeKind::_sk_flow);
    llvm::BranchInst::Create(mergeBB, context.currentBlock());
    function->getBasicBlockList().push_back(mergeBB);

    context.popBlock();

    context.setInsertPoint(mergeBB);

    return mergeBB;

} /* -----  end of function IterStatement::IterWhile  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  IterStatement::IterFor
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* IterStatement::IterFor(CodeGenContext& context)
{
    if (_initial == nullptr) {
        e2::log::bug("initial is null");
        return nullptr;
    }

    llvm::Function* function = context.currentBlock()->getParent();

    _initial->codeGen(context);
#ifdef E2L_DEBUG
    e2::log::info("initial is ok -------------");
#endif
    llvm::BasicBlock* firstCondBlock = BBLock("firstcond", function);
    llvm::BasicBlock* condBB = BBLock("cond", nullptr);
    llvm::BasicBlock* loopBB = BBLock("loop", nullptr);
    llvm::BasicBlock* breakBB = BBLock("break", nullptr);
    llvm::BasicBlock* mergeBB = BBLock("merge", nullptr);

    llvm::BranchInst::Create(firstCondBlock, context.currentBlock());

    ///// enter
    context.pushBlock(firstCondBlock, ScopeKind::_sk_flow);
    llvm::Value* firstCondValue = _condition->codeGen(context);
    if (firstCondValue == nullptr) {
        e2::log::bug("Missing condition in while loop.");
        return nullptr;
    }
    ToBool(firstCondValue, context);

#ifdef E2L_DEBUG
    e2::log::info("firstCondValue is ok -------------");
#endif
    llvm::BranchInst::Create(loopBB, breakBB, firstCondValue,
                             context.currentBlock());

    function->getBasicBlockList().push_back(condBB);
    context.popBlock();
    ////

    /// check cond agent
    context.pushBlock(condBB, ScopeKind::_sk_flow);
    llvm::Value* condValue = _condition->codeGen(context);
    if (condValue == nullptr) {
        e2::log::bug("Code gen for condition expression in while loop failed.");
        return nullptr;
    }
    ToBool(condValue, context);

#ifdef E2L_DEBUG
    e2::log::info("agent CondValue is ok -------------");
#endif
    llvm::BranchInst::Create(loopBB, mergeBB, condValue,
                             context.currentBlock());

    function->getBasicBlockList().push_back(loopBB);
    context.popBlock();
    ///

    /// block
    context.pushBlock(loopBB, ScopeKind::_sk_flow);
    llvm::Value* loopValue = _block->codeGen(context);
    if (loopValue == nullptr) {
        e2::log::bug("Code gen for loop value in while loop failed.");
        return nullptr;
    }

    if (_range != nullptr) {
        _range->codeGen(context);
    }

    llvm::BranchInst::Create(condBB, context.currentBlock());

    function->getBasicBlockList().push_back(breakBB);
    context.popBlock();

    // break
    context.pushBlock(breakBB, ScopeKind::_sk_flow);

    llvm::BranchInst::Create(mergeBB, context.currentBlock());
    function->getBasicBlockList().push_back(mergeBB);
    context.popBlock();

    context.setInsertPoint(mergeBB);

    return mergeBB;
} /* -----  end of function IterStatement::IterFor  ----- */
}  // namespace e2
