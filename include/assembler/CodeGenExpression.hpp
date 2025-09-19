/*
 * =====================================================================================
 *
 *       Filename:  CodeGenExpression.hpp
 *
 *    Description:  CodeGenExpression
 *
 *        Version:  1.0
 *        Created:  2023年11月01日 10时49分40秒
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

#ifndef CODEGENEXPRESSION_INC
#define CODEGENEXPRESSION_INC

#include <llvm/IR/Constants.h>

#include <cstddef>
#include <cstring>
#include <string>

#include "BaseNode.hpp"
#include "BaseType.hpp"
#include "assembler/BaseNode.hpp"
#include "assembler/CodeGenContext.hpp"
#include "utility/Log.hpp"

namespace e2 {

/*
 * ================================
 *        Class:  Number
 *  Description:  [0-9.] to bignumber
 *  到时候再优化
 * ================================
 */
class Number : public Expression {
public:
    /* =============  LIFECYCLE     =================== */
    Number(Int_e value)
    {
        /**
         * cmake set
         */
#ifdef NUMBER_DECI
        _value = value * NUMBER_DECI;
#else
        _value = value;
#endif
    };
    Number(Int_e value, bool t)
    {
        /**
         * cmake set
         */
#ifdef NUMBER_DECI
        _value = value * NUMBER_DECI;
#else
        _value = value;
#endif
        if (t) {
            negative();
        }
    };
    /* constructor */
    Number(float value)
    {
#ifdef NUMBER_DECI
        _value = (Int_e)(value * NUMBER_DECI);
#else
        _value = (Int_e)(value);
#endif
    };
    Number(float value, bool t)
    {
#ifdef NUMBER_DECI
        _value = (Int_e)(value * NUMBER_DECI);
#else
        _value = (Int_e)(value);
#endif
        if (t) {
            negative();
        }
    };
    /* =============  ACCESSORS     =================== */
    virtual llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_number; }
    /* =============  MUTATORS      =================== */
    void negative()
    {
        _neg = 1;
        _value = -_value;
    }
    Int_e value() { return _value; }
    void genuine() { _value /= NUMBER_DECI; }
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    Int_e _value;
    int _neg{0};  // 否则为负数

}; /* -----  end of class Number  ----- */

/*
 * ================================
 *        Class:  StrObj
 *  Description:
 * ================================
 */
class StrObj : public Expression {
public:
    /* =============  LIFECYCLE     =================== */
    StrObj(std::string str, size_t line, const char *path)
    {
        _str = str.substr(1, str.length() - 2);
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    };
    StrObj(std::string str, bool full) : _str(str) {};

    ~StrObj() {}
    /* constructor */

    /* =============  ACCESSORS     =================== */
    virtual llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_string; }

    /* =============  MUTATORS      =================== */
    std::string value() { return _str; };
    void name(std::string n)
    {
        _name = llog::format("_str_%s_%ld_%ld", n.c_str(), _codeLine,
                             variable_str_num++);
    }

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    std::string _str;

    std::string _name = "";
    // std::size_t _idx = 0;
}; /* -----  end of class StrObj  ----- */

/*
 * ================================
 *        Class:  BinaryOperator
 *  Description:  eg .  b > c;  b < 13;  13 != B
 * ================================
 */
class BinaryOperator : public Expression {
public:
    /* =============  LIFECYCLE     =================== */
    BinaryOperator(Expression *lhs, int op, Expression *rhs, size_t line,
                   const char *path)
        : _op(op), _lhs(lhs), _rhs(rhs)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    };
    BinaryOperator(Expression *lhs, int op, size_t line, const char *path)
        : _op(op), _lhs(lhs)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
        _rhs = nullptr;
    }

    /* constructor */
    ~BinaryOperator()
    {
        RELEASE(_lhs);
        RELEASE(_rhs);
    }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_binaryop; }

    const std::string name()
    {
        if (_rhs == nullptr) {
            return _lhs->uname() + " [ " + std::to_string(_op) + " ]";
        }
        else {
            return _lhs->uname() + " [ " + std::to_string(_op) + " ] " +
                   _rhs->uname();
        }
    };

    /* =============  MUTATORS      =================== */

    Expression *lhs() { return _lhs; }
    Expression *rhs() { return _rhs; }
    int op() { return _op; }
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

    int _op{0};
    Expression *_lhs{nullptr};
    Expression *_rhs{nullptr};

}; /* -----  end of class BinaryOperator  ----- */

/*
 * ================================
 *        Class:  Assignment
 *  Description:  主要用在 取 右则变量 和 method call 上面
 *  eg.
 *  call.   echo(a);  echo(3);
 * ================================
 */
class Assignment : public Expression {
public:
    /* =============  LIFECYCLE     =================== */
    Assignment(Identifier *id, Expression *exp, size_t line, const char *path)
        : _rhs(exp)
    {
        _id = std::move(id);
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;

    }; /* constructor */
    ~Assignment()
    {
        RELEASE(_id);
        RELEASE(_rhs);
    }
    /* =============  ACCESSORS     =================== */
    virtual llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_binaryop; }
    const std::string name()
    {
        if (_rhs == nullptr) {
            return _id->uname() + " []";
        }
        else {
            return _id->uname() + " - " + _rhs->uname();
        }
    };

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

    Expression *_rhs{nullptr};
}; /* -----  end of class Assignment  ----- */

/*
 * ================================
 *        Class:  CompOperator
 *  Description: eg. a != b ; a < b ;  a >= b
 *              return true false 0  1
 * ================================
 */
class CompOperator : public Expression {
public:
    /* =============  LIFECYCLE     =================== */
    CompOperator(Expression *lhs, int op, Expression *rhs, size_t line,
                 const char *path)
        : _op(op), _lhs(lhs), _rhs(rhs)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    }; /* constructor */

    CompOperator(Expression *lhs, size_t line, const char *path) : _lhs(lhs)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    }
    ~CompOperator()
    {
        RELEASE(_lhs);
        RELEASE(_rhs);
    }
    /* =============  ACCESSORS     =================== */
    virtual llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_comp; }
    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

    int _op{0};
    Expression *_lhs{nullptr};
    Expression *_rhs{nullptr};
}; /* -----  end of class CompOperator  ----- */

}  // namespace e2
#endif /* ----- #ifndef CODEGENEXPRESSION_INC  ----- */
