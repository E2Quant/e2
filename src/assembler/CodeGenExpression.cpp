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
#include <cstdint>
#include <exception>
#include <map>

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
    e2::log::bug("Number: ", _value);
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
 *
 * ============================================
 */
const std::string Expression::uname()
{
    if (_union_name.length() > 0) {
        return _union_name;
    }
    if (_id != nullptr) {
        return _id->name();
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
    std::string cname = name();
    bool _gl = FIND_GV(cname);

    if (_idtype == IDType::_global || _gl) {
        llvm::GlobalVariable* gVar = context.getModule()->getNamedGlobal(cname);
        if (gVar == nullptr) {
            if (_gl) {
                e2::log::bug("identifier gvar is nullptr! ", cname);
            }

            return nullptr;
        }
        return gVar->getOperand(0);
    }
    llvm::Value* val = nullptr;
    std::array<std::string, 2> args = {"__arg0", "__arg1"};
    for (std::size_t m = 0; m < 2; m++) {
        if (cname == args[m]) {
            val = context.MainArgx(m);
            return val;
        }
    }

    val = context.findBlockId(cname);
    if (val == nullptr) {
        return nullptr;
    }

    retType* type = val->getType();

    return new llvm::LoadInst(type, val, cname, true, context.currentBlock());
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
    if (_union_name.length() == 0 || _union_name.empty()) {
        return real_name();
    }

    _idtype = IDType::_global;
    return _union_name + "." + real_name();

} /* -----  end of function identifier::name  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Identifier::real_name
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
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
            name_full += "." + *it;
        }
    }

    return name_full;
} /* -----  end of function Identifier::real_name  ----- */

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
    e2::log::bug("lhs: ", _lhs->getType(), " rhs:", _rhs->getType());
    e2::log::bug("_op:", _op);
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
            return nullptr;
    }
    llvm::Value* rhs = CodeGen(_rhs);
    llvm::Value* lhs = CodeGen(_lhs);
    if (rhs == nullptr) {
        std::cout << "rhs is nullptr:" << _rhs->getType()
                  << " name:" << _rhs->uname() << " line:" << _codeLine
                  << " file:" << _path << std::endl;
        context.DontRun();

        return nullptr;
    }
    if (lhs == nullptr) {
        std::cout << "lhs is nullptr:" << _lhs->getType()
                  << " name:" << _lhs->uname() << " line:" << _codeLine
                  << " file:" << _path << std::endl;

        context.DontRun();

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
        return dret;
    }
    else if (_op == '/') {
        deci_instr = llvm::Instruction::Mul;

        ret = llvm::BinaryOperator::Create(deci_instr, lhs, deci, "mathtmp",
                                           context.currentBlock());

        dret = llvm::BinaryOperator::Create(instr, ret, rhs, "mathtmp2",
                                            context.currentBlock());
        return dret;
    }

#endif

    return llvm::BinaryOperator::Create(instr, lhs, rhs, "mathtmp",
                                        context.currentBlock());

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
        context.DontRun();
        return nullptr;
    }

    llvm::Value* idVal = nullptr;

    bool _gl = FIND_GV(cname);

    if (_id->idType() == IDType::_global || _gl) {
        return nullptr;
    }
    else {
        idVal = context.findBlockId(cname);
    }
    if (idVal == nullptr) {
        log::bug("error id");
        context.DontRun();

        return nullptr;
    }

    /* log::info("value type:", value->getType()->getTypeID(), */
    /*           " idval type:", idVal->getType()->isIntegerTy(), " name:",
     * cname, */
    /*           " code line:", _codeLine, " : ", value->getType()->getTypeID(),
     */
    /*           ": ", llvm::Type::TypeID::IntegerTyID); */

    return new llvm::StoreInst(value, idVal, true, context.currentBlock());
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
    if (_lhs == nullptr) {
        log::bug("comp operator lhs or rhs is nullptr. line:", _codeLine,
                 " file:", _path);
        return nullptr;
    }
    llvm::Value* rval = nullptr;
    llvm::Value* lval = nullptr;
    llvm::CmpInst* ret = nullptr;

    lval = CodeGen(_lhs);

    if (lval == nullptr) {
        if (_lhs->id() == nullptr) {
            log::bug("rval or lval is nullptr, lhs is null:", " rhs:",
                     _rhs->id()->name(), " . line:", _codeLine,
                     " file:", _path);
        }
        else if (_rhs != nullptr) {
            if (_rhs->id() != nullptr) {
                log::bug("rval or lval is nullptr, lhs:", _lhs->id()->name(),
                         " rhs:", _rhs->id()->name(), " . line:", _codeLine,
                         " file:", _path);
            }
            else if (_rhs->id() == nullptr) {
                log::bug("rval or lval is nullptr, lhs id null:",
                         " rhs id null :", " . line:", _codeLine,
                         " file:", _path);
            }
        }
        else {
            log::bug("rval or lval is nullptr, lhs:", _lhs->id()->name(),
                     " rhs id null:", " . line:", _codeLine, " file:", _path);
        }
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
                return lval;
            }
        }
        if (lval->getType()->getTypeID() == llvm::Type::TypeID::IntegerTyID) {
            return lval;
        }
        _op = yy::Parser::token::OP_NE;
        Int_e a = 0;
        _rhs = MALLOC(Number, a);
        _rhs->union_name("rhs_def");
        rval = CodeGen(_rhs);
    }
    else {
        rval = CodeGen(_rhs);
        if (rval == nullptr) {
            log::bug("comp operator  rhs is nullptr. line:", _codeLine,
                     " file:", _path);
            return nullptr;
        }
    }

#ifdef E2L_DEBUG
    e2::log::bug("---------lhs: ", _lhs->getType(), " rhs:", _rhs->getType());
    e2::log::bug("_op:", _op);

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
            log::bug("op is null ..");
            return nullptr;
    }

    ret = llvm::CmpInst::Create(oinstr, predicate, lval, rval, "cmptmp",
                                context.currentBlock());

    return ret;
} /* -----  end of function CompOperator::codeGen  ----- */

}  // namespace e2
