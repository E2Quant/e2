/*
 * =====================================================================================
 *
 *       Filename:  system.hpp
 *
 *    Description:  system
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 17时39分31秒
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

#ifndef SYSTEM_INC
#define SYSTEM_INC
#include "E2LType.hpp"
#include "assembler/BaseType.hpp"
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ethread_id
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ethread_id(); /* -----  end of function ethread_id  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  process_id
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e process_id(); /* -----  end of function process_id  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  process_runs
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  第几次运行进程了
 * ============================================
 */
e2::Int_e process_runs(); /* -----  end of function process_runs  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ethread
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ethread(e2::Int_e); /* -----  end of function ethread  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ApiList
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ApiList(); /* -----  end of function ApiList  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  SymbolCurrent
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  USymbols union 的值
 * ============================================
 */
e2::Int_e SymbolCurrent(); /* -----  end of function SymbolCurrent  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TypeOf
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Bool TypeOf(const char *func); /* -----  end of function TypeOf  ----- */
}  // namespace e2l
#endif /* ----- #ifndef SYSTEM_INC  ----- */
