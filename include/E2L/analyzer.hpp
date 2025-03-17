/*
 * =====================================================================================
 *
 *       Filename:  analyzer.hpp
 *
 *    Description:  analyzer
 *
 *        Version:  1.0
 *        Created:  2024年03月05日 09时51分41秒
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

#ifndef ANALYZER_INC
#define ANALYZER_INC
#include "assembler/BaseType.hpp"
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  analysis
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e analysis(
    e2::Int_e qid,
    e2::Int_e analy); /* -----  end of function analysis  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  analytotal
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e analytotal(
    e2::Int_e analy); /* -----  end of function analytotal  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Analse
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  log 传出来记录图表的，ID 表示某一个指标或 某一个事件
 * ============================================
 */
void Analse(e2::Int_e id,
            const char *name); /* -----  end of function Analse  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AnalseArgv
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void AnalseArgv(e2::Int_e id,
                e2::Int_e); /* -----  end of function AnalseArgv  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AnalseDB
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void AnalseDB(); /* -----  end of function AnalseDB  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AnalseValue
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void AnalseValue(e2::Int_e id,
                 e2::Int_e val); /* -----  end of function AnalseValue  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AnalseLog
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void AnalseLog(e2::Int_e key, e2::Int_e val, e2::Int_e type,
               e2::Int_e time); /* -----  end of function AnalseLog  ----- */
}  // namespace e2l
#endif /* ----- #ifndef ANALYZER_INC  ----- */
