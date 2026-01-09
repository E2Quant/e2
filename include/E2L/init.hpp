/*
 * =====================================================================================
 *
 *       Filename:  init.hpp
 *
 *    Description:  init
 *
 *        Version:  1.0
 *        Created:  2024年01月22日 12时02分34秒
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

#ifndef INIT_INC
#define INIT_INC
#include "E2LType.hpp"
#include "assembler/BaseType.hpp"
namespace e2l {
// init function

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  isInit
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  是否已经初始化 完成
 * ============================================
 */
e2::Int_e isInit(); /* -----  end of function isInit  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  fix
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   fix 的配置文件
 * ============================================
 */
void fix(const char* cfg); /* -----  end of function fix  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  mktype
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  tick or bar
 * ============================================
 */
void mktype(e2::Int_e); /* -----  end of function mktype  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  csvdata
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void mkcsv(const char* source,
           const char* symbol); /* -----  end of function csvdata  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  mkkafka
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   kafka 结构体传送 symbol 过来
 * ============================================
 */
void mkkf(const char* source); /* -----  end of function mkkafka  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  topic_tick
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void topic_tick(
    const char* topic); /* -----  end of function topic_tick  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  topic_log
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void topic_log(const char* topic); /* -----  end of function topic_log  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  tframe
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  TimeFrames struct
 * ============================================
 */
void tframe(e2::Int_e); /* -----  end of function tframe  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  deftframe
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  默认 timeframe
 * ============================================
 */
e2::Int_e deftframe(); /* -----  end of function deftframe  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  tframelength
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  返回周期数量
 * ============================================
 */
e2::Int_e tframelength(); /* -----  end of function tframelength  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  gettframe
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  返回第几个周期
 * ============================================
 */
e2::Int_e gettframe(e2::Int_e); /* -----  end of function gettframe  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  index
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  单个 tick 报价 或 以 index 报价 ,是否 index offers
 * ============================================
 */
e2::Int_e index(); /* -----  end of function index  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  offers
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   设置 offers
 * ============================================
 */
void offers(e2::Int_e); /* -----  end of function offers  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TradeTime
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  开盘收盘时间，可以多次填写
 * ============================================
 */
void TradeTime(
    e2::Int_e open_hour, e2::Int_e open_min, e2::Int_e close_hour,
    e2::Int_e close_min); /* -----  end of function TradeTime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  gmtime
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   TimeZone=GMT+0
 * ============================================
 */
void gmtime(); /* -----  end of function gmtime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  commission
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   commission , Currency
 * ============================================
 */
void commission(e2::Int_e,
                const char* ccy); /* -----  end of function commission  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  QuantId
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  analy, risk ... use this uuid
 *  主要是区别当前的 策略 ID
 * ============================================
 */
void QuantId(e2::Int_e uuid); /* -----  end of function QuantId  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  GenerateQuantId
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void GenerateQuantId(); /* -----  end of function GenerateQuantId  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CurrentQuantId
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e CurrentQuantId(); /* -----  end of function CurrentQuantId  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TradeMode
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 * ENUM_SYMBOL_TRADE_MODE   long or short positions
 * ============================================
 */
void TradeMode(
    e2::SymbolTradeMode); /* -----  end of function TradeMode  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Simulation
 *  ->  void *
 *  Parametersdfsdfsdf
 *  - size_t  arg
 *  Description:
 *  simulation trade for oms
 *  自动产生K 线
 * ============================================
 */
void Simulation(); /* -----  end of function Simulation  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OfferTime
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  min  time >= 100ms
 * ============================================
 */
void OfferTime(e2::Int_e); /* -----  end of function OfferTime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  QuantVersion
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void QuantVersion(
    e2::Int_e major, e2::Int_e minor,
    e2::Int_e patch); /* -----  end of function QuantVersion  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  VersionId
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e VersionId(); /* -----  end of function VersionId  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LotAndShare
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  一手股票（英语：Lot）
 *  上海和深圳交易所均订明，不论股价，以100股为一手
 *  每手一千股（香港证券交易所）
 *
 * ============================================
 */
void LotAndShare(e2::Int_e); /* -----  end of function LotAndShare  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  CurrentLS
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  当前一手是多少 股
 * ============================================
 */
e2::Int_e CurrentLS(); /* -----  end of function CurrentLS  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  whois
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e whois(); /* -----  end of function whois  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ConfigShow
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 * 显示当前的配置，包括ea 和 oms 端
 * ============================================
 */
void ConfigShow(); /* -----  end of function ConfigShow  ----- */
}  // namespace e2l
#endif /* ----- #ifndef INIT_INC  ----- */
