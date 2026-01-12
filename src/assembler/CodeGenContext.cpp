/*
 * =====================================================================================
 *
 *       Filename:  CodeGenContext.cpp
 *
 *    Description:  CodeGenContext
 *
 *        Version:  1.0
 *        Created:  2023年10月26日 17时37分25秒
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
#include "assembler/CodeGenContext.hpp"

#include <llvm/ADT/StringRef.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/Casting.h>
#include <string.h>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "E2L/E2LType.hpp"
#include "assembler/BaseNode.hpp"
#include "assembler/BaseType.hpp"
#include "assembler/ExternFunction.hpp"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include "utility/pack.hpp"

extern "C" {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  PrintStr
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   for e2l  FPrintCurrentPath
 * ============================================
 */

void PrintStr(const char* toPrint)
{
    if (toPrint) {
        fprintf(stderr, "{e2l file:[ %s ] }\n", toPrint);
    }
    else {
        fprintf(stderr, "::calll:NULL arg.\n");
    }
} /* -----  end of function PrintStr  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  version
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   print e2l version
 * ============================================
 */
void e2version()
{
    fprintf(stderr, "e2l version:%s\n", e2::version::version_full);
} /* -----  end of function version  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  GlobalUnion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void GlobalUnion()
{
    char* tokens = NULL;
    char* pre = NULL;
    char* str;
    char delim[] = ".";
    long val = 0;
    for (auto it = _GlobalVariables.begin(); it != _GlobalVariables.end();
         ++it) {
        val = it->second / NUMBER_DECI;
        str = strdup(it->first.c_str());

        if (str != NULL) {
            tokens = strtok(str, delim);
            if (pre == NULL) {
                pre = strdup(tokens);
                printf("union %s {\n", tokens);
            }
            if (strcmp(tokens, pre) != 0) {
                free(pre);
                pre = NULL;
                printf("}\n");
                printf("union %s {\n", tokens);
                pre = strdup(tokens);
            }

            while ((tokens = strtok(NULL, delim))) {
                printf("  %s = %ld;\n", tokens, val);
            }
            free(str);
        }
    }
    if (pre != NULL) {
        free(pre);
        pre = NULL;
    }
    printf("}\n");
} /* -----  end of function GlobalUnion  ----- */
}
namespace e2 {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::defType
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   defautl type
 * ============================================
 */
retType* CodeGenContext::defType()
{
    return E2LType(_llvmContext);
} /* -----  end of function CodeGenContext::defType  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenCotext::generateCode
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool CodeGenContext::generateCode(Block* root)
{
    if (root == nullptr) {
        e2::llog::bug("root is nullptr");

        return false;
    }

    std::string cname = "FPrintCurrentPath";
    ArgType sarg(1, E2LVoid(_llvmContext));
    ExternBuild(E2LVoid(_llvmContext), sarg, (void*)PrintStr, cname);

    std::string ver = "FVersion";
    ArgType varg(0, E2LVoid(_llvmContext));
    ExternBuild(E2LVoid(_llvmContext), varg, (void*)e2version, ver);

    std::string gl = "FGlobalUnion";
    ArgType garg(0, E2LVoid(_llvmContext));
    ExternBuild(E2LVoid(_llvmContext), garg, (void*)GlobalUnion, gl);

    std::vector<retType*> argTypes;
    argTypes.push_back(E2LType(_llvmContext));
    argTypes.push_back(E2LType(_llvmContext));
    int random_val = std::rand();
    llvm::FunctionType* ftype =
        llvm::FunctionType::get(E2LType(_llvmContext), argTypes, false);

    _mainFunction =
        llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage,
                               "main" + std::to_string(random_val), _module);

    if (_mainFunction == nullptr) {
        e2::llog::bug("_mainFunction is nullptr");
        return false;
    }

    llvm::Function::arg_iterator args = _mainFunction->arg_begin();
    llvm::Value* arg_0 = &*args++;
    arg_0->setName("argc");
    llvm::Value* arg_1 = &*args++;
    arg_1->setName("argv");

    llvm::BasicBlock* bblock = llvm::BasicBlock::Create(
        _llvmContext, "entry." + std::to_string(random_val), _mainFunction, 0);

#ifdef E2L_DEBUG
    if (bblock->hasName()) {
        llvm::StringRef bbname(bblock->getName());
        e2::llog::echo("main function name:", bbname.str());
    }
#endif

    InitGlobalVar();

    pushBlock(bblock, ScopeKind::_sk_main);
    root->codeGen(*this);

    if (currentBlock()->getTerminator() == nullptr) {
        llvm::ReturnInst::Create(_llvmContext, 0, currentBlock());
    }
    popBlock();

#ifdef E2L_DEBUG
    _debug = true;
#endif
    if (_debug) {
        llvm::verifyFunction(*_mainFunction, &llvm::errs());

        if (llvm::verifyModule(*_module, &llvm::errs())) {
            e2::llog::bug("module is error:");
        }
        else {
            e2::llog::info("module is verify ok");
        }
        _module->print(llvm::outs(), nullptr);
    }
    return _CanRun;
} /* -----  end of function CodeGenCotext::generateCode  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::runCode
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::runCode()
{
    /* #ifdef E2L_DEBUG */
    /*     toDebug(); */
    /* #endif */

    std::string err = "";
    _ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(_module))
              .setErrorStr(&err)
              .setEngineKind(llvm::EngineKind::JIT)
              .create();
    assert(_ee);

    for (auto efun : _ExternFunc) {
        _ee->addGlobalMapping(efun.fun, efun.addr);
    }
    if (!err.empty()) {
        e2::llog::echo("error:", err);
    }
    _ee->finalizeObject();

    // std::vector<llvm::GenericValue> noargs(1);
    //  llvm::GenericValue v = _ee->runFunction(_mainFunction, noargs);

    _function = (funPtr)_ee->getPointerToFunction(_mainFunction);

} /* -----  end of function CodeGenContext::runCode  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::Result
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::GenericValue CodeGenContext::Result()
{
    return _GenericRet;
} /* -----  end of function CodeGenContext::Result  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::runFunction
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */

Int_e CodeGenContext::runFunction(double arg1 = 0, double arg2 = 0)
{
    Int_e _arg1 = (Int_e)VALNUMBER(arg1);
    Int_e _arg2 = (Int_e)VALNUMBER(arg2);

    Int_e ret = _function(_arg1, _arg2);

    _GenericRet.IntVal = ret;
    return ret;
}

/* -----  end of function CodeGenContext::runFunction  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::currentBreak
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::currentBreak(llvm::BasicBlock* bb)
{
    _breakStack.push_front(bb);
} /* -----  end of function CodeGenContext::currentBreak  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::currentBreak
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::BasicBlock* CodeGenContext::currentBreak()
{
    if (_breakStack.size() == 0) {
        return nullptr;
    }
    llvm::BasicBlock* bb = _breakStack.front();

    return bb;
} /* -----  end of function CodeGenContext::currentBreak  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::popBreak
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::popBreak()
{
    if (_breakStack.size() == 0) {
        return;
    }
    _breakStack.pop_front();
} /* -----  end of function CodeGenContext::popBreak  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::setBreakPoint
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::setBreakPoint(bool b)
{
    _breakStat = b;
} /* -----  end of function CodeGenContext::setBreakPoint  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::isBreakPoint
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool CodeGenContext::isBreakPoint()
{
    return _breakStat;
} /* -----  end of function CodeGenContext::isBreakPoint  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::currentBlock
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::BasicBlock* CodeGenContext::currentBlock()
{
    if (_blockStack.size() == 0) {
        return nullptr;
    }
    return _blockStack.front()->block();
} /* -----  end of function CodeGenContext::currentBlock  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::currentScope
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
ScopeKind CodeGenContext::currentScope()
{
    return _blockStack.front()->scope();
} /* -----  end of function CodeGenContext::currentScope  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::pushBlock
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::pushBlock(llvm::BasicBlock* block, ScopeKind sc)
{
    if (block == nullptr) {
        block = llvm::BasicBlock::Create(_llvmContext, "scope");
    }
    _blockStack.push_front(MALLOC(CodeGenBlock, block, sc));

} /* -----  end of function CodeGenContext::pushBlock  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::popBlock
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::popBlock()
{
    CodeGenBlock* top = _blockStack.front();
    _blockStack.pop_front();

    RELEASE(top);

} /* -----  end of function CodeGenContext::popBlock  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::setInsertPoint
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::setInsertPoint(llvm::BasicBlock* block)
{
    _blockStack.front()->setCodeBlock(block);

} /* -----  end of function CodeGenContext::setInsertPoint  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::currentFuncName
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::currentFuncName(std::string func)
{
    _current_func_name = func;
} /* -----  end of function CodeGenContext::currentFuncName  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::currentFuncName
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::string CodeGenContext::currentFuncName()
{
    return _current_func_name;
} /* -----  end of function CodeGenContext::currentFuncName  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::locales
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
MapLocals& CodeGenContext::locals()
{
    return _blockStack.front()->local();
} /* -----  end of function CodeGenContext::locales  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::pushUnion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::pushUnion(std::string name)
{
    _union_name.push(name);
} /* -----  end of function CodeGenContext::pushUnion  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::topUnion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::string CodeGenContext::topUnion()
{
    std::string top = "";
    if (_union_name.size() > 0) {
        top = _union_name.top();
    }
    return top;
} /* -----  end of function CodeGenContext::topUnion  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::popUnion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::popUnion()
{
    if (_union_name.size() > 0) {
        _union_name.pop();
    }
} /* -----  end of function CodeGenContext::popUnion  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::MainArgxfunction_self_pop
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* CodeGenContext::MainArgx(size_t index)
{
    if (index >= _mainFunction->arg_size()) {
        return nullptr;
    }
    llvm::Argument* argx = _mainFunction->getArg(index);

    if (argx == nullptr) {
        llog::bug("argx is nullptr");
        return nullptr;
    }

    /* llvm::StringRef name(argx->getName()); */
    /* llog::echo("args:", name.str()); */

    return argx;
} /* -----  end of function CodeGenContext::MainArgx  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::setCurrentReturnValue
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::setCurrentReturnValue(llvm::Value* value)
{
    _blockStack.front()->setValue(value);
} /* -----  end of function CodeGenContext::setCurrentReturnValue  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::getCurrentReturnValue
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* CodeGenContext::getCurrentReturnValue()
{
    if (_blockStack.size() == 0) {
        //        llog::info("_break_stat size is 0");
        return nullptr;
    }
    return _blockStack.front()->getValue();
} /* -----  end of function CodeGenContext::getCurrentReturnValue  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::findBlockId
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::AllocaInst* CodeGenContext::findBlockId(const std::string name)
{
    ScopeKind current = ScopeKind::_sk_null;
    for (auto cb : _blockStack) {
        if (cb == nullptr) {
            continue;
        }
        auto cb_local = cb->local();
        ScopeKind sk = cb->scope();

        if (current == ScopeKind::_sk_null || sk == ScopeKind::_sk_fun) {
            current = sk;
        }
        if (current != sk) {
            break;
        }

        if (cb_local.find(name) != cb_local.end()) {
            return cb_local[name];
        }

        if (sk != ScopeKind::_sk_flow) {
            break;
        }
    }

    return nullptr;
} /* -----  end of function CodeGenContext::findBlockId  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::ExternBuild
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::ExternBuild(retType* ret, ArgType arg, void* fun,
                                 std::string& fname)
{
    llvm::FunctionType* ft = nullptr;

    if (arg.size() == 0) {
        ft = llvm::FunctionType::get(ret, true);
    }
    else {
        ft = llvm::FunctionType::get(ret, arg, false);
    }
    llvm::Function* f = llvm::Function::Create(
        ft, llvm::Function::ExternalLinkage, llvm::Twine(fname), _module);
    llvm::Function::arg_iterator i = f->arg_begin();
    if (i != f->arg_end())
        i->setName("val" + std::to_string(std::hash<std::string>{}(fname)));
    _ExternFunc.push_back({f, fun});

} /* -----  end of function CodeGenContext::ExternBuild  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::ExternBuildInt
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::ExternBuildInt(void* fun, size_t args, std::string& fname,
                                    bool isVoid)
{
    ArgType arg;

    for (size_t m = 0; m < args; m++) {
        arg.push_back(E2LType(_llvmContext));
    }

    retType* ret = nullptr;
    if (isVoid) {
        ret = E2LVoid(_llvmContext);
    }
    else {
        ret = E2LType(_llvmContext);
    }
    ExternBuild(ret, arg, fun, fname);

} /* -----  end of function CodeGenContext::ExternBuildInt  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::ExternGlobalVar
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::ExternGlobalVar(const std::string& key, Int_e val)
{
    llvm::Constant* gvcon =
        llvm::ConstantInt::get(E2LType(getGlobalContext()), val);

    _module->getOrInsertGlobal(key, E2LType(getGlobalContext()));
    llvm::GlobalVariable* gVar = _module->getNamedGlobal(key);
    gVar->setLinkage(llvm::GlobalValue::InternalLinkage);
    gVar->setInitializer(gvcon);
} /* -----  end of function CodeGenContexname */

/*
 *  ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::InitGlobalVar
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::InitGlobalVar()
{
#ifndef E2L_DEBUG
    AddGlobal();
#endif

    for (auto it = _GlobalVariables.begin(); it != _GlobalVariables.end();
         ++it) {
        ExternGlobalVar(it->first, it->second);
    }
} /* -----  end of function CodeGenContext::InitGlobalVar  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::OutGlobalVar
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::OutGlobalVar(const std::string& name, Int_e val)
{
    ADD_GV(name, val);
} /* -----  end of function CodeGenContext::OutGlobalVar  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::AddGlobal
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::AddGlobal()
{
    ADD_GV("UNumber.NaN", 0);
    ADD_GV("UExecInst.Ei_Do_Not_Increase", ExecInst::ei_do_not_increase);
    ADD_GV("UExecInst.Ei_Do_Not_Reduce", ExecInst::ei_do_not_reduce);
    ADD_GV("UExecInst.Ei_All_Or_None", ExecInst::ei_all_or_none);

    ADD_GV("UTimeInForce.Tif_Day", TimeInForce::tif_day);
    ADD_GV("UTimeInForce.Tif_Good_Till_Cancel",
           TimeInForce::tif_good_till_cancel);
    ADD_GV("UTimeInForce.Tif_At_The_Opening", TimeInForce::tif_at_the_opening);
    ADD_GV("UTimeInForce.Tif_Immediate_Or_Cancel",
           TimeInForce::tif_immediate_or_cancel);
    ADD_GV("UTimeInForce.Tif_Fill_Or_Kill", TimeInForce::tif_fill_or_kill);
    ADD_GV("UTimeInForce.Tif_Good_Till_Crossing",
           TimeInForce::tif_good_till_crossing);
    ADD_GV("UTimeInForce.Tif_Good_Till_Date", TimeInForce::tif_good_till_date);
    ADD_GV("UTimeInForce.Tif_At_The_Close", TimeInForce::tif_at_the_close);

    ADD_GV("UOrdType.Ot_Market", OrdType::ot_market);
    ADD_GV("UOrdType.Ot_Limit", OrdType::ot_limit);
    ADD_GV("UOrdType.Ot_Stop", OrdType::ot_stop);
    ADD_GV("UOrdType.Ot_Stop_limit", OrdType::ot_stop_limit);

    ADD_GV("UExecType.NewOrder", ExecType::NewOrder);
    ADD_GV("UExecType.Done_For_The_Day", ExecType::Done_for_the_day);
    ADD_GV("UExecType.Canceled", ExecType::Canceled);
    ADD_GV("UExecType.Replaced", ExecType::Replaced);
    ADD_GV("UExecType.Stopped", ExecType::Stopped);
    ADD_GV("UExecType.Rejected", ExecType::Rejected);
    ADD_GV("UExecType.Pending_New", ExecType::Pending_New);
    ADD_GV("UExecType.Expired", ExecType::Expired);
    ADD_GV("UExecType.Restated", ExecType::Restated);
    ADD_GV("UExecType.Pending_Replace", ExecType::Pending_Replace);
    ADD_GV("UExecType.Trade", ExecType::Trade);
    ADD_GV("UExecType.Trade_Correct", ExecType::Trade_Correct);
    ADD_GV("UExecType.Trade_Cancel", ExecType::Trade_Cancel);
    ADD_GV("UExecType.Trigerred_Activated", ExecType::Trigerred_Activated);
    ADD_GV("UExecType.UNKONWN", ExecType::UNKONWN);

    ADD_GV("UOrdStatus.Ost_New", OrdStatus::ost_New);
    ADD_GV("UOrdStatus.Ost_Partially_Filled", OrdStatus::ost_Partially_filled);
    ADD_GV("UOrdStatus.Ost_Filled", OrdStatus::ost_Filled);
    ADD_GV("UOrdStatus.Ost_Done_For_Day", OrdStatus::ost_Done_for_day);
    ADD_GV("UOrdStatus.Ost_Canceled", OrdStatus::ost_Canceled);
    ADD_GV("UOrdStatus.Ost_Replaced", OrdStatus::ost_Replaced);
    ADD_GV("UOrdStatus.Ost_Pending_Cancel", OrdStatus::ost_Pending_Cancel);
    ADD_GV("UOrdStatus.Ost_Stopped", OrdStatus::ost_Stopped);
    ADD_GV("UOrdStatus.Ost_Rejected", OrdStatus::ost_Rejected);
    ADD_GV("UOrdStatus.Ost_Suspended", OrdStatus::ost_Suspended);
    ADD_GV("UOrdStatus.Ost_Pending_New", OrdStatus::ost_Pending_New);
    ADD_GV("UOrdStatus.Ost_Calculated", OrdStatus::ost_Calculated);
    ADD_GV("UOrdStatus.Ost_Expired", OrdStatus::ost_Expired);
    ADD_GV("UOrdStatus.Ost_Accepted_For_Bidding",
           OrdStatus::ost_Accepted_for_bidding);
    ADD_GV("UOrdStatus.Ost_Pending_Replace", OrdStatus::ost_Pending_Replace);

    ADD_GV("USide.Os_Buy", Side::os_Buy);
    ADD_GV("USide.Os_Sell", Side::os_Sell);

    ADD_GV("UBarType.MODE_TIME", BarType::MODE_TIME);
    ADD_GV("UBarType.MODE_OPEN", BarType::MODE_OPEN);
    ADD_GV("UBarType.MODE_HIGH", BarType::MODE_HIGH);
    ADD_GV("UBarType.MODE_LOW", BarType::MODE_LOW);
    ADD_GV("UBarType.MODE_CLOSE", BarType::MODE_CLOSE);
    ADD_GV("UBarType.MODE_VOL", BarType::MODE_VOL);
    /* ADD_GV("UBarType.MODE_BID", BarType::MODE_BID); */
    /* ADD_GV("UBarType.MODE_ASK", BarType::MODE_ASK); */

    ADD_GV("UTimeFrames.Period_Current", TimeFrames::PERIOD_CURRENT);
    ADD_GV("UTimeFrames.Period_M1", TimeFrames::PERIOD_M1);
    ADD_GV("UTimeFrames.Period_M", TimeFrames::PERIOD_M);
    ADD_GV("UTimeFrames.Period_M15", TimeFrames::PERIOD_M15);
    ADD_GV("UTimeFrames.Period_M30", TimeFrames::PERIOD_M30);
    ADD_GV("UTimeFrames.Period_H1", TimeFrames::PERIOD_H1);
    ADD_GV("UTimeFrames.Period_H4", TimeFrames::PERIOD_H4);
    ADD_GV("UTimeFrames.Period_D1", TimeFrames::PERIOD_D1);
    ADD_GV("UTimeFrames.Period_W1", TimeFrames::PERIOD_W1);
    ADD_GV("UTimeFrames.Period_MN1", TimeFrames::PERIOD_MN1);

    ADD_GV("UMKType.Mk_Csv", MKType::mk_csv);
    ADD_GV("UMKType.Mk_Kafka", MKType::mk_kafka);
    ADD_GV("UMKType.Mk_Tick", MKType::mk_tick);
    ADD_GV("UMKType.Mk_Bar", MKType::mk_bar);

    ADD_GV("UAnaly.Id", Analy::id);
    ADD_GV("UAnaly.Cash", Analy::cash);
    ADD_GV("UAnaly.Start", Analy::start);
    ADD_GV("UAnaly.End", Analy::end);
    ADD_GV("UAnaly.Duration", Analy::Duration);
    ADD_GV("UAnaly.ExposureTime", Analy::ExposureTime);
    ADD_GV("UAnaly.EquityFinal", Analy::EquityFinal);
    ADD_GV("UAnaly.EquityPeak", Analy::EquityPeak);
    ADD_GV("UAnaly.Return", Analy::Return);
    ADD_GV("UAnaly.BuyAndHold", Analy::BuyAndHold);
    ADD_GV("UAnaly.ReturnAnn", Analy::ReturnAnn);
    ADD_GV("UAnaly.VolatilityAnn", Analy::VolatilityAnn);
    ADD_GV("UAnaly.SharpeRatio", Analy::SharpeRatio);
    ADD_GV("UAnaly.SortinoRatio", Analy::SortinoRatio);
    ADD_GV("UAnaly.CalmarRatio", Analy::CalmarRatio);
    ADD_GV("UAnaly.MaxDrawdown", Analy::MaxDrawdown);
    ADD_GV("UAnaly.AvgDrawdown", Analy::AvgDrawdown);
    ADD_GV("UAnaly.MaxDrawdownDuration", Analy::MaxDrawdownDuration);
    ADD_GV("UAnaly.AvgTradeDuration", Analy::AvgTradeDuration);
    ADD_GV("UAnaly.WinRate", Analy::WinRate);
    ADD_GV("UAnaly.BestTrade", Analy::BestTrade);
    ADD_GV("UAnaly.WorstTrade", Analy::WorstTrade);
    ADD_GV("UAnaly.AvgTrade", Analy::AvgTrade);
    ADD_GV("UAnaly.MaxTradeDuration", Analy::MaxTradeDuration);
    ADD_GV("UAnaly.AvgTradeDuration", Analy::AvgTradeDuration);
    ADD_GV("UAnaly.MaxDrawdownDuration", Analy::MaxDrawdownDuration);
    ADD_GV("UAnaly.AvgDrawdownDuration", Analy::AvgDrawdownDuration);
    ADD_GV("UAnaly.ProfitFactor", Analy::ProfitFactor);
    ADD_GV("UAnaly.Expectancy", Analy::Expectancy);
    ADD_GV("UAnaly.SQN", Analy::SQN);
    ADD_GV("UAnaly.KellyCriterion", Analy::KellyCriterion);
    ADD_GV("UAnaly.Curve", Analy::curve);

    ADD_GV("UCommit.Pass", Commit::Pass);
    ADD_GV("UCommit.Reject", Commit::Reject);
    ADD_GV("UCommit.Restate", Commit::Restate);

    ADD_GV("UOffers.OF_Index", Offers::OF_Index);
    ADD_GV("UOffers.OF_Tick", Offers::OF_Tick);

    ADD_GV("UInitOk.I_Proc", InitOk::I_Proc);
    ADD_GV("UInitOk.I_OK", InitOk::I_OK);

    ADD_GV("UOMSRisk.I_OMS", OMSRisk::I_OMS);
    ADD_GV("UOMSRisk.I_BROKER", OMSRisk::I_BROKER);
    ADD_GV("UOMSRisk.I_EA", OMSRisk::I_EA);

    ADD_GV("ULineState.L_Dotted", LineState::L_Dotted);
    ADD_GV("ULineState.L_Solid", LineState::L_Solid);

    ADD_GV("USymbolTradeMode.M_Disabled", SymbolTradeMode::M_Disabled);
    ADD_GV("USymbolTradeMode.M_LongOnly", SymbolTradeMode::M_LongOnly);
    ADD_GV("USymbolTradeMode.M_ShortOnly", SymbolTradeMode::M_ShortOnly);
    ADD_GV("USymbolTradeMode.M_CloseOnly", SymbolTradeMode::M_CloseOnly);
    ADD_GV("USymbolTradeMode.M_Full", SymbolTradeMode::M_Full);

    ADD_GV("USelectFlag.F_ByPos", SelectFlag::F_ByPos);
    ADD_GV("USelectFlag.F_ByTicket", SelectFlag::F_ByTicket);
    ADD_GV("USelectFlag.P_Trade", SelectFlag::P_Trade);
    ADD_GV("USelectFlag.P_History", SelectFlag::P_History);

    ADD_GV("UBool.B_FALSE", Bool::B_FALSE);
    //    ADD_GV("UBool.B_TRUE", Bool::B_TRUE);
    _GlobalVariables.insert({"UBool.B_TRUE", Bool::B_TRUE});

    ADD_GV("USettleInstMode.S_Settle", SettleInstMode::_settle);
    ADD_GV("USettleInstMode.S_Settle_Balance", SettleInstMode::_settle_balance);
    ADD_GV("USettleInstMode.S_Observer", SettleInstMode::_observer);

    ADD_GV("UOrderEvent.Oe_Compleate", OrderEvent::Oe_Compleate);
    ADD_GV("UOrderEvent.Oe_StopLoss", OrderEvent::Oe_StopLoss);
    ADD_GV("UOrderEvent.Oe_TakeProfit", OrderEvent::Oe_TakeProfit);

    ADD_GV("UMatchEvent.ME_OrderIn", MatchEvent::ME_OrderIn);
    ADD_GV("UMatchEvent.ME_Open", MatchEvent::ME_Open);
    ADD_GV("UMatchEvent.ME_Close", MatchEvent::ME_Close);

    ADD_GV("UBookType.BBook", BookType::BBook);
    ADD_GV("UBookType.ABook", BookType::ABook);
} /* -----  end of function CodeGenContext::AddGlobal  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::newNameSpace
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::newNameSpace(std::string name)
{
    _NameSpace = name;

    if (_NameSpaceAttributes.count(name) == 0 && _blockStack.size() > 0) {
        _self_ns = _blockStack.front();
        // 保存私有变量的 map
        _NameSpaceAttributes[name] = NameSpaceValueNames();
    }
    else {
        llog::echo("block size ==0");
    }

} /* -----  end of function CodeGenContext::newNameSpace  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::NameSpaceVariableSize
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
std::size_t CodeGenContext::NameSpaceVariableSize(std::string ns)
{
    std::size_t nsize = 0;
    if (_NameSpaceAttributes.count(ns) == 1) {
        nsize = _NameSpaceAttributes[ns].size();
    }

    return nsize;
} /* -----  end of function CodeGenContext::NameSpaceVariableSize  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::NameSpaceVariable
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
NameSpaceValueNames CodeGenContext::NameSpaceVariable(std::string ns)
{
    NameSpaceValueNames nsv;

    if (_NameSpaceAttributes.count(ns) > 0) {
        nsv = _NameSpaceAttributes[ns];
    }
    return nsv;

} /* -----  end of function CodeGenContext::NameSpaceVariable  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::NameSpaceAddVariableAccess
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  记录 namespace 的私有变量在 gep 中的 索引及类型
 * ============================================
 */
void CodeGenContext::NameSpaceAddVariableAccess(std::string name, int index,
                                                llvm::Type* type)
{
    _NameSpaceAttributes[_NameSpace][name] = {index, type};
} /* -----  end of function CodeGenContext::NameSpaceAddVariableAccess  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::getNameSpaceVariableType
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Type* CodeGenContext::getNameSpaceVariableType(std::string name,
                                                     std::string var)
{
    if (_NameSpaceAttributes.count(name) == 0) {
        return nullptr;
    }
    if (_NameSpaceAttributes[name].count(var) == 0) {
        return nullptr;
    }
    return std::get<1>(_NameSpaceAttributes[name][var]);
} /* -----  end of function CodeGenContext::getNameSpaceVariableType  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::getNameSpaceVarAccessInst
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Instruction* CodeGenContext::getNameSpaceVarAccessInst(
    std::string ns, std::string var_name, llvm::AllocaInst* this_ptr)
{
    if (_NameSpaceAttributes.count(ns) == 0) {
        llog::bug("error namespace:", ns);
        DontRun();
        return nullptr;
    }
    int index = std::get<0>(_NameSpaceAttributes[ns][var_name]);
    llvm::Instruction* instr = block_ns_var_current(var_name);

    if (instr != nullptr) {
        llog::echo("instr is null", ns, " var_name:", var_name);
        return instr;
    }

    if (this_ptr == nullptr) {
        return nullptr;
    }

    std::vector<llvm::Value*> ptr_indices;
    llvm::ConstantInt* const_int32_0 =
        llvm::ConstantInt::get(_module->getContext(), llvm::APInt(32, 0));

    llvm::ConstantInt* const_int32 =
        llvm::ConstantInt::get(_module->getContext(), llvm::APInt(32, index));

    ptr_indices.push_back(const_int32_0);
    ptr_indices.push_back(const_int32);

    llvm::Type* structTy = getNSType(ns);

    if (this_ptr->getAllocatedType() != nullptr &&
        this_ptr->getAllocatedType()->isPointerTy()) {
        if (this_ptr->getType() == nullptr) {
            llog::bug("gettype is nullptr");
        }

        llvm::Value* nsPtr = function_self_current();

        if (nsPtr == nullptr) {
            llog::bug("nsptr is nullptr");
            return nullptr;
        }

        instr = llvm::GetElementPtrInst::CreateInBounds(
            structTy, nsPtr, ptr_indices, var_name, currentBlock());
    }

    if (instr == nullptr) {
        instr = llvm::GetElementPtrInst::CreateInBounds(
            structTy, this_ptr, ptr_indices, var_name, currentBlock());
    }

    block_ns_var_push(var_name, instr);

    return instr;

} /* -----  end of function CodeGenContext::getNameSpaceVarAccessInst  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::addNameSpaceinitCode
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   保存转换后的表达式
 * ============================================
 */
void CodeGenContext::addNameSpaceinitCode(std::string name, Assignment* assign)
{
    _ns_assign[name].insert(assign);
} /* -----  end of function CodeGenContext::addNameSpaceinitCode  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::getNameSpaceAssign
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  返回某个 namespace 的表达式
 * ============================================
 */
NameSpaceInitCodeAssign& CodeGenContext::getNameSpaceAssign(std::string name)
{
    assert(_ns_assign.count(name) != 0);

    return _ns_assign[name];
} /* -----  end of function CodeGenContext::getNameSpaceAssign  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::function_self
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  创建一个 namespace 变量 allocainst的值
 * ============================================
 */
llvm::AllocaInst* CodeGenContext::function_self(std::string arg_name)
{
    llvm::AllocaInst* alloca = nullptr;
    std::string name_space = getNameSpace();
    llvm::Type* self_ty = getNSType(name_space);
    if (self_ty == nullptr) {
        llog::bug("self type is nullptr");
        DontRun();

        return alloca;
    }

    llvm::PointerType* self_ptr_ty = llvm::PointerType::getUnqual(self_ty);

    alloca = new llvm::AllocaInst(self_ptr_ty, ALLOCAINST_SIZE,
                                  arg_name.c_str(), currentBlock());

    locals()[arg_name] = alloca;

    return alloca;
} /* -----  end of function CodeGenContext::function_self  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::function_self_push
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 * loadinst 的值
 * ============================================
 */
void CodeGenContext::function_self_push(llvm::AllocaInst* self)
{
    if (self->getAllocatedType() != nullptr &&
        self->getAllocatedType()->isPointerTy()) {
        if (self->getType() == nullptr) {
            llog::bug("gettype is nullptr");
        }
        llvm::Value* nsPtr = new llvm::LoadInst(
            self->getType()->getPointerElementType(), self, self->getName(),
            false, storeinst_align, currentBlock());
        _function_ns_arg.push_back(nsPtr);
    }

} /* -----  end of function CodeGenContext::function_self_push  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::function_self_current
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* CodeGenContext::function_self_current()
{
    if (_function_ns_arg.size() == 0) {
        return nullptr;
    }
    return _function_ns_arg.front();
} /* -----  end of function CodeGenContext::function_self_current  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::function_self_pop
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::function_self_pop()
{
    if (_function_ns_arg.size() == 0) {
        return;
    }
    _function_ns_arg.pop_front();

} /* -----  end of function CodeGenContext::function_self_pop  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::block_ns_var_push
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  function block start init
 * ============================================
 */
void CodeGenContext::block_ns_var_push(std::string var, llvm::Instruction* inst)
{
    if (inst == nullptr) {
        // init
        std::string name_space = getNameSpace();
        NameSpaceVarMap svm;
        for (auto it : _NameSpaceAttributes[name_space]) {
            svm.insert({it.first, inst});
        }

        _NameSpaceVarBlockInst.push_back(svm);
    }
    else {
        // 某一个变量初始化的时候加入来
        if (_NameSpaceVarBlockInst.front().count(var) == 0) {
            llog::bug("not found var:", var);
            return;
        }

        _NameSpaceVarBlockInst.front()[var] = inst;
    }

} /* -----  end of function CodeGenContext::block_ns_var_push  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::block_ns_var_current
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Instruction* CodeGenContext::block_ns_var_current(std::string var)
{
    llvm::Instruction* inst = nullptr;
    if (_NameSpaceVarBlockInst.size() == 0) {
        return inst;
    }
    if (_NameSpaceVarBlockInst.front().count(var) == 0) {
        return inst;
    }
    inst = _NameSpaceVarBlockInst.front()[var];
    return inst;
} /* -----  end of function CodeGenContext::block_ns_var_current  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::block_ns_var_pop
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::block_ns_var_pop()
{
    if (_NameSpaceVarBlockInst.size() == 0) {
        return;
    }
    _NameSpaceVarBlockInst.pop_front();
} /* -----  end of function CodeGenContext::block_ns_var_pop  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::MethodCallInst
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::AllocaInst* CodeGenContext::MethodCallInst(Identifier* id)
{
    IDType idt = id->idType();
    std::vector<llvm::Value*> args;
    llvm::AllocaInst* alloca = nullptr;
    if (idt == IDType::_ns_methodcall) {
        std::string ns_name = id->qname().back();
        std::string tag = id->NameSpaceTag();

        if (_NameSpaceTag.count(tag) == 0) {
            llvm::Type* ns_ty = getNSType(ns_name);
            if (ns_ty == nullptr) {
                llog::bug("namespace not found:", ns_name);
                return nullptr;
            }

            alloca = new llvm::AllocaInst(ns_ty, ALLOCAINST_SIZE, tag.c_str(),
                                          currentBlock());
            NameSpaceTagProperty ntp;
            ntp._alloca = alloca;

            _NameSpaceTag.insert({tag, ntp});
        }
        else {
            alloca = _NameSpaceTag[tag]._alloca;
        }
    }

    return alloca;
} /* -----  end of function CodeGenContext::MethodCallInst  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::isTagInitVariable
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool CodeGenContext::isTagInitVariable(std::string tag)
{
    return _NameSpaceTag.count(tag) == 0;
} /* -----  end of function CodeGenContext::isTagInitVariable  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::addNSSelfFunc
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::addNSSelfFunc(std::string func)
{
    _NameSpaceSelfFuncList.insert(func);
} /* -----  end of function CodeGenContext::addNSSelfFunc  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::isNSSelfFunc
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
bool CodeGenContext::isNSSelfFunc(std::string func)
{
    if (_NameSpaceSelfFuncList.empty()) {
        return false;
    }
    auto search = _NameSpaceSelfFuncList.find(func);
    if (search != _NameSpaceSelfFuncList.end()) {
        return true;
    }
    return false;
} /* -----  end of function CodeGenContext::isNSSelfFunc  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::cleanSelfFunc
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::cleanSelfFunc()
{
    _NameSpaceSelfFuncList.clear();
} /* -----  end of function CodeGenContext::cleanSelfFunc  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::endNameSpace
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   当前 namespace 处理完成了,生成了 ir 了
 * ============================================
 */
void CodeGenContext::endNameSpace()
{
    _self_ns = nullptr;
    _NameSpace = "";
} /* -----  end of function CodeGenContext::endNameSpace  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::ScriptList
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::ScriptList(NodeType nt, std::string name, size_t argc)
{
    ScriptList_t sl;
    sl.nt = nt;
    sl.name = name;
    sl.argc = argc;
    _script_list.push_back(sl);
} /* -----  end of function CodeGenContext::ScriptList  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::ScriptList
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  把变量，函数记录下来，方便 E2L API 对比或者什么的
 * ============================================
 */
const std::vector<ScriptList_t>& CodeGenContext::ScriptList()
{
    return _script_list;
} /* -----  end of function CodeGenContext::ScriptList  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::ScriptError
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::ScriptError(NodeType nt,       // Identifier type
                                 std::string name,  // Identifier name
                                 ErrorNo en,        // error number
                                 std::string msg,   // error msg
                                 size_t line        // error line number

)
{
    ScriptError_t se;
    se.nt = nt;
    se.name = name;
    se.en = en;
    se.msg = msg;
    se.line = line;
    _script_error.push_back(se);
} /* -----  end of function CodeGenContext::ScriptError  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::ScriptError
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
const std::vector<ScriptError_t>& CodeGenContext::ScriptError()
{
    return _script_error;
} /* -----  end of function CodeGenContext::ScriptError  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::toDebug
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::toDebug()
{
    _debug = true;
    /* llvm::legacy::PassManager pm; */

    /* pm.add(llvm::createPrintModulePass(llvm::outs())); */
    /* pm.run(*_module); */

    // two debug
    //    _module->print(llvm::outs(), nullptr);
} /* -----  end of function CodeGenContext::toDebug  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CodeGenContext::DontRun
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void CodeGenContext::DontRun()
{
    _CanRun = false;
} /* -----  end of function CodeGenContext::DontRun  ----- */

}  // namespace e2

