/*
 * =====================================================================================
 *
 *       Filename:  broker.hpp
 *
 *    Description:  broker
 *
 *        Version:  1.0
 *        Created:  2023年12月22日 10时06分16秒
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

#ifndef BROKER_INC
#define BROKER_INC
#include "E2LType.hpp"
#include "assembler/BaseType.hpp"

namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  setCash
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void setCash(e2::Int_e); /* -----  end of function setCash  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  getCash
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e getCash(); /* -----  end of function getCash  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  changeCash
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void changeCash(e2::Int_e); /* -----  end of function changeCash  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  SettlInst
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  系统 结算模式
 * ============================================
 */
void SettlInst(
    e2::SettleInstMode); /* -----  end of function SettlInst  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TIForce
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void TIForce(e2::TimeInForce); /* -----  end of function TIForce  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  MarginRate
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  设置 保证金率, 用以挂单的时候，扣掉的保证金
 *  eg. https://www.mql5.com/en/book/automation/symbols/symbols_margin_rates
 * ============================================
 */
void MarginRate(e2::Int_e); /* -----  end of function MarginRate  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  MatchEventInit
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   撮合事件
 * ============================================
 */
void MatchEventInit(
    e2::MatchEvent); /* -----  end of function MatchEventInit  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  EnableExdividend
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void EnableExdividend(e2::Bool);
/* -----  end of function EnableExdividend  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExDivPrice
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ExDivPrice(e2::Int_e); /* -----  end of function ExDivPrice  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExDividendSize
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ExDividendSize(
    e2::Int_e); /* -----  end of function ExDividendSize  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExDividendDate
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ExDividendDate(
    e2::Int_e, e2::Int_e); /* -----  end of function ExDividendDate  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExDividendCash
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ExDividendCash(
    e2::Int_e, e2::Int_e); /* -----  end of function ExDividendCash  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ExDividendShare
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ExDividendShare(
    e2::Int_e, e2::Int_e); /* -----  end of function ExDividendShare  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  BrokerBook
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void BrokerBook(e2::BookType); /* -----  end of function BrokerBook  ----- */
}  // namespace e2l
#endif /* ----- #ifndef BROKER_INC  ----- */
