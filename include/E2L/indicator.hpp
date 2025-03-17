/*
 * =====================================================================================
 *
 *       Filename:  indicator.hpp
 *
 *    Description:  indicator
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 16时17分37秒
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

#ifndef INDICATOR_INC
#define INDICATOR_INC
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eAC
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Accelerator Oscillator
 * ============================================
 */
void eAC(); /* -----  end of function eAC  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eAD
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Accumulation/Distribution
 * ============================================
 */
void eAD(); /* -----  end of function eAD  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eADX
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Average Directional Index
 * ============================================
 */
void eADX(); /* -----  end of function eADX  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eAlligator
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Alligator
 * ============================================
 */
void eAlligator(); /* -----  end of function eAlligator  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eAO
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Awesome Oscillator
 * ============================================
 */
void eAO(); /* -----  end of function eAO  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eATR
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Average True Range
 * ============================================
 */
void eATR(); /* -----  end of function eATR  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eBearsPower
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Bears Power
 * ============================================
 */
void eBearsPower(); /* -----  end of function eBearsPower  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eBands
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Bollinger Bands®
 * ============================================
 */
void eBands(); /* -----  end of function eBands  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eCCI
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Commodity Channel Index
 * ============================================
 */
void eCCI(); /* -----  end of function eCCI  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eMA
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Moving Average
 * ============================================
 */
void eMA(); /* -----  end of function eMA  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eMACD
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 * Moving Averages Convergence-Divergence
 * ============================================
 */
void eMACD(); /* -----  end of function eMACD  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eOBV
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  On Balance Volume
 * ============================================
 */
void eOBV(); /* -----  end of function eOBV  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eRSI
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Relative Strength Index
 * ============================================
 */
void eRSI(); /* -----  end of function eRSI  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eStdDev
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 * Standard Deviation
 * ============================================
 */
void eStdDev(); /* -----  end of function eStdDev  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  eStochastic
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Stochastic Oscillator
 * ============================================
 */
void eStochastic(); /* -----  end of function eStochastic  ----- */

}  // namespace e2l

#endif /* ----- #ifndef INDICATOR_INC  ----- */
