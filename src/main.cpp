/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  main
 *
 *        Version:  1.0
 *        Created:  2023年10月25日 16时14分34秒
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

#include <llvm/IR/Type.h>
#include <stdlib.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "assembler/BaseType.hpp"
#include "ast/ParserCtx.hpp"

/* #ifdef NUMBER_DECI */
/* #undef NUMBER_DECI */
/* #define NUMBER_DECI 100 */
/* #endif */

extern "C" {

void call(const char* toPrint)
{
    if (toPrint) {
        fprintf(stderr, "ok... %s \n", toPrint);
    }
    else {
        fprintf(stderr, "::calll:NULL arg.\n");
    }
}

const char* toChar()
{
    int a = 12345;
    size_t len = snprintf(NULL, 0, "%d", a);
    len += 1;
    char* abc = (char*)malloc(len);
    memset(abc, len, sizeof(char));
    snprintf(abc, len, "%d", a);

    fprintf(stderr, "toChar: %s \n", abc);

    return abc;
}
}
std::int64_t last(std::int64_t index)
{
    std::int64_t b = index + 6;
    std::cout << "b:" << b << std::endl;
    return b;
}

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  toDo
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void toDo(const char* f, const char* s, std::pair<std::string, Int_e>& b)
{
    e2::ParserCtx ctx;

    if (s != nullptr) {
        ctx.search_path(s);
    }

    int ret = ctx.toparse(f);

    if (ret == -1) {
        return;
    }

    std::string name = "last";
    std::string cname = "call";
    Int_e a = 19;
    CodeGenContext context;
    context.toDebug();
    createCoreFunctions(context);
    ArgType arg(1, E2LType(context.getGlobalContext()));
    context.ExternBuild(E2LType(context.getGlobalContext()), arg,
                        (std::int64_t*)last, name);

    llvm::Type* charType = E2LStr(context.getGlobalContext());
    llvm::Type* rType = E2LVoid(context.getGlobalContext());
    ArgType carg(1, charType);
    context.ExternBuild(rType, carg, (void*)call, cname);

    ArgType targ;
    std::string tochar = "tochar";
    context.ExternBuild(charType, targ, (void*)toChar, tochar);

    if (b.first.length() > 0) {
        context.OutGlobalVar(b.first, b.second);
    }
    Block* block = ctx.RootBlock();
    bool isgc = context.generateCode(block);

    if (isgc) {
        context.runCode();
        Int_e ret = context.runFunction(a, a);
        llog::echo("runFunction:", ret);
    }
    else {
        llog::bug("generateCode is error");
    }

} /* -----  end of function toDo  ----- */

/*
 * ===  FUNCTION  =============================
 *         Name:  main
 *  Description:
 * ============================================
 */
int main(int argc, char* argv[])
{
    char* f = nullptr;
    char* s = nullptr;

    if (argc > 2) {
        s = argv[2];
    }

    if (argc >= 2) {
        f = argv[1];
    }
    else {
        exit(0);
    }
    std::pair<std::string, Int_e> b;
    b = std::make_pair("sfd.ssfd.sfd", 1198);

    toDo(f, s, b);

    // toDo(f, b);

    return EXIT_SUCCESS;
} /* ----------  end of function main  ---------- */
