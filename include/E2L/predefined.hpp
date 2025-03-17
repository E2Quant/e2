/*
 * =====================================================================================
 *
 *       Filename:  predefined.hpp
 *
 *    Description:  predefined
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 14时28分33秒
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

#ifndef PREDEFINED_INC
#define PREDEFINED_INC

/**
 * The predefined Variables
 */
namespace e2l {
/*
  The predefined Variables
   global union

   union Series{
       Open=1; #Series array that contains open prices of each bar of the
                    current chart

       High=1; # Series array that contains the highest prices of each
                    bar of the current chart

       Low=1;  #Series array that contains the lowest
                    prices of each bar of the current chart

       Close=1; # Series array that contains
                    close prices for each bar of the current chart

       Time=1;  # Series array that
                    contains open time of each bar of the current chart

       Volume=1; # Series array
                    that contains tick volumes of each bar of the current chart
   }

   union Price{
       Ask=1;  # The latest known seller's price (ask price) of the current
                    symbol
       Bid=1; # The latest known buyer's price (offer price, bid price) of
                    the current symbol
   }

   union Point{
       Digits=1; #The _Digits variable stores number of digits after a decimal
                    point, which defines the price accuracy of the symbol of the
                    current chart.

       Symbol=1; # The _Symbol variable contains the symbol name of the current
                    chart.

       Period=1; # The _Period variable contains the value of the timeframe of
                    the current chart.
   }

 */

}  // namespace e2l

#endif /* ----- #ifndef PREDEFINED_INC  ----- */
