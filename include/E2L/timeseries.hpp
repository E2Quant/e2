/*
 * =====================================================================================
 *
 *       Filename:  timeseries.hpp
 *
 *    Description:  timeseries
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 15时51分11秒
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

#ifndef TIMESERIES_INC
#define TIMESERIES_INC
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ShiftOpen
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  	Returns Open price value for the bar of specified symbol with timeframe
 * and shift
 * ============================================
 */
void ShiftOpen(); /* -----  end of function ShiftOpen  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ShiftClose
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns Close price value for the bar of specified symbol with timeframe and
 * shift
 * ============================================
 */
void ShiftClose(); /* -----  end of function ShiftClose  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ShiftHigh
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   Returns High price value for the bar of specified symbol with timeframe and
 * shift
 * ============================================
 */
void ShiftHigh(); /* -----  end of function ShiftHigh  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ShiftLow
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns Low price value for the bar of indicated symbol with timeframe and
 * shift
 * ============================================
 */
void ShiftLow(); /* -----  end of function ShiftLow  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ShiftTime
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns time value for the bar of specified symbol with timeframe and shift
 * ============================================
 */
void ShiftTime(); /* -----  end of function ShiftTime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ShiftVolume
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  	Returns Tick Volume value for the bar of specified symbol with timeframe
 * and shift
 * ============================================
 */
void ShiftVolume(); /* -----  end of function ShiftVolume  ----- */
}  // namespace e2l
#endif /* ----- #ifndef TIMESERIES_INC  ----- */
