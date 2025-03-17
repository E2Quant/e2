/*
 * =====================================================================================
 *
 *       Filename:  BaseType.hpp
 *
 *    Description:  BaseType
 *
 *        Version:  1.0
 *        Created:  2024年01月30日 15时13分19秒
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

#ifndef BASETYPE_INC
#define BASETYPE_INC
#include <array>
#include <cstdint>
#include <map>
#include <string>
namespace e2 {
using Int_e = std::int64_t;

enum __NodeType {

    _statement,  // 0

    _identifier,  // 1
    _variable,    // 2
    _number,      // 3

    _function,    // 4
    _methodcall,  // 5
    _union,       // 6
    _return,      // 7

    _block,  // 8

    _binaryop,  // 9

    _ifcf,      // 10
    _switchcf,  // 11
    _flowiter,  // 12

    _assign,      // 13
    _expression,  // 14
    _comp,        // 15
    _string,      // 16
    _module,      // 17

    _break  // 18
};          /* ----------  end of enum Nodetype  ---------- */

typedef enum __NodeType NodeType;

enum __IterType {
    _while,
    _do,
    _for,
    _forfull,
}; /* ----------  end of enum IterType  ---------- */

typedef enum __IterType IterType;

enum __Selection {
    _if,
    _then,
    _else,
    _switch,
    _case,
    _default,
}; /* ----------  end of enum Selection  ---------- */

typedef enum __Selection Selection;

enum __IDType {
    _normal,  //  normal
    _global,  // global id

}; /* ----------  end of enum IDType  ---------- */

typedef enum __IDType IDType;

enum __ScopeKind {
    _sk_null,   // null sk
    _sk_fun,    // function declaration
    _sk_union,  // union declaration
    _sk_flow,   // control flow
    _sk_main,   // variable
};              /* ----------  end of enum ScopeKind  ---------- */

typedef enum __ScopeKind ScopeKind;

inline std::map<std::string, Int_e> _GlobalVariables = {};

#define FIND_GV(arg)                                     \
    ({                                                   \
        bool __ok_find = false;                          \
        do {                                             \
            std::map<std::string, Int_e>::iterator _it = \
                _GlobalVariables.find(arg);              \
            if (_it != _GlobalVariables.end()) {         \
                __ok_find = true;                        \
            }                                            \
        } while (0);                                     \
        __ok_find;                                       \
    })

/**
 * 比例 如果 是1 的时候，别的值，不一定是1 的比例
 * 到时候再优化
 */

#ifndef NUMBER_DECI
#define NUMBER_DECI 1
#endif

#define NUMBERVAL(arg)                                 \
    ({                                                 \
        double __val = 0.0;                            \
        do {                                           \
            __val = (double)arg / (double)NUMBER_DECI; \
        } while (0);                                   \
        __val;                                         \
    })

#define VALNUMBER(arg)                                 \
    ({                                                 \
        double __val = 0.0;                            \
        do {                                           \
            __val = (double)arg * (double)NUMBER_DECI; \
        } while (0);                                   \
        __val;                                         \
    })

/**
 *
 * ret = (lhs * rhs) / NUMBER_DECI
 *
 */
#define Mul(lhs, rhs)                         \
    ({                                        \
        int64_t _ret = 0;                     \
        do {                                  \
            _ret = (lhs * rhs) / NUMBER_DECI; \
        } while (0);                          \
        _ret;                                 \
    })

/**
 * ret = (lhs * NUMBER_DECI) / rhs
 */
#define SDiv(lhs, rhs)                            \
    ({                                            \
        int64_t _ret = 0;                         \
        do {                                      \
            if (rhs == 0) {                       \
                _ret = 0;                         \
            }                                     \
            else {                                \
                _ret = (lhs * NUMBER_DECI) / rhs; \
            }                                     \
        } while (0);                              \
        _ret;                                     \
    })

#define ADD_GV(key, val)                                   \
    do {                                                   \
        _GlobalVariables.insert({key, val * NUMBER_DECI}); \
    } while (0)

/**
 * check memory
 */
//#define CMALLOC 1

#if (defined E2L_DEBUG && defined CMALLOC)
inline std::atomic<int> ptr_number = 0;
#define RELEASE(ptr)                                                  \
    do {                                                              \
        if (ptr != nullptr) {                                         \
            delete ptr;                                               \
            ptr = nullptr;                                            \
            int num = ptr_number.load(std::memory_order_acquire) - 1; \
            ptr_number.store(num, std::memory_order_release);         \
            e2::log::bug("release, num:", num);                       \
        }                                                             \
    } while (0)
#else
#define RELEASE(ptr)          \
    do {                      \
        if (ptr != nullptr) { \
            delete ptr;       \
            ptr = nullptr;    \
        }                     \
    } while (0)
#endif

#if (defined E2L_DEBUG && defined CMALLOC)
#define MALLOC(obj, args...)                                               \
    ({                                                                     \
        obj *__ptr = nullptr;                                              \
        do {                                                               \
            int _num = ptr_number.fetch_add(1, std::memory_order_release); \
            e2::log::info("new obj, num:", _num);                          \
            __ptr = new obj(args);                                         \
        } while (0);                                                       \
        __ptr;                                                             \
    })
#else
#define MALLOC(obj, args...)       \
    ({                             \
        obj *__ptr = nullptr;      \
        do {                       \
            __ptr = new obj(args); \
        } while (0);               \
        __ptr;                     \
    })
#endif
}  // namespace e2
#endif /* ----- #ifndef BASETYPE_INC  ----- */

