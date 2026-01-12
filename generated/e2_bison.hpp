// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file /Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_USERS_VYOUZHI_WORKSPACE_C_C_PLUG_ETOMC2LAN_E2_GENERATED_E2_BISON_HPP_INCLUDED
# define YY_YY_USERS_VYOUZHI_WORKSPACE_C_C_PLUG_ETOMC2LAN_E2_GENERATED_E2_BISON_HPP_INCLUDED
// "%code requires" blocks.
#line 29 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"

    /* you may need these header files 
     * add more header file if you need more
     */
    #include <stdio.h>
    #include <iostream>
    #include <list>
    #include <string>
    #include <functional>


#include "ast/ParserCtx.hpp"
    #include "utility/Log.hpp"
    #include "assembler/BaseNode.hpp"
    extern  int code_line;

/* define the sturctures using as types for non-terminals */

/* end the structures for non-terminal types */

#line 70 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace yy {
#line 205 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.hpp"




  /// A Bison parser.
  class Parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // translation_unit
      // compound_statement
      // compound_block
      // union_list
      // namespace_body
      char dummy1[sizeof (e2::Block *)];

      // expression
      // additive_expression
      // multiplicative_expression
      // shift_expression
      // conditional
      // expression_rvalue
      // primary_rvalue
      char dummy2[sizeof (e2::Expression *)];

      // parameter_list
      // function_parameter
      char dummy3[sizeof (e2::ExpressionList *)];

      // extern_call
      char dummy4[sizeof (e2::ExternDeclaration *)];

      // function_definition
      char dummy5[sizeof (e2::FunctionDeclaration *)];

      // primary_lvalue
      // id_func_call_name
      // id_ns_gl_name
      // id_ns_name
      // global_union_variable
      // namespace_variable
      // identifier_str
      char dummy6[sizeof (e2::Identifier *)];

      // import_module
      char dummy7[sizeof (e2::ImportModule *)];

      // iteration_statement
      char dummy8[sizeof (e2::IterStatement *)];

      // labled_if
      // labeled_switch
      char dummy9[sizeof (e2::LabledBlock *)];

      // method_call
      char dummy10[sizeof (e2::MethodCall *)];

      // namespace_definition
      char dummy11[sizeof (e2::NameSpace *)];

      // block
      // statement
      // selection_statement
      // for_range
      // jump_statement
      char dummy12[sizeof (e2::Statement *)];

      // unary_val
      char dummy13[sizeof (e2::UnaryOperator *)];

      // union_definition
      char dummy14[sizeof (e2::UnionDeclaration *)];

      // variable_val
      // union_statement
      // namespace_member
      char dummy15[sizeof (e2::VariableStatement *)];

      // FCONSTANT
      char dummy16[sizeof (float)];

      // NAMESPACE_ATTR
      // OP_LE
      // OP_GE
      // OP_EQ
      // OP_NE
      // LOGICAL_AND
      // LOGICAL_OR
      // LOGICAL_NOT
      // ASSIGN_MUL
      // ASSIGN_DIV
      // ASSIGN_MOD
      // ASSIGN_ADD
      // ASSIGN_SUB
      // ASSIGN_LEFT
      // ASSIGN_RIGHT
      // ASSIGN_AND
      // ASSIGN_XOR
      // ASSIGN_OR
      // ARITH_LEFT
      // ARITH_RIGHT
      // UNARY_INC
      // UNARY_DEC
      // ASSIGN_EQ
      // '*'
      // '/'
      // '%'
      // '+'
      // '-'
      // '<'
      // '>'
      // '&'
      // '^'
      // '|'
      // unary
      // add_arithmetic
      // mul_arithmetic
      // shift_arithmetic
      // comparison
      // logical
      // assignment
      char dummy17[sizeof (int)];

      // CONSTANT
      char dummy18[sizeof (std::int64_t)];

      // IDENTIFIER
      // STRING_LITERAL
      // IMPORT_LITERAL
      // NSFUNC_CALL
      char dummy19[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    END = 0,                       // END
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    IDENTIFIER = 258,              // IDENTIFIER
    STRING_LITERAL = 259,          // STRING_LITERAL
    IMPORT_LITERAL = 260,          // IMPORT_LITERAL
    NSFUNC_CALL = 261,             // NSFUNC_CALL
    CONSTANT = 262,                // CONSTANT
    FCONSTANT = 263,               // FCONSTANT
    NAMESPACE_ATTR = 264,          // NAMESPACE_ATTR
    OP_LE = 265,                   // OP_LE
    OP_GE = 266,                   // OP_GE
    OP_EQ = 267,                   // OP_EQ
    OP_NE = 268,                   // OP_NE
    LOGICAL_AND = 269,             // LOGICAL_AND
    LOGICAL_OR = 270,              // LOGICAL_OR
    LOGICAL_NOT = 271,             // LOGICAL_NOT
    ASSIGN_MUL = 272,              // ASSIGN_MUL
    ASSIGN_DIV = 273,              // ASSIGN_DIV
    ASSIGN_MOD = 274,              // ASSIGN_MOD
    ASSIGN_ADD = 275,              // ASSIGN_ADD
    ASSIGN_SUB = 276,              // ASSIGN_SUB
    ASSIGN_LEFT = 277,             // ASSIGN_LEFT
    ASSIGN_RIGHT = 278,            // ASSIGN_RIGHT
    ASSIGN_AND = 279,              // ASSIGN_AND
    ASSIGN_XOR = 280,              // ASSIGN_XOR
    ASSIGN_OR = 281,               // ASSIGN_OR
    ARITH_LEFT = 282,              // ARITH_LEFT
    ARITH_RIGHT = 283,             // ARITH_RIGHT
    UNARY_INC = 284,               // UNARY_INC
    UNARY_DEC = 285,               // UNARY_DEC
    ASSIGN_EQ = 286,               // ASSIGN_EQ
    NAMESPACE = 287,               // NAMESPACE
    UNION = 288,                   // UNION
    FUNCTION = 289,                // FUNCTION
    EXTERN = 290,                  // EXTERN
    IMPORT = 291,                  // IMPORT
    THIS = 292,                    // THIS
    SELF = 293,                    // SELF
    IF = 294,                      // IF
    ELSE = 295,                    // ELSE
    SWITCH = 296,                  // SWITCH
    CASE = 297,                    // CASE
    DEFAULT = 298,                 // DEFAULT
    WHILE = 299,                   // WHILE
    DO = 300,                      // DO
    FOR = 301,                     // FOR
    CONTINUE = 302,                // CONTINUE
    BREAK = 303,                   // BREAK
    RETURN = 304                   // RETURN
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 72, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // END
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_IDENTIFIER = 3,                        // IDENTIFIER
        S_STRING_LITERAL = 4,                    // STRING_LITERAL
        S_IMPORT_LITERAL = 5,                    // IMPORT_LITERAL
        S_NSFUNC_CALL = 6,                       // NSFUNC_CALL
        S_CONSTANT = 7,                          // CONSTANT
        S_FCONSTANT = 8,                         // FCONSTANT
        S_NAMESPACE_ATTR = 9,                    // NAMESPACE_ATTR
        S_OP_LE = 10,                            // OP_LE
        S_OP_GE = 11,                            // OP_GE
        S_OP_EQ = 12,                            // OP_EQ
        S_OP_NE = 13,                            // OP_NE
        S_LOGICAL_AND = 14,                      // LOGICAL_AND
        S_LOGICAL_OR = 15,                       // LOGICAL_OR
        S_LOGICAL_NOT = 16,                      // LOGICAL_NOT
        S_ASSIGN_MUL = 17,                       // ASSIGN_MUL
        S_ASSIGN_DIV = 18,                       // ASSIGN_DIV
        S_ASSIGN_MOD = 19,                       // ASSIGN_MOD
        S_ASSIGN_ADD = 20,                       // ASSIGN_ADD
        S_ASSIGN_SUB = 21,                       // ASSIGN_SUB
        S_ASSIGN_LEFT = 22,                      // ASSIGN_LEFT
        S_ASSIGN_RIGHT = 23,                     // ASSIGN_RIGHT
        S_ASSIGN_AND = 24,                       // ASSIGN_AND
        S_ASSIGN_XOR = 25,                       // ASSIGN_XOR
        S_ASSIGN_OR = 26,                        // ASSIGN_OR
        S_ARITH_LEFT = 27,                       // ARITH_LEFT
        S_ARITH_RIGHT = 28,                      // ARITH_RIGHT
        S_UNARY_INC = 29,                        // UNARY_INC
        S_UNARY_DEC = 30,                        // UNARY_DEC
        S_ASSIGN_EQ = 31,                        // ASSIGN_EQ
        S_32_ = 32,                              // '*'
        S_33_ = 33,                              // '/'
        S_34_ = 34,                              // '%'
        S_35_ = 35,                              // '+'
        S_36_ = 36,                              // '-'
        S_37_ = 37,                              // '<'
        S_38_ = 38,                              // '>'
        S_39_ = 39,                              // '&'
        S_40_ = 40,                              // '^'
        S_41_ = 41,                              // '|'
        S_NAMESPACE = 42,                        // NAMESPACE
        S_UNION = 43,                            // UNION
        S_FUNCTION = 44,                         // FUNCTION
        S_EXTERN = 45,                           // EXTERN
        S_IMPORT = 46,                           // IMPORT
        S_THIS = 47,                             // THIS
        S_SELF = 48,                             // SELF
        S_IF = 49,                               // IF
        S_ELSE = 50,                             // ELSE
        S_SWITCH = 51,                           // SWITCH
        S_CASE = 52,                             // CASE
        S_DEFAULT = 53,                          // DEFAULT
        S_WHILE = 54,                            // WHILE
        S_DO = 55,                               // DO
        S_FOR = 56,                              // FOR
        S_CONTINUE = 57,                         // CONTINUE
        S_BREAK = 58,                            // BREAK
        S_RETURN = 59,                           // RETURN
        S_60_ = 60,                              // '='
        S_61_ = 61,                              // "!="
        S_62_ = 62,                              // "<="
        S_63_ = 63,                              // ">="
        S_64_ = 64,                              // ';'
        S_65_ = 65,                              // '('
        S_66_ = 66,                              // ')'
        S_67_ = 67,                              // '{'
        S_68_ = 68,                              // '}'
        S_69_ = 69,                              // ':'
        S_70_ = 70,                              // ','
        S_71_ = 71,                              // '.'
        S_YYACCEPT = 72,                         // $accept
        S_translation_unit = 73,                 // translation_unit
        S_import_module = 74,                    // import_module
        S_block = 75,                            // block
        S_unary_val = 76,                        // unary_val
        S_unary = 77,                            // unary
        S_variable_val = 78,                     // variable_val
        S_expression = 79,                       // expression
        S_additive_expression = 80,              // additive_expression
        S_add_arithmetic = 81,                   // add_arithmetic
        S_multiplicative_expression = 82,        // multiplicative_expression
        S_mul_arithmetic = 83,                   // mul_arithmetic
        S_shift_expression = 84,                 // shift_expression
        S_shift_arithmetic = 85,                 // shift_arithmetic
        S_conditional = 86,                      // conditional
        S_expression_rvalue = 87,                // expression_rvalue
        S_comparison = 88,                       // comparison
        S_logical = 89,                          // logical
        S_assignment = 90,                       // assignment
        S_compound_statement = 91,               // compound_statement
        S_compound_block = 92,                   // compound_block
        S_statement = 93,                        // statement
        S_labled_if = 94,                        // labled_if
        S_labeled_switch = 95,                   // labeled_switch
        S_selection_statement = 96,              // selection_statement
        S_for_range = 97,                        // for_range
        S_iteration_statement = 98,              // iteration_statement
        S_jump_statement = 99,                   // jump_statement
        S_parameter_list = 100,                  // parameter_list
        S_function_parameter = 101,              // function_parameter
        S_function_definition = 102,             // function_definition
        S_method_call = 103,                     // method_call
        S_extern_call = 104,                     // extern_call
        S_union_statement = 105,                 // union_statement
        S_union_list = 106,                      // union_list
        S_union_definition = 107,                // union_definition
        S_namespace_member = 108,                // namespace_member
        S_namespace_body = 109,                  // namespace_body
        S_namespace_definition = 110,            // namespace_definition
        S_primary_lvalue = 111,                  // primary_lvalue
        S_primary_rvalue = 112,                  // primary_rvalue
        S_id_func_call_name = 113,               // id_func_call_name
        S_id_ns_gl_name = 114,                   // id_ns_gl_name
        S_id_ns_name = 115,                      // id_ns_name
        S_global_union_variable = 116,           // global_union_variable
        S_namespace_variable = 117,              // namespace_variable
        S_identifier_str = 118                   // identifier_str
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
      case symbol_kind::S_namespace_body: // namespace_body
        value.move< e2::Block * > (std::move (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        value.move< e2::Expression * > (std::move (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        value.move< e2::ExpressionList * > (std::move (that.value));
        break;

      case symbol_kind::S_extern_call: // extern_call
        value.move< e2::ExternDeclaration * > (std::move (that.value));
        break;

      case symbol_kind::S_function_definition: // function_definition
        value.move< e2::FunctionDeclaration * > (std::move (that.value));
        break;

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
        value.move< e2::Identifier * > (std::move (that.value));
        break;

      case symbol_kind::S_import_module: // import_module
        value.move< e2::ImportModule * > (std::move (that.value));
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        value.move< e2::IterStatement * > (std::move (that.value));
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        value.move< e2::LabledBlock * > (std::move (that.value));
        break;

      case symbol_kind::S_method_call: // method_call
        value.move< e2::MethodCall * > (std::move (that.value));
        break;

      case symbol_kind::S_namespace_definition: // namespace_definition
        value.move< e2::NameSpace * > (std::move (that.value));
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        value.move< e2::Statement * > (std::move (that.value));
        break;

      case symbol_kind::S_unary_val: // unary_val
        value.move< e2::UnaryOperator * > (std::move (that.value));
        break;

      case symbol_kind::S_union_definition: // union_definition
        value.move< e2::UnionDeclaration * > (std::move (that.value));
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
      case symbol_kind::S_namespace_member: // namespace_member
        value.move< e2::VariableStatement * > (std::move (that.value));
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.move< float > (std::move (that.value));
        break;

      case symbol_kind::S_NAMESPACE_ATTR: // NAMESPACE_ATTR
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_LOGICAL_AND: // LOGICAL_AND
      case symbol_kind::S_LOGICAL_OR: // LOGICAL_OR
      case symbol_kind::S_LOGICAL_NOT: // LOGICAL_NOT
      case symbol_kind::S_ASSIGN_MUL: // ASSIGN_MUL
      case symbol_kind::S_ASSIGN_DIV: // ASSIGN_DIV
      case symbol_kind::S_ASSIGN_MOD: // ASSIGN_MOD
      case symbol_kind::S_ASSIGN_ADD: // ASSIGN_ADD
      case symbol_kind::S_ASSIGN_SUB: // ASSIGN_SUB
      case symbol_kind::S_ASSIGN_LEFT: // ASSIGN_LEFT
      case symbol_kind::S_ASSIGN_RIGHT: // ASSIGN_RIGHT
      case symbol_kind::S_ASSIGN_AND: // ASSIGN_AND
      case symbol_kind::S_ASSIGN_XOR: // ASSIGN_XOR
      case symbol_kind::S_ASSIGN_OR: // ASSIGN_OR
      case symbol_kind::S_ARITH_LEFT: // ARITH_LEFT
      case symbol_kind::S_ARITH_RIGHT: // ARITH_RIGHT
      case symbol_kind::S_UNARY_INC: // UNARY_INC
      case symbol_kind::S_UNARY_DEC: // UNARY_DEC
      case symbol_kind::S_ASSIGN_EQ: // ASSIGN_EQ
      case symbol_kind::S_32_: // '*'
      case symbol_kind::S_33_: // '/'
      case symbol_kind::S_34_: // '%'
      case symbol_kind::S_35_: // '+'
      case symbol_kind::S_36_: // '-'
      case symbol_kind::S_37_: // '<'
      case symbol_kind::S_38_: // '>'
      case symbol_kind::S_39_: // '&'
      case symbol_kind::S_40_: // '^'
      case symbol_kind::S_41_: // '|'
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_assignment: // assignment
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< std::int64_t > (std::move (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::Block *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::Block *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::Expression *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::Expression *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::ExpressionList *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::ExpressionList *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::ExternDeclaration *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::ExternDeclaration *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::FunctionDeclaration *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::FunctionDeclaration *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::Identifier *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::Identifier *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::ImportModule *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::ImportModule *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::IterStatement *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::IterStatement *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::LabledBlock *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::LabledBlock *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::MethodCall *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::MethodCall *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::NameSpace *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::NameSpace *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::Statement *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::Statement *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::UnaryOperator *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::UnaryOperator *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::UnionDeclaration *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::UnionDeclaration *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, e2::VariableStatement *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const e2::VariableStatement *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, float&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const float& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::int64_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::int64_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
      case symbol_kind::S_namespace_body: // namespace_body
        value.template destroy< e2::Block * > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        value.template destroy< e2::Expression * > ();
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        value.template destroy< e2::ExpressionList * > ();
        break;

      case symbol_kind::S_extern_call: // extern_call
        value.template destroy< e2::ExternDeclaration * > ();
        break;

      case symbol_kind::S_function_definition: // function_definition
        value.template destroy< e2::FunctionDeclaration * > ();
        break;

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
        value.template destroy< e2::Identifier * > ();
        break;

      case symbol_kind::S_import_module: // import_module
        value.template destroy< e2::ImportModule * > ();
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        value.template destroy< e2::IterStatement * > ();
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        value.template destroy< e2::LabledBlock * > ();
        break;

      case symbol_kind::S_method_call: // method_call
        value.template destroy< e2::MethodCall * > ();
        break;

      case symbol_kind::S_namespace_definition: // namespace_definition
        value.template destroy< e2::NameSpace * > ();
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        value.template destroy< e2::Statement * > ();
        break;

      case symbol_kind::S_unary_val: // unary_val
        value.template destroy< e2::UnaryOperator * > ();
        break;

      case symbol_kind::S_union_definition: // union_definition
        value.template destroy< e2::UnionDeclaration * > ();
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
      case symbol_kind::S_namespace_member: // namespace_member
        value.template destroy< e2::VariableStatement * > ();
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.template destroy< float > ();
        break;

      case symbol_kind::S_NAMESPACE_ATTR: // NAMESPACE_ATTR
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_LOGICAL_AND: // LOGICAL_AND
      case symbol_kind::S_LOGICAL_OR: // LOGICAL_OR
      case symbol_kind::S_LOGICAL_NOT: // LOGICAL_NOT
      case symbol_kind::S_ASSIGN_MUL: // ASSIGN_MUL
      case symbol_kind::S_ASSIGN_DIV: // ASSIGN_DIV
      case symbol_kind::S_ASSIGN_MOD: // ASSIGN_MOD
      case symbol_kind::S_ASSIGN_ADD: // ASSIGN_ADD
      case symbol_kind::S_ASSIGN_SUB: // ASSIGN_SUB
      case symbol_kind::S_ASSIGN_LEFT: // ASSIGN_LEFT
      case symbol_kind::S_ASSIGN_RIGHT: // ASSIGN_RIGHT
      case symbol_kind::S_ASSIGN_AND: // ASSIGN_AND
      case symbol_kind::S_ASSIGN_XOR: // ASSIGN_XOR
      case symbol_kind::S_ASSIGN_OR: // ASSIGN_OR
      case symbol_kind::S_ARITH_LEFT: // ARITH_LEFT
      case symbol_kind::S_ARITH_RIGHT: // ARITH_RIGHT
      case symbol_kind::S_UNARY_INC: // UNARY_INC
      case symbol_kind::S_UNARY_DEC: // UNARY_DEC
      case symbol_kind::S_ASSIGN_EQ: // ASSIGN_EQ
      case symbol_kind::S_32_: // '*'
      case symbol_kind::S_33_: // '/'
      case symbol_kind::S_34_: // '%'
      case symbol_kind::S_35_: // '+'
      case symbol_kind::S_36_: // '-'
      case symbol_kind::S_37_: // '<'
      case symbol_kind::S_38_: // '>'
      case symbol_kind::S_39_: // '&'
      case symbol_kind::S_40_: // '^'
      case symbol_kind::S_41_: // '|'
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_assignment: // assignment
        value.template destroy< int > ();
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.template destroy< std::int64_t > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, float v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const float& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::int64_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::int64_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
    Parser (void *scanner_yyarg, yy::location& loc_yyarg, class e2::ParserCtx& ctx_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING_LITERAL (std::string v, location_type l)
      {
        return symbol_type (token::STRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING_LITERAL (const std::string& v, const location_type& l)
      {
        return symbol_type (token::STRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IMPORT_LITERAL (std::string v, location_type l)
      {
        return symbol_type (token::IMPORT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IMPORT_LITERAL (const std::string& v, const location_type& l)
      {
        return symbol_type (token::IMPORT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NSFUNC_CALL (std::string v, location_type l)
      {
        return symbol_type (token::NSFUNC_CALL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NSFUNC_CALL (const std::string& v, const location_type& l)
      {
        return symbol_type (token::NSFUNC_CALL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONSTANT (std::int64_t v, location_type l)
      {
        return symbol_type (token::CONSTANT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CONSTANT (const std::int64_t& v, const location_type& l)
      {
        return symbol_type (token::CONSTANT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FCONSTANT (float v, location_type l)
      {
        return symbol_type (token::FCONSTANT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FCONSTANT (const float& v, const location_type& l)
      {
        return symbol_type (token::FCONSTANT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NAMESPACE_ATTR (int v, location_type l)
      {
        return symbol_type (token::NAMESPACE_ATTR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NAMESPACE_ATTR (const int& v, const location_type& l)
      {
        return symbol_type (token::NAMESPACE_ATTR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_LE (int v, location_type l)
      {
        return symbol_type (token::OP_LE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OP_LE (const int& v, const location_type& l)
      {
        return symbol_type (token::OP_LE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_GE (int v, location_type l)
      {
        return symbol_type (token::OP_GE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OP_GE (const int& v, const location_type& l)
      {
        return symbol_type (token::OP_GE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_EQ (int v, location_type l)
      {
        return symbol_type (token::OP_EQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OP_EQ (const int& v, const location_type& l)
      {
        return symbol_type (token::OP_EQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_NE (int v, location_type l)
      {
        return symbol_type (token::OP_NE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OP_NE (const int& v, const location_type& l)
      {
        return symbol_type (token::OP_NE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGICAL_AND (int v, location_type l)
      {
        return symbol_type (token::LOGICAL_AND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LOGICAL_AND (const int& v, const location_type& l)
      {
        return symbol_type (token::LOGICAL_AND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGICAL_OR (int v, location_type l)
      {
        return symbol_type (token::LOGICAL_OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LOGICAL_OR (const int& v, const location_type& l)
      {
        return symbol_type (token::LOGICAL_OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGICAL_NOT (int v, location_type l)
      {
        return symbol_type (token::LOGICAL_NOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LOGICAL_NOT (const int& v, const location_type& l)
      {
        return symbol_type (token::LOGICAL_NOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_MUL (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_MUL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_MUL (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_MUL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_DIV (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_DIV, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_DIV (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_DIV, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_MOD (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_MOD, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_MOD (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_MOD, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_ADD (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_ADD, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_ADD (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_ADD, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_SUB (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_SUB, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_SUB (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_SUB, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_LEFT (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_LEFT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_LEFT (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_LEFT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_RIGHT (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_RIGHT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_RIGHT (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_RIGHT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_AND (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_AND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_AND (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_AND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_XOR (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_XOR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_XOR (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_XOR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_OR (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_OR (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARITH_LEFT (int v, location_type l)
      {
        return symbol_type (token::ARITH_LEFT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ARITH_LEFT (const int& v, const location_type& l)
      {
        return symbol_type (token::ARITH_LEFT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARITH_RIGHT (int v, location_type l)
      {
        return symbol_type (token::ARITH_RIGHT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ARITH_RIGHT (const int& v, const location_type& l)
      {
        return symbol_type (token::ARITH_RIGHT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNARY_INC (int v, location_type l)
      {
        return symbol_type (token::UNARY_INC, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNARY_INC (const int& v, const location_type& l)
      {
        return symbol_type (token::UNARY_INC, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNARY_DEC (int v, location_type l)
      {
        return symbol_type (token::UNARY_DEC, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNARY_DEC (const int& v, const location_type& l)
      {
        return symbol_type (token::UNARY_DEC, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_EQ (int v, location_type l)
      {
        return symbol_type (token::ASSIGN_EQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_EQ (const int& v, const location_type& l)
      {
        return symbol_type (token::ASSIGN_EQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NAMESPACE (location_type l)
      {
        return symbol_type (token::NAMESPACE, std::move (l));
      }
#else
      static
      symbol_type
      make_NAMESPACE (const location_type& l)
      {
        return symbol_type (token::NAMESPACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNION (location_type l)
      {
        return symbol_type (token::UNION, std::move (l));
      }
#else
      static
      symbol_type
      make_UNION (const location_type& l)
      {
        return symbol_type (token::UNION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FUNCTION (location_type l)
      {
        return symbol_type (token::FUNCTION, std::move (l));
      }
#else
      static
      symbol_type
      make_FUNCTION (const location_type& l)
      {
        return symbol_type (token::FUNCTION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXTERN (location_type l)
      {
        return symbol_type (token::EXTERN, std::move (l));
      }
#else
      static
      symbol_type
      make_EXTERN (const location_type& l)
      {
        return symbol_type (token::EXTERN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IMPORT (location_type l)
      {
        return symbol_type (token::IMPORT, std::move (l));
      }
#else
      static
      symbol_type
      make_IMPORT (const location_type& l)
      {
        return symbol_type (token::IMPORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THIS (location_type l)
      {
        return symbol_type (token::THIS, std::move (l));
      }
#else
      static
      symbol_type
      make_THIS (const location_type& l)
      {
        return symbol_type (token::THIS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SELF (location_type l)
      {
        return symbol_type (token::SELF, std::move (l));
      }
#else
      static
      symbol_type
      make_SELF (const location_type& l)
      {
        return symbol_type (token::SELF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (location_type l)
      {
        return symbol_type (token::IF, std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const location_type& l)
      {
        return symbol_type (token::IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (location_type l)
      {
        return symbol_type (token::ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const location_type& l)
      {
        return symbol_type (token::ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SWITCH (location_type l)
      {
        return symbol_type (token::SWITCH, std::move (l));
      }
#else
      static
      symbol_type
      make_SWITCH (const location_type& l)
      {
        return symbol_type (token::SWITCH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE (location_type l)
      {
        return symbol_type (token::CASE, std::move (l));
      }
#else
      static
      symbol_type
      make_CASE (const location_type& l)
      {
        return symbol_type (token::CASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFAULT (location_type l)
      {
        return symbol_type (token::DEFAULT, std::move (l));
      }
#else
      static
      symbol_type
      make_DEFAULT (const location_type& l)
      {
        return symbol_type (token::DEFAULT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (location_type l)
      {
        return symbol_type (token::WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const location_type& l)
      {
        return symbol_type (token::WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO (location_type l)
      {
        return symbol_type (token::DO, std::move (l));
      }
#else
      static
      symbol_type
      make_DO (const location_type& l)
      {
        return symbol_type (token::DO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR (location_type l)
      {
        return symbol_type (token::FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_FOR (const location_type& l)
      {
        return symbol_type (token::FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTINUE (location_type l)
      {
        return symbol_type (token::CONTINUE, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTINUE (const location_type& l)
      {
        return symbol_type (token::CONTINUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BREAK (location_type l)
      {
        return symbol_type (token::BREAK, std::move (l));
      }
#else
      static
      symbol_type
      make_BREAK (const location_type& l)
      {
        return symbol_type (token::BREAK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (location_type l)
      {
        return symbol_type (token::RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_RETURN (const location_type& l)
      {
        return symbol_type (token::RETURN, l);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 354,     ///< Last index in yytable_.
      yynnts_ = 47,  ///< Number of nonterminal symbols.
      yyfinal_ = 29 ///< Termination state number.
    };


    // User arguments.
    void *scanner;
    yy::location& loc;
    class e2::ParserCtx& ctx;

  };

  inline
  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    34,    39,     2,
      65,    66,    32,    35,    70,    36,    71,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    64,
      37,    60,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,    41,    68,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    61,    62,    63
    };
    // Last valid token kind.
    const int code_max = 307;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
      case symbol_kind::S_namespace_body: // namespace_body
        value.copy< e2::Block * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        value.copy< e2::Expression * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        value.copy< e2::ExpressionList * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_extern_call: // extern_call
        value.copy< e2::ExternDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_definition: // function_definition
        value.copy< e2::FunctionDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
        value.copy< e2::Identifier * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_module: // import_module
        value.copy< e2::ImportModule * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        value.copy< e2::IterStatement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        value.copy< e2::LabledBlock * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method_call: // method_call
        value.copy< e2::MethodCall * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_namespace_definition: // namespace_definition
        value.copy< e2::NameSpace * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        value.copy< e2::Statement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_val: // unary_val
        value.copy< e2::UnaryOperator * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_union_definition: // union_definition
        value.copy< e2::UnionDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
      case symbol_kind::S_namespace_member: // namespace_member
        value.copy< e2::VariableStatement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.copy< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAMESPACE_ATTR: // NAMESPACE_ATTR
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_LOGICAL_AND: // LOGICAL_AND
      case symbol_kind::S_LOGICAL_OR: // LOGICAL_OR
      case symbol_kind::S_LOGICAL_NOT: // LOGICAL_NOT
      case symbol_kind::S_ASSIGN_MUL: // ASSIGN_MUL
      case symbol_kind::S_ASSIGN_DIV: // ASSIGN_DIV
      case symbol_kind::S_ASSIGN_MOD: // ASSIGN_MOD
      case symbol_kind::S_ASSIGN_ADD: // ASSIGN_ADD
      case symbol_kind::S_ASSIGN_SUB: // ASSIGN_SUB
      case symbol_kind::S_ASSIGN_LEFT: // ASSIGN_LEFT
      case symbol_kind::S_ASSIGN_RIGHT: // ASSIGN_RIGHT
      case symbol_kind::S_ASSIGN_AND: // ASSIGN_AND
      case symbol_kind::S_ASSIGN_XOR: // ASSIGN_XOR
      case symbol_kind::S_ASSIGN_OR: // ASSIGN_OR
      case symbol_kind::S_ARITH_LEFT: // ARITH_LEFT
      case symbol_kind::S_ARITH_RIGHT: // ARITH_RIGHT
      case symbol_kind::S_UNARY_INC: // UNARY_INC
      case symbol_kind::S_UNARY_DEC: // UNARY_DEC
      case symbol_kind::S_ASSIGN_EQ: // ASSIGN_EQ
      case symbol_kind::S_32_: // '*'
      case symbol_kind::S_33_: // '/'
      case symbol_kind::S_34_: // '%'
      case symbol_kind::S_35_: // '+'
      case symbol_kind::S_36_: // '-'
      case symbol_kind::S_37_: // '<'
      case symbol_kind::S_38_: // '>'
      case symbol_kind::S_39_: // '&'
      case symbol_kind::S_40_: // '^'
      case symbol_kind::S_41_: // '|'
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_assignment: // assignment
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.copy< std::int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
      case symbol_kind::S_namespace_body: // namespace_body
        value.move< e2::Block * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        value.move< e2::Expression * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        value.move< e2::ExpressionList * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_extern_call: // extern_call
        value.move< e2::ExternDeclaration * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_definition: // function_definition
        value.move< e2::FunctionDeclaration * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
        value.move< e2::Identifier * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_import_module: // import_module
        value.move< e2::ImportModule * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        value.move< e2::IterStatement * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        value.move< e2::LabledBlock * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_method_call: // method_call
        value.move< e2::MethodCall * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_namespace_definition: // namespace_definition
        value.move< e2::NameSpace * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        value.move< e2::Statement * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_unary_val: // unary_val
        value.move< e2::UnaryOperator * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_union_definition: // union_definition
        value.move< e2::UnionDeclaration * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
      case symbol_kind::S_namespace_member: // namespace_member
        value.move< e2::VariableStatement * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.move< float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NAMESPACE_ATTR: // NAMESPACE_ATTR
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_LOGICAL_AND: // LOGICAL_AND
      case symbol_kind::S_LOGICAL_OR: // LOGICAL_OR
      case symbol_kind::S_LOGICAL_NOT: // LOGICAL_NOT
      case symbol_kind::S_ASSIGN_MUL: // ASSIGN_MUL
      case symbol_kind::S_ASSIGN_DIV: // ASSIGN_DIV
      case symbol_kind::S_ASSIGN_MOD: // ASSIGN_MOD
      case symbol_kind::S_ASSIGN_ADD: // ASSIGN_ADD
      case symbol_kind::S_ASSIGN_SUB: // ASSIGN_SUB
      case symbol_kind::S_ASSIGN_LEFT: // ASSIGN_LEFT
      case symbol_kind::S_ASSIGN_RIGHT: // ASSIGN_RIGHT
      case symbol_kind::S_ASSIGN_AND: // ASSIGN_AND
      case symbol_kind::S_ASSIGN_XOR: // ASSIGN_XOR
      case symbol_kind::S_ASSIGN_OR: // ASSIGN_OR
      case symbol_kind::S_ARITH_LEFT: // ARITH_LEFT
      case symbol_kind::S_ARITH_RIGHT: // ARITH_RIGHT
      case symbol_kind::S_UNARY_INC: // UNARY_INC
      case symbol_kind::S_UNARY_DEC: // UNARY_DEC
      case symbol_kind::S_ASSIGN_EQ: // ASSIGN_EQ
      case symbol_kind::S_32_: // '*'
      case symbol_kind::S_33_: // '/'
      case symbol_kind::S_34_: // '%'
      case symbol_kind::S_35_: // '+'
      case symbol_kind::S_36_: // '-'
      case symbol_kind::S_37_: // '<'
      case symbol_kind::S_38_: // '>'
      case symbol_kind::S_39_: // '&'
      case symbol_kind::S_40_: // '^'
      case symbol_kind::S_41_: // '|'
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_assignment: // assignment
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< std::int64_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


} // yy
#line 3101 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.hpp"




#endif // !YY_YY_USERS_VYOUZHI_WORKSPACE_C_C_PLUG_ETOMC2LAN_E2_GENERATED_E2_BISON_HPP_INCLUDED
