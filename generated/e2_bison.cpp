// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "e2_bison.hpp"


// Unqualified %code blocks.
#line 51 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"


yy::Parser::symbol_type yylex(void* yyscanner,
                         yy::location& loc,
                         class e2::ParserCtx& ctx);

#line 53 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 145 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"

  /// Build a parser object.
  Parser::Parser (void *scanner_yyarg, yy::location& loc_yyarg, class e2::ParserCtx& ctx_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      loc (loc_yyarg),
      ctx (ctx_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
        value.YY_MOVE_OR_COPY< e2::Block * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        value.YY_MOVE_OR_COPY< e2::Expression * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        value.YY_MOVE_OR_COPY< e2::ExpressionList * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_extern_call: // extern_call
        value.YY_MOVE_OR_COPY< e2::ExternDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_definition: // function_definition
        value.YY_MOVE_OR_COPY< e2::FunctionDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier_list: // identifier_list
        value.YY_MOVE_OR_COPY< e2::Identifier * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_module: // import_module
        value.YY_MOVE_OR_COPY< e2::ImportModule * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        value.YY_MOVE_OR_COPY< e2::IterStatement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        value.YY_MOVE_OR_COPY< e2::LabledBlock * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method_call: // method_call
        value.YY_MOVE_OR_COPY< e2::MethodCall * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        value.YY_MOVE_OR_COPY< e2::Statement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_val: // unary_val
        value.YY_MOVE_OR_COPY< e2::UnaryOperator * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_union_definition: // union_definition
        value.YY_MOVE_OR_COPY< e2::UnionDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
        value.YY_MOVE_OR_COPY< e2::VariableStatement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

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
      case symbol_kind::S_30_: // '*'
      case symbol_kind::S_31_: // '/'
      case symbol_kind::S_32_: // '%'
      case symbol_kind::S_33_: // '+'
      case symbol_kind::S_34_: // '-'
      case symbol_kind::S_35_: // '<'
      case symbol_kind::S_36_: // '>'
      case symbol_kind::S_37_: // '&'
      case symbol_kind::S_38_: // '^'
      case symbol_kind::S_39_: // '|'
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.YY_MOVE_OR_COPY< std::int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
        value.move< e2::Block * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        value.move< e2::Expression * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        value.move< e2::ExpressionList * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_extern_call: // extern_call
        value.move< e2::ExternDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_definition: // function_definition
        value.move< e2::FunctionDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier_list: // identifier_list
        value.move< e2::Identifier * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_module: // import_module
        value.move< e2::ImportModule * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        value.move< e2::IterStatement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        value.move< e2::LabledBlock * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method_call: // method_call
        value.move< e2::MethodCall * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        value.move< e2::Statement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_val: // unary_val
        value.move< e2::UnaryOperator * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_union_definition: // union_definition
        value.move< e2::UnionDeclaration * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
        value.move< e2::VariableStatement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.move< float > (YY_MOVE (that.value));
        break;

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
      case symbol_kind::S_30_: // '*'
      case symbol_kind::S_31_: // '/'
      case symbol_kind::S_32_: // '%'
      case symbol_kind::S_33_: // '+'
      case symbol_kind::S_34_: // '-'
      case symbol_kind::S_35_: // '<'
      case symbol_kind::S_36_: // '>'
      case symbol_kind::S_37_: // '&'
      case symbol_kind::S_38_: // '^'
      case symbol_kind::S_39_: // '|'
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_assignment: // assignment
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< std::int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
        value.copy< e2::Block * > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        value.copy< e2::Expression * > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        value.copy< e2::ExpressionList * > (that.value);
        break;

      case symbol_kind::S_extern_call: // extern_call
        value.copy< e2::ExternDeclaration * > (that.value);
        break;

      case symbol_kind::S_function_definition: // function_definition
        value.copy< e2::FunctionDeclaration * > (that.value);
        break;

      case symbol_kind::S_identifier_list: // identifier_list
        value.copy< e2::Identifier * > (that.value);
        break;

      case symbol_kind::S_import_module: // import_module
        value.copy< e2::ImportModule * > (that.value);
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        value.copy< e2::IterStatement * > (that.value);
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        value.copy< e2::LabledBlock * > (that.value);
        break;

      case symbol_kind::S_method_call: // method_call
        value.copy< e2::MethodCall * > (that.value);
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        value.copy< e2::Statement * > (that.value);
        break;

      case symbol_kind::S_unary_val: // unary_val
        value.copy< e2::UnaryOperator * > (that.value);
        break;

      case symbol_kind::S_union_definition: // union_definition
        value.copy< e2::UnionDeclaration * > (that.value);
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
        value.copy< e2::VariableStatement * > (that.value);
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.copy< float > (that.value);
        break;

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
      case symbol_kind::S_30_: // '*'
      case symbol_kind::S_31_: // '/'
      case symbol_kind::S_32_: // '%'
      case symbol_kind::S_33_: // '+'
      case symbol_kind::S_34_: // '-'
      case symbol_kind::S_35_: // '<'
      case symbol_kind::S_36_: // '>'
      case symbol_kind::S_37_: // '&'
      case symbol_kind::S_38_: // '^'
      case symbol_kind::S_39_: // '|'
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_assignment: // assignment
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.copy< std::int64_t > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
        value.move< e2::Block * > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        value.move< e2::Expression * > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        value.move< e2::ExpressionList * > (that.value);
        break;

      case symbol_kind::S_extern_call: // extern_call
        value.move< e2::ExternDeclaration * > (that.value);
        break;

      case symbol_kind::S_function_definition: // function_definition
        value.move< e2::FunctionDeclaration * > (that.value);
        break;

      case symbol_kind::S_identifier_list: // identifier_list
        value.move< e2::Identifier * > (that.value);
        break;

      case symbol_kind::S_import_module: // import_module
        value.move< e2::ImportModule * > (that.value);
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        value.move< e2::IterStatement * > (that.value);
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        value.move< e2::LabledBlock * > (that.value);
        break;

      case symbol_kind::S_method_call: // method_call
        value.move< e2::MethodCall * > (that.value);
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        value.move< e2::Statement * > (that.value);
        break;

      case symbol_kind::S_unary_val: // unary_val
        value.move< e2::UnaryOperator * > (that.value);
        break;

      case symbol_kind::S_union_definition: // union_definition
        value.move< e2::UnionDeclaration * > (that.value);
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
        value.move< e2::VariableStatement * > (that.value);
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.move< float > (that.value);
        break;

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
      case symbol_kind::S_30_: // '*'
      case symbol_kind::S_31_: // '/'
      case symbol_kind::S_32_: // '%'
      case symbol_kind::S_33_: // '+'
      case symbol_kind::S_34_: // '-'
      case symbol_kind::S_35_: // '<'
      case symbol_kind::S_36_: // '>'
      case symbol_kind::S_37_: // '&'
      case symbol_kind::S_38_: // '^'
      case symbol_kind::S_39_: // '|'
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_assignment: // assignment
        value.move< int > (that.value);
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< std::int64_t > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, loc, ctx));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_compound_statement: // compound_statement
      case symbol_kind::S_compound_block: // compound_block
      case symbol_kind::S_union_list: // union_list
        yylhs.value.emplace< e2::Block * > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_shift_expression: // shift_expression
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_expression_rvalue: // expression_rvalue
      case symbol_kind::S_primary_rvalue: // primary_rvalue
        yylhs.value.emplace< e2::Expression * > ();
        break;

      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_function_parameter: // function_parameter
        yylhs.value.emplace< e2::ExpressionList * > ();
        break;

      case symbol_kind::S_extern_call: // extern_call
        yylhs.value.emplace< e2::ExternDeclaration * > ();
        break;

      case symbol_kind::S_function_definition: // function_definition
        yylhs.value.emplace< e2::FunctionDeclaration * > ();
        break;

      case symbol_kind::S_identifier_list: // identifier_list
        yylhs.value.emplace< e2::Identifier * > ();
        break;

      case symbol_kind::S_import_module: // import_module
        yylhs.value.emplace< e2::ImportModule * > ();
        break;

      case symbol_kind::S_iteration_statement: // iteration_statement
        yylhs.value.emplace< e2::IterStatement * > ();
        break;

      case symbol_kind::S_labled_if: // labled_if
      case symbol_kind::S_labeled_switch: // labeled_switch
        yylhs.value.emplace< e2::LabledBlock * > ();
        break;

      case symbol_kind::S_method_call: // method_call
        yylhs.value.emplace< e2::MethodCall * > ();
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_for_range: // for_range
      case symbol_kind::S_jump_statement: // jump_statement
        yylhs.value.emplace< e2::Statement * > ();
        break;

      case symbol_kind::S_unary_val: // unary_val
        yylhs.value.emplace< e2::UnaryOperator * > ();
        break;

      case symbol_kind::S_union_definition: // union_definition
        yylhs.value.emplace< e2::UnionDeclaration * > ();
        break;

      case symbol_kind::S_variable_val: // variable_val
      case symbol_kind::S_union_statement: // union_statement
        yylhs.value.emplace< e2::VariableStatement * > ();
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        yylhs.value.emplace< float > ();
        break;

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
      case symbol_kind::S_30_: // '*'
      case symbol_kind::S_31_: // '/'
      case symbol_kind::S_32_: // '%'
      case symbol_kind::S_33_: // '+'
      case symbol_kind::S_34_: // '-'
      case symbol_kind::S_35_: // '<'
      case symbol_kind::S_36_: // '>'
      case symbol_kind::S_37_: // '&'
      case symbol_kind::S_38_: // '^'
      case symbol_kind::S_39_: // '|'
      case symbol_kind::S_add_arithmetic: // add_arithmetic
      case symbol_kind::S_mul_arithmetic: // mul_arithmetic
      case symbol_kind::S_shift_arithmetic: // shift_arithmetic
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_logical: // logical
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        yylhs.value.emplace< std::int64_t > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // translation_unit: block
#line 137 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1181 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 3: // translation_unit: import_module
#line 138 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                    { if(yystack_[0].value.as < e2::ImportModule * > ()!=nullptr) ctx.RootBlock()->push_back(yystack_[0].value.as < e2::ImportModule * > ()); }
#line 1187 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 4: // translation_unit: function_definition
#line 139 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                           { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::FunctionDeclaration * > ());}
#line 1193 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 5: // translation_unit: union_definition
#line 140 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                           { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::UnionDeclaration * > ());}
#line 1199 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 6: // translation_unit: translation_unit block
#line 141 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                              { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1205 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 7: // translation_unit: translation_unit function_definition
#line 142 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                            { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::FunctionDeclaration * > ());}
#line 1211 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 8: // translation_unit: translation_unit union_definition
#line 143 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                            { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::UnionDeclaration * > ());}
#line 1217 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 9: // translation_unit: translation_unit import_module
#line 144 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                     { if(yystack_[0].value.as < e2::ImportModule * > ()!=nullptr)ctx.RootBlock()->push_back(yystack_[0].value.as < e2::ImportModule * > ()); }
#line 1223 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 10: // import_module: IMPORT IMPORT_LITERAL
#line 148 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                               {yylhs.value.as < e2::ImportModule * > () = MALLOC( e2::ImportModule,yystack_[0].value.as < std::string > ());}
#line 1229 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 11: // block: variable_val ';'
#line 153 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                        {yylhs.value.as < e2::Statement * > () = yystack_[1].value.as < e2::VariableStatement * > (); }
#line 1235 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 12: // block: method_call ';'
#line 154 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                        {yylhs.value.as < e2::Statement * > () = yystack_[1].value.as < e2::MethodCall * > (); }
#line 1241 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 13: // block: extern_call ';'
#line 155 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                       {yylhs.value.as < e2::Statement * > () = yystack_[1].value.as < e2::ExternDeclaration * > ();}
#line 1247 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 14: // block: unary_val ';'
#line 156 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::Statement * > () = yystack_[1].value.as < e2::UnaryOperator * > ();}
#line 1253 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 15: // variable_val: identifier_list assignment expression
#line 161 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                            {
            yylhs.value.as < e2::VariableStatement * > () = MALLOC( e2::VariableStatement,yystack_[2].value.as < e2::Identifier * > (),yystack_[1].value.as < int > (), yystack_[0].value.as < e2::Expression * > (),code_line, ctx.path());
            }
#line 1261 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 16: // unary_val: identifier_list unary
#line 167 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                            {
        yylhs.value.as < e2::UnaryOperator * > () = MALLOC(e2::UnaryOperator,yystack_[1].value.as < e2::Identifier * > (),yystack_[0].value.as < int > (),code_line, ctx.path()); 
         }
#line 1269 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 17: // expression: additive_expression
#line 174 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                          {yylhs.value.as < e2::Expression * > ()=yystack_[0].value.as < e2::Expression * > ();}
#line 1275 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 18: // additive_expression: multiplicative_expression
#line 178 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                    {yylhs.value.as < e2::Expression * > ()=yystack_[0].value.as < e2::Expression * > ();}
#line 1281 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 19: // additive_expression: additive_expression add_arithmetic multiplicative_expression
#line 179 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                                       {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::BinaryOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path());
            }
#line 1289 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 20: // add_arithmetic: '+'
#line 187 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='+';}
#line 1295 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 21: // add_arithmetic: '-'
#line 188 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='-';}
#line 1301 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 22: // multiplicative_expression: shift_expression
#line 193 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                           {yylhs.value.as < e2::Expression * > ()=yystack_[0].value.as < e2::Expression * > ();}
#line 1307 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 23: // multiplicative_expression: multiplicative_expression mul_arithmetic shift_expression
#line 194 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                                    {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::BinaryOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path());
         }
#line 1315 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 24: // mul_arithmetic: '*'
#line 202 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='*';}
#line 1321 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 25: // mul_arithmetic: '/'
#line 203 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='/';}
#line 1327 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 26: // mul_arithmetic: '%'
#line 204 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='%';}
#line 1333 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 27: // shift_expression: conditional
#line 208 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < e2::Expression * > () = yystack_[0].value.as < e2::Expression * > ();   }
#line 1339 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 28: // shift_expression: shift_expression shift_arithmetic conditional
#line 209 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                    {
        yylhs.value.as < e2::Expression * > () = MALLOC(e2::BinaryOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path());        
        }
#line 1347 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 29: // shift_arithmetic: ARITH_LEFT
#line 216 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 {yylhs.value.as < int > ()= token::ARITH_LEFT;}
#line 1353 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 30: // shift_arithmetic: ARITH_RIGHT
#line 217 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < int > ()=token::ARITH_RIGHT;}
#line 1359 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 31: // shift_arithmetic: '&'
#line 218 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='&';}
#line 1365 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 32: // shift_arithmetic: '^'
#line 219 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='^';}
#line 1371 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 33: // shift_arithmetic: '|'
#line 220 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='|';}
#line 1377 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 34: // conditional: expression_rvalue
#line 226 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                         {yylhs.value.as < e2::Expression * > () = yystack_[0].value.as < e2::Expression * > (); }
#line 1383 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 35: // conditional: expression_rvalue comparison expression_rvalue
#line 227 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                     {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::CompOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path() ); 
         }
#line 1391 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 36: // conditional: expression_rvalue logical expression_rvalue
#line 230 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                  {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::BinaryOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path()); 
         }
#line 1399 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 37: // conditional: method_call
#line 233 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < e2::Expression * > ()=yystack_[0].value.as < e2::MethodCall * > ();}
#line 1405 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 38: // expression_rvalue: primary_rvalue
#line 238 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::Expression * > () = yystack_[0].value.as < e2::Expression * > ();}
#line 1411 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 39: // expression_rvalue: '(' expression ')'
#line 239 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                          {yylhs.value.as < e2::Expression * > () = yystack_[1].value.as < e2::Expression * > ();}
#line 1417 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 40: // comparison: OP_LE
#line 244 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
            {yylhs.value.as < int > () = token::OP_LE;}
#line 1423 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 41: // comparison: OP_GE
#line 245 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
            {yylhs.value.as < int > () = token::OP_GE;}
#line 1429 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 42: // comparison: OP_EQ
#line 246 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
            {yylhs.value.as < int > () = token::OP_EQ;}
#line 1435 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 43: // comparison: OP_NE
#line 247 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
            {yylhs.value.as < int > () = token::OP_NE;}
#line 1441 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 44: // comparison: '<'
#line 248 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='<';}
#line 1447 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 45: // comparison: '>'
#line 249 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='>';}
#line 1453 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 46: // logical: LOGICAL_NOT
#line 254 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < int > () = token::LOGICAL_NOT;}
#line 1459 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 47: // logical: LOGICAL_AND
#line 255 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < int > () = token::LOGICAL_AND;}
#line 1465 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 48: // logical: LOGICAL_OR
#line 256 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 {yylhs.value.as < int > () = token::LOGICAL_OR;}
#line 1471 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 49: // unary: UNARY_INC
#line 261 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                {yylhs.value.as < int > ()= token::UNARY_INC;}
#line 1477 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 50: // unary: UNARY_DEC
#line 262 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                {yylhs.value.as < int > ()= token::UNARY_DEC;}
#line 1483 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 51: // assignment: ASSIGN_EQ
#line 267 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_EQ;}
#line 1489 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 52: // assignment: ASSIGN_MUL
#line 268 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_MUL;}
#line 1495 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 53: // assignment: ASSIGN_DIV
#line 269 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_DIV;}
#line 1501 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 54: // assignment: ASSIGN_MOD
#line 270 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_MOD;}
#line 1507 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 55: // assignment: ASSIGN_ADD
#line 271 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_ADD;}
#line 1513 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 56: // assignment: ASSIGN_SUB
#line 272 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_SUB;}
#line 1519 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 57: // assignment: ASSIGN_LEFT
#line 273 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_LEFT;}
#line 1525 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 58: // assignment: ASSIGN_RIGHT
#line 274 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_RIGHT;}
#line 1531 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 59: // assignment: ASSIGN_AND
#line 275 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_AND;}
#line 1537 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 60: // assignment: ASSIGN_XOR
#line 276 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_XOR;}
#line 1543 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 61: // assignment: ASSIGN_OR
#line 277 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_OR;}
#line 1549 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 62: // compound_statement: '{' '}'
#line 281 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < e2::Block * > () = nullptr;}
#line 1555 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 63: // compound_statement: '{' compound_block '}'
#line 282 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                 {yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > ();}
#line 1561 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 64: // compound_block: block
#line 287 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "decl_vari", code_line, ctx.path() );yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1567 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 65: // compound_block: statement
#line 288 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "decl_statement", code_line, ctx.path() ); yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1573 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 66: // compound_block: compound_block block
#line 289 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > (); yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1579 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 67: // compound_block: compound_block statement
#line 290 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > (); yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1585 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 68: // statement: selection_statement
#line 295 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                              {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::Statement * > ();}
#line 1591 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 69: // statement: iteration_statement
#line 296 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                              {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::IterStatement * > ();}
#line 1597 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 70: // statement: jump_statement
#line 297 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                         {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::Statement * > ();}
#line 1603 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 71: // labled_if: compound_statement
#line 302 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::LabledBlock * > () = MALLOC(e2::LabledBlock, "labled_if", code_line, ctx.path()); 
            yylhs.value.as < e2::LabledBlock * > ()->push(yystack_[0].value.as < e2::Block * > (), e2::Selection::_then);

        }
#line 1613 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 72: // labled_if: compound_statement ELSE compound_statement
#line 308 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {  

            yylhs.value.as < e2::LabledBlock * > () = MALLOC(e2::LabledBlock,"labled_if", code_line, ctx.path()); 
            yylhs.value.as < e2::LabledBlock * > ()->push(yystack_[2].value.as < e2::Block * > (), e2::Selection::_then);

            yylhs.value.as < e2::LabledBlock * > ()->push(yystack_[0].value.as < e2::Block * > (), e2::Selection::_else);
        }
#line 1625 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 73: // labeled_switch: CASE primary_rvalue ':' compound_block
#line 319 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::LabledBlock * > () = MALLOC(e2::LabledBlock, "labeled_switch", code_line, ctx.path());
            yylhs.value.as < e2::LabledBlock * > ()->push(yystack_[2].value.as < e2::Expression * > (),yystack_[0].value.as < e2::Block * > (), e2::Selection::_case) ;
        }
#line 1634 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 74: // labeled_switch: labeled_switch CASE primary_rvalue ':' compound_block
#line 324 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        { 
            yylhs.value.as < e2::LabledBlock * > () = yystack_[4].value.as < e2::LabledBlock * > ();  
            yystack_[4].value.as < e2::LabledBlock * > ()->push(yystack_[2].value.as < e2::Expression * > (),yystack_[0].value.as < e2::Block * > (), e2::Selection::_case) ;
            
        }
#line 1644 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 75: // labeled_switch: labeled_switch DEFAULT ':' compound_block
#line 330 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        { 
            yylhs.value.as < e2::LabledBlock * > () = yystack_[3].value.as < e2::LabledBlock * > ();
            yystack_[3].value.as < e2::LabledBlock * > ()->push(yystack_[0].value.as < e2::Block * > (),e2::Selection::_default);
        }
#line 1653 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 76: // selection_statement: IF '(' conditional ')' labled_if
#line 338 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Statement * > () = MALLOC(e2::IFStatement, yystack_[2].value.as < e2::Expression * > (),yystack_[0].value.as < e2::LabledBlock * > (), code_line, ctx.path());
        }
#line 1661 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 77: // selection_statement: SWITCH '(' conditional ')' '{' labeled_switch '}'
#line 343 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Statement * > () = MALLOC(e2::SwitchStatement, yystack_[4].value.as < e2::Expression * > (),yystack_[1].value.as < e2::LabledBlock * > ());
        }
#line 1669 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 78: // for_range: unary_val
#line 349 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::UnaryOperator * > ();}
#line 1675 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 79: // for_range: variable_val
#line 350 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::VariableStatement * > ();}
#line 1681 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 80: // iteration_statement: WHILE '(' conditional ')' compound_statement
#line 355 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {   
            yylhs.value.as < e2::IterStatement * > () = MALLOC(e2::IterStatement, yystack_[2].value.as < e2::Expression * > (),yystack_[0].value.as < e2::Block * > (),e2::IterType::_while);
        }
#line 1689 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 81: // iteration_statement: DO compound_statement WHILE '(' conditional ')' ';'
#line 359 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::IterStatement * > () = MALLOC(e2::IterStatement,yystack_[2].value.as < e2::Expression * > (),yystack_[5].value.as < e2::Block * > (),e2::IterType::_do);
        }
#line 1697 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 82: // iteration_statement: FOR '(' variable_val ';' conditional ';' ')' compound_statement
#line 363 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::IterStatement * > () = MALLOC(e2::IterStatement,yystack_[5].value.as < e2::VariableStatement * > (),yystack_[3].value.as < e2::Expression * > (),yystack_[0].value.as < e2::Block * > (),e2::IterType::_for);
        }
#line 1705 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 83: // iteration_statement: FOR '(' variable_val ';' conditional ';' for_range ')' compound_statement
#line 367 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::IterStatement * > () = MALLOC(e2::IterStatement,yystack_[6].value.as < e2::VariableStatement * > (),yystack_[4].value.as < e2::Expression * > (),yystack_[2].value.as < e2::Statement * > (),yystack_[0].value.as < e2::Block * > (),e2::IterType::_forfull);
        }
#line 1713 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 84: // jump_statement: CONTINUE ';'
#line 374 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                 {yylhs.value.as < e2::Statement * > () = nullptr;}
#line 1719 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 85: // jump_statement: BREAK ';'
#line 375 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Statement * > () = MALLOC(e2::BreakStatement) ;}
#line 1725 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 86: // jump_statement: RETURN ';'
#line 376 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 {yylhs.value.as < e2::Statement * > () = MALLOC(e2::ReturnStatement, code_line, ctx.path());}
#line 1731 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 87: // jump_statement: RETURN primary_rvalue ';'
#line 377 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                    {yylhs.value.as < e2::Statement * > () = MALLOC(e2::ReturnStatement,yystack_[1].value.as < e2::Expression * > (), code_line, ctx.path());}
#line 1737 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 88: // parameter_list: primary_rvalue
#line 382 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::ExpressionList * > () = MALLOC(e2::ExpressionList);yylhs.value.as < e2::ExpressionList * > ()->push_back(yystack_[0].value.as < e2::Expression * > ());}
#line 1743 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 89: // parameter_list: parameter_list ',' primary_rvalue
#line 383 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                        {yylhs.value.as < e2::ExpressionList * > ()=yystack_[2].value.as < e2::ExpressionList * > ();  yystack_[2].value.as < e2::ExpressionList * > ()->push_back(yystack_[0].value.as < e2::Expression * > ());}
#line 1749 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 90: // function_parameter: '(' ')'
#line 387 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
              {yylhs.value.as < e2::ExpressionList * > () = nullptr;}
#line 1755 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 91: // function_parameter: '(' parameter_list ')'
#line 388 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                             {yylhs.value.as < e2::ExpressionList * > () = yystack_[1].value.as < e2::ExpressionList * > ();}
#line 1761 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 92: // function_definition: FUNCTION IDENTIFIER function_parameter compound_statement
#line 392 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                                {yylhs.value.as < e2::FunctionDeclaration * > () = MALLOC(e2::FunctionDeclaration,yystack_[2].value.as < std::string > (), yystack_[1].value.as < e2::ExpressionList * > (), yystack_[0].value.as < e2::Block * > ());}
#line 1767 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 93: // method_call: IDENTIFIER function_parameter
#line 397 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                   {
            yylhs.value.as < e2::MethodCall * > () = MALLOC(e2::MethodCall, yystack_[1].value.as < std::string > (), yystack_[0].value.as < e2::ExpressionList * > (), code_line, ctx.path());
        }
#line 1775 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 94: // extern_call: EXTERN IDENTIFIER IDENTIFIER '(' IDENTIFIER primary_rvalue ')'
#line 403 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                                      { 
        e2::ExpressionList *el = MALLOC(e2::ExpressionList); 
         el->push_back(yystack_[1].value.as < e2::Expression * > ()); 
         yylhs.value.as < e2::ExternDeclaration * > () = MALLOC(e2::ExternDeclaration,yystack_[4].value.as < std::string > (),el);}
#line 1784 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 95: // union_statement: ';'
#line 410 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < e2::VariableStatement * > () = nullptr; }
#line 1790 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 96: // union_statement: variable_val ';'
#line 411 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                       {yylhs.value.as < e2::VariableStatement * > () = yystack_[1].value.as < e2::VariableStatement * > ();}
#line 1796 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 97: // union_list: union_statement
#line 415 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                    {yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "union_list", code_line, ctx.path() ); yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::VariableStatement * > ());}
#line 1802 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 98: // union_list: union_list union_statement
#line 416 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                    {yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > (); yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::VariableStatement * > ());}
#line 1808 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 99: // union_list: union_definition
#line 417 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                    {yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "union_def", code_line, ctx.path() ); yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::UnionDeclaration * > ());}
#line 1814 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 100: // union_list: union_list union_definition
#line 418 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                    {yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > (); yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::UnionDeclaration * > ());}
#line 1820 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 101: // union_definition: UNION IDENTIFIER '{' union_list '}'
#line 422 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                          {  yylhs.value.as < e2::UnionDeclaration * > () = MALLOC(e2::UnionDeclaration,yystack_[3].value.as < std::string > (),yystack_[1].value.as < e2::Block * > ());}
#line 1826 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 102: // primary_rvalue: identifier_list
#line 427 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                      {yylhs.value.as < e2::Expression * > () = yystack_[0].value.as < e2::Identifier * > ();}
#line 1832 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 103: // primary_rvalue: CONSTANT
#line 428 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                {yylhs.value.as < e2::Expression * > () = MALLOC(e2::Number,yystack_[0].value.as < std::int64_t > ());}
#line 1838 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 104: // primary_rvalue: '-' CONSTANT
#line 429 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                    {yylhs.value.as < e2::Expression * > () = MALLOC(e2::Number,yystack_[0].value.as < std::int64_t > (), true); }
#line 1844 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 105: // primary_rvalue: FCONSTANT
#line 430 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 {yylhs.value.as < e2::Expression * > () = MALLOC(e2::Number,yystack_[0].value.as < float > ());}
#line 1850 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 106: // primary_rvalue: '-' FCONSTANT
#line 431 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::Expression * > () = MALLOC(e2::Number,yystack_[0].value.as < float > (), true);}
#line 1856 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 107: // primary_rvalue: STRING_LITERAL
#line 432 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::Expression * > () = MALLOC(e2::StrObj, yystack_[0].value.as < std::string > (), code_line, ctx.path()); }
#line 1862 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 108: // identifier_list: IDENTIFIER
#line 436 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < e2::Identifier * > () = MALLOC(e2::Identifier, yystack_[0].value.as < std::string > (), e2::IDType::_normal);}
#line 1868 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 109: // identifier_list: identifier_list '.' IDENTIFIER
#line 437 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                     {yylhs.value.as < e2::Identifier * > ()=yystack_[2].value.as < e2::Identifier * > ();  yystack_[2].value.as < e2::Identifier * > ()->push_back(yystack_[0].value.as < std::string > ());yystack_[2].value.as < e2::Identifier * > ()->idType(e2::IDType::_global);}
#line 1874 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;


#line 1878 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short Parser::yypact_ninf_ = -147;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      48,   -46,    15,    23,    32,    36,   133,  -147,  -147,   -22,
      -6,  -147,    18,    22,  -147,   178,    21,  -147,    25,   -46,
      80,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,    89,  -147,    39,  -147,  -147,  -147,
    -147,    14,  -147,   -48,  -147,    31,     9,    41,    51,  -147,
      39,  -147,     5,   118,   115,  -147,   200,  -147,  -147,  -147,
    -147,  -147,    26,  -147,    42,  -147,     7,  -147,   202,    56,
    -147,   110,    53,  -147,  -147,    39,  -147,  -147,  -147,    39,
    -147,  -147,  -147,  -147,  -147,    39,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,   124,   124,  -147,  -147,  -147,
    -147,  -147,    58,    60,    61,    41,    63,    65,    67,   157,
    -147,  -147,    93,  -147,  -147,  -147,  -147,    26,  -147,   118,
     115,  -147,  -147,  -147,    39,    39,    39,    83,   126,  -147,
    -147,  -147,    75,  -147,  -147,  -147,    94,    98,   101,   104,
     106,   108,  -147,  -147,    41,   109,    41,    39,    39,   123,
    -147,   125,  -147,   116,   111,    41,    26,   -32,   119,     4,
    -147,   117,    26,   139,  -147,  -147,    41,  -147,  -147,   122,
     201,   151,   201,  -147,    41,   201,   201,   201,  -147,   201
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,   108,     0,     0,     0,     0,     0,     3,     2,     0,
       0,     4,     0,     0,     5,     0,     0,    93,     0,     0,
       0,    10,     1,     9,     6,     7,     8,    11,    14,    12,
      13,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    49,    50,    51,     0,    16,     0,   108,   107,   103,
     105,     0,    90,     0,    88,   102,     0,     0,     0,   109,
       0,    15,    17,    18,    22,    27,    34,    37,    38,   104,
     106,    91,     0,    95,     0,    97,     0,    99,     0,     0,
      92,     0,     0,    20,    21,     0,    24,    25,    26,     0,
      29,    30,    31,    32,    33,     0,    40,    41,    42,    43,
      47,    48,    46,    44,    45,     0,     0,    89,    96,   101,
      98,   100,     0,     0,     0,     0,     0,     0,     0,     0,
      62,    64,     0,    65,    68,    69,    70,     0,    39,    19,
      23,    28,    35,    36,     0,     0,     0,     0,     0,    84,
      85,    86,     0,    63,    66,    67,     0,     0,     0,     0,
       0,     0,    87,    94,     0,     0,     0,     0,     0,    71,
      76,     0,    80,     0,     0,     0,     0,     0,     0,     0,
      72,     0,     0,     0,    77,    81,     0,    79,    78,     0,
       0,     0,     0,    82,     0,    73,     0,    75,    83,    74
  };

  const short
  Parser::yypgoto_[] =
  {
    -147,  -147,   173,     3,   -54,    59,   167,  -147,  -147,   144,
    -147,   141,  -147,   -72,   -31,  -147,  -147,  -147,  -147,  -104,
    -146,  -118,  -147,  -147,  -147,  -147,  -147,  -147,  -147,   213,
     227,   -41,  -147,   158,  -147,     2,   -15,     0
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,     6,     7,   121,     9,    10,    61,    62,    85,    63,
      89,    64,    95,    65,    66,   105,   106,    45,    46,    80,
     122,   123,   160,   167,   124,   179,   125,   126,    53,    17,
      11,    12,    13,    75,    76,    14,    68,    55
  };

  const unsigned char
  Parser::yytable_[] =
  {
      15,    54,    74,     8,   145,    67,    15,    47,    26,    24,
      47,   137,    47,    71,    16,   172,   173,    72,    18,    67,
      69,    70,    74,   131,    47,    48,    19,    49,    50,    47,
      48,   174,    49,    50,   185,    20,   187,    27,    83,    84,
     189,    21,     1,    48,    67,    49,    50,     2,    67,     2,
     159,     1,   162,    28,    67,    51,    78,   107,    77,     1,
      51,   170,   147,   148,   149,   176,    73,   145,    73,   145,
     109,   145,   183,    51,   132,   133,    78,    29,   111,    15,
     188,    30,    52,    58,   151,   163,   164,    56,     2,     3,
       4,     5,    59,    67,    67,    67,     1,    44,     4,    60,
     112,   108,   113,    79,   142,   114,   115,   116,   117,   118,
     119,    81,   146,   127,   128,   177,    67,    67,   134,   120,
     135,   136,    15,   138,   139,   144,   140,    47,    48,    47,
      49,    50,   150,    22,   152,     4,     1,   112,    78,   113,
      90,    91,   114,   115,   116,   117,   118,   119,    86,    87,
      88,   171,    92,    93,    94,   153,   143,   181,    51,   154,
      47,    48,   155,    49,    50,   156,   157,   158,   165,    15,
     169,   161,   166,     2,     3,     4,     5,   168,   175,    23,
      15,   180,    15,   184,    60,    15,    15,    15,   144,    15,
     144,    51,   144,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,   182,     1,    41,    42,    43,    96,    97,
      98,    99,   100,   101,   102,   186,   141,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    82,   178,   129,
     130,    43,    57,    25,   110,   103,   104,     0,     0,     0,
       0,     0,     0,     4,    44,   112,     0,   113,     0,     0,
     114,   115,   116,   117,   118,   119,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    44
  };

  const short
  Parser::yycheck_[] =
  {
       0,    16,    56,     0,   122,    46,     6,     3,     6,     6,
       3,   115,     3,    61,    60,    47,    48,    65,     3,    60,
       6,     7,    76,    95,     3,     4,     3,     6,     7,     3,
       4,    63,     6,     7,   180,     3,   182,    59,    33,    34,
     186,     5,     3,     4,    85,     6,     7,    40,    89,    40,
     154,     3,   156,    59,    95,    34,    56,    72,    56,     3,
      34,   165,   134,   135,   136,    61,    59,   185,    59,   187,
      63,   189,   176,    34,   105,   106,    76,    59,    76,    79,
     184,    59,    61,     3,   138,   157,   158,    62,    40,    41,
      42,    43,     3,   134,   135,   136,     3,    66,    42,    60,
      44,    59,    46,    62,   119,    49,    50,    51,    52,    53,
      54,    60,   127,     3,    61,   169,   157,   158,    60,    63,
      60,    60,   122,    60,    59,   122,    59,     3,     4,     3,
       6,     7,    49,     0,    59,    42,     3,    44,   138,    46,
      25,    26,    49,    50,    51,    52,    53,    54,    30,    31,
      32,   166,    37,    38,    39,    61,    63,   172,    34,    61,
       3,     4,    61,     6,     7,    61,    60,    59,    45,   169,
      59,    62,    47,    40,    41,    42,    43,    61,    59,     6,
     180,    64,   182,    61,    60,   185,   186,   187,   185,   189,
     187,    34,   189,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    64,     3,    27,    28,    29,     8,     9,
      10,    11,    12,    13,    14,    64,    59,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    60,   169,    85,
      89,    29,    19,     6,    76,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    66,    44,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,    40,    41,    42,    43,    68,    69,    70,    71,
      72,    97,    98,    99,   102,   104,    60,    96,     3,     3,
       3,     5,     0,    69,    70,    97,   102,    59,    59,    59,
      59,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    27,    28,    29,    66,    84,    85,     3,     4,     6,
       7,    34,    61,    95,   103,   104,    62,    96,     3,     3,
      60,    73,    74,    76,    78,    80,    81,    98,   103,     6,
       7,    61,    65,    59,    71,   100,   101,   102,   104,    62,
      86,    60,    73,    33,    34,    75,    30,    31,    32,    77,
      25,    26,    37,    38,    39,    79,     8,     9,    10,    11,
      12,    13,    14,    35,    36,    82,    83,   103,    59,    63,
     100,   102,    44,    46,    49,    50,    51,    52,    53,    54,
      63,    70,    87,    88,    91,    93,    94,     3,    61,    76,
      78,    80,    81,    81,    60,    60,    60,    86,    60,    59,
      59,    59,   103,    63,    70,    88,   103,    80,    80,    80,
      49,    71,    59,    61,    61,    61,    61,    60,    59,    86,
      89,    62,    86,    80,    80,    45,    47,    90,    61,    59,
      86,   103,    47,    48,    63,    59,    61,    71,    72,    92,
      64,   103,    64,    86,    61,    87,    64,    87,    86,    87
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    67,    68,    68,    68,    68,    68,    68,    68,    68,
      69,    70,    70,    70,    70,    71,    72,    73,    74,    74,
      75,    75,    76,    76,    77,    77,    77,    78,    78,    79,
      79,    79,    79,    79,    80,    80,    80,    80,    81,    81,
      82,    82,    82,    82,    82,    82,    83,    83,    83,    84,
      84,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    86,    86,    87,    87,    87,    87,    88,    88,
      88,    89,    89,    90,    90,    90,    91,    91,    92,    92,
      93,    93,    93,    93,    94,    94,    94,    94,    95,    95,
      96,    96,    97,    98,    99,   100,   100,   101,   101,   101,
     101,   102,   103,   103,   103,   103,   103,   103,   104,   104
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     2,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     1,     1,     2,     2,     1,     1,
       1,     1,     3,     4,     5,     4,     5,     7,     1,     1,
       5,     7,     8,     9,     2,     2,     2,     3,     1,     3,
       2,     3,     4,     2,     7,     1,     2,     1,     2,     1,
       2,     5,     1,     1,     2,     1,     2,     1,     1,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "END", "error", "\"invalid token\"", "IDENTIFIER", "STRING_LITERAL",
  "IMPORT_LITERAL", "CONSTANT", "FCONSTANT", "OP_LE", "OP_GE", "OP_EQ",
  "OP_NE", "LOGICAL_AND", "LOGICAL_OR", "LOGICAL_NOT", "ASSIGN_MUL",
  "ASSIGN_DIV", "ASSIGN_MOD", "ASSIGN_ADD", "ASSIGN_SUB", "ASSIGN_LEFT",
  "ASSIGN_RIGHT", "ASSIGN_AND", "ASSIGN_XOR", "ASSIGN_OR", "ARITH_LEFT",
  "ARITH_RIGHT", "UNARY_INC", "UNARY_DEC", "ASSIGN_EQ", "'*'", "'/'",
  "'%'", "'+'", "'-'", "'<'", "'>'", "'&'", "'^'", "'|'", "UNION",
  "FUNCTION", "EXTERN", "IMPORT", "IF", "ELSE", "SWITCH", "CASE",
  "DEFAULT", "WHILE", "DO", "FOR", "CONTINUE", "BREAK", "RETURN", "'='",
  "\"!=\"", "\"<=\"", "\">=\"", "';'", "'('", "')'", "'{'", "'}'", "':'",
  "','", "'.'", "$accept", "translation_unit", "import_module", "block",
  "variable_val", "unary_val", "expression", "additive_expression",
  "add_arithmetic", "multiplicative_expression", "mul_arithmetic",
  "shift_expression", "shift_arithmetic", "conditional",
  "expression_rvalue", "comparison", "logical", "unary", "assignment",
  "compound_statement", "compound_block", "statement", "labled_if",
  "labeled_switch", "selection_statement", "for_range",
  "iteration_statement", "jump_statement", "parameter_list",
  "function_parameter", "function_definition", "method_call",
  "extern_call", "union_statement", "union_list", "union_definition",
  "primary_rvalue", "identifier_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   137,   137,   138,   139,   140,   141,   142,   143,   144,
     148,   153,   154,   155,   156,   161,   167,   174,   178,   179,
     187,   188,   193,   194,   202,   203,   204,   208,   209,   216,
     217,   218,   219,   220,   226,   227,   230,   233,   238,   239,
     244,   245,   246,   247,   248,   249,   254,   255,   256,   261,
     262,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   281,   282,   287,   288,   289,   290,   295,   296,
     297,   301,   307,   318,   323,   329,   337,   342,   349,   350,
     354,   358,   362,   366,   374,   375,   376,   377,   382,   383,
     387,   388,   392,   397,   403,   410,   411,   415,   416,   417,
     418,   422,   427,   428,   429,   430,   431,   432,   436,   437
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2498 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"

#line 440 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"


/**
* 以后再优化
*/



void yy::Parser::error(const yy::location& l, const std::string& m)
{
    ctx.current_file();
    std::cout<<"script error line: "<< (code_line - 1)<< ".  chars: "<< l<< ". msg: "<< m<< std::endl;
}


