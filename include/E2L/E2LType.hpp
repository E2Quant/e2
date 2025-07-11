/*
 * =====================================================================================
 *
 *       Filename:  E2LType.hpp
 *
 *    Description:  E2LType
 *
 *        Version:  1.0
 *        Created:  2024年01月09日 16时34分08秒
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

#ifndef E2LTYPE_INC
#define E2LTYPE_INC
#include <initializer_list>
namespace e2 {

/**
 * FIX Protocol FIX.4.4
 * Message ExecutionReport
 */

/**
 * FIX Protocol FIX.4.4
 * ExecInst <18> field
 * Instructions for order handling on exchange trading floor. If more than one
 * instruction is applicable to an order, this field can contain multiple
 * instructions separated by space.
 */
enum __ExecInst {

    ei_do_not_increase = 0,
    // 'E',E DNI  A limit order to buy, a stop order to sell,
    // or a stop-limit order to sell which is not to be
    // increased in shares on the ex-dividend date as a
    // result of a stock dividend or distribution.
    ei_do_not_reduce = 1,
    // 'F',F DNR  A limit order to buy, a stop order to sell, or
    // a stop-limit order to sell that is not to be reduced
    // in price by the amount of an ordinary cash dividend on
    // the ex-dividend date. A do-not-reduce order applies
    // only to ordinary cash dividends; it should be reduced
    // for other distributions - such as when a stock goes
    // "ex" stock dividend or "ex" rights.
    ei_all_or_none = 2,
    // 'G',G  AON  A round-lot market or limit-price order that
    // must be executed in its entirety or not at all; unlike
    // Fill or Kill orders, AON orders are not treated as
    // canceled if they are not executed as soon as represented
    // in the Trading Crowd.
}; /* ----------  end of enum __ExecInst  ---------- */

typedef enum __ExecInst ExecInst;

/**
 * FIX Protocol FIX.4.4
 * TimeInForce <59>
 * Specifies how long the order remains in effect. Absence of this field is
 * interpreted as DAY. NOTE not applicable to CIV Orders.
 * 参照 MT4 的 订单执行模式
 *
 *
 */
enum __TimeInForce {
    tif_day = 0,
    tif_good_till_cancel = 1,  // Good Till Cancel (GTC)
    tif_at_the_opening = 2,    // At the Opening (OPG) [ SYMBOL_TRADE_EXEMODE ]
    // ioc
    // 市场订单或限价订单一旦在市场上可用，将全部或部分执行；任何未如此执行的部分将被取消。
    tif_immediate_or_cancel =
        3,  // Immediate or Cancel (IOC) [ SYMBOL_FILLING_MODE  ]
    // fok
    // 市价单或限价单一旦在市场上出现就将全部执行；如果不这样做，则订单将被取消。
    tif_fill_or_kill = 4,  // Fill or Kill (FOK) [SYMBOL_FILLING_MODE  ]

    tif_good_till_crossing = 5,  // Good Till Crossing (GTX)
    tif_good_till_date = 6,      // Good Till Date
    tif_at_the_close = 7         //	At the Close  [ SYMBOL_TRADE_EXEMODE ]
}; /* ----------  end of enum __TimeInForce  ---------- */

typedef enum __TimeInForce TimeInForce;

/**
 * FIX Protocol FIX.4.4
 * OrdType <40>
 * Order type
 */
enum __OrdType {
    ot_market = 1,
    ot_limit = 2,
    ot_stop = 3,
    ot_stop_limit = 4,
    /* ot_close, */
    /* ot_stop_trail, */
    /* ot_stop_trail_limit */

}; /* ----------  end of enum __OrdType  ---------- */

typedef enum __OrdType OrdType;

/**
 * FIX Protocol FIX.4.4
 * ExecType <150> field
 *  Describes the specific Execution Report (i.e. Pending Cancel) while
 * OrdStatus <39> will always identify the current order status (i.e. Partially
 * Filled)
 */
enum __ExecType {
    NewOrder = 0,
    /* Partially_filled,  // 1 (deprecated) */
    /* Filled,            // 2 (deprecated) */
    Done_for_the_day = 3,  // 3
    Canceled = 4,          // 4
    Replaced = 5,          // 5
    /* PendingCancel,     // 6 */
    Stopped = 6,  // 7
    Rejected = 8,
    Pending_New = 10,
    Expired = 12,              // C
    Restated = 13,             // D
    Pending_Replace = 14,      // E
    Trade = 15,                // F
    Trade_Correct = 16,        // G
    Trade_Cancel = 17,         // H
    Trigerred_Activated = 21,  // L
    UNKONWN = 99
};
typedef __ExecType ExecType;
/**
 * FIX Protocol FIX 4.4
 * OrdStatus <39>
 * Identifies current status of order.
 */
enum __OrdStatus {
    ost_New = 0,  // Outstanding order with no executions

    ost_Partially_filled,  // Outstanding order with executions and
                           // remaining quantity

    ost_Filled,  // Order completely filled, no remaining quantity

    ost_Done_for_day,  // Order not, or partially, filled; no further executions
                       // forthcoming for the trading day

    ost_Canceled,  // Canceled order with or without executions

    ost_Replaced,  //(Removed/Replaced)

    ost_Pending_Cancel,  // Order with an Order Cancel Request pending (e.g.
                         // result of Order Cancel Request <F>)

    ost_Stopped,  // Order has been stopped at the exchange. Used when
                  // guranteeing or protecting a price and quantity

    ost_Rejected,  // Order has been rejected by sell-side

    ost_Suspended,  // Order has been placed in suspended state at the request
                    // of the client.

    ost_Pending_New = 'A',  // A  Order has been received by sell-side's

    ost_Calculated = 'B',  // B

    ost_Expired = 'C',  // C  Order has been canceled in broker's system due to
                        // time in force instructions.

    ost_Accepted_for_bidding = 'D',  // D

    ost_Pending_Replace =
        'E'  // E (e.g. result of Order Cancel/Replace Request <G>)
}; /* ----------  end of enum __OrderStatus  ---------- */

typedef enum __OrdStatus OrdStatus;

/**
 * FIX Protocol FIX 4.4
 * Side <54>
 * Side of order.
 */
enum __Side {
    os_Buy = 1,
    os_Sell = 2
    // ...

}; /* ----------  end of enum __Side  ---------- */

typedef enum __Side Side;

/**
 * e2l function api type
 *
 */

enum __BarType {
    MODE_TIME = 0,
    MODE_OPEN,
    MODE_HIGH,
    MODE_LOW,
    MODE_CLOSE,
    MODE_VOL,
    MODE_ADJCLOSE
    /* MODE_BID, */
    /* MODE_ASK, */
    /* MODE_DIGITS, */
    /* MODE_POINT, */
}; /* ----------  end of enum __BarType  ---------- */

typedef enum __BarType BarType;
/**
 * ticket 报价的话，可以 低于 1 分钟的周期
 * Container.cpp 这儿需要用到
 */

enum __TimeFrames {
    PERIOD_CURRENT = 0,  // 1. Current timeframe
    PERIOD_M1 = 1,       // 2. 1 minutes
    PERIOD_M = 5,        // 3. 5 minutes
    PERIOD_M15 = 15,     // 4. 15 minutes
    PERIOD_M30 = 30,     // 5. 30 minutes
    PERIOD_H1 = 60,      // 6. 1 hours
    PERIOD_H4 = 240,     // 7. 4 hours
    PERIOD_D1 = 1440,    // 8. 1 day
    PERIOD_W1 = 10080,   // 9. 1 week
    PERIOD_MN1 = 43200,  // 10. 1 month
}; /* ----------  end of enum __TimeFrames  ---------- */

typedef enum __TimeFrames TimeFrames;

enum __mkType {
    mk_csv,
    mk_kafka,
    mk_tick,
    mk_bar
}; /* ----------  end of enum __mkType  ---------- */

typedef enum __mkType MKType;

/*
 * Strategy run e2l
 */
enum __Offers {
    OF_Index = 0,  // 以 index 报价
    OF_Tick = 1    // 以每笔 tick 报价
}; /* ----------  end of enum __Offers  ---------- */

typedef enum __Offers Offers;

/**
 * is init e2l
 */

enum __InitOk {
    I_Proc = 0,  // proceed
    I_OK = 1     // initok
}; /* ----------  end of enum __InitOk  ---------- */

typedef enum __InitOk InitOk;

enum __OMSRisk {
    I_OMS = 0,     //  oms server run
    I_BROKER = 1,  // fixapplication broker
    I_EA = 2       //  ea
}; /* ----------  end of enum __OMSRisk  ---------- */

typedef enum __OMSRisk OMSRisk;

enum __LineState {
    L_Dotted = 0,
    L_Solid = 1,
}; /* ----------  end of enum __LineState  ---------- */

typedef enum __LineState LineState;

enum __SymbolTradeMode {
    M_Disabled = 0,  // Trade is disabled for the symbol
    M_LongOnly,      // Allowed only long positions
    M_ShortOnly,     // Allowed only short positions
    M_CloseOnly,     // Allowed only position close operations
    M_Full,          // No trade restrictions
}; /* ----------  end of enum SymbolTradeMode  ---------- */

typedef enum __SymbolTradeMode SymbolTradeMode;

/**
 * order select flag
 */
enum __SelectFlag {
    F_ByPos = 0,
    F_ByTicket,
    P_Trade,
    P_History,
}; /* ----------  end of enum __SelectFlag  ---------- */

typedef enum __SelectFlag SelectFlag;

/**
 * bool type
 */
enum __Bool {
    B_FALSE = 0,  // false
    B_TRUE = 1    // true
}; /* ----------  end of enum __Bool  ---------- */

typedef enum __Bool Bool;

enum __OrderEvent {
    Oe_Compleate = 0,
    Oe_StopLoss,
    Oe_TakeProfit
}; /* ----------  end of enum __OrderEvent  ---------- */

typedef enum __OrderEvent OrderEvent;

/**
 * 什么时候 撮合
 */
enum __MatchEvent {
    ME_OrderIn = 0,  // 有订单进入，就撮合
    ME_Open,         // 开盘集合竞价的时候
    ME_Close         // 收盘的时候
}; /* ----------  end of enum __MatchEvent  ---------- */

typedef enum __MatchEvent MatchEvent;

#define SequentialEnum(Name, ...)                                          \
    enum Name { __VA_ARGS__ };                                             \
    namespace {                                                            \
    [[maybe_unused]] inline static std::initializer_list<Name> Name##List{ \
        __VA_ARGS__};                                                      \
    };

SequentialEnum(Analy,
               id,                   // unique id for any node
               cash,                 // allot cash
               start,                // start timestamp
               end,                  // end timestamp
               Duration,             //                   3116 days 00:00:00
               ExposureTime,         // [%]                       94.27
               EquityFinal,          // [$]                     68935.12
               EquityPeak,           // [$]                      68991.22
               Return,               // [%]                             589.35
               BuyAndHold,           // Return [%]                  703.46
               ReturnAnn,            // (Ann.) [%]                       25.42
               VolatilityAnn,        // (Ann.) [%]                   38.43
               SharpeRatio,          //                        0.66
               SortinoRatio,         //                          1.30
               CalmarRatio,          //                            0.77
               MaxDrawdown,          // [%]                      -33.08
               AvgDrawdown,          // [%]                       -5.58
               MaxDrawdownDuration,  //      688 days 00:00:00
               AvgDrawdownDuration,  //       41 days 00:00:00
                                     // # Trades 93
               WinRate,              // [%]                            53.76
               BestTrade,            // [%]                          57.12
               WorstTrade,           // [%]                        -16.63
               AvgTrade,             // [%]                           1.96
               MaxTradeDuration,     //         121 days 00:00:00
               AvgTradeDuration,     //          32 days 00:00:00
               ProfitFactor,         //                            2.13
               Expectancy,           // [%]                           6.91
               SQN,             //                                      1.78
               KellyCriterion,  //                        0.6134
               curve,           //                          Equ...

); /* ----------  end of enum __Analy  ---------- */
typedef enum Analy Analy;

enum __Commit {
    Pass = 0,    // 通过
    Reject = 1,  // 不下单
    Restate = 2  // 在没有单的时候，可以下，有单的时候，就等待
}; /* ----------  end of enum __Commit  ---------- */

typedef enum __Commit Commit;

/**
 * 回测结算模式
 */
enum __SettleInstMode {
    _settle = 0,      // 结算模式，但余额不再增加
    _settle_balance,  // 结算模式，余额可增加
    _observer,        // 观察者模式，不会结算
}; /* ----------  end of enum _SettleInstMode  ---------- */

typedef enum __SettleInstMode SettleInstMode;

/*
 * A-B book
 */
enum __BookType {
    ABook = 0,
    BBook = 1
}; /* ----------  end of enum __BookType  ---------- */

typedef enum __BookType BookType;
}  // namespace e2
#endif /* ----- #ifndef E2LTYPE_INC  ----- */
