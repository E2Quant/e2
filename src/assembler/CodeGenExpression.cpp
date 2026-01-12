/*
 * =====================================================================================
 *
 *       Filename:  CodeGenExpression.cpp
 *
 *    Description: CodeGenExpression
 *
 *        Version:  1.0
 *        Created:  2023年11月01日 10时55分53秒
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

#include "assembler/CodeGenExpression.hpp"

#include <llvm/ADT/StringRef.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/SourceMgr.h>

#include <array>
#include <cstddef>
#include <string>

#include "assembler/BaseNode.hpp"
#include "assembler/BaseType.hpp"
#include "generated/e2_bison.hpp"
namespace e2 {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ImportModule::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* ImportModule::codeGen(CodeGenContext& context)
{
    return nullptr;
} /* -----  end of function ImportModule::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Number::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* Number::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("Number");
#endif
#ifdef E2L_DEBUG
    ExitCode("Number");
#endif

    return llvm::ConstantInt::get(context.defType(), _value, true);
}

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  StrObj::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* StrObj::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("StrObj");
#endif
    // https://stackoverflow.com/questions/51809274/llvm-defining-strings-and-arrays-via-c-api
    auto charType = E2LStr(context.getGlobalContext());

    // 1. Initialize chars vector
    std::vector<llvm::Constant*> chars(_str.length());
    for (unsigned int i = 0; i < _str.size(); i++) {
        chars[i] = llvm::ConstantInt::get(charType, _str[i]);
    }

    // 1b. add a zero terminator too
    chars.push_back(llvm::ConstantInt::get(charType, 0));

    // 2. Initialize the string from the characters
    auto stringType = llvm::ArrayType::get(charType, chars.size());

    // 3. Create the declaration statement
    auto globalDeclaration =
        (llvm::GlobalVariable*)context.getModule()->getOrInsertGlobal(
            _name, stringType);
    globalDeclaration->setInitializer(
        llvm::ConstantArray::get(stringType, chars));
    globalDeclaration->setConstant(true);
    globalDeclaration->setLinkage(
        llvm::GlobalValue::LinkageTypes::PrivateLinkage);
    globalDeclaration->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);

#ifdef E2L_DEBUG
    ExitCode("StrObj");
#endif
    // 4. Return a cast to an i8*
    return llvm::ConstantExpr::getBitCast(globalDeclaration,
                                          charType->getPointerTo());

} /* -----  end of function StrObj::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Expression::uname
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   只返回当前几层 union 的信息
 * ============================================
 */
const std::string Expression::uname()
{
    if (_union_name.length() > 0) {
        return _union_name;
    }

    return "";
}

/* -----  end of function Expression::uname  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Identifier::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* Identifier::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("Identifier");
#endif
    UNION_NAME(_id, context);

    std::string cname = name();
    bool _gl = FIND_GV(cname);
    std::string name_space = context.getNameSpace();

    if (_idtype == IDType::_global || _gl) {
        llvm::GlobalVariable* gVar = context.getModule()->getNamedGlobal(cname);
        if (gVar == nullptr) {
            if (_gl) {
                llog::bug(
                    "can't found the globale variable:" + cname + " .line : ",
                    _codeLine, " file:", _path, " type:", _idtype);
            }
#ifdef E2L_DEBUG
            ExitCode("Identifier");
#endif
            return nullptr;
        }
#ifdef E2L_DEBUG
        ExitCode("Identifier");
#endif
        return gVar->getOperand(0);
    }
    llvm::Value* val = nullptr;
    std::array<std::string, 2> args = {"__arg0", "__arg1"};
    for (std::size_t m = 0; m < 2; m++) {
        if (cname == args[m]) {
            val = context.MainArgx(m);
#ifdef E2L_DEBUG
            ExitCode("Identifier");
#endif
            return val;
        }
    }

    if (name_space.length() > 0 && _idtype == IDType::_ns_private) {
        NameSpaceInitCodeAssign assptr = context.getNameSpaceAssign(name_space);

        llvm::Value* nsalloc = nullptr;
        std::string ass_name = "";
        for (Assignment* it : assptr) {
            ass_name = it->id()->name();
            if (ass_name == name_space + "_" + cname) {
                // 同一个 function block 内
                nsalloc = context.getNameSpaceVarAccessInst(name_space,
                                                            ass_name, nullptr);
                if (nsalloc == nullptr) {
                    // block ns var 这儿如果没有初始化，才会进这儿来

                    nsalloc = it->codeGen(context);
                }

                break;
            }
        }

        if (nsalloc != nullptr) {
            retType* ctype = nsalloc->getType()->getPointerElementType();

#ifdef E2L_DEBUG
            ExitCode("Identifier");
#endif
            return new llvm::LoadInst(ctype, nsalloc, name_space + "_" + cname,
                                      false, storeinst_align,
                                      context.currentBlock());
        }
        llog::bug("can't found the findBlockId variable:" + cname + " .line : ",
                  _codeLine, " file:", _path, " type:", _idtype);
#ifdef E2L_DEBUG
        ExitCode("Identifier");
#endif
        return nullptr;
    }

    val = context.findBlockId(cname);
    if (val == nullptr) {
#ifdef E2L_DEBUG
        ExitCode("Identifier");
#endif
        return nullptr;
    }

    retType* type = E2LType(context.getGlobalContext());  // val->getType();
#ifdef E2L_DEBUG
    ExitCode("Identifier");
#endif
    return new llvm::LoadInst(type, val, cname, false, storeinst_align,
                              context.currentBlock());
}

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  identifier::name
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
const std::string Identifier::name()
{
    std::string value = real_name();
    std::string un = uname();
#ifdef E2L_DEBUG
    llog::echo("un:", un, ", real:", value);
#endif

    if (_idtype == IDType::_global) {
        // UnionDeclaration 中
        std::string union_parent = un;
        if (union_parent.length() > 0) {
            value = union_parent + UnionName(value);  // "." + value;
        }
    }
    return value;

} /* -----  end of function identifier::name  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Identifier::real_name
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   _name 基本上是在 bison.y 那儿进来的变量名字
 * ============================================
 */
const std::string Identifier::real_name()
{
    std::string name_full = "";

    for (auto it = _name.begin(); it != _name.end(); it++) {
        if (name_full.empty()) {
            name_full = *it;
        }
        else {
            if (_idtype == IDType::_global) {
                // union
                name_full += UnionName(*it);  // "." + *it;
            }
            else {
                // namespace
                // *it + "_" + name_full;
                name_full = NameSpaceFunc(*it, name_full);
            }
        }
    }
#ifdef E2L_DEBUG
    llog::echo("un:", name_full, " type:", _idtype);
#endif
    return name_full;
} /* -----  end of function Identifier::real_name  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Identifier::id_name
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
const std::string Identifier::id_name()
{
    std::string idn = _name.front();
    return idn;
} /* -----  end of function Identifier::id_name  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  BinaryOperator::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* BinaryOperator::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("BinaryOperator");
#endif

#ifdef E2L_DEBUG
    e2::llog::bug("lhs: ", _lhs->getType(), " rhs:", _rhs->getType());
    e2::llog::bug("_op:", _op);
#endif
    llvm::Instruction::BinaryOps instr;
    switch (_op) {
        case '+':
            instr = llvm::Instruction::Add;
            break;
        case '-':
            instr = llvm::Instruction::Sub;
            break;
        case '*':
            instr = llvm::Instruction::Mul;
            break;
        case '/':
            instr = llvm::Instruction::SDiv;
            break;
        case '%':
            instr = llvm::Instruction::SRem;
            break;
        case yy::Parser::token::LOGICAL_OR:
            instr = llvm::Instruction::Or;
            break;
        case yy::Parser::token::LOGICAL_AND:
            instr = llvm::Instruction::And;
            break;
        default:
#ifdef E2L_DEBUG
            ExitCode("BinaryOperator");
#endif
            return nullptr;
    }
    llvm::Value* lhs = CodeGen(_lhs);
    llvm::Value* rhs = CodeGen(_rhs);

    if (rhs == nullptr) {
        llog::bug("rhs is nullptr:", _rhs->getType(),
                  " name:", _rhs->id()->name(), " line:", _codeLine,
                  " file:", _path);
        context.DontRun();
#ifdef E2L_DEBUG
        ExitCode("BinaryOperator");
#endif
        return nullptr;
    }
    if (lhs == nullptr) {
        llog::bug("lhs is nullptr:", _lhs->getType(),
                  " name:", _lhs->id()->name(), " line:", _codeLine,
                  " file:", _path);

        context.DontRun();
#ifdef E2L_DEBUG
        ExitCode("BinaryOperator");
#endif
        return nullptr;
    }

    llvm::BinaryOperator* ret = nullptr;
    llvm::Instruction::BinaryOps deci_instr;

    /**
     * 先这样限一下先，到时候，有必要了，再优化
     */

    /**
     * 如果是 bool 类型就转成 double 类型
     */
    if (lhs->getType()->getTypeID() == llvm::Type::TypeID::IntegerTyID) {
        auto cinstr = llvm::CastInst::getCastOpcode(
            lhs, true, llvm::Type::getDoublePtrTy(context.getGlobalContext()),
            true);
        lhs = llvm::CastInst::Create(
            cinstr, lhs, llvm::Type::getDoublePtrTy(context.getGlobalContext()),
            "castdb", context.currentBlock());
    }

    if (rhs->getType()->getTypeID() == llvm::Type::TypeID::IntegerTyID) {
        auto cinstr = llvm::CastInst::getCastOpcode(
            rhs, true, llvm::Type::getDoublePtrTy(context.getGlobalContext()),
            true);
        rhs = llvm::CastInst::Create(
            cinstr, rhs, llvm::Type::getDoublePtrTy(context.getGlobalContext()),
            "castdb", context.currentBlock());
    }

#ifdef NUMBER_DECI

    llvm::Constant* deci =
        llvm::ConstantInt::get(context.defType(), NUMBER_DECI, true);

    llvm::BinaryOperator* dret = nullptr;
    if (_op == '*') {
        ret = llvm::BinaryOperator::Create(instr, lhs, rhs, "mathtmp",
                                           context.currentBlock());

        deci_instr = llvm::Instruction::SDiv;
        dret = llvm::BinaryOperator::Create(deci_instr, ret, deci, "mathtmp2",
                                            context.currentBlock());
#ifdef E2L_DEBUG
        ExitCode("BinaryOperator");
#endif
        return dret;
    }
    else if (_op == '/') {
        deci_instr = llvm::Instruction::Mul;

        ret = llvm::BinaryOperator::Create(deci_instr, lhs, deci, "mathtmp",
                                           context.currentBlock());

        dret = llvm::BinaryOperator::Create(instr, ret, rhs, "mathtmp2",
                                            context.currentBlock());
#ifdef E2L_DEBUG
        ExitCode("BinaryOperator");
#endif
        return dret;
    }

#endif

    if (instr == llvm::Instruction::SDiv) {
        llvm::ConstantInt* ck = llvm::dyn_cast<llvm::ConstantInt>(rhs);
        if (ck->isZero()) {
            llog::bug("rhs is zeor!");
            context.DontRun();

#ifdef E2L_DEBUG
            ExitCode("BinaryOperator");
#endif

            return nullptr;
        }
    }
    llvm::BinaryOperator* bop = llvm::BinaryOperator::Create(
        instr, lhs, rhs, "mathtmp", context.currentBlock());

#ifdef E2L_DEBUG
    ExitCode("BinaryOperator");
#endif

    return bop;
} /* -----  end of function BinaryOperator::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Assignment::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   主要用在 取 右则变量 和 method call 上面, 已存在的
 * ============================================
 */
llvm::Value* Assignment::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("Assignment");
#endif

    std::string cname = _id->name();

    NodeType nt = _rhs->getType();

    if (nt == NodeType::_string) {
        StrObj* str_obj = (StrObj*)_rhs;
        str_obj->name(cname);
    }
    /**
     * call 返回 char 到时候再修改好了
     */
    /* if (nt == NodeType::_methodcall) { */

    /* } */
    llvm::Value* value = _rhs->codeGen(context);
    if (value == nullptr) {
        llog::bug(
            "can't found the right value for variable:" + cname + " . line : ",
            _codeLine, " file:", _path);
        context.DontRun();
#ifdef E2L_DEBUG
        ExitCode("Assignment");
#endif
        return nullptr;
    }

    llvm::AllocaInst* idVal = nullptr;

    bool _gl = FIND_GV(cname);

    if (_id->idType() == IDType::_global || _gl) {
        llog::bug("can't found the globale variable:" + cname + " . line : ",
                  _codeLine, " file:", _path);
#ifdef E2L_DEBUG
        ExitCode("Assignment");
#endif
        return nullptr;
    }
    else {
        idVal = context.findBlockId(cname);
    }
    if (idVal == nullptr) {
        std::string name_space = context.getNameSpace();
        if (_id->idType() == IDType::_ns_private && name_space.length() > 0) {
            std::string func = context.currentFuncName();
            std::string arg_name = NameSpaceSelfArg(func);
            if (context.isNSSelfFunc(func)) {
                arg_name = NameSpaceSelfFunc(arg_name);
            }
            llvm::AllocaInst* ns_Val = context.findBlockId(arg_name);

            if (ns_Val == nullptr) {
                llog::bug("arg_name not found:", arg_name);
                context.DontRun();
#ifdef E2L_DEBUG
                ExitCode("Assignment");
#endif
                return nullptr;
            }

            llvm::Instruction* gep =
                context.getNameSpaceVarAccessInst(name_space, cname, ns_Val);
            if (gep == nullptr) {
                llog::bug("get namespace var inst is nullptr:", arg_name);
                context.DontRun();
#ifdef E2L_DEBUG
                ExitCode("Assignment");
#endif
                return nullptr;
            }
            if (!checkNsInit()) {
                // 同时再检查同一个 ns 中的 cname 是不是在之前就来过儿
                // 如果来过了，ns init 就要 设置 就不需要再来 store 了
                // 毕竟儿是在 右值这儿调用的

                // llvm::StringRef sr = context.currentBlock()->getName();
                // llog::echo("it's ns init variable ns:", name_space,
                //            " function:", sr.str());
                new llvm::StoreInst(value, gep, false, storeinst_align,
                                    context.currentBlock());
            }

#ifdef E2L_DEBUG
            ExitCode("Assignment");
#endif
            return gep;
        }
        else {
            llog::info("nsalloc");
        }
        llog::bug("can't found the  variable:" + cname, " idtype:", nt,
                  " . line : ", _codeLine, " ns :", name_space,
                  " file:", _path);
        context.DontRun();
#ifdef E2L_DEBUG
        ExitCode("Assignment");
#endif
        return nullptr;
    }

    llvm::StoreInst* si = new llvm::StoreInst(
        value, idVal, false, storeinst_align, context.currentBlock());

#ifdef E2L_DEBUG
    ExitCode("Assignment");
#endif
    return si;
} /* -----  end of function Assignment::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CompOperator::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* CompOperator::codeGen(CodeGenContext& context)
{
#ifdef E2L_DEBUG
    EnterCode("CompOperator");
#endif

    if (_lhs == nullptr) {
        llog::bug("comp operator lhs or rhs is nullptr. line:", _codeLine,
                  " file:", _path);
#ifdef E2L_DEBUG
        ExitCode("CompOperator");
#endif

        return nullptr;
    }
    llvm::Value* rval = nullptr;
    llvm::Value* lval = nullptr;
    llvm::CmpInst* ret = nullptr;

    lval = CodeGen(_lhs);

    if (lval == nullptr) {
        if (_lhs->id() == nullptr) {
            llog::bug("rval or lval is nullptr, lhs is null:", " rhs:",
                      _rhs->id()->name(), " . line:", _codeLine,
                      " file:", _path);
        }
        else if (_rhs != nullptr) {
            if (_rhs->id() != nullptr) {
                llog::bug("rval or lval is nullptr, lhs:", _lhs->id()->name(),
                          " rhs:", _rhs->id()->name(), " . line:", _codeLine,
                          " file:", _path);
            }
            else if (_rhs->id() == nullptr) {
                llog::bug("rval or lval is nullptr, lhs id null:",
                          " rhs id null :", " . line:", _codeLine,
                          " file:", _path);
            }
        }
        else {
            llog::bug("rval or lval is nullptr, lhs:", _lhs->id()->name(),
                      " rhs id null:", " . line:", _codeLine, " file:", _path);
        }
#ifdef E2L_DEBUG
        ExitCode("CompOperator");
#endif
        return nullptr;
    }

    if (_rhs == nullptr) {
        if (lval->getType()->getTypeID() == llvm::Type::TypeID::PointerTyID) {
            llvm::PointerType* ptine =
                llvm::dyn_cast<llvm::PointerType>(lval->getType());
            llvm::Type* vtype = ptine->getPointerElementType();

            llvm::IntegerType* inttype =
                llvm::dyn_cast<llvm::IntegerType>(vtype);

            if (inttype->getBitWidth() == 1) {
#ifdef E2L_DEBUG
                ExitCode("CompOperator");
#endif
                return lval;
            }
        }
        if (lval->getType()->getTypeID() == llvm::Type::TypeID::IntegerTyID) {
#ifdef E2L_DEBUG
            ExitCode("CompOperator");
#endif
            return lval;
        }
        _op = yy::Parser::token::OP_NE;
        Int_e a = 0;
        _rhs = MALLOC(Number, a, _codeLine, _path.c_str());
        _rhs->union_name("rhs_def");
        rval = CodeGen(_rhs);
    }
    else {
        rval = CodeGen(_rhs);
        if (rval == nullptr) {
            llog::bug("comp operator  rhs is nullptr. line:", _codeLine,
                      " file:", _path);
#ifdef E2L_DEBUG
            ExitCode("CompOperator");
#endif
            return nullptr;
        }
    }

#ifdef E2L_DEBUG
    e2::llog::bug("---------lhs: ", _lhs->getType(), " rhs:", _rhs->getType());
    e2::llog::bug("_op:", _op);

#endif

    llvm::Instruction::OtherOps oinstr = llvm::Instruction::ICmp;
    llvm::CmpInst::Predicate predicate = llvm::CmpInst::ICMP_EQ;

    switch (_op) {
        case yy::Parser::token::OP_EQ:
            // ==

            predicate = llvm::CmpInst::ICMP_EQ;
            break;
        case yy::Parser::token::OP_LE:
            //<=

            predicate = llvm::CmpInst::ICMP_SLE;
            break;
        case yy::Parser::token::OP_GE:

            //>=
            predicate = llvm::CmpInst::ICMP_SGE;
            break;
        case yy::Parser::token::OP_NE:

            // !=
            predicate = llvm::CmpInst::ICMP_NE;
            break;
        case '<':

            predicate = llvm::CmpInst::ICMP_SLT;
            break;
        case '>':
            predicate = llvm::CmpInst::ICMP_SGT;
            break;

        default:
            llog::bug("op is null ..");
#ifdef E2L_DEBUG
            ExitCode("CompOperator");
#endif
            return nullptr;
    }

    ret = llvm::CmpInst::Create(oinstr, predicate, lval, rval, "cmptmp",
                                context.currentBlock());
#ifdef E2L_DEBUG
    ExitCode("CompOperator");
#endif
    return ret;
} /* -----  end of function CompOperator::codeGen  ----- */

}  // namespace e2
