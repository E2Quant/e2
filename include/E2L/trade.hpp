/*
 * =====================================================================================
 *
 *       Filename:  trade.hpp
 *
 *    Description:  trade
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 15时56分10秒
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

#ifndef TRADE_INC
#define TRADE_INC
#include <string>

#include "E2LType.hpp"
#include "assembler/BaseType.hpp"
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderClose
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  return bool
 *  Closes opened order
 * ============================================
 */
e2::Bool OrderClose(
    e2::Int_e ticket,   // int ticket   Unique number of the order ticket.
    e2::Int_e lots,     // double volume Number of lots.
    e2::Int_e stopx,    // double close price Closing price.
    e2::Int_e slippage  // int slippage  Value of the maximum price slippage in
                        // points.
);
/* -----  end of function OrderClose  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderCloseBy
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Closes an opened order by another opposite opened order
 * ============================================
 */
void OrderCloseBy(); /* -----  end of function OrderCloseBy  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderClosePrice
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns close price of the currently selected order
 * ============================================
 */
void OrderClosePrice(); /* -----  end of function OrderClosePrice  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderCloseTime
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns close time of the currently selected order
 * ============================================
 */
void OrderCloseTime(); /* -----  end of function OrderCloseTime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderCommission
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns calculated commission of the currently selected order
 * ============================================
 */
void OrderCommission(); /* -----  end of function OrderCommission  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderDelete
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Deletes previously opened pending order
 * ============================================
 */
void OrderDelete(); /* -----  end of function OrderDelete  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderExpiration
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns expiration date of the selected pending order
 * ============================================
 */
void OrderExpiration(); /* -----  end of function OrderExpiration  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderLots
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns amount of lots of the selected order
 * ============================================
 */
e2::Int_e OrderLots(e2::Int_e); /* -----  end of function OrderLots  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderModify
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Modification of characteristics of the previously opened or pending orders
 * ============================================
 */
void OrderModify(); /* -----  end of function OrderModify  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderOpenPrice
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns open price of the currently selected order
 * ============================================
 */
e2::Int_e OrderOpenPrice(e2::Int_e ticket,
    e2::Bool); /* -----  end of function OrderOpenPrice  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderOpenTime
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns open time of the currently selected order
 * ============================================
 */
void OrderOpenTime(); /* -----  end of function OrderOpenTime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderPrint
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Prints information about the selected order in the log
 * ============================================
 */
void OrderPrint(); /* -----  end of function OrderPrint  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderProfit
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 *  当前一笔的 profit
 *  Returns profit of the currently selected order
 * ============================================
 */
void OrderProfit(); /* -----  end of function OrderProfit  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderSelect
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  The function selects an order for further processing
 *  OrdersTotal or OrdersHistoryTotal  => index or ticket
 * ============================================
 */
e2::Bool OrderSelect(
    e2::Int_e index, e2::SelectFlag sel,
    e2::SelectFlag pool); /* -----  end of function OrderSelect  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderSend
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  The main function used to open an order or place a pending order
 * ============================================
 */

e2::Bool OrderSend(e2::Int_e symbol_id,  // symbol  Symbol for trading.
                   e2::Side side,        // operation Operation type.
                   e2::Int_e qty,        // volume Number of lots.
                   e2::Int_e price,      // price Order price.
                   e2::Int_e slippage,  // slippage   Maximum price slippage for
                                        // buy or sell orders.
                   e2::OrdType ordtype  // stop loss Stop loss level.

); /* -----  end of function OrderSend  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrdersHistoryTotal
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the number of closed orders in the account history loaded into the
 * terminal
 * ============================================
 */
e2::Int_e
OrdersHistoryTotal(); /* -----  end of function OrdersHistoryTotal  -----
                       */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderStopLoss
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns stop loss value of the currently selected order
 * ============================================
 */
void OrderStopLoss(); /* -----  end of function OrderStopLoss  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrdersTotal
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  	Returns the number of market and pending orders
 *  	挂单或者已经成交的订单
 * ============================================
 */
e2::Int_e OrdersTotal(); /* -----  end of function OrdersTotal  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderSymbol
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  	 Returns symbol name of the currently selected order
 * ============================================
 */
void OrderSymbol(); /* -----  end of function OrderSymbol  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderTakeProfit
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns take profit value of the currently selected order
 * ============================================
 */
void OrderTakeProfit(); /* -----  end of function OrderTakeProfit  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderTicket
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns ticket number of the currently selected order
 * ============================================
 */
e2::Int_e OrderTicket(); /* -----  end of function OrderTicket  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderType
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns order operation type of the currently selected order
 * ============================================
 */
void OrderType(); /* -----  end of function OrderType  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  OrderComment
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  risk manager
 * ============================================
 */
void OrderComment(
    e2::Int_e ticket, e2::Side,
    e2::OrderEvent); /* -----  end of function OrderComment  ----- */

}  // namespace e2l
#endif /* ----- #ifndef TRADE_INC  ----- */
