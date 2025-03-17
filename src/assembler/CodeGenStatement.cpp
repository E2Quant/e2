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

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/Casting.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include <cstddef>
#include <vector>

#include "generated/e2_bison.hpp"

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
    if (_expression) {
#ifdef E2L_DEBUG
        e2::log::bug("ExpressionStatement : expression");
#endif
        return _expression->codeGen(context);
    }
    if (_statement) {
#ifdef E2L_DEBUG
        e2::log::bug("ExpressionStatement : statement");
#endif
        return _statement->codeGen(context);
    }
    return nullptr;
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
    std::string cname = _id->name();
#ifdef E2L_DEBUG
    e2::log::bug("method call name: ", cname, " code line:", _codeLine);
#endif

    llvm::Function* func = context.getModule()->getFunction(cname.c_str());
    if (func == nullptr) {
        std::string err = "call name not found: " + cname;
        std::cout << err << ", line:" << _codeLine << " path:" << _path
                  << std::endl;

        context.ScriptError(NodeType::_methodcall, cname, ErrorNo::_NotExist,
                            err, 0);
        context.DontRun();
        return nullptr;
    }

    DebugLoc();

    /*
     * 检查 参数类型是否一致的，以后再做
    llvm::Type* charType = E2LStr(context.getGlobalContext());

    //    func->arg_begin();
    for (auto arg = func->arg_begin(); arg != func->arg_end(); ++arg) {
        llvm::Type* atype = arg->getType();
        if (atype == charType) {
            log::echo("str type");
        }
        log::echo("atype:", atype->getTypeID());
    }
*/
    std::vector<llvm::Value*> args;

    if (_arguments != nullptr) {
        if (func->arg_size() != _arguments->size()) {
            std::cout << "call name : " << cname
                      << ", func arg size:" << func->arg_size()
                      << ", not eq call arg size:" << _arguments->size()
                      << ", line:" << _codeLine << " path:" << _path
                      << std::endl;
            context.DontRun();
            return nullptr;
        }
        for (auto expr : *_arguments) {
            if (expr == nullptr) {
                e2::log::bug("expr is null");
                context.DontRun();
                break;
            }

            auto arg = expr->codeGen(context);
            if (arg == nullptr) {
                e2::log::bug("args is null");
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
        e2::log::bug("call name ,", cname,
                     " arg size not eq ! args size:", args.size(),
                     " line:", _codeLine, " path:", _path);
        context.DontRun();
        return nullptr;
    }
    context.ScriptList(NodeType::_methodcall, cname, func->arg_size());

    llvm::CallInst* call = nullptr;
    if (args.size() == 0) {
        call = llvm::CallInst::Create(func, "", context.currentBlock());
    }
    else {
        call = llvm::CallInst::Create(func, llvm::makeArrayRef(args), "",
                                      context.currentBlock());
    }
    return call;
}
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
    if (_expression == nullptr) {
        log::bug("expression is nullptr");
        context.DontRun();
        return nullptr;
    }

    llvm::Value* ret = _expression->codeGen(context);
    if (ret == nullptr) {
        context.DontRun();
        log::bug("var is nullptr: ", _expression->id()->name());
        return nullptr;
    }
    context.setCurrentReturnValue(ret);

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
    UNION_NAME(_id);
    std::string cname = _id->name();
    llvm::Value* alloc = nullptr;
#ifdef E2L_DEBUG
    e2::log::bug("VariableStatement, id name:", cname, " _op:", _op);
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
                e2::log::bug("VariableStatement, bad: _op:", _op);

                return alloc;
        }

        BinaryOperator* b =
            MALLOC(BinaryOperator, _id, nop, _rhs, _codeLine, _path.c_str());
        VariableStatement* v =
            MALLOC(VariableStatement, _id,
                   yy::Parser::token::token_kind_type::ASSIGN_EQ, b, _codeLine,
                   _path.c_str());
        alloc = v->codeGen(context);

        return alloc;
    }

    if (_rhs == nullptr) {
        e2::log::bug("VariableStatement, rhs is nullptr, line:", _codeLine,
                     " path:", _path);

        return nullptr;
    }

    context.ScriptList(NodeType::_variable, cname, _id->idType());

    bool _gl = FIND_GV(cname);
    if (_id->idType() == IDType::_global || _gl) {
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

            return nullptr;
        }
        else {
            /**
             * update global val
             */
            if (_rhs->getType() == NodeType::_number) {
                alloc = _rhs->codeGen(context);

                gVar->setOperand(0, alloc);
                return nullptr;
            }
            else {
                e2::log::bug("error type:", _rhs->getType());
            }
        }
    }
    else {
        alloc = _id->codeGen(context);

        retType* _ty = nullptr;
        std::size_t size = 4;

        if (_rhs->getType() == NodeType::_comp) {
            size = 1;
            _ty = context.typeOf(_rhs);
        }
        else {
            _ty = context.typeOf(_id);
        }

        if (alloc == nullptr) {
            alloc = new llvm::AllocaInst(_ty, size, cname.c_str(),
                                         context.currentBlock());
            context.locals()[cname] = alloc;
        }
    }

    /**
     *  把 rhs 的内容存入到 id 中去
     */
    if (_rhs->getType() == NodeType::_identifier) {
        Identifier* id = (Identifier*)_rhs;
        if (id->idType() == IDType::_normal) {
            llvm::Value* check = context.findBlockId(id->name());
            if (check == nullptr) {
                log::bug("---- not in current! ", id->name());
                return nullptr;
            }
        }
    }

    _ass = MALLOC(Assignment, _id, _rhs, _codeLine, _path.c_str());
    _ass->codeGen(context);

    return alloc;

} /* -----  end of function VariableStatement::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  UnaryOperator::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* UnaryOperator::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    e2::log::bug("lhs: ", _id->getType());
    e2::log::bug("_op:", _op);
#endif

    Int_e num = 1;
    Number* rhs = new Number(num);
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
    return ass->codeGen(context);

} /* -----  end of function UnaryOperator::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  FunctionStatement::codeGen
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

    e2::log::bug("FunctionStatement, id name:", _id->name());
#endif

    std::vector<llvm::Type*> argTypes;
    if (_arguments != nullptr) {
        for (auto it : *_arguments) {
            if (it == nullptr) {
                e2::log::bug(" FunctionDeclaration arguments id error ");

                continue;
            }

            argTypes.push_back(context.typeOf(it));
        }
    }
    llvm::FunctionType* ftype = llvm::FunctionType::get(
        context.typeOf(_id), llvm::makeArrayRef(argTypes), false);

    llvm::Function* func =
        llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage,
                               _id->name().c_str(), context.getModule());
    llvm::BasicBlock* bblock = llvm::BasicBlock::Create(
        context.getGlobalContext(), _id->name(), func, 0);

    context.pushBlock(bblock, ScopeKind::_sk_fun);

    llvm::Function::arg_iterator args = func->arg_begin();
    llvm::Value* arg;
    if (_arguments != nullptr) {
        for (auto it : *_arguments) {
#ifdef E2L_DEBUG
            e2::log::bug(" FunctionDeclaration arguments: ", it->id()->name());
#endif
            context.locals()[it->id()->name()] = new llvm::AllocaInst(
                context.typeOf(it), 4, it->id()->name().c_str(),
                context.currentBlock());
            arg = args++;
            arg->setName(it->id()->name());

            new llvm::StoreInst(arg, context.locals()[it->id()->name()], true,
                                bblock);
        }
    }
    if (_block != nullptr) {
        _block->codeGen(context);
    }
    context.ScriptList(NodeType::_function, _id->name(), func->arg_size());

    llvm::ReturnInst::Create(context.getGlobalContext(),
                             context.getCurrentReturnValue(),
                             context.currentBlock());

    context.popBlock();

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
        e2::log::bug("func:", _id->name(), " not found!");
    }
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
    llvm::Value* value = _id->codeGen(context);
    std::string cname = _id->name();

    union_name(cname);

    if (_block != nullptr) {
        UNION_NAME(_block);
        _block->codeGen(context);
    }
    else {
        e2::log::info("block is null");
    }
    return value;

} /* -----  end of function UnionDeclaration::codeGen  ----- */
}  // namespace e2
