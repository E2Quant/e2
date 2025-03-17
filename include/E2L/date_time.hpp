/*
 * =====================================================================================
 *
 *       Filename:  date_time.hpp
 *
 *    Description:  date_time
 *
 *        Version:  1.0
 *        Created:  2023年12月21日 15时12分25秒
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

#ifndef DATE_TIME_INC
#define DATE_TIME_INC
/**
 * This is the group of functions for working with data of datetime type (an
 * integer that represents the number of seconds elapsed from 0 hours of January
 * 1, 1970).
 *
 * To arrange high-resolution counters and timers, use the GetTickCount()
 * function, which produces values in milliseconds.
 */
#include "assembler/BaseType.hpp"
namespace e2l {
/* union DateTime */
/*   { */
/*     year=1;           # year */
/*     mon=1;            # month */
/*     day=1;            # day */
/*     hour=1;           # hour */
/*     min=1;            # minutes */
/*     sec=1;            # seconds */
/*     day_of_week=1;    # day of week (0 - Sunday, 1 - Monday, ..., 6 -
 * Saturday) */
/*     day_of_year=1;    # number of a day in a year (January 1 has number 0)
 */
/*   }; */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TimeToString
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *   Converting a value containing time in seconds elapsed since 01.01.1970 into
 * a string of "yyyy.mm.dd hh:mi" format
 * ============================================
 */
void TimeToString(); /* -----  end of function TimeToString  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  StringToTime
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Converts string in the format "yyyy.mm.dd hh:mi" to datetime type
 * ============================================
 */
void StringToTime(); /* -----  end of function StringToTime  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TimeCurrent
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the last known server time (time of the last quote receipt) in the
 * datetime format
 * ============================================
 */
e2::Int_e TimeCurrent(); /* -----  end of function TimeCurrent  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TimeLocal
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the local computer time in datetime format
 * ============================================
 */
e2::Int_e TimeLocal(); /* -----  end of function TimeLocal  ----- */
/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TimeGMT
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *
Returns GMT in datetime format with the Daylight Saving Time by local time of
the computer, where the client terminal is running
 * ============================================
 */
void TimeGMT(); /* -----  end of function TimeGMT  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  TimeGMTOffset
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 *  Returns the current difference between GMT time and the local computer time
 * in seconds, taking into account DST switch
 * ============================================
 */
void TimeGMTOffset(); /* -----  end of function TimeGMTOffset  ----- */

/*
 * ===  FUNCTION  =============================
 *
 *         Name:  Clock
 *  ->  void *
 *  Parameters:
 *  - size_t  arg
 *  Description:
 * return millisecond time
 * ============================================
 */
e2::Int_e Clock(); /* -----  end of function Clock  ----- */
}  // namespace e2l
#endif /* ----- #ifndef DATE_TIME_INC  ----- */
