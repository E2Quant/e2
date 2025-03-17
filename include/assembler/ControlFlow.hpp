/*
 * =====================================================================================
 *
 *       Filename:  ControlFlow.hpp
 *
 *    Description:  ControlFlow
 *
 *        Version:  1.0
 *        Created:  2023年11月03日 10时07分22秒
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

#ifndef CONTROLFLOW_INC
#define CONTROLFLOW_INC

#include <llvm/IR/Value.h>

#include <algorithm>
#include <cstddef>
#include <tuple>
#include <vector>

#include "BaseType.hpp"
#include "assembler/BaseNode.hpp"
#include "assembler/CodeGenExpression.hpp"
#include "assembler/CodeGenStatement.hpp"

namespace e2 {

using LBType = std::vector<std::tuple<Expression *, Block *, Selection>>;
/*
 * ================================
 *        Class:  LabledBlock
 *  Description:
 * ================================
 */
class LabledBlock : public Block {
public:
    /* =============  LIFECYCLE     =================== */
    LabledBlock(const std::string name, size_t line, const char *path)
        : Block(name, line, path)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    };

    ~LabledBlock()
    {
        for (auto it : _labled) {
            auto one = std::get<0>(it);
            RELEASE(one);
            auto two = std::get<1>(it);
            RELEASE(two);
        }
    }

    /* constructor */

    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context) override;
    NodeType getType() override { return NodeType::_block; }

    /* =============  MUTATORS      =================== */
    void push(Expression *cond, Block *block, Selection selection)
    {
        _labled.push_back(std::make_tuple(cond, block, selection));
    };

    void push(Block *block, Selection selection)
    {
        _labled.push_back(std::make_tuple(nullptr, block, selection));
    };

    size_t size() { return _labled.size(); }
    Expression *toCase(size_t index) { return std::get<0>(_labled.at(index)); }
    Block *block(size_t index) { return std::get<1>(_labled.at(index)); }
    Selection selection(size_t index) { return std::get<2>(_labled.at(index)); }
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

    LBType _labled;
}; /* -----  end of class LabledBlock  ----- */

/*
 * ================================
 *        Class:  IFStatement
 *  Description:
 * ================================
 */
class IFStatement : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    IFStatement(Expression *exp, LabledBlock *lableBlock, size_t line,
                const char *path)
        : _exp(exp), _labledBlock(lableBlock)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;
    };

    ~IFStatement()
    {
        // RELEASE(_exp);
        RELEASE(_Comp);
        RELEASE(_labledBlock);
    }
    /* constructor */

    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context) override;
    NodeType getType() override { return NodeType::_ifcf; }
    /* =============  MUTATORS      =================== */
    Selection type() { return Selection::_if; };

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    Expression *_exp{nullptr};
    CompOperator *_Comp{nullptr};
    LabledBlock *_labledBlock{nullptr};

}; /* -----  end of class IFStatement  ----- */

/*
 * ================================
 *        Class:  SwitchStatement
 *  Description:
 * ================================
 */
class SwitchStatement : public Statement {
public:
    /* =============  LIFECYCLE     =================== */

    SwitchStatement(Expression *condition, LabledBlock *lableBlock)
        : _condition(condition),
          _labledBlock(lableBlock){

          };

    /* constructor */

    ~SwitchStatement()
    {
        RELEASE(_condition);
        RELEASE(_labledBlock);
    }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context) override;
    NodeType getType() override { return NodeType::_switchcf; }

    /* =============  MUTATORS      =================== */
    Selection type() { return Selection::_switch; };

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    Expression *_condition{nullptr};
    LabledBlock *_labledBlock{nullptr};

}; /* -----  end of class SwitchStatement  ----- */

/*
 * ================================
 *        Class:  IterStatement
 *  Description:
 * ================================
 */
class IterStatement : public Statement {
public:
    /* =============  LIFECYCLE     =================== */

    /*
     * ===  FUNCTION
     * ======================================================================
     *         Name:  IterStatement
     *  Description:  while (){};  do{}while();
     * =====================================================================================
     */
    IterStatement(Expression *cond, Block *block, IterType it)
        : _block(block), _it(it)
    {
        _initial = nullptr;
        _range = nullptr;

        if (cond->getType() != NodeType::_comp) {
            _condition = MALLOC(CompOperator, cond, 0, nullptr);
        }
        else {
            _condition = dynamic_cast<CompOperator *>(cond);
        }
    };
    /*
     * ===  FUNCTION
     * ======================================================================
     *         Name:  IterStatement
     *  Description:  for(a=2; a<b;) {}
     * =====================================================================================
     */
    IterStatement(VariableStatement *init, Expression *cond, Block *block,
                  IterType it)
        : _initial(init), _block(block), _it(it)
    {
        _range = nullptr;
        if (cond->getType() != NodeType::_comp) {
            _condition = MALLOC(CompOperator, cond, 0, nullptr);
        }
        else {
            _condition = dynamic_cast<CompOperator *>(cond);
        }
    };
    /*
     * ===  FUNCTION
     * ======================================================================
     *         Name:  IterStatement
     *  Description:  for(a=2; a<b;a++) {}; for(; a<b;a++) {}
     * =====================================================================================
     */
    IterStatement(VariableStatement *init, Expression *cond, Statement *range,
                  Block *block, IterType it)
        : _initial(init), _range(range), _block(block), _it(it)
    {
        if (cond->getType() != NodeType::_comp) {
            _condition = MALLOC(CompOperator, cond, 0, nullptr);
        }
        else {
            _condition = dynamic_cast<CompOperator *>(cond);
        }
    };

    /* constructor */

    ~IterStatement()
    {
        RELEASE(_initial);
        RELEASE(_condition);
        RELEASE(_range);
        RELEASE(_block);
    }
    /* =============  ACCESSORS     =================== */
    llvm::Value *codeGen(CodeGenContext &context) override;
    NodeType getType() override { return NodeType::_flowiter; }

    /* =============  MUTATORS      =================== */
    IterType type() { return _it; };

    llvm::Value *IterWhile(CodeGenContext &context);
    llvm::Value *IterFor(CodeGenContext &context);
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    VariableStatement *_initial{nullptr};
    CompOperator *_condition{nullptr};
    Statement *_range{nullptr};
    Block *_block{nullptr};
    IterType _it;
}; /* -----  end of class IterStatement  ----- */

}  // namespace e2
#endif /* ----- #ifndef CONTROLFLOW_INC  ----- */
