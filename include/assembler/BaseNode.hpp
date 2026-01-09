/*
 * =====================================================================================
 *
 *       Filename:  BaseNode.hpp
 *
 *    Description:  BaseNode
 *
 *        Version:  1.0
 *        Created:  2023年10月30日 17时33分54秒
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

#ifndef BASENODE_INC
#define BASENODE_INC

#include <llvm/ADT/APInt.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/Twine.h>
#include <llvm/Bitstream/BitstreamReader.h>
#include <llvm/Bitstream/BitstreamWriter.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/Argument.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/StandardInstrumentations.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Scalar/Reassociate.h>
#include <llvm/Transforms/Scalar/SimplifyCFG.h>

#include <cstddef>
#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "assembler/BaseType.hpp"
#include "utility/pack.hpp"
namespace e2 {

using retType = llvm::Type;
using ArgType = std::vector<llvm::Type*>;
inline std::size_t variable_str_num = 1;
/**
 * code in codeGen , conver to the next
 * 如果定义时候，有上一级别的 union id 就加进来
 */
#define UNION_NAME(u, ctx)                         \
    do {                                           \
        std::string union_parent = ctx.topUnion(); \
        if (union_parent.length()) {               \
            u->union_name(union_parent);           \
        }                                          \
    } while (0)

#define CodeGen(hs)                                                  \
    ({                                                               \
        llvm::Value* __rhs = nullptr;                                \
        do {                                                         \
            std::string cname = "";                                  \
            if (hs->getType() == NodeType::_identifier) {            \
                Identifier* ids = dynamic_cast<Identifier*>(hs);     \
                cname = ids->name();                                 \
                bool __ok_find = false;                              \
                std::map<std::string, Int_e>::iterator _it =         \
                    _GlobalVariables.find(cname);                    \
                if (_it != _GlobalVariables.end()) {                 \
                    __ok_find = true;                                \
                }                                                    \
                if (ids->idType() == IDType::_global || __ok_find) { \
                    llvm::GlobalVariable* gVar =                     \
                        context.getModule()->getNamedGlobal(cname);  \
                    if (gVar != nullptr) {                           \
                        __rhs = gVar->getOperand(0);                 \
                    }                                                \
                }                                                    \
            }                                                        \
            if (__rhs == nullptr) {                                  \
                __rhs = hs->codeGen(context);                        \
            }                                                        \
        } while (0);                                                 \
        __rhs;                                                       \
    })

#define E2LType(con)                              \
    ({                                            \
        retType* __TPtr;                          \
        do {                                      \
            __TPtr = llvm::Type::getInt64Ty(con); \
        } while (0);                              \
        __TPtr;                                   \
    })

#define E2L32Type(con)                            \
    ({                                            \
        retType* __TPtr;                          \
        do {                                      \
            __TPtr = llvm::Type::getInt32Ty(con); \
        } while (0);                              \
        __TPtr;                                   \
    })

#define E2LVoid(con)                                \
    ({                                              \
        retType* __VoidPtr;                         \
        do {                                        \
            __VoidPtr = llvm::Type::getVoidTy(con); \
        } while (0);                                \
        __VoidPtr;                                  \
    })

#define E2LStr(con)                                    \
    ({                                                 \
        retType* __StrPtr;                             \
        do {                                           \
            __StrPtr = llvm::IntegerType::get(con, 8); \
        } while (0);                                   \
        __StrPtr;                                      \
    })

#define E2LBool(con)                                \
    ({                                              \
        retType* __boolPtr;                         \
        do {                                        \
            __boolPtr = llvm::Type::getInt1Ty(con); \
        } while (0);                                \
        __boolPtr;                                  \
    })

#define ToBool(args, con)                                                \
    ({                                                                   \
        do {                                                             \
            if (args->getType()->getTypeID() !=                          \
                llvm::Type::TypeID::IntegerTyID) {                       \
                retType* t = E2LBool(con.getGlobalContext());            \
                auto cinstr =                                            \
                    llvm::CastInst::getCastOpcode(args, true, t, true);  \
                args = llvm::CastInst::Create(cinstr, args, t, "castdb", \
                                              context.currentBlock());   \
            }                                                            \
        } while (0);                                                     \
    })

//
#define BuildGlobal(context, type, name, val)                               \
    ({                                                                      \
        llvm::GlobalVariable* __GPtr;                                       \
        do {                                                                \
            llvm::Constant* __init_val = llvm::ConstantInt::get(type, val); \
            context.getModule()->getOrInsertGlobal(name, type);             \
            __GPtr = context.getModule()->getNamedGlobal(name);             \
            __GPtr->setConstant(true);                                      \
            __GPtr->setLinkage(llvm::GlobalValue::InternalLinkage);         \
            __GPtr->setInitializer(__init_val);                             \
        } while (0);                                                        \
        __GPtr;                                                             \
    })

/* debug start*/

#ifdef E2L_DEBUG
inline std::size_t _code_gen_number = 0;

#define EnterCode(gen)                                                  \
    ({                                                                  \
        do {                                                            \
            _code_gen_number++;                                         \
            llog::debug(llog::format("-> %ld.", _code_gen_number), gen, \
                        " (code line:", _codeLine, ")");                \
        } while (0);                                                    \
    })

#define ExitCode(gen)                                                   \
    ({                                                                  \
        do {                                                            \
            llog::warn(llog::format("<- %ld.", _code_gen_number), gen); \
            _code_gen_number--;                                         \
        } while (0);                                                    \
    })

#endif
/* debug end*/

// context.currentBlock()->getName().str()
#define NameSpaceSelfArg(func_name)      \
    ({                                   \
        std::string __arg = "";          \
        do {                             \
            __arg = func_name + "_self"; \
        } while (0);                     \
        __arg;                           \
    })

#define NameSpaceFunc(a, b)      \
    ({                           \
        std::string __nsf = "";  \
        do {                     \
            __nsf = a + "_" + b; \
        } while (0);             \
        __nsf;                   \
    })

#define UnionName(a)           \
    ({                         \
        std::string __nn = ""; \
        do {                   \
            __nn = "." + a;    \
        } while (0);           \
        __nn;                  \
    })

#define NameSpaceCallTagName(a, b)     \
    ({                                 \
        std::string __nsctn = "";      \
        do {                           \
            __nsctn = a + "_tag_" + b; \
        } while (0);                   \
        __nsctn;                       \
    })

#define NameSpaceInitName(n)     \
    ({                           \
        std::string __nsin = ""; \
        do {                     \
            __nsin = n + "_#";   \
        } while (0);             \
        __nsin;                  \
    })

typedef Int_e (*funPtr)(Int_e, Int_e);

#define ALLOCAINST_SIZE 0

static llvm::Align storeinst_align(8);

class CodeGenContext;
class Identifier;

template <typename T, typename Container = std::deque<T>>
class iterable_queue : public std::queue<T, Container> {
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }
};

/*
 * ================================
 *        Class:  BaseNode
 *  Description:
 * ================================
 */
class BaseNode {
public:
    /* =============  LIFECYCLE     =================== */
    //  BaseNode(){}; /* constructor */
    virtual ~BaseNode() = default;

    /* =============  ACCESSORS     =================== */
    virtual llvm::Value* codeGen(CodeGenContext& context) = 0;

    /* Returns the type of the node. */
    virtual NodeType getType() = 0;

    /* virtual void visit() = 0; */
    /* =============  MUTATORS      =================== */
    virtual Identifier* id() = 0;
    std::size_t line() { return _codeLine; }
    std::string path() { return _path; }
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    std::size_t _codeLine = 0;
    std::string _path = "";

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

}; /* -----  end of class BaseNode  ----- */

/*
 * ================================
 *        Class:  Expression
 *  Description:
 * ================================
 */
class Expression : public BaseNode {
public:
    /* =============  LIFECYCLE     =================== */
    /* =============  ACCESSORS     =================== */
    virtual NodeType getType() { return NodeType::_expression; }
    /* =============  MUTATORS      =================== */
    Identifier* id() { return _id; };

    /**
     * union name
     */
    void union_name(const std::string uname)
    {
        if (_union_name.empty()) {
            _union_name = uname;
        }
        else {
            _union_name += "." + uname;
        }
#ifdef E2L_DEBUG
        llog::echo("un:", _union_name);
#endif
    }
    const std::string uname();

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    Identifier* _id{nullptr};

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    std::string _union_name = "";
}; /* -----  end of class Expression  ----- */

/*
 * ================================
 *        Class:  Identifier
 *  Description:  variable name, function name, union name
 * ================================
 */
class Identifier : public Expression {
public:
    /* =============  LIFECYCLE     =================== */
    Identifier(std::string name, IDType it) : _idtype(it)
    {
        _name.push(name);
        _id = this;
    }; /* constructor */
    ~Identifier() {};

    /* =============  ACCESSORS     =================== */
    virtual llvm::Value* codeGen(CodeGenContext& context);
    NodeType getType() { return NodeType::_identifier; }
    /* =============  MUTATORS      =================== */

    void codeLine(size_t line) { _codeLine = line; };
    void codePath(const char* path)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
    };
    size_t size() { return _name.size(); }
    const iterable_queue<std::string>& qname() { return _name; }
    void push_back(Identifier* it) { _name.push(it->name()); };
    void push_back(std::string it) { _name.push(it); };
    const std::string name();
    const std::string real_name();
    const std::string id_name();
    IDType idType() { return _idtype; }
    void idType(IDType it) { _idtype = it; }
    void nss(NameSpaceStatus n) { _nss = n; }
    NameSpaceStatus nss() { return _nss; }

    std::string NameSpaceTag()
    {
        //  _name.back() + "_tag_" + _name_space_tag;
        return NameSpaceCallTagName(_name.back(), _name_space_tag);
    };
    std::string Tag() { return _name_space_tag; };
    void NameSpaceTag(std::string n)
    {
        if (n.length() > 4) {
            _name_space_tag = n.substr(1, n.length() - 4);
        }
    };
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */
    /* =============  DATA MEMBERS  =================== */
    iterable_queue<std::string> _name;
    IDType _idtype = IDType::_normal;

    NameSpaceStatus _nss = NameSpaceStatus::_n_null;

    std::string _name_space_tag = "";
}; /* -----  end of class Identifier  ----- */
typedef std::vector<Expression*> ExpressionList;

/*
 * ================================
 *        Class:  ImportModule
 *  Description:
 * ================================
 */
class ImportModule : public Expression {
public:
    /* =============  LIFECYCLE     =================== */
    ImportModule(std::string file)
    {
        _mod = file.substr(1, file.length() - 2);
    }; /* constructor */

    /* =============  ACCESSORS     =================== */
    virtual llvm::Value* codeGen(CodeGenContext& context);
    NodeType getType() { return NodeType::_module; }
    /* =============  MUTATORS      =================== */
    std::string value() { return _mod; };
    // void name(std::string n) { _name = "_str_" + n; }

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    std::string _mod = "";

}; /* -----  end of class ImportModule  ----- */

/*
 * ================================
 *        Class:  Statement
 *  Description:
 * ================================
 */
class Statement : public Expression {
public:
    /* =============  LIFECYCLE     =================== */

    /* =============  ACCESSORS     =================== */

    virtual NodeType getType() { return NodeType::_statement; }
    void idType(IDType it)
    {
        if (_id != nullptr) {
            _id->idType(it);
        }
    }
    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

}; /* -----  end of class Statement  ----- */

typedef std::vector<Statement*> StatementList;

/*
 * ======================Assignment==========
 *        Class:  Assignment
 *  Description:  主要用在 取 右则变量 和 method call 上面
 *  eg.
 *  call.   echo(a);  echo(3);
 * ================================
 */
class Assignment : public Expression {
public:
    /* =============  LIFECYCLE     =================== */
    Assignment(Identifier* id, Expression* exp, size_t line, const char* path)
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
    virtual llvm::Value* codeGen(CodeGenContext& context);
    Expression* getRhs() { return _rhs; }
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

    void NsVarInit(bool f) { _ns_var_init = f; };
    bool checkNsInit() { return _ns_var_init; }

    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

    // name space init var
    // 初始化的 assig
    bool _ns_var_init = false;
    Expression* _rhs{nullptr};
}; /* -----  end of class Assignment  ----- */

// 保存 namespace 表达式的 map
using NameSpaceInitCodeAssign = std::set<Assignment*>;
// namespace->assign
using NameSpaceinitCode = std::map<std::string, NameSpaceInitCodeAssign>;

/*
 * ================================
 *        Class:  Block
 *  Description:
 * ================================
 */
class Block : public Statement {
public:
    /* =============  LIFECYCLE     =================== */
    Block(const std::string name, size_t line, const char* path) : _name(name)
    {
        if (path != nullptr) {
            _path = std::string(path);
        }
        _codeLine = line;

    }; /* constructor */
    ~Block()
    {
        for (auto s : _statements) {
            RELEASE(s);
        }

        _statements.clear();

        for (auto e : _exps) {
            RELEASE(e);
        }
        _exps.clear();
    };
    /* =============  ACCESSORS     =================== */
    virtual llvm::Value* codeGen(CodeGenContext& context);
    NodeType getType() { return NodeType::_block; }
    NodeType getType(size_t index)
    {
        if (_statements.size() < index) {
            llog::bug("statement index:", index);
        }
        return _statements.at(index)->getType();
    }
    std::string getIdName(size_t index)
    {
        if (_statements.size() < index) {
            llog::bug("statement index:", index);
        }
        return _statements.at(index)->id()->name();
    }

    void updateIdName(size_t idx, Identifier* id)
    {
        if (_statements.size() < idx) {
            // llog::bug("statement index:", index);
            return;
        }
        _statements.at(idx)->id()->push_back(id);
    }
    void erase_id(NodeType nt)
    {
        for (auto it = _statements.begin(); it != _statements.end();) {
            if ((*it)->getType() == nt) {
                llog::echo("earase variable");
                it = _statements.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    bool importnull(std::string l) { return _imports.count(l) == 0; }
    std::deque<std::string> get_import(std::string l)
    {
        if (importnull(l)) {
            llog::bug("import :", l);
        }
        return _imports.at(l);
    }
    /* =============  MUTATORS      =================== */
    void push_back(Expression* exp);
    void push_back(Statement* stat);
    void push_back(Block* block);

    Statement* getStatement(std::size_t idx);

    void update(std::string mod);

    void mod()
    {
        _ismod = true;
        _mod_next = 0;
    }

    size_t size() { return _statements.size(); }
    const std::string& name() { return _name; }

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    StatementList _statements;
    ExpressionList _exps;

    std::string _current_mod = "main";
    std::map<std::string, std::deque<std::string>> _imports;

    std::string _name = "";

    bool _ismod = false;
    size_t _mod_next = 0;

}; /* -----  end of class Block  ----- */
}  // namespace e2
#endif /* ----- #ifndef BASENODE_INC  ----- */
