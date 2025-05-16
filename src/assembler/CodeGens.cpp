/*
 * =====================================================================================
 *
 *       Filename:  CodeGen.cpp
 *
 *    Description:  CodeGen
 *
 *        Version:  1.0
 *        Created:  2023年10月26日 11时49分19秒
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

#include <string>
#include <utility>
#include <vector>

#include "assembler/CodeGenContext.hpp"

namespace e2 {
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Block::codeGen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
llvm::Value* Block::codeGen(CodeGenContext& context)
{
    llvm::Value* last = nullptr;

    for (auto v : _statements) {
        if (v == nullptr) {
            continue;
        }
        UNION_NAME(v);

        last = v->codeGen(context);
    }

    return last;
} /* -----  end of function Block::codeGen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Block::push_back
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void Block::push_back(Expression* exp)
{
    if (exp != nullptr) {
        if (exp->getType() == NodeType::_module) {
            ImportModule* im = static_cast<ImportModule*>(exp);
            std::string mod = im->value();

            if (_imports.count(mod) > 0) {
                log::info("exit curent:", _current_mod, " mod:", mod);
                for (auto it = _imports.begin(); it != _imports.end(); ++it) {
                    for (std::string key : it->second) {
                        if (key == mod) {
                            log::info("duplicate import mod in here:",
                                      it->first);
                            return;
                        }
                    }
                }
                log::bug("import error:", _current_mod, " mod:", mod);
            }

            std::deque<std::string> emp;
            _imports.insert({mod, emp});

            if (_imports.count(_current_mod) == 0) {
                // init
                std::deque<std::string> one;
                one.push_back(mod);
                _imports.insert({_current_mod, one});
            }
            else {
                _imports[_current_mod].push_front(mod);
            }
        }
        if (_ismod) {
            auto it = _exps.begin();
            _exps.insert(it, exp);
        }
        else {
            _exps.push_back(exp);
        }
    }
    else {
        e2::log::bug("Expression push_back is nullptr code_line:", _codeLine,
                     " path:", _path);
    }
}
void Block::push_back(Statement* stat)
{
    if (stat != nullptr) {
        if (_ismod) {
            auto it = _statements.begin();
            _statements.insert(it + _mod_next, stat);
            _mod_next++;
        }
        else {
            _statements.push_back(stat);
        }
    }
    else {
        e2::log::bug("statement push_back is nullptr code_line:", _codeLine,
                     " path:", _path);
    }
}
void Block::push_back(Block* blk)
{
    if (blk != nullptr) {
        if (_ismod) {
            auto it = _statements.begin();
            _statements.insert(it + _mod_next, blk);
            _mod_next++;
        }
        else {
            _statements.push_back(blk);
        }
    }
    else {
        e2::log::bug("block push_back is nullptr code_line:", _codeLine,
                     " path:", _path);
    }
} /* -----  end of function Block::push_back  ----- */

/* -----  end of function Block::insert  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Block::update
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void Block::update(std::string mod)
{
    _current_mod = mod;

} /* -----  end of function Block::update  ----- */
}  // namespace e2
