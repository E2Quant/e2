/*
 * =====================================================================================
 *
 *       Filename:  CodeGenStatement.hpp
 *
 *    Description:  CodeGenStatement
 *
 *        Version:  1.0
 *        Created:  2023年11月01日 10时50分05秒
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

#ifndef CODEGENSTATEMENT_INC
#define CODEGENSTATEMENT_INC

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <string>
#include <vector>

#include "BaseType.hpp"
#include "assembler/BaseNode.hpp"
#include "assembler/CodeGenExpression.hpp"
namespace e2 {

/*
 * ================================
 *        Class:  ExpressionStatement
 *  Description:  eg..  a * b;  a + 0
 * ================================
 */
class ExpressionStatement : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    ExpressionStatement(Expression *exp) : _expression(exp){};
    ExpressionStatement(Statement *stat) : _statement(stat){};
    /* constructor */
    ~ExpressionStatement()
    {
        RELEASE(_expression);
        RELEASE(_statement);
    }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType()
    {
        if (_expression) {
            return NodeType::_expression;
        }
        return NodeType::_statement;
    }

    /* =============  MUTATORS      =================== */
    Expression *exp() { return _expression; }
    Statement *sta() { return _statement; }
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    Expression *_expression{nullptr};
    Statement *_statement{nullptr};
}; /* -----  end of class ExpressionStatement  ----- */

/*
 * ================================
 *        Class:  MethodCall
 *  Description:  function call :  eg.  echo(arg);
 * ================================
 */
class MethodCall : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    explicit MethodCall(Identifier *id, ExpressionList *arguments, size_t line,
                        const char *path)
        : _arguments(arguments)
    {
        _id = std::move(id);

        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    };

    MethodCall(std::string id, ExpressionList *arguments, size_t line,
               const char *path)
        : _arguments(arguments)
    {
        _id = MALLOC(Identifier, id, IDType::_normal);
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    };
    /* constructor */
    ~MethodCall()
    {
        if (_arguments) {
            for (auto a : *_arguments) {
                RELEASE(a);
            }
            _arguments->clear();
            RELEASE(_arguments);
        }
        RELEASE(_id);
    }
    /* =============  ACCESSORS     =================== */
    virtual llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_methodcall; }
    const std::string name() { return _id->name(); };

    /* =============  MUTATORS      =================== */
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /**
     *
     * call fun echo or PrintXXX
     *  差不多了，以后再优化
     */
    void DebugLoc()
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
            StrObj *str = MALLOC(StrObj, _path, true);

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
                    Identifier *id = (Identifier *)_arguments->at(0);
                    vname = id->name();
                }
                StrObj *vn = MALLOC(StrObj, vname, true);
                _arguments->push_back(vn);
            }

            e2::Number *line = MALLOC(Number, (Int_e)_codeLine);
            line->genuine();
            _arguments->push_back(line);

            StrObj *str = MALLOC(StrObj, _path, true);
            _arguments->push_back(str);
        }
    }

    /* =============  DATA MEMBERS  =================== */

    ExpressionList *_arguments{nullptr};

}; /* -----  end of class MethodCall  ----- */

/*
 * ================================
 *        Class:  BreakStatement
 *  Description:
 * ================================
 */
class BreakStatement : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    BreakStatement()
    {
        Int_e val = 1;
        _expression = MALLOC(Number, val);

    }; /* constructor */
    ~BreakStatement() { RELEASE(_expression); }
    /* =============  ACCESSORS     =================== */

    /* =============  MUTATORS      =================== */
    llvm::Value *codeGen(CodeGenContext &context)
    {
        context.setBreakPoint(true);
        return nullptr;
    };
    NodeType getType() { return NodeType::_break; }

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    Expression *_expression{nullptr};

}; /* -----  end of class BreakStatement  ----- */

/*
 * ================================
 *        Class:  ReturnStatement
 *  Description: eg. return abc;
 *  return 需要有值，否则报错
 * ================================
 */
class ReturnStatement : public Statement {
public:
    /*i =============  LIFECYCLE     =================== */
    ReturnStatement(size_t line, const char *path)
    {
        Int_e val = 0;
        _expression = MALLOC(Number, val);
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    };
    ReturnStatement(Expression *exp, size_t line, const char *path)
        : _expression(exp)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    }; /* constructor */
    ~ReturnStatement() { RELEASE(_expression); }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_return; }

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    Expression *_expression{nullptr};
}; /* -----  end of class ReturnStatement  ----- */

/*
 * ================================
 *        Class:  VariableStatement
 *  Description:  eg. func  echo(a,b,c)
 *  用在定义函数, 变量左则 值上面， 之前没有出现过的
 * ================================
 */
class VariableStatement : public Statement {
public:
    /* =============  LIFECYCLE     =================== */

    VariableStatement(Identifier *id, int op, Expression *rhs, size_t line,
                      const char *path)
        : _op(op), _rhs(rhs)
    {
        _id = std::move(id);
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    };
    /* VariableStatement(Identifier *id) */
    /* { */
    /*     _id = std::move(id); */
    /*     _rhs = nullptr; */
    /* }; */
    /* constructor */

    ~VariableStatement()
    {
        if (_ass == nullptr) {
            RELEASE(_id);
            RELEASE(_rhs);
        }
        else {
            RELEASE(_ass);
        }

        // RELEASE(_rhs);
    }
    /* =============  ACCESSORS     =================== */
    virtual llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_variable; }

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

    int _op{0};
    Expression *_rhs{nullptr};

    Assignment *_ass{nullptr};
}; /* -----  end of class VariableStatement  ----- */
typedef std::vector<VariableStatement *> VariableList;

/*
 * ================================
 *        Class:  UnaryOperator
 *  Description:
 * ================================
 */
class UnaryOperator : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    UnaryOperator(Identifier *id, int op, size_t line, const char *path)
        : _op(op)
    {
        _id = std::move(id);
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    }; /* constructor */
    ~UnaryOperator() { RELEASE(_id); }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_binaryop; }

    const std::string name()
    {
        return _id->uname() + "()" + std::to_string(_op);
    };

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

    int _op{0};

}; /* -----  end of class UnaryOperator  ----- */

/*
 * ================================
 *        Class:  FunctionDeclaration
 *  Description:  func abc ( arg ) { block; }
 * ================================
 */
class FunctionDeclaration : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    FunctionDeclaration(Identifier *id, ExpressionList *arguments, Block *block)
        : _arguments(arguments), _block(block)
    {
        _id = std::move(id);
    };
    FunctionDeclaration(std::string id, ExpressionList *arguments, Block *block)
        : _arguments(arguments), _block(block)
    {
        _id = MALLOC(Identifier, id, IDType::_normal);
    };

    /* constructor */
    ~FunctionDeclaration()
    {
        RELEASE(_id);
        RELEASE(_block);

        if (_arguments != nullptr) {
            for (auto it : *_arguments) {
                RELEASE(it);
            }
            _arguments->clear();

            RELEASE(_arguments);
        }
    }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_function; }

    /* =============  MUTATORS      =================== */
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    ExpressionList *_arguments{nullptr};
    Block *_block{nullptr};
}; /* -----  end of class FunctionDeclaration  ----- */

/*
 * ================================
 *        Class:  ExternDeclaration
 *  Description:
 * ================================
 */
class ExternDeclaration : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    ExternDeclaration(Identifier *id, ExpressionList *args) : _arguments(args)
    {
        _id = std::move(id);
    };
    ExternDeclaration(std::string id, ExpressionList *arguments)
        : _arguments(arguments)
    {
        _id = MALLOC(Identifier, id, IDType::_normal);
    };
    /* constructor */
    ~ExternDeclaration()
    {
        RELEASE(_id);

        if (_arguments != nullptr) {
            for (auto it : *_arguments) {
                RELEASE(it);
            }
            _arguments->clear();

            RELEASE(_arguments);
        }
    }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_function; }

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    ExpressionList *_arguments{nullptr};

}; /* -----  end of class ExternDeclaration  ----- */

/*
 * ================================
 *        Class:  UnionDeclaration
 *  Description:
 * ================================
 */
class UnionDeclaration : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    UnionDeclaration() {}
    UnionDeclaration(Identifier *id, Block *block) : _block(block)
    {
        _id = std::move(id);
    };

    UnionDeclaration(std::string id, Block *block) : _block(block)
    {
        _id = MALLOC(Identifier, id, IDType::_global);
    };
    /* constructor */
    ~UnionDeclaration()
    {
        RELEASE(_id);
        RELEASE(_block);
    }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context);
    NodeType getType() { return NodeType::_union; }

    llvm::StructType *UnionType() { return _unionType; };
    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    Block *_block{nullptr};

    llvm::StructType *_unionType{nullptr};
}; /* -----  end of class UnionDeclaration  ----- */

}  // namespace e2
#endif /* ----- #ifndef CODEGENSTATEMENT_INC  ----- */
