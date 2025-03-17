/*
 * =====================================================================================
 *
 *       Filename:  math.hpp
 *
 *    Description:  math
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 15时01分04秒
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

#ifndef MATH_INC
#define MATH_INC

/**
 * A set of mathematical and trigonometric functions.
 */
#include "E2LType.hpp"
#include "assembler/BaseType.hpp"
namespace e2l {

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Array
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void Array(e2::Int_e, e2::Int_e, const char *_vname, e2::Int_e loc,
           const char *_path); /* -----  end of function Array  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  FixedArray
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ArrayFixed(
    e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function FixedArray  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ArrayShare
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ArrayShare(
    e2::Int_e id, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function ArrayShare  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ArrayFill
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
void ArrayFill(e2::Int_e, e2::Int_e, const char *_vname, e2::Int_e loc,
               const char *_path); /* -----  end of function ArrayFill  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  AddArray
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Bool ArrayAdd(
    e2::Int_e, e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function AddArray  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ArrayLength
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ArrayLength(
    e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function ArrayLength  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ArraySize
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ArraySize(
    e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function ArraySize  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  GetArray
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ArrayGet(
    e2::Int_e, e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function GetArray  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  LastArray
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ArrayLast(
    e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function LastArray  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  UpdateArray
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Bool ArrayUpdate(
    e2::Int_e, e2::Int_e, e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function UpdateArray  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ArrayMax
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ArrayMax(
    e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function ArrayMax  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  ArrayMin
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e ArrayMin(
    e2::Int_e, const char *_vname, e2::Int_e loc,
    const char *_path); /* -----  end of function ArrayMin  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  between
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Bool between(e2::Int_e, e2::Int_e, e2::Int_e);
/* -----  end of function between  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Abs
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns absolute value (modulus) of the specified numeric value
 * ============================================
 */
e2::Int_e Abs(e2::Int_e); /* -----  end of function Abs  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Arccos
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the arc cosine of x in radians
 * ============================================
 */
void Arccos(); /* -----  end of function Arccos  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Arcsin
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the arc sine of x in radians
 * ============================================
 */
void Arcsin(); /* -----  end of function Arcsin  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Arctan
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the arc tangent of x in radians
 * ============================================
 */
void Arctan(); /* -----  end of function Arctan  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Ceil
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns integer numeric value closest from above
 *  若不出现错误，则返回不小于 arg 的最小整数值
 * ============================================
 */
e2::Int_e Ceil(e2::Int_e); /* -----  end of function Ceil  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Cos
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the cosine of a number
 * ============================================
 */
void Cos(); /* -----  end of function Cos  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Exp
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns exponent of a number
 * ============================================
 */
void Exp(); /* -----  end of function Exp  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Floor
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns integer numeric value closest from below
 *  http://localhost/cplus/reference/zh/cpp/numeric/math/floor.html
 *  若不出现错误，则返回不大于 arg 的最大整数值
 * ============================================
 */
e2::Int_e Floor(e2::Int_e); /* -----  end of function Floor  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Log
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns natural logarithm
 * ============================================
 */
void Log(); /* -----  end of function Log  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Log10
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the logarithm of a number by base 10
 * ============================================
 */
void Log10(); /* -----  end of function Log10  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Max
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the maximal value of the two numeric values
 * ============================================
 */
e2::Int_e Max(e2::Int_e, e2::Int_e); /* -----  end of function Max  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Maxs
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e Maxs(e2::Int_e, e2::Int_e,
               e2::Int_e); /* -----  end of function Maxs  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Min
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the minimal value of the two numeric values
 * ============================================
 */
e2::Int_e Min(e2::Int_e, e2::Int_e); /* -----  end of function Min  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Mins
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e Mins(e2::Int_e, e2::Int_e,
               e2::Int_e); /* -----  end of function Mins  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Mod
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the real remainder after the division of two numbers
 * ============================================
 */
void Mod(); /* -----  end of function Mod  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Pow
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Raises the base to the specified power
 * ============================================
 */
void Pow(); /* -----  end of function Pow  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Rand
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns a pseudorandom value within the range of 0 to 32767
 * ============================================
 */
void Rand(); /* -----  end of function Rand  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Round
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Rounds of a value to the nearest integer
 * ============================================
 */
void Round(); /* -----  end of function Round  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Sin
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the sine of a number
 * ============================================
 */
void Sin(); /* -----  end of function Sin  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Sqrt
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns a square root
 * ============================================
 */
e2::Int_e Sqrt(e2::Int_e); /* -----  end of function Sqrt  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Stdev
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e Stdev(e2::Int_e); /* -----  end of function Stdev  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Srand
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Sets the starting point for generating a series of pseudorandom integers
 * ============================================
 */
void Srand(); /* -----  end of function Srand  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Tan
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the tangent of a number
 * ============================================
 */
void Tan(); /* -----  end of function Tan  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Sum
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
 * ============================================
 */
e2::Int_e Sum(e2::Int_e, e2::Int_e); /* -----  end of function Sum  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Last
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 * <F12>
 * ============================================
 */
e2::Int_e Last(e2::Int_e index); /* -----  end of function Last  ----- */
}  // namespace e2l
#endif /* ----- #ifndef MATH_INC  ----- */
