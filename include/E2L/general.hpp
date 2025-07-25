/*
 * =====================================================================================
 *
 *       Filename:  general.hpp
 *
 *    Description:  general
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 14时43分11秒
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

#ifndef GENERAL_INC
#define GENERAL_INC

#include "E2LType.hpp"
#include "assembler/BaseType.hpp"

/**
 * General-purpose functions not included into any specialized group are listed
 * here.
 */
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ShowGlobalUnion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  列出所有的全局 union 结构体
 * ============================================
 */
void ShowGlobalUnion(); /* -----  end of function ShowGlobalUnion  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  SymbolUnion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  打印  oms 端给过来的 symbol union 结构体
 * ============================================
 */
void SymbolUnion(); /* -----  end of function SymbolUnion  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  isDebug
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void isDebug(e2::Bool); /* -----  end of function isDebug  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  log
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void log(e2::Int_e, const char *_vname, e2::Int_e loc,
         const char *_path); /* -----  end of function log  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  PrintLine
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  不同的线
 * ============================================
 */
void PrintLine(e2::Int_e, const char *_vname, e2::Int_e loc,
               const char *_path); /* -----  end of function PrintLine  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  PrintDeci
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   print deci
 * ============================================
 */
void PrintDeci(e2::Int_e, e2::Int_e, const char *_vname, e2::Int_e loc,
               const char *_path); /* -----  end of function toPrint  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  PrintTime
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void PrintTime(e2::Int_e, const char *_vname, e2::Int_e loc,
               const char *_path); /* -----  end of function PrintTime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  PrintBar
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  最近的几个 bar
 * ============================================
 */
void PrintBar(e2::Int_e id, e2::Int_e timeframe,
              e2::Int_e); /* -----  end of function PrintBar  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Sleep
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *    sleep any tick or bar
 * ============================================
 */
void Sleep(); /* -----  end of function Sleep  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  StoreId
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e StoreId(
    e2::Int_e loc,
    const char *_path); /* -----  end of function StoreId  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LastStoreId
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e LastStoreId(
    e2::Int_e loc,
    const char *_path); /* -----  end of function LastStoreId  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  isStore
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Bool isStore(e2::Int_e id); /* -----  end of function isStore  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  fetch
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  fetch value
 * ============================================
 */
e2::Int_e fetch(e2::Int_e id); /* -----  end of function fetch  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  store
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  store value
 * ============================================
 */
void store(e2::Int_e id,
           e2::Int_e val); /* -----  end of function store  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TicketSize
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e TicketSize(); /* -----  end of function TicketSize  ----- */
}  // namespace e2l
#endif /* ----- #ifndef GENERAL_INC  ----- */
