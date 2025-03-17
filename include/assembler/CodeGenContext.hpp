/*
 * =====================================================================================
 *
 *       Filename:  CodeGenContext.hpp
 *
 *    Description:  CodeGenContext
 *
 *        Version:  1.0
 *        Created:  2023年10月26日 15时35分33秒
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

#ifndef CODEGENCONTEXT_INC
#define CODEGENCONTEXT_INC

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

#include <cstddef>
#include <cstdlib>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "BaseType.hpp"
#include "E2L/E2LType.hpp"
#include "assembler/BaseNode.hpp"

namespace e2 {

using MapLocals = std::map<std::string, llvm::Value *>;

struct __ExternFunc_t {
    llvm::Function *fun{nullptr};
    void *addr{nullptr};
}; /* ----------  end of struct __ExternFunc  ---------- */

typedef struct __ExternFunc_t ExternFunc_t;

struct __ScriptList_t {
    NodeType nt;       // Identifier type
    std::string name;  // Identifier name
    size_t argc;
}; /* ----------  end of struct __ScriptList_t  ---------- */

typedef struct __ScriptList_t ScriptList_t;

enum ErrorNo {
    _NotExist = 0,  // not exist
    _ArgSize,       // call func arg number is error
};                  /* ----------  end of enum ErrorNo  ---------- */

typedef enum ErrorNo ErrorNo;
struct __ScriptError {
    NodeType nt;       // Identifier type
    std::string name;  // Identifier name
    ErrorNo en;        // error number
    std::string msg;   // error msg
    size_t line;       // error line number
};                     /* ----------  end of struct __ScriptError  ---------- */

typedef struct __ScriptError ScriptError_t;

/*
 * ================================
 *        Class:  CodeGenBlock
 *  Description:
 * ================================
 */
class CodeGenBlock {
public:
    /* =============  LIFECYCLE     =================== */
    CodeGenBlock(llvm::BasicBlock *block, ScopeKind sc)
        : _block(block), _scope(sc){}; /* constructor */
    ~CodeGenBlock() {}

    /* =============  ACCESSORS     =================== */
    void setCodeBlock(llvm::BasicBlock *bb) { _block = bb; }
    llvm::BasicBlock *block() const { return _block; }

    /**
     * block 有多个 return 就只要第一个就可以了
     * ..
     *  return 1;
     *  ...
     *  return 0;
     *
     */
    void setValue(llvm::Value *value)
    {
        if (_returnValue == nullptr) _returnValue = value;
    }
    llvm::Value *getValue() const { return _returnValue; }
    MapLocals &local() { return _locals; }
    void scope(ScopeKind sc) { _scope = sc; }
    ScopeKind scope() { return _scope; }
    /* =============  MUTATORS      =================== */

    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */
    llvm::BasicBlock *_block{nullptr};
    llvm::Value *_returnValue{nullptr};
    MapLocals _locals;
    ScopeKind _scope{_sk_main};

}; /* -----  end of class CodeGenBlock  ----- */
/*
 * ================================
 *        Class:  CodeGenContext
 *  Description:
 * ================================
 */
class CodeGenContext {
public:
    /* =============  LIFECYCLE     =================== */
    CodeGenContext()
    {
        /**
         * error Unable to find target for this triple (no targets are
         * registered)
         */
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmParser();
        llvm::InitializeNativeTargetAsmPrinter();

        int random_val = std::rand();
        _module =
            new llvm::Module("e2l." + std::to_string(random_val), _llvmContext);
    }; /* constructor */

    ~CodeGenContext()
    {
        for (auto it : _blockStack) {
            RELEASE(it);
        }

        RELEASE(_ee);

        llvm::llvm_shutdown();
    }
    /* =============  ACCESSORS     =================== */
    llvm::Module *getModule() const { return _module; }

    llvm::LLVMContext &getGlobalContext() { return _llvmContext; }

    retType *typeOf(Expression *type)
    {
        switch (type->getType()) {
            case NodeType::_identifier:
            case NodeType::_number:

                return defType();
            case NodeType::_string: {
                auto charType = E2LStr(_llvmContext);
                return charType;
            }
            case NodeType::_comp: {
                auto ptyp = E2LBool(_llvmContext);
                return ptyp;
            }
            default:
                break;
        }
        return llvm::Type::getVoidTy(_llvmContext);
    }

    /* =============  MUTATORS      =================== */

    retType *defType();
    /*! Compile the AST into a module */
    bool generateCode(Block *root);
    llvm::GenericValue Result();
    int runFunction(double, double);

    void runCode();

    void currentBreak(llvm::BasicBlock *);
    llvm::BasicBlock *currentBreak();
    void popBreak();
    void setBreakPoint(bool);
    bool isBreakPoint();

    llvm::BasicBlock *currentBlock();
    ScopeKind currentScope();
    void pushBlock(llvm::BasicBlock *block, ScopeKind sc);
    void setInsertPoint(llvm::BasicBlock *block);

    void popBlock();

    MapLocals &locals();

    llvm::Value *MainArgx(size_t index);
    void setCurrentReturnValue(llvm::Value *value);
    llvm::Value *getCurrentReturnValue();

    llvm::Value *findBlockId(const std::string name);

    void ExternBuild(retType *ret, ArgType arg, void *fun, std::string &fname);

    void ExternBuildInt(void *fun, size_t args, std::string &fname,
                        bool isVoid = false);

    void ScriptList(NodeType nt, std::string name, size_t argc);

    void OutGlobalVar(const std::string &, Int_e);

    const std::vector<ScriptList_t> &ScriptList();

    void ScriptError(NodeType nt,       // Identifier type
                     std::string name,  // Identifier name
                     ErrorNo en,        // error number
                     std::string msg,   // error msg
                     size_t line        // error line number

    );
    const std::vector<ScriptError_t> &ScriptError();

    void DontRun();

    void toDebug();
    /* =============  OPERATORS     =================== */

protected:
    /* =============  METHODS       =================== */

    /* =============  DATA MEMBERS  =================== */

private:
    /* =============  METHODS       =================== */

    void InitGlobalVar();
    void ExternGlobalVar(const std::string &, Int_e);
    void AddGlobal();
    /* =============  DATA MEMBERS  =================== */

    llvm::Module *_module{nullptr};
    std::list<CodeGenBlock *> _blockStack;
    std::list<llvm::BasicBlock *> _breakStack;
    bool _breakStat = false;

    llvm::Function *_mainFunction{nullptr};
    llvm::LLVMContext _llvmContext;

    llvm::ExecutionEngine *_ee{nullptr};
    funPtr _function;

    std::vector<ExternFunc_t> _ExternFunc;

    llvm::GenericValue _GenericRet;

    /**
     * Identifier list
     */
    std::vector<ScriptList_t> _script_list;

    /**
     * grammar error
     *
     */
    std::vector<ScriptError_t> _script_error;

    bool _CanRun = true;

    bool _debug = false;
}; /* -----  end of class CodeGenContext  ----- */

}  // namespace e2
#endif /* ----- #ifndef CODEGENCONTEXT_INC  ----- */
