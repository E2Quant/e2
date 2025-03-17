/*
 * =====================================================================================
 *
 *       Filename:  account.hpp
 *
 *    Description:  account
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 15时18分34秒
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

#ifndef ACCOUNT_INC
#define ACCOUNT_INC
#include "assembler/BaseType.hpp"

/**
 * Functions that return parameters of the current account.
 */
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  cash
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   init cash
 * ============================================
 */
void AccountCash(e2::Int_e);

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountInfo
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns a value of  the corresponding account property
 * ============================================
 */
void AccountInfo(); /* -----  end of function AccountInfo  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountBalance
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns balance value of the current account
 * ============================================
 */
e2::Int_e AccountBalance(); /* -----  end of function AccountBalance  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountCredit
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns credit value of the current account
 * ============================================
 */
void AccountCredit(); /* -----  end of function AccountCredit  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountCompany
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the brokerage company name where the current account was registered
 * ============================================
 */
void AccountCompany(); /* -----  end of function AccountCompany  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountCurrency
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns currency name of the current account
 * ============================================
 */
void AccountCurrency(); /* -----  end of function AccountCurrency  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountEquity
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns equity value of the current account
 * ============================================
 */
e2::Int_e AccountEquity(); /* -----  end of function AccountEquity  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountFreeMargin
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns free margin value of the current account
 * ============================================
 */
void AccountFreeMargin(); /* -----  end of function AccountFreeMargin  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountFreeMarginCheck
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns free margin that remains after the specified position has been
 * opened at the current price on the current account
 * ============================================
 */
void AccountFreeMarginCheck(); /* -----  end of function AccountFreeMarginCheck
                                  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountFreeMarginMode
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Calculation mode of free margin allowed to open orders on the current
 * account
 * ============================================
 */
void AccountFreeMarginMode(); /* -----  end of function AccountFreeMarginMode
                                 ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountLeverage
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns leverage of the current account
 * ============================================
 */
void AccountLeverage(); /* -----  end of function AccountLeverage  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountMargin
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns margin value of the current account
 * ============================================
 */
e2::Int_e AccountMargin(); /* -----  end of function AccountMargin  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountName
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the current account name
 * ============================================
 */
void AccountName(); /* -----  end of function AccountName  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountNumber
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the current account number
 * ============================================
 */
void AccountNumber(); /* -----  end of function AccountNumber  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AccountProfit
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns profit value of the current account
 * ============================================
 */
e2::Int_e AccountProfit(); /* -----  end of function AccountProfit  ----- */

}  // namespace e2l

#endif /* ----- #ifndef ACCOUNT_INC  ----- */
