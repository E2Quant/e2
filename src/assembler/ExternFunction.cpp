/*
 * =====================================================================================
 *
 *       Filename:  ExternFunction.cpp
 *
 *    Description:  ExternFunction
 *
 *        Version:  1.0
 *        Created:  2023年10月31日 10时21分54秒
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
#include "assembler/ExternFunction.hpp"

#include <llvm/IR/DebugLoc.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <iostream>
#include <vector>


using namespace std;

llvm::Function* createPrintfFunction(CodeGenContext& context)
{
    std::vector<llvm::Type*> printf_arg_types;
    printf_arg_types.push_back(
        llvm::Type::getInt64Ty(context.getGlobalContext()));  // char*

    llvm::FunctionType* printf_type = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(context.getGlobalContext()), printf_arg_types,
        true);

    llvm::Function* func =
        llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage,
                               llvm::Twine("printf"), context.getModule());
    func->setCallingConv(llvm::CallingConv::C);

    return func;
}

void createEchoFunction(CodeGenContext& context, llvm::Function* printfFn)
{
    std::vector<llvm::Type*> echo_arg_types;
    echo_arg_types.push_back(
        llvm::Type::getInt64Ty(context.getGlobalContext()));
    echo_arg_types.push_back(
        llvm::Type::getInt64Ty(context.getGlobalContext()));

    echo_arg_types.push_back(
        llvm::IntegerType::get(context.getGlobalContext(), 64));

    echo_arg_types.push_back(
        llvm::IntegerType::get(context.getGlobalContext(), 64));

    llvm::FunctionType* echo_type = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context.getGlobalContext()), echo_arg_types,
        false);

    llvm::Function* func =
        llvm::Function::Create(echo_type, llvm::Function::InternalLinkage,
                               llvm::Twine("echo"), context.getModule()

        );
    llvm::BasicBlock* bblock =
        llvm::BasicBlock::Create(context.getGlobalContext(), "entry", func, 0);
    context.pushBlock(bblock, ScopeKind::_sk_main);

    const char* constValue = "%ld [echo varname: %s  line:%ld, file:%s]\n";
    llvm::Constant* format_const = llvm::ConstantDataArray::getString(
        context.getGlobalContext(), constValue);

    llvm::GlobalVariable* var = new llvm::GlobalVariable(
        *context.getModule(),
        llvm::ArrayType::get(
            llvm::IntegerType::get(context.getGlobalContext(), 64),
            strlen(constValue) + 1),
        true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");

    llvm::Constant* zero = llvm::Constant::getNullValue(
        llvm::IntegerType::getInt64Ty(context.getGlobalContext()));

    std::vector<llvm::Constant*> indices;
    indices.push_back(zero);
    indices.push_back(zero);

    llvm::Constant* var_ref = llvm::ConstantExpr::getGetElementPtr(
        llvm::ArrayType::get(
            llvm::IntegerType::get(context.getGlobalContext(), 64),
            strlen(constValue) + 1),
        var, indices);

    std::vector<llvm::Value*> args;
    args.push_back(var_ref);

    llvm::Function::arg_iterator argsValues = func->arg_begin();
    llvm::Value* argPrint = &*argsValues++;
    argPrint->setName("codeLine");
    args.push_back(argPrint);

    argPrint = &*argsValues++;
    argPrint->setName("varname");
    args.push_back(argPrint);

    argPrint = &*argsValues++;
    argPrint->setName("toPrint");
    args.push_back(argPrint);

    argPrint = &*argsValues++;
    argPrint->setName("varpath");
    args.push_back(argPrint);

    llvm::CallInst::Create(printfFn, makeArrayRef(args), "", bblock);
    llvm::ReturnInst::Create(context.getGlobalContext(), bblock);

    context.popBlock();
}

void createCoreFunctions(CodeGenContext& context)
{
    llvm::Function* printfFn = createPrintfFunction(context);
    createEchoFunction(context, printfFn);
}

