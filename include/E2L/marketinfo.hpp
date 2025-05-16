/*
 * =====================================================================================
 *
 *       Filename:  marketinfo.hpp
 *
 *    Description:  marketinfo
 *
 *        Version:  1.0
 *        Created:  2024年01月30日 11时33分18秒
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

#ifndef MARKETINFO_INC
#define MARKETINFO_INC
#include "E2LType.hpp"
#include "assembler/BaseType.hpp"
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Settlement
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  t=0 T+0  t=1 T+1 ..
 * ============================================
 */
void Settlement(e2::Int_e t); /* -----  end of function Settlement  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  SymbolsTotal
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  返回 symbols 的总数
 * ============================================
 */
e2::Int_e SymbolsTotal(); /* -----  end of function SymbolsTotal  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  SymbolName
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 * ============================================
 */
void SymbolName(e2::Int_e index); /* -----  end of function SymbolName  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  SymbolCFICode
 *  ->  void *
 *  Parametersfdsf
 *  - size_t  arg
 *  Description:
 *   MIC cfi
 *   https://en.wikipedia.org/wiki/ISO_10962
 *   https://www.iso20022.org/market-identifier-codes
 * ============================================
 */
e2::Int_e SymbolCFICode(
    e2::Int_e idx); /* -----  end of function SymbolCFICode  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  SymbolSelect
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  取哪些股票，哪些周期
 *  union id
 * ============================================
 */
void SymbolSelect(
    e2::Int_e id); /* -----  end of function SymbolSelect  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  BarOnOpen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  default bar on open timestamp
 * ============================================
 */
void BarOnOpen(); /* -----  end of function BarOnOpen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  BarVolumeAppend
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  设置 volume 累加
 * ============================================
 */
void BarVolumeAppend(); /* -----  end of function BarVolumeAppend  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  BarSize
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  返回目前 bar 的长度
 * ============================================
 */
e2::Int_e BarSize(
    e2::Int_e id,
    e2::Int_e timeframe); /* -----  end of function BarSize  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Bar
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Bool Bar(e2::Int_e id, e2::TimeFrames timeframe,
             e2::Int_e shift); /* -----  end of function Bar  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  BarSeries
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e BarSeries(e2::BarType); /* -----  end of function BarSeries  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iOpen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   TimeFrames
 * ============================================
 */
e2::Int_e iOpen(e2::Int_e id, e2::TimeFrames timeframe,
                e2::Int_e shift); /* -----  end of function iOpen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iHigh
 *  ->  e2::Int_e *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iHigh(e2::Int_e id, e2::TimeFrames timeframe,
                e2::Int_e shift); /* -----  end of function iHigh  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iHighest
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iHighest(
    e2::Int_e id, e2::TimeFrames timeframe, e2::BarType, e2::Int_e count,
    e2::Int_e start); /* -----  end of function iHighest  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iLow
 *  ->  e2::Int_e *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iLow(e2::Int_e id, e2::TimeFrames timeframe,
               e2::Int_e shift); /* -----  end of function iLow  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iLowest
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iLowest(e2::Int_e id, e2::TimeFrames timeframe, e2::BarType,
                  e2::Int_e count,
                  e2::Int_e start); /* -----  end of function iLowest  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iClose
 *  ->  e2::Int_e *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iClose(e2::Int_e id, e2::TimeFrames timeframe,
                 e2::Int_e shift); /* -----  end of function iClose  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iAdjClose
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iAdjClose(
    e2::Int_e id, e2::TimeFrames timeframe,
    e2::Int_e shift); /* -----  end of function iAdjClose  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iBid
 *  ->  e2::Int_e *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iBid(e2::Int_e id,
               e2::Int_e shift); /* -----  end of function iBid  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iAsk
 *  ->  e2::Int_e *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iAsk(e2::Int_e id,
               e2::Int_e shift); /* -----  end of function iAsk  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iVolume
 *  ->  e2::Int_e *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iVolume(e2::Int_e id, e2::TimeFrames timeframe,
                  e2::Int_e shift); /* -----  end of function iVolume  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  iTime
 *  ->  e2::Int_e *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e iTime(e2::Int_e id, e2::TimeFrames timeframe,
                e2::Int_e shift); /* -----  end of function iTime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExdiDate
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Bool isExdiDate(e2::Int_e id); /* -----  end of function ExdiDate  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExdiLoop
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Bool ExdiLoop(e2::Int_e id); /* -----  end of function ExdiLoop  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExdiCash
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ExdiCash(e2::Int_e id); /* -----  end of function ExdiCash  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExdiShare
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ExdiShare(e2::Int_e id); /* -----  end of function ExdiShare  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CustomDataSize
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e CustomDataSize(
    e2::Int_e, e2::Int_e); /* -----  end of function CustomDataSize  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CustomDataGet
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e CustomDataGet(
    e2::Int_e, e2::Int_e,
    e2::Int_e); /* -----  end of function CustomDataGet  ----- */
}  // namespace e2l
#endif /* ----- #ifndef MARKETINFO_INC  ----- */
