/*
 * =====================================================================================
 *
 *       Filename:  CodeGenStatement.cpp
 *
 *    Description:  CodeGenStatement
 *
 *        Version:  1.0
 *        Created:  2023年11月01日 10时58分46秒
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

#include "assembler/CodeGenStatement.hpp"

#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>

#include <cstddef>
#include <string>
#include <vector>

#include "assembler/BaseNode.hpp"
#include "assembler/BaseType.hpp"
#include "assembler/CodeGenContext.hpp"
#include "generated/e2_bison.hpp"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Metadata.h"
#include "llvm/Support/Alignment.h"
#include "utility/Log.hpp"

namespace e2 {
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExpressionStatement::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* ExpressionStatement::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("ExpressionStatement");
#endif
    llvm::Value* _value = nullptr;
    if (_expression) {
        _value = _expression->codeGen(context);
    }
    if (_statement) {
        _value = _statement->codeGen(context);
    }

#ifdef E2L_DEBUG
    ExitCode("ExpressionStatement");
#endif

    return _value;
} /* -----  end of function ExpressionStatement::codeGen  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  methodCall::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* MethodCall::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("MethodCall");
#endif

    std::string cname = _id->name();
    IDType idt = _id->idType();
    std::vector<llvm::Value*> args;
    bool isInit = false;
    llvm::AllocaInst* alloca = nullptr;

    if (idt == IDType::_ns_methodcall) {
        if (context.isTagInitVariable(_id->NameSpaceTag())) {
            isInit = true;
        }
        alloca = context.MethodCallInst(_id);

        if (alloca != nullptr) {
            args.push_back(alloca);
        }
        else {
            llog::bug("MethodCall NameSpace Tag is nullptr, tag:",
                      _id->NameSpaceTag(), ", line:", _codeLine,
                      " path:", _path);

            context.DontRun();
#ifdef E2L_DEBUG
            ExitCode("MethodCall");
#endif
            return nullptr;
        }
    }

    if (idt == IDType::_ns_private) {
        // 内部调用
        std::string name_space = context.getNameSpace();
        cname = NameSpaceFunc(name_space, cname);  // name_space + "_" + cname ;
        if (name_space.length() == 0) {
            llog::bug("name space not found!");
            context.DontRun();
#ifdef E2L_DEBUG
            ExitCode("MethodCall");
#endif
            return nullptr;
        }

        llvm::Value* self_alloca = context.function_self_current();
        if (self_alloca != nullptr) {
            args.push_back(self_alloca);
        }
        else {
            llog::bug("MethodCall NameSpace  is nullptr", ", line:", _codeLine,
                      " path:", _path);

            context.DontRun();
#ifdef E2L_DEBUG
            ExitCode("MethodCall");
#endif
            return nullptr;
        }
    }

#ifdef E2L_DEBUG
    e2::llog::bug("method call name: ", cname, " idtype:", idt,
                  " code line:", _codeLine);
#endif

    llvm::Function* func = context.getModule()->getFunction(cname.c_str());
    if (func == nullptr) {
        std::string err = "call name not found: " + cname;

        llog::bug(err, ", line:", _codeLine, " path:", _path);
        context.ScriptError(NodeType::_methodcall, cname, ErrorNo::_NotExist,
                            err, 0);
        context.DontRun();
#ifdef E2L_DEBUG
        ExitCode("MethodCall");
#endif
        return nullptr;
    }

    DebugLoc();

#ifdef E2L_DEBUG
    llog::info("func arg size:", func->arg_size());
#endif
    /*
     * 检查 参数类型是否一致的，以后再做
    llvm::Type* charType = E2LStr(context.getGlobalContext());

    //    func->arg_begin();
    for (auto arg = func->arg_begin(); arg != func->arg_end(); ++arg) {
        llvm::Type* atype = arg->getType();
        if (atype == charType) {
            llog::echo("str type");
        }
        llog::echo("atype:", atype->getTypeID());
    }
*/

    if (_arguments != nullptr) {
        std::size_t arg_size = _arguments->size() + args.size();
        if (func->arg_size() != arg_size) {
            llog::bug("call name : ", cname,
                      ", func arg size:", func->arg_size(),
                      ", not eq call arg size:", _arguments->size());
            context.DontRun();
#ifdef E2L_DEBUG
            ExitCode("MethodCall");
#endif
            return nullptr;
        }
        for (auto expr : *_arguments) {
            if (expr == nullptr) {
                e2::llog::bug("expr is null");
                context.DontRun();
                break;
            }

            auto arg = expr->codeGen(context);
            if (arg == nullptr) {
                e2::llog::bug("args is null");
                context.DontRun();
                break;
            }
            args.push_back(arg);
        }
    }

    /**
     * check func arg size and type is the same
     */
    if (func->arg_size() != args.size()) {
        e2::llog::bug("call name ,", cname,
                      " arg size not eq ! args size:", args.size(),
                      " line:", _codeLine, " path:", _path);
        context.DontRun();
#ifdef E2L_DEBUG
        ExitCode("MethodCall");
#endif
        return nullptr;
    }
    context.ScriptList(NodeType::_methodcall, cname, func->arg_size());

    if (isInit) {
        callNameSpaceInit(context, alloca);
    }

    llvm::CallInst* call = nullptr;
    if (args.size() == 0) {
        call = llvm::CallInst::Create(func, "", context.currentBlock());
    }
    else {
        call = llvm::CallInst::Create(func, llvm::makeArrayRef(args), "",
                                      context.currentBlock());
    }

#ifdef E2L_DEBUG
    ExitCode("MethodCall");
#endif

    return call;
} /* -----  end of function MethodCall::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  MethodCall::callNameSpaceInit
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void MethodCall::callNameSpaceInit(CodeGenContext& context,
                                   llvm::AllocaInst* alloca)
{
    std::vector<llvm::Value*> args;

    std::string fname = _id->qname().back();
    fname = NameSpaceFunc(fname, NameSpaceInitName(fname));

    llvm::Function* func = context.getModule()->getFunction(fname.c_str());
    if (func == nullptr) {
        std::string err = "call name not found: " + fname;

        llog::bug(err, ", line:", _codeLine, " path:", _path);
        context.ScriptError(NodeType::_methodcall, fname, ErrorNo::_NotExist,
                            err, 0);

        return;
    }
    args.push_back(alloca);

    if (func->arg_size() != args.size()) {
        std::string err = "call name : " + fname;

        llog::bug(err, "args has some bug, line:", _codeLine, " path:", _path);
        context.ScriptError(NodeType::_methodcall, fname, ErrorNo::_NotExist,
                            err, 0);
        return;
    }

    llvm::CallInst::Create(func, llvm::makeArrayRef(args), "",
                           context.currentBlock());

} /* -----  end of function MethodCall::callNameSpaceInit  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  MethodCall::DebugLoc
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void MethodCall::DebugLoc()
{
    std::array<std::string, 5> diff_str{"FPrint", "echo", "log", "StoreId",
                                        "Array"};

    if (_arguments == nullptr) {
        _arguments = MALLOC(ExpressionList);
    }
    /**
     * 在多次运行的情况，初始化的时候，就知道了
     */
    if (_id->name() == "FPrintCurrentPath") {
        StrObj* str = MALLOC(StrObj, _path, true);

        _arguments->push_back(str);
        return;
    }

    bool diff = false;
    std::string::size_type isfound;
    std::string find_str = _id->name();
    for (std::string key : diff_str) {
        isfound = find_str.find(key);
        if (isfound != std::string::npos) {
            diff = true;
            break;
        }
    }

    if (diff) {
        std::string vname = "";

        if (_arguments->size() > 0) {
            if (_arguments->at(0)->getType() == NodeType::_identifier) {
                Identifier* id = (Identifier*)_arguments->at(0);
                vname = id->name();
            }
            StrObj* vn = MALLOC(StrObj, vname, true);
            _arguments->push_back(vn);
        }

        e2::Number* line =
            MALLOC(Number, (Int_e)_codeLine, _codeLine, _path.c_str());
        line->genuine();
        _arguments->push_back(line);

        StrObj* str = MALLOC(StrObj, _path, true);
        _arguments->push_back(str);
    }
} /* -----  end of function MethodCall::DebugLoc  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ReturnStatement::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* ReturnStatement::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("ReturnStatement");
#endif
    if (_expression == nullptr) {
        llog::bug("expression is nullptr");
        context.DontRun();
#ifdef E2L_DEBUG
        ExitCode("ReturnStatement");
#endif
        return nullptr;
    }

    llvm::Value* ret = _expression->codeGen(context);
    if (ret == nullptr) {
        llog::bug("var is nullptr: ", _expression->id()->name());
        context.DontRun();
#ifdef E2L_DEBUG
        ExitCode("ReturnStatement");
#endif
        return nullptr;
    }
    context.setCurrentReturnValue(ret);

#ifdef E2L_DEBUG
    ExitCode("ReturnStatement");
#endif
    return ret;
} /* -----  end of function ReturnStatement::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  VariableStatement::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  用在定义函数, 变量左则 值上面， 之前没有出现过的
 * ============================================
 */
llvm::Value* VariableStatement::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("VariableStatement");
#endif

    std::string name_space = context.getNameSpace();
    NameSpaceStatus nss = _id->nss();

    if (name_space.length() > 0 && nss != NameSpaceStatus::_n_null) {
        if (_id->qname().size() == 1) {
            _id->push_back(name_space);
        }
    }

    UNION_NAME(_id, context);
    std::string cname = _id->name();

    llvm::Value* alloc = nullptr;
#ifdef E2L_DEBUG
    e2::llog::bug("VariableStatement, id name:", cname, " _op:", _op,
                  " nss:", nss);
#endif

    if (_op != yy::Parser::token::token_kind_type::ASSIGN_EQ) {
        int nop = 0;
        switch (_op) {
            case yy::Parser::token::token_kind_type::ASSIGN_ADD:
                nop = '+';
                break;
            case yy::Parser::token::token_kind_type::ASSIGN_SUB:
                nop = '-';
                break;
            case yy::Parser::token::token_kind_type::ASSIGN_MUL:
                nop = '*';
                break;
            case yy::Parser::token::token_kind_type::ASSIGN_DIV:
                nop = '/';
                break;
            default:
                e2::llog::bug("VariableStatement, bad: _op:", _op);
#ifdef E2L_DEBUG
                ExitCode("VariableStatement");
#endif
                return alloc;
        }

        BinaryOperator* b =
            MALLOC(BinaryOperator, _id, nop, _rhs, _codeLine, _path.c_str());

        VariableStatement* v =
            MALLOC(VariableStatement, _id,
                   yy::Parser::token::token_kind_type::ASSIGN_EQ, b, _codeLine,
                   _path.c_str());

        alloc = v->codeGen(context);
#ifdef E2L_DEBUG
        ExitCode("VariableStatement");
#endif
        return alloc;
    }

    if (_rhs == nullptr) {
        e2::llog::bug("VariableStatement, rhs is nullptr, line:", _codeLine,
                      " path:", _path);
#ifdef E2L_DEBUG
        ExitCode("VariableStatement");
#endif
        return nullptr;
    }

    context.ScriptList(NodeType::_variable, cname, _id->idType());

    bool _gl = FIND_GV(cname);
    if (_id->idType() == IDType::_global || _gl) {
#ifdef E2L_DEBUG
        e2::llog::bug("global name:", cname);
#endif
        if (cname.length() == 0) {
#ifdef E2L_DEBUG
            ExitCode("VariableStatement");
#endif
            return nullptr;
        }
        llvm::GlobalVariable* gVar = context.getModule()->getNamedGlobal(cname);

        if (gVar == nullptr) {
            /**
             * init global val
             */
            Int_e init_val = 0;
            if (_rhs->getType() == NodeType::_number) {
                init_val = dynamic_cast<Number*>(_rhs)->value();
            }
            llvm::Type* type = E2LType(context.getGlobalContext());
            BuildGlobal(context, type, cname, init_val);
#ifdef E2L_DEBUG
            ExitCode("VariableStatement");
#endif
            return nullptr;
        }
        else {
            /**
             * update global val
             */
            if (_rhs->getType() == NodeType::_number) {
                alloc = _rhs->codeGen(context);
                gVar->setOperand(0, alloc);
#ifdef E2L_DEBUG
                ExitCode("VariableStatement");
#endif
                return nullptr;
            }
            else {
                e2::llog::bug("error type:", _rhs->getType());
            }
        }
    }
    else if (nss == NameSpaceStatus::_n_null) {
        alloc = _id->codeGen(context);

        retType* _ty = nullptr;
        std::size_t size = ALLOCAINST_SIZE;

        if (_rhs->getType() == NodeType::_comp) {
            size = 1;
            _ty = context.typeOf(_rhs);
        }
        else {
            _ty = context.typeOf(_id);
        }

        if (alloc == nullptr) {
            llvm::AllocaInst* alloc_t = new llvm::AllocaInst(
                _ty, size, cname.c_str(), context.currentBlock());
            context.locals()[cname] = alloc_t;
        }
    }

    /**
     *  把 rhs 的内容存入到 id 中去
     */
    if (_rhs->getType() == NodeType::_identifier) {
        Identifier* rid = (Identifier*)_rhs;
        std::string rname = rid->name();
        if (rid->idType() == IDType::_normal) {
            llvm::Value* check = context.findBlockId(rname);
            if (check == nullptr) {
                llog::bug("can't found variable:", rname, " . line:", _codeLine,
                          " file:", _path);
#ifdef E2L_DEBUG
                ExitCode("VariableStatement");
#endif
                return nullptr;
            }
        }
    }

    _ass = MALLOC(Assignment, _id, _rhs, _codeLine, _path.c_str());
    _ass->codeGen(context);

#ifdef E2L_DEBUG
    ExitCode("VariableStatement");
#endif
    return alloc;

} /* -----  end of function VariableStatement::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  UnaryOperator::codeGen
 *  ->  void *
 *  Parameters:
 ExternDeclaration*  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* UnaryOperator::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("UnaryOperator");
#endif

#ifdef E2L_DEBUG
    e2::llog::bug("lhs: ", _id->getType());
    e2::llog::bug("_op:", _op);
#endif

    Int_e num = 1;
    Number* rhs = new Number(num, _codeLine, _path.c_str());
    int op = 0;
    switch (_op) {
        case yy::Parser::token::UNARY_INC:
            //++
            op = '+';
            break;
        case yy::Parser::token::UNARY_DEC:
            // --
            op = '-';
            break;
    }

    BinaryOperator* bo =
        MALLOC(BinaryOperator, _id, op, rhs, _codeLine, _path.c_str());
    Assignment* ass = MALLOC(Assignment, _id, bo, _codeLine, _path.c_str());
    llvm::Value* _value = ass->codeGen(context);

#ifdef E2L_DEBUG
    ExitCode("UnaryOperator");
#endif
    return _value;

} /* -----  end of function UnaryOperator::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  FunctionDeclaration::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* FunctionDeclaration::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("FunctionDeclaration");
#endif

    std::string func_name = _id->name();
    context.currentFuncName(func_name);

    std::string name_space = context.getNameSpace();

    std::vector<llvm::Type*> argTypes;
    if (!name_space.empty()) {
        llvm::Type* nstype = context.getNSType(name_space);
        argTypes.push_back(llvm::PointerType::getUnqual(nstype));
    }
    if (_arguments != nullptr) {
        for (auto it : *_arguments) {
            if (it == nullptr) {
                e2::llog::bug(" FunctionDeclaration arguments id error ");

                continue;
            }

            argTypes.push_back(context.typeOf(it));
        }
    }
    llvm::FunctionType* ftype = llvm::FunctionType::get(
        context.typeOf(_id), llvm::makeArrayRef(argTypes), false);

    llvm::Function* func =
        llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage,
                               func_name.c_str(), context.getModule());
    llvm::BasicBlock* bblock = llvm::BasicBlock::Create(
        context.getGlobalContext(), func_name, func, 0);

    context.pushBlock(bblock, ScopeKind::_sk_fun);

    llvm::Function::arg_iterator args = func->arg_begin();
    llvm::Value* arg;
    if (!context.getNameSpace().empty()) {
        /**
         * param attr
         */
        unsigned argno = 0;
        func->addParamAttr(argno, llvm::Attribute::NoUndef);
        func->addParamAttr(argno, llvm::Attribute::NonNull);

        // Specify an alignment of 8 bytes
        llvm::Align anign(8);
        func->addParamAttr(argno, llvm::Attribute::getWithAlignment(
                                      context.getGlobalContext(), anign));

        func->addParamAttr(argno, llvm::Attribute::getWithDereferenceableBytes(
                                      context.getGlobalContext(), 16));

        arg = args;

        std::string arg_name = NameSpaceSelfArg(func_name);
        arg->setName(arg_name);

        llvm::AllocaInst* alloca = context.function_self(arg_name);
        if (alloca == nullptr) {
            llog::bug("NameSpace self arg is nullptr");
            context.DontRun();
#ifdef E2L_DEBUG
            ExitCode("FunctionDeclaration");
#endif
            return nullptr;
        }

        new llvm::StoreInst(arg, alloca, false, storeinst_align, bblock);

        context.function_self_push(alloca);

        context.block_ns_var_push("", nullptr);

        args++;
    }

    if (_arguments != nullptr) {
        for (auto it : *_arguments) {
            std::string it_name = it->id()->name();
#ifdef E2L_DEBUG
            e2::llog::bug(" FunctionDeclaration arguments: ", it_name);
#endif
            context.locals()[it_name] =
                new llvm::AllocaInst(context.typeOf(it), ALLOCAINST_SIZE,
                                     it_name.c_str(), context.currentBlock());
            arg = args++;
            arg->setName(it_name);

            new llvm::StoreInst(arg, context.locals()[it_name], false,
                                storeinst_align, bblock);
        }
    }

    if (_block != nullptr) {
        _block->codeGen(context);
    }
    context.ScriptList(NodeType::_function, func_name, func->arg_size());

    llvm::Value* _Return = context.getCurrentReturnValue();
    if (_Return == nullptr) {
        ReturnStatement* _ret =
            MALLOC(ReturnStatement, _codeLine, _path.c_str());

        _Return = _ret->codeGen(context);
    }

    llvm::ReturnInst::Create(context.getGlobalContext(), _Return,
                             context.currentBlock());

    if (!context.getNameSpace().empty()) {
        context.function_self_pop();
        context.block_ns_var_pop();
    }

    context.currentFuncName("");
    context.popBlock();

#ifdef E2L_DEBUG
    ExitCode("FunctionDeclaration");
#endif
    return func;
} /* -----  end of function FunctionStatement::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExternDeclaration::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* ExternDeclaration::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("ExternDeclaration");
#endif
    std::vector<llvm::Type*> argTypes;
    for (auto it : *_arguments) {
        argTypes.push_back(context.typeOf(it));
    }
    llvm::FunctionType* ftype = llvm::FunctionType::get(
        context.typeOf(_id), makeArrayRef(argTypes), false);
    llvm::Function* function =
        llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage,
                               _id->name().c_str(), context.getModule());
    if (function == nullptr) {
        e2::llog::bug("func:", _id->name(), " not found!");
    }
#ifdef E2L_DEBUG
    ExitCode("ExternDeclaration");
#endif
    return function;

} /* -----  end of function ExternDeclaration::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  UnionDeclaration::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* UnionDeclaration::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("UnionDeclaration");
#endif

    UNION_NAME(_id, context);

    std::string cname = _id->name();
    context.pushUnion(cname);

    if (_block != nullptr) {
        // 开始处理当前union 的变量
        // 或者子 union
        _block->codeGen(context);
    }
    else {
        e2::llog::info("block is null");
    }

    context.popUnion();

#ifdef E2L_DEBUG
    ExitCode("UnionDeclaration");
#endif
    return nullptr;

} /* -----  end of function UnionDeclaration::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  NameSpace::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* NameSpace::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("NameSpace");
#endif

    llvm::Value* value = nullptr;
    std::string cname = _id->name();
    if (_block == nullptr) {
#ifdef E2L_DEBUG
        ExitCode("NameSpace");
#endif
        return nullptr;
    }
    context.newNameSpace(cname);

    std::vector<llvm::Type*> StructTy_fields;

    constructStructFields(StructTy_fields, context);

    llvm::StructType* classTy =
        llvm::StructType::create(context.getGlobalContext(), StructTy_fields,
                                 std::string("NameSpace.") + cname, false);

    addVarsToClassAttributes(context, StructTy_fields);

    removeVarDeclStatements();

    context.addNSType(cname, classTy);

    context.ScriptList(NodeType::_namespace, cname, StructTy_fields.size());

    InitFunc();

    value = _block->codeGen(context);

    context.endNameSpace();

#ifdef E2L_DEBUG
    ExitCode("NameSpace");
#endif
    return value;
} /* -----  end of function NameSpace::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  NameSpace::InitFunc
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void NameSpace::InitFunc()
{
    std::string init_name = NameSpaceInitName(_id->name());
    Identifier* fname = MALLOC(Identifier, init_name, IDType::_ns_private);
    fname->push_back(_id);

    e2::FunctionDeclaration* ns = MALLOC(FunctionDeclaration, fname, nullptr,
                                         _member, _codeLine, path().c_str());

    _block->mod();
    _block->push_back(ns);
} /* -----  end of function NameSpace::InitFunc  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  NameSpace::constructStructFields
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void NameSpace::constructStructFields(std::vector<llvm::Type*>& StructTy_fields,
                                      CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("NameSpace Fields");
#endif
    auto structName = _id->name();

    std::size_t block_size = _block->size();
    llog::echo("block size:", block_size);
    for (std::size_t idx = 0; idx < block_size; idx++) {
        NodeType nt = _block->getType(idx);

        if (nt == NodeType::_variable) {
            llog::echo("variable");
            StructTy_fields.push_back(E2LType(context.getGlobalContext()));
        }

        _block->updateIdName(idx, _id);
    }
#ifdef E2L_DEBUG
    ExitCode("NameSpace Fields");
#endif

} /* -----  end of function NameSpace::constructStructFields  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  NameSpace::addVarsToClassAttributes
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void NameSpace::addVarsToClassAttributes(
    CodeGenContext& context, std::vector<llvm::Type*>& StructTy_fields)
{
#ifdef E2L_DEBUG
    EnterCode("NameSpace Attr");
#endif
    auto structName = _id->name();
    std::size_t block_size = _block->size();
    for (std::size_t idx = 0; idx < block_size; idx++) {
        NodeType nt = _block->getType(idx);

        if (nt == NodeType::_variable) {
            Statement* val = _block->getStatement(idx);
            std::string varName = val->id()->real_name();
            llog::echo("variable var name:", varName, " idx:", idx);
            context.NameSpaceAddVariableAccess(varName, idx,
                                               StructTy_fields[idx]);

            if (val->getType() == NodeType::_variable) {
                VariableStatement* vs = (VariableStatement*)val;

                _member->push_back(std::move(val));

                if (vs->hasRhs()) {
                    // 如果不是定义，是表达式的话，需要处理一下
                    // 重新处理过
                    Expression* rhs = vs->getRhs();

                    Identifier* nid = vs->id();

                    if (nid->nss() != NameSpaceStatus::_n_attr_definition) {
                        llog::bug("name space definition variable:[",
                                  nid->id_name(), "] must set this::");
                        context.DontRun();
                        return;
                    }
                    Assignment* nass = MALLOC(Assignment, nid, rhs, rhs->line(),
                                              rhs->path().c_str());
                    nass->NsVarInit(true);
                    context.addNameSpaceinitCode(structName, nass);
                }
                else {
                    llog::bug("hasrhs false");
                }
            }
            else {
                llog::bug("get:", val->getType(),
                          " varl:", NodeType::_variable);
            }
        }
    }
#ifdef E2L_DEBUG
    ExitCode("NameSpace Attr");
#endif
} /* -----  end of function NameSpace::addVarsToClassAttributes  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  NameSpace::removeVarDeclStatements
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void NameSpace::removeVarDeclStatements()
{
    std::size_t block_size = _block->size();
    if (block_size > 0) {
        _block->erase_id(NodeType::_variable);
    }
} /* -----  end of function NameSpace::removeVarDeclStatements  ----- */
}  // namespace e2
