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
      case symbol_kind::S_namespace_body: // namespace_body
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

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
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

      case symbol_kind::S_namespace_definition: // namespace_definition
        value.YY_MOVE_OR_COPY< e2::NameSpace * > (YY_MOVE (that.value));
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
      case symbol_kind::S_namespace_member: // namespace_member
        value.YY_MOVE_OR_COPY< e2::VariableStatement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.YY_MOVE_OR_COPY< std::int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
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
      case symbol_kind::S_namespace_body: // namespace_body
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

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
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

      case symbol_kind::S_namespace_definition: // namespace_definition
        value.move< e2::NameSpace * > (YY_MOVE (that.value));
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
      case symbol_kind::S_namespace_member: // namespace_member
        value.move< e2::VariableStatement * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.move< float > (YY_MOVE (that.value));
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
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< std::int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
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
      case symbol_kind::S_namespace_body: // namespace_body
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

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
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

      case symbol_kind::S_namespace_definition: // namespace_definition
        value.copy< e2::NameSpace * > (that.value);
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
      case symbol_kind::S_namespace_member: // namespace_member
        value.copy< e2::VariableStatement * > (that.value);
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.copy< float > (that.value);
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
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.copy< std::int64_t > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
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
      case symbol_kind::S_namespace_body: // namespace_body
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

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
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

      case symbol_kind::S_namespace_definition: // namespace_definition
        value.move< e2::NameSpace * > (that.value);
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
      case symbol_kind::S_namespace_member: // namespace_member
        value.move< e2::VariableStatement * > (that.value);
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        value.move< float > (that.value);
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
        value.move< int > (that.value);
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< std::int64_t > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
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
      case symbol_kind::S_namespace_body: // namespace_body
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

      case symbol_kind::S_primary_lvalue: // primary_lvalue
      case symbol_kind::S_id_func_call_name: // id_func_call_name
      case symbol_kind::S_id_ns_gl_name: // id_ns_gl_name
      case symbol_kind::S_id_ns_name: // id_ns_name
      case symbol_kind::S_global_union_variable: // global_union_variable
      case symbol_kind::S_namespace_variable: // namespace_variable
      case symbol_kind::S_identifier_str: // identifier_str
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

      case symbol_kind::S_namespace_definition: // namespace_definition
        yylhs.value.emplace< e2::NameSpace * > ();
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
      case symbol_kind::S_namespace_member: // namespace_member
        yylhs.value.emplace< e2::VariableStatement * > ();
        break;

      case symbol_kind::S_FCONSTANT: // FCONSTANT
        yylhs.value.emplace< float > ();
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
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        yylhs.value.emplace< std::int64_t > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IMPORT_LITERAL: // IMPORT_LITERAL
      case symbol_kind::S_NSFUNC_CALL: // NSFUNC_CALL
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
#line 158 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1251 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 3: // translation_unit: import_module
#line 159 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                    { if(yystack_[0].value.as < e2::ImportModule * > ()!=nullptr) ctx.RootBlock()->push_back(yystack_[0].value.as < e2::ImportModule * > ()); }
#line 1257 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 4: // translation_unit: namespace_definition
#line 160 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                           { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::NameSpace * > ());}
#line 1263 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 5: // translation_unit: function_definition
#line 161 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                           { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::FunctionDeclaration * > ());}
#line 1269 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 6: // translation_unit: union_definition
#line 162 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                           { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::UnionDeclaration * > ());}
#line 1275 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 7: // translation_unit: translation_unit block
#line 163 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                              { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1281 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 8: // translation_unit: translation_unit namespace_definition
#line 164 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                            { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::NameSpace * > ());}
#line 1287 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 9: // translation_unit: translation_unit function_definition
#line 165 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                            { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::FunctionDeclaration * > ());}
#line 1293 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 10: // translation_unit: translation_unit union_definition
#line 166 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                            { ctx.RootBlock()->push_back(yystack_[0].value.as < e2::UnionDeclaration * > ());}
#line 1299 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 11: // translation_unit: translation_unit import_module
#line 167 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                     { if(yystack_[0].value.as < e2::ImportModule * > ()!=nullptr)ctx.RootBlock()->push_back(yystack_[0].value.as < e2::ImportModule * > ()); }
#line 1305 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 12: // import_module: IMPORT IMPORT_LITERAL
#line 171 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                   {yylhs.value.as < e2::ImportModule * > () = MALLOC( e2::ImportModule,yystack_[0].value.as < std::string > ());}
#line 1311 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 13: // block: variable_val ';'
#line 176 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                        {yylhs.value.as < e2::Statement * > () = yystack_[1].value.as < e2::VariableStatement * > (); }
#line 1317 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 14: // block: unary_val ';'
#line 177 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::Statement * > () = yystack_[1].value.as < e2::UnaryOperator * > ();}
#line 1323 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 15: // block: method_call ';'
#line 178 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                        {yylhs.value.as < e2::Statement * > () = yystack_[1].value.as < e2::MethodCall * > (); }
#line 1329 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 16: // block: extern_call ';'
#line 179 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                       {yylhs.value.as < e2::Statement * > () = yystack_[1].value.as < e2::ExternDeclaration * > ();}
#line 1335 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 17: // unary_val: primary_lvalue unary
#line 186 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                           {
        yylhs.value.as < e2::UnaryOperator * > () = MALLOC(e2::UnaryOperator,yystack_[1].value.as < e2::Identifier * > (),yystack_[0].value.as < int > (),code_line, ctx.path()); 
         }
#line 1343 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 18: // unary: UNARY_INC
#line 193 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                {yylhs.value.as < int > ()= token::UNARY_INC;}
#line 1349 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 19: // unary: UNARY_DEC
#line 194 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                {yylhs.value.as < int > ()= token::UNARY_DEC;}
#line 1355 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 20: // variable_val: primary_lvalue assignment expression
#line 199 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                           {
            yylhs.value.as < e2::VariableStatement * > () = MALLOC( e2::VariableStatement,yystack_[2].value.as < e2::Identifier * > (),yystack_[1].value.as < int > (), yystack_[0].value.as < e2::Expression * > (),code_line, ctx.path());
            }
#line 1363 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 21: // expression: additive_expression
#line 206 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                          {yylhs.value.as < e2::Expression * > ()=yystack_[0].value.as < e2::Expression * > ();}
#line 1369 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 22: // additive_expression: multiplicative_expression
#line 210 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Expression * > ()=yystack_[0].value.as < e2::Expression * > ();}
#line 1375 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 23: // additive_expression: additive_expression add_arithmetic multiplicative_expression
#line 211 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                                   {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::BinaryOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path());
            }
#line 1383 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 24: // add_arithmetic: '+'
#line 219 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='+';}
#line 1389 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 25: // add_arithmetic: '-'
#line 220 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='-';}
#line 1395 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 26: // multiplicative_expression: shift_expression
#line 225 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                       {yylhs.value.as < e2::Expression * > ()=yystack_[0].value.as < e2::Expression * > ();}
#line 1401 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 27: // multiplicative_expression: multiplicative_expression mul_arithmetic shift_expression
#line 226 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                                {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::BinaryOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path());
         }
#line 1409 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 28: // mul_arithmetic: '*'
#line 234 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='*';}
#line 1415 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 29: // mul_arithmetic: '/'
#line 235 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='/';}
#line 1421 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 30: // mul_arithmetic: '%'
#line 236 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='%';}
#line 1427 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 31: // shift_expression: conditional
#line 240 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < e2::Expression * > () = yystack_[0].value.as < e2::Expression * > ();   }
#line 1433 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 32: // shift_expression: shift_expression shift_arithmetic conditional
#line 241 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                    {
        yylhs.value.as < e2::Expression * > () = MALLOC(e2::BinaryOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path());        
        }
#line 1441 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 33: // shift_arithmetic: ARITH_LEFT
#line 248 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 {yylhs.value.as < int > ()= token::ARITH_LEFT;}
#line 1447 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 34: // shift_arithmetic: ARITH_RIGHT
#line 249 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < int > ()=token::ARITH_RIGHT;}
#line 1453 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 35: // shift_arithmetic: '&'
#line 250 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='&';}
#line 1459 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 36: // shift_arithmetic: '^'
#line 251 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='^';}
#line 1465 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 37: // shift_arithmetic: '|'
#line 252 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='|';}
#line 1471 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 38: // conditional: expression_rvalue
#line 258 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                         {yylhs.value.as < e2::Expression * > () = yystack_[0].value.as < e2::Expression * > (); }
#line 1477 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 39: // conditional: expression_rvalue comparison expression_rvalue
#line 259 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                     {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::CompOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path() ); 
         }
#line 1485 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 40: // conditional: expression_rvalue logical expression_rvalue
#line 262 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                  {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::BinaryOperator,yystack_[2].value.as < e2::Expression * > (),yystack_[1].value.as < int > (),yystack_[0].value.as < e2::Expression * > (), code_line, ctx.path()); 
         }
#line 1493 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 41: // conditional: method_call
#line 265 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < e2::Expression * > ()=yystack_[0].value.as < e2::MethodCall * > ();}
#line 1499 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 42: // expression_rvalue: primary_rvalue
#line 270 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::Expression * > () = yystack_[0].value.as < e2::Expression * > ();}
#line 1505 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 43: // expression_rvalue: '(' expression ')'
#line 271 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                          {yylhs.value.as < e2::Expression * > () = yystack_[1].value.as < e2::Expression * > ();}
#line 1511 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 44: // comparison: OP_LE
#line 276 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
            {yylhs.value.as < int > () = token::OP_LE;}
#line 1517 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 45: // comparison: OP_GE
#line 277 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
            {yylhs.value.as < int > () = token::OP_GE;}
#line 1523 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 46: // comparison: OP_EQ
#line 278 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
            {yylhs.value.as < int > () = token::OP_EQ;}
#line 1529 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 47: // comparison: OP_NE
#line 279 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
            {yylhs.value.as < int > () = token::OP_NE;}
#line 1535 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 48: // comparison: '<'
#line 280 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='<';}
#line 1541 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 49: // comparison: '>'
#line 281 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < int > ()='>';}
#line 1547 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 50: // logical: LOGICAL_NOT
#line 286 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < int > () = token::LOGICAL_NOT;}
#line 1553 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 51: // logical: LOGICAL_AND
#line 287 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                  {yylhs.value.as < int > () = token::LOGICAL_AND;}
#line 1559 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 52: // logical: LOGICAL_OR
#line 288 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 {yylhs.value.as < int > () = token::LOGICAL_OR;}
#line 1565 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 53: // assignment: ASSIGN_EQ
#line 295 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_EQ;}
#line 1571 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 54: // assignment: ASSIGN_MUL
#line 296 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_MUL;}
#line 1577 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 55: // assignment: ASSIGN_DIV
#line 297 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_DIV;}
#line 1583 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 56: // assignment: ASSIGN_MOD
#line 298 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_MOD;}
#line 1589 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 57: // assignment: ASSIGN_ADD
#line 299 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_ADD;}
#line 1595 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 58: // assignment: ASSIGN_SUB
#line 300 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_SUB;}
#line 1601 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 59: // assignment: ASSIGN_LEFT
#line 301 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_LEFT;}
#line 1607 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 60: // assignment: ASSIGN_RIGHT
#line 302 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_RIGHT;}
#line 1613 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 61: // assignment: ASSIGN_AND
#line 303 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_AND;}
#line 1619 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 62: // assignment: ASSIGN_XOR
#line 304 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_XOR;}
#line 1625 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 63: // assignment: ASSIGN_OR
#line 305 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < int > ()= token::ASSIGN_OR;}
#line 1631 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 64: // compound_statement: '{' '}'
#line 309 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
               {yylhs.value.as < e2::Block * > () = nullptr;}
#line 1637 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 65: // compound_statement: '{' compound_block '}'
#line 310 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                             {yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > ();}
#line 1643 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 66: // compound_block: block
#line 315 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "decl_vari", code_line, ctx.path() );yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1649 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 67: // compound_block: statement
#line 316 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "decl_statement", code_line, ctx.path() ); yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1655 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 68: // compound_block: compound_block block
#line 317 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > (); yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1661 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 69: // compound_block: compound_block statement
#line 318 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > (); yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::Statement * > ());}
#line 1667 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 70: // statement: selection_statement
#line 323 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                          {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::Statement * > ();}
#line 1673 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 71: // statement: iteration_statement
#line 324 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                          {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::IterStatement * > ();}
#line 1679 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 72: // statement: jump_statement
#line 325 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::Statement * > ();}
#line 1685 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 73: // labled_if: compound_statement
#line 330 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::LabledBlock * > () = MALLOC(e2::LabledBlock, "labled_if", code_line, ctx.path()); 
            yylhs.value.as < e2::LabledBlock * > ()->push(yystack_[0].value.as < e2::Block * > (), e2::Selection::_then);

}
#line 1695 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 74: // labled_if: compound_statement ELSE compound_statement
#line 336 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {  

yylhs.value.as < e2::LabledBlock * > () = MALLOC(e2::LabledBlock,"labled_if", code_line, ctx.path()); 
            yylhs.value.as < e2::LabledBlock * > ()->push(yystack_[2].value.as < e2::Block * > (), e2::Selection::_then);

yylhs.value.as < e2::LabledBlock * > ()->push(yystack_[0].value.as < e2::Block * > (), e2::Selection::_else);
        }
#line 1707 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 75: // labeled_switch: CASE primary_rvalue ':' compound_block
#line 347 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::LabledBlock * > () = MALLOC(e2::LabledBlock, "labeled_switch", code_line, ctx.path());
            yylhs.value.as < e2::LabledBlock * > ()->push(yystack_[2].value.as < e2::Expression * > (),yystack_[0].value.as < e2::Block * > (), e2::Selection::_case) ;
        }
#line 1716 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 76: // labeled_switch: labeled_switch CASE primary_rvalue ':' compound_block
#line 352 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        { 
            yylhs.value.as < e2::LabledBlock * > () = yystack_[4].value.as < e2::LabledBlock * > ();  
            yystack_[4].value.as < e2::LabledBlock * > ()->push(yystack_[2].value.as < e2::Expression * > (),yystack_[0].value.as < e2::Block * > (), e2::Selection::_case) ;

        }
#line 1726 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 77: // labeled_switch: labeled_switch DEFAULT ':' compound_block
#line 358 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        { 
            yylhs.value.as < e2::LabledBlock * > () = yystack_[3].value.as < e2::LabledBlock * > ();
            yystack_[3].value.as < e2::LabledBlock * > ()->push(yystack_[0].value.as < e2::Block * > (),e2::Selection::_default);
        }
#line 1735 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 78: // selection_statement: IF '(' conditional ')' labled_if
#line 366 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Statement * > () = MALLOC(e2::IFStatement, yystack_[2].value.as < e2::Expression * > (),yystack_[0].value.as < e2::LabledBlock * > (), code_line, ctx.path());
        }
#line 1743 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 79: // selection_statement: SWITCH '(' conditional ')' '{' labeled_switch '}'
#line 371 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Statement * > () = MALLOC(e2::SwitchStatement, yystack_[4].value.as < e2::Expression * > (),yystack_[1].value.as < e2::LabledBlock * > ());
        }
#line 1751 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 80: // for_range: unary_val
#line 377 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::UnaryOperator * > ();}
#line 1757 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 81: // for_range: variable_val
#line 378 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                   {yylhs.value.as < e2::Statement * > () = yystack_[0].value.as < e2::VariableStatement * > ();}
#line 1763 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 82: // iteration_statement: WHILE '(' conditional ')' compound_statement
#line 383 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {   
            yylhs.value.as < e2::IterStatement * > () = MALLOC(e2::IterStatement, yystack_[2].value.as < e2::Expression * > (),yystack_[0].value.as < e2::Block * > (),e2::IterType::_while);
        }
#line 1771 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 83: // iteration_statement: DO compound_statement WHILE '(' conditional ')' ';'
#line 387 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::IterStatement * > () = MALLOC(e2::IterStatement,yystack_[2].value.as < e2::Expression * > (),yystack_[5].value.as < e2::Block * > (),e2::IterType::_do);
        }
#line 1779 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 84: // iteration_statement: FOR '(' variable_val ';' conditional ';' ')' compound_statement
#line 391 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::IterStatement * > () = MALLOC(e2::IterStatement,yystack_[5].value.as < e2::VariableStatement * > (),yystack_[3].value.as < e2::Expression * > (),yystack_[0].value.as < e2::Block * > (),e2::IterType::_for);
        }
#line 1787 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 85: // iteration_statement: FOR '(' variable_val ';' conditional ';' for_range ')' compound_statement
#line 395 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::IterStatement * > () = MALLOC(e2::IterStatement,yystack_[6].value.as < e2::VariableStatement * > (),yystack_[4].value.as < e2::Expression * > (),yystack_[2].value.as < e2::Statement * > (),yystack_[0].value.as < e2::Block * > (),e2::IterType::_forfull);
        }
#line 1795 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 86: // jump_statement: CONTINUE ';'
#line 402 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                             {yylhs.value.as < e2::Statement * > () = nullptr;}
#line 1801 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 87: // jump_statement: BREAK ';'
#line 403 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                            {yylhs.value.as < e2::Statement * > () = MALLOC(e2::BreakStatement, code_line, ctx.path()) ;}
#line 1807 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 88: // jump_statement: RETURN ';'
#line 404 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 {yylhs.value.as < e2::Statement * > () = MALLOC(e2::ReturnStatement, code_line, ctx.path());}
#line 1813 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 89: // jump_statement: RETURN primary_rvalue ';'
#line 405 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                {yylhs.value.as < e2::Statement * > () = MALLOC(e2::ReturnStatement,yystack_[1].value.as < e2::Expression * > (), code_line, ctx.path());}
#line 1819 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 90: // parameter_list: primary_rvalue
#line 412 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     {yylhs.value.as < e2::ExpressionList * > () = MALLOC(e2::ExpressionList);yylhs.value.as < e2::ExpressionList * > ()->push_back(yystack_[0].value.as < e2::Expression * > ());}
#line 1825 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 91: // parameter_list: parameter_list ',' primary_rvalue
#line 413 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                        {yylhs.value.as < e2::ExpressionList * > ()=yystack_[2].value.as < e2::ExpressionList * > ();  yystack_[2].value.as < e2::ExpressionList * > ()->push_back(yystack_[0].value.as < e2::Expression * > ());}
#line 1831 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 92: // function_parameter: '(' ')'
#line 417 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
              {yylhs.value.as < e2::ExpressionList * > () = nullptr;}
#line 1837 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 93: // function_parameter: '(' parameter_list ')'
#line 418 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                             {yylhs.value.as < e2::ExpressionList * > () = yystack_[1].value.as < e2::ExpressionList * > ();}
#line 1843 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 94: // function_definition: FUNCTION identifier_str function_parameter compound_statement
#line 423 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::FunctionDeclaration * > () = MALLOC(e2::FunctionDeclaration, yystack_[2].value.as < e2::Identifier * > (), yystack_[1].value.as < e2::ExpressionList * > (), yystack_[0].value.as < e2::Block * > (), code_line, ctx.path());
        }
#line 1851 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 95: // method_call: id_func_call_name function_parameter
#line 430 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                          {
            yylhs.value.as < e2::MethodCall * > () = MALLOC(e2::MethodCall, yystack_[1].value.as < e2::Identifier * > (), yystack_[0].value.as < e2::ExpressionList * > (), code_line, ctx.path());
        }
#line 1859 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 96: // extern_call: EXTERN IDENTIFIER identifier_str '(' identifier_str primary_rvalue ')'
#line 436 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                                                              { 
        e2::ExpressionList *el = MALLOC(e2::ExpressionList); 
         el->push_back(yystack_[1].value.as < e2::Expression * > ()); 
         yylhs.value.as < e2::ExternDeclaration * > () = MALLOC(e2::ExternDeclaration,yystack_[4].value.as < e2::Identifier * > (),el);}
#line 1868 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 97: // union_statement: ';'
#line 443 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < e2::VariableStatement * > () = nullptr; }
#line 1874 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 98: // union_statement: variable_val ';'
#line 445 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::VariableStatement * > () = yystack_[1].value.as < e2::VariableStatement * > ();  
            yystack_[1].value.as < e2::VariableStatement * > ()->idType(e2::IDType::_global); 
        }
#line 1883 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 99: // union_list: union_statement
#line 453 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "union_list", code_line, ctx.path() ); 
            yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::VariableStatement * > ());
        }
#line 1892 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 100: // union_list: union_list union_statement
#line 458 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > (); 
            yystack_[0].value.as < e2::VariableStatement * > ()->idType(e2::IDType::_global);
            yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::VariableStatement * > ()); 
        }
#line 1902 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 101: // union_list: union_definition
#line 464 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yystack_[0].value.as < e2::UnionDeclaration * > ()->idType(e2::IDType::_global);
            yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "union_def", code_line, ctx.path() ); 
            yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::UnionDeclaration * > ()); 
        }
#line 1912 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 102: // union_list: union_list union_definition
#line 470 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Block * > () = yystack_[1].value.as < e2::Block * > (); 
            yystack_[0].value.as < e2::UnionDeclaration * > ()->idType(e2::IDType::_global); 
            yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::UnionDeclaration * > ());
        }
#line 1922 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 103: // union_definition: UNION identifier_str '{' union_list '}'
#line 479 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {  
            yylhs.value.as < e2::UnionDeclaration * > () = MALLOC(e2::UnionDeclaration,yystack_[3].value.as < e2::Identifier * > (),yystack_[1].value.as < e2::Block * > (), code_line, ctx.path());
        }
#line 1930 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 104: // namespace_member: ';'
#line 486 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
          {yylhs.value.as < e2::VariableStatement * > () = nullptr; }
#line 1936 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 105: // namespace_member: variable_val ';'
#line 488 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::VariableStatement * > () = yystack_[1].value.as < e2::VariableStatement * > (); 
            if(yystack_[1].value.as < e2::VariableStatement * > ()->id()->idType() ==e2::IDType::_ns_private){
                yystack_[1].value.as < e2::VariableStatement * > ()->id()->nss(NameSpaceStatus::_n_attr_definition);
            }
        }
#line 1947 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 106: // namespace_body: namespace_member
#line 499 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "namespace_member", code_line, ctx.path() ); 
            yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::VariableStatement * > ());
        }
#line 1956 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 107: // namespace_body: SELF function_definition
#line 504 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yystack_[0].value.as < e2::FunctionDeclaration * > ()->idType(e2::IDType::_ns_private); 
            yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "namespace_func", code_line, ctx.path());
            yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::FunctionDeclaration * > ());
        }
#line 1966 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 108: // namespace_body: function_definition
#line 510 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yystack_[0].value.as < e2::FunctionDeclaration * > ()->idType(e2::IDType::_ns_public); 

            yylhs.value.as < e2::Block * > () = MALLOC(e2::Block, "namespace_func", code_line, ctx.path());
            yylhs.value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::FunctionDeclaration * > ());
        }
#line 1977 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 109: // namespace_body: namespace_body namespace_member
#line 516 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                                      {yylhs.value.as < e2::Block * > ()=yystack_[1].value.as < e2::Block * > (); yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::VariableStatement * > ());}
#line 1983 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 110: // namespace_body: namespace_body SELF function_definition
#line 518 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Block * > ()=yystack_[2].value.as < e2::Block * > (); 
            yystack_[0].value.as < e2::FunctionDeclaration * > ()->idType(e2::IDType::_ns_private); 
            yystack_[2].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::FunctionDeclaration * > ());
        }
#line 1993 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 111: // namespace_body: namespace_body function_definition
#line 524 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Block * > ()=yystack_[1].value.as < e2::Block * > (); 
            yystack_[0].value.as < e2::FunctionDeclaration * > ()->idType(e2::IDType::_ns_public);  
            yystack_[1].value.as < e2::Block * > ()->push_back(yystack_[0].value.as < e2::FunctionDeclaration * > ());
        }
#line 2003 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 112: // namespace_definition: NAMESPACE identifier_str '{' namespace_body '}'
#line 534 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {  
            yylhs.value.as < e2::NameSpace * > () = MALLOC(e2::NameSpace, yystack_[3].value.as < e2::Identifier * > (), yystack_[1].value.as < e2::Block * > (), code_line, ctx.path());
           
        }
#line 2012 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 113: // primary_lvalue: id_ns_name
#line 543 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 { yylhs.value.as < e2::Identifier * > () = yystack_[0].value.as < e2::Identifier * > (); }
#line 2018 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 114: // primary_rvalue: id_ns_gl_name
#line 548 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                    { yylhs.value.as < e2::Expression * > () = yystack_[0].value.as < e2::Identifier * > (); }
#line 2024 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 115: // primary_rvalue: CONSTANT
#line 550 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::Number,yystack_[0].value.as < std::int64_t > (), code_line, ctx.path());
        }
#line 2032 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 116: // primary_rvalue: '-' CONSTANT
#line 554 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::Number,yystack_[0].value.as < std::int64_t > (), true, code_line, ctx.path()); 
        }
#line 2040 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 117: // primary_rvalue: FCONSTANT
#line 558 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::Number,yystack_[0].value.as < float > (), code_line, ctx.path());
        }
#line 2048 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 118: // primary_rvalue: '-' FCONSTANT
#line 562 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::Number,yystack_[0].value.as < float > (), true, code_line, ctx.path());
        }
#line 2056 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 119: // primary_rvalue: STRING_LITERAL
#line 566 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Expression * > () = MALLOC(e2::StrObj, yystack_[0].value.as < std::string > (), code_line, ctx.path()); 
        }
#line 2064 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 120: // id_func_call_name: id_ns_name
#line 573 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 {yylhs.value.as < e2::Identifier * > ()=yystack_[0].value.as < e2::Identifier * > ();}
#line 2070 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 121: // id_func_call_name: identifier_str NSFUNC_CALL identifier_str
#line 575 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Identifier * > ()=yystack_[0].value.as < e2::Identifier * > ();
            yystack_[0].value.as < e2::Identifier * > ()->push_back(yystack_[2].value.as < e2::Identifier * > ());
            yystack_[0].value.as < e2::Identifier * > ()->NameSpaceTag(yystack_[1].value.as < std::string > ());
            yystack_[0].value.as < e2::Identifier * > ()->idType(IDType::_ns_methodcall); 
        }
#line 2081 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 122: // id_ns_gl_name: id_ns_name
#line 585 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                 { yylhs.value.as < e2::Identifier * > () = yystack_[0].value.as < e2::Identifier * > (); }
#line 2087 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 123: // id_ns_gl_name: global_union_variable
#line 586 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                            { yylhs.value.as < e2::Identifier * > () = yystack_[0].value.as < e2::Identifier * > (); }
#line 2093 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 124: // id_ns_name: identifier_str
#line 591 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                     { yylhs.value.as < e2::Identifier * > () = yystack_[0].value.as < e2::Identifier * > (); }
#line 2099 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 125: // id_ns_name: namespace_variable
#line 592 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
                         {yylhs.value.as < e2::Identifier * > () = yystack_[0].value.as < e2::Identifier * > ();}
#line 2105 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 126: // global_union_variable: identifier_str '.' identifier_str
#line 598 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Identifier * > ()=yystack_[2].value.as < e2::Identifier * > ();  
            yylhs.value.as < e2::Identifier * > ()->push_back(yystack_[0].value.as < e2::Identifier * > ());
            yylhs.value.as < e2::Identifier * > ()->idType(e2::IDType::_global);
            yylhs.value.as < e2::Identifier * > ()->codeLine(code_line);
            yylhs.value.as < e2::Identifier * > ()->codePath(ctx.path());
        }
#line 2117 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 127: // global_union_variable: global_union_variable '.' identifier_str
#line 606 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Identifier * > ()=yystack_[2].value.as < e2::Identifier * > ();  
            yystack_[2].value.as < e2::Identifier * > ()->push_back(yystack_[0].value.as < e2::Identifier * > ());
            yystack_[2].value.as < e2::Identifier * > ()->idType(e2::IDType::_global);
            yystack_[2].value.as < e2::Identifier * > ()->codeLine(code_line);
            yystack_[2].value.as < e2::Identifier * > ()->codePath(ctx.path());
        }
#line 2129 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 128: // namespace_variable: THIS NAMESPACE_ATTR identifier_str
#line 619 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        { 
            yylhs.value.as < e2::Identifier * > () = yystack_[0].value.as < e2::Identifier * > ();
            yystack_[0].value.as < e2::Identifier * > ()->idType(e2::IDType::_ns_private); 
            yystack_[0].value.as < e2::Identifier * > ()->nss(NameSpaceStatus::_n_attr_expression);
        }
#line 2139 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;

  case 129: // identifier_str: IDENTIFIER
#line 629 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"
        {
            yylhs.value.as < e2::Identifier * > () = MALLOC(e2::Identifier, yystack_[0].value.as < std::string > (), e2::IDType::_normal);
            yylhs.value.as < e2::Identifier * > ()->codeLine(code_line);
            yylhs.value.as < e2::Identifier * > ()->codePath(ctx.path());
        }
#line 2149 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"
    break;


#line 2153 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"

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


  const short Parser::yypact_ninf_ = -145;

  const signed char Parser::yytable_ninf_ = -121;

  const short
  Parser::yypact_[] =
  {
     251,  -145,    21,    21,    21,    26,     6,    -4,   285,  -145,
    -145,   -16,   -13,  -145,    -3,    11,  -145,  -145,   331,    28,
      32,  -145,    15,    24,    37,    28,    21,  -145,    21,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,   210,   176,  -145,    21,   129,    17,    41,
      44,  -145,  -145,  -145,  -145,    25,   210,  -145,    10,    80,
     339,  -145,   327,  -145,  -145,  -145,    32,    46,    12,  -145,
     -44,  -145,  -145,    52,  -145,    38,  -145,    60,  -145,  -145,
      71,    18,  -145,  -145,  -145,    61,  -145,    95,  -145,   182,
    -145,    21,  -145,  -145,    67,  -145,  -145,   210,  -145,  -145,
    -145,   210,  -145,  -145,  -145,  -145,  -145,   210,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,   210,   210,    21,
      21,  -145,   300,  -145,  -145,    38,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,    69,    75,    76,    41,    82,    72,    81,
     270,  -145,  -145,   204,  -145,  -145,  -145,  -145,   300,  -145,
      80,   339,  -145,  -145,  -145,  -145,  -145,  -145,  -145,   210,
     210,   210,    94,    20,  -145,  -145,  -145,    86,  -145,  -145,
    -145,    92,    96,    99,   100,   102,   107,  -145,  -145,    41,
     108,    41,   210,   210,   124,  -145,   126,  -145,   115,   118,
      41,   300,   -40,   122,     3,  -145,   120,   300,   121,  -145,
    -145,    41,  -145,  -145,   128,   267,   127,   267,  -145,    41,
     267,   267,   267,  -145,   267
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,   129,     0,     0,     0,     0,     0,     0,     0,     3,
       2,     0,     0,     5,     0,     0,     6,     4,     0,     0,
     113,   125,   124,     0,     0,     0,     0,    12,     0,     1,
      11,     7,     9,    10,     8,    14,    13,    15,    16,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    18,
      19,    53,    17,     0,     0,    95,     0,     0,     0,     0,
       0,   128,   119,   115,   117,     0,     0,    20,    21,    22,
      26,    31,    38,    41,    42,   114,   122,   123,   124,    92,
       0,    90,   122,   124,   121,     0,   104,     0,   108,   106,
       0,     0,   113,   124,    97,     0,    99,     0,   101,     0,
      94,     0,   116,   118,     0,    24,    25,     0,    28,    29,
      30,     0,    33,    34,    35,    36,    37,     0,    44,    45,
      46,    47,    51,    52,    50,    48,    49,     0,     0,     0,
       0,    93,     0,   107,   105,     0,   112,   111,   109,    98,
     103,   100,   102,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    66,     0,    67,    70,    71,    72,     0,    43,
      23,    27,    32,    39,    40,   127,   126,    91,   110,     0,
       0,     0,     0,     0,    86,    87,    88,     0,    65,    68,
      69,     0,     0,     0,     0,     0,     0,    89,    96,     0,
       0,     0,     0,     0,    73,    78,     0,    82,     0,     0,
       0,     0,     0,     0,     0,    74,     0,     0,     0,    79,
      83,     0,    80,    81,     0,     0,     0,     0,    84,     0,
      75,     0,    77,    85,    76
  };

  const short
  Parser::yypgoto_[] =
  {
    -145,  -145,   179,     0,    -7,  -145,   -43,   132,  -145,  -145,
      97,  -145,    88,  -145,   -98,   -26,  -145,  -145,  -145,  -112,
    -131,  -144,  -145,  -145,  -145,  -145,  -145,  -145,  -145,   177,
       2,   -49,  -145,   104,  -145,     8,   131,  -145,   200,   -27,
     -47,  -145,  -145,    98,  -145,  -145,    -1
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,     8,     9,   152,    11,    52,    12,    67,    68,   107,
      69,   111,    70,   117,    71,    72,   127,   128,    53,   100,
     153,   154,   195,   202,   155,   214,   156,   157,    80,    55,
      13,    14,    15,    96,    97,    16,    89,    90,    17,    18,
      74,    19,    75,    20,    77,    21,    22
  };

  const short
  Parser::yytable_[] =
  {
      10,    23,    24,    25,    73,    28,     1,    81,    31,   180,
      32,    27,   207,   208,    87,    95,    33,    73,    56,   162,
       1,    56,   131,     1,     1,    60,   132,    61,   209,    26,
      91,    91,   102,   103,   172,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,   105,   106,    87,    35,    51,
       7,    36,    78,    83,    95,    84,    93,    93,    73,    88,
       3,    37,    73,    91,     7,    78,    98,     7,    73,   211,
      91,   182,   183,   184,     1,    38,   180,   194,   180,   197,
     180,    94,     4,   130,   220,   167,   222,   133,   205,    93,
     224,    57,   137,    54,   198,   199,    93,  -120,     1,   218,
     158,   163,   164,   177,    58,   142,    78,   223,    99,   101,
      78,   181,   108,   109,   110,     4,    78,   129,     7,   135,
      73,    73,    73,   130,   134,   139,    83,    83,   165,   166,
     186,    83,     1,   159,   169,    86,   174,   168,     3,   136,
     170,   171,     7,    73,    73,   175,    91,   173,   185,    83,
     187,    76,    82,   179,   206,    92,    92,    83,   188,    94,
     216,   213,   189,   140,    76,   190,   191,   192,    78,    78,
      78,   193,    93,     4,   200,   196,     7,    85,   201,     1,
      62,   203,   204,    63,    64,     1,   210,    30,    92,   215,
     217,    78,    78,    86,   219,    92,   221,   212,   104,   161,
      83,   141,    59,    93,   160,    76,    83,     1,    34,    76,
       0,     0,    65,     1,    62,    76,     0,    63,    64,     0,
     179,   138,   179,     7,   179,    82,    82,     5,     0,     7,
      82,   143,     0,   144,     0,     0,   145,   146,   147,   148,
     149,   150,    79,     0,     0,     0,    65,     0,    82,     5,
     151,     7,     0,   143,     1,   144,    82,     7,   145,   146,
     147,   148,   149,   150,     0,     0,     0,    76,    76,    76,
       1,    92,   178,     1,    62,    66,     0,    63,    64,     0,
       0,     0,     0,     0,     0,    29,     0,     0,     1,     0,
      76,    76,     0,     2,     3,     4,     5,     6,     7,    82,
       0,     0,    92,     1,    62,    82,    65,    63,    64,     0,
       0,     0,     5,     0,     7,     0,   143,     7,   144,     0,
       0,   145,   146,   147,   148,   149,   150,     2,     3,     4,
       5,     6,     7,     0,   176,     0,    65,   118,   119,   120,
     121,   122,   123,   124,     0,     0,     0,     7,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     0,     0,
      49,    50,    51,     0,   125,   126,   112,   113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,   115,
     116
  };

  const short
  Parser::yycheck_[] =
  {
       0,     2,     3,     4,    53,     9,     3,    54,     8,   153,
       8,     5,    52,    53,    57,    58,     8,    66,     6,   117,
       3,     6,    66,     3,     3,    26,    70,    28,    68,     3,
      57,    58,     7,     8,   146,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    35,    36,    90,    64,    31,
      47,    64,    53,    54,    97,    56,    57,    58,   107,    57,
      43,    64,   111,    90,    47,    66,    58,    47,   117,    66,
      97,   169,   170,   171,     3,    64,   220,   189,   222,   191,
     224,    64,    44,    71,   215,   132,   217,    85,   200,    90,
     221,    67,    90,    65,   192,   193,    97,    65,     3,   211,
     101,   127,   128,   150,    67,    97,   107,   219,    67,    65,
     111,   158,    32,    33,    34,    44,   117,    71,    47,    48,
     169,   170,   171,    71,    64,    64,   127,   128,   129,   130,
     173,   132,     3,    66,    65,    64,    64,   135,    43,    68,
      65,    65,    47,   192,   193,    64,   173,    65,    54,   150,
      64,    53,    54,   153,   201,    57,    58,   158,    66,    64,
     207,   204,    66,    68,    66,    66,    66,    65,   169,   170,
     171,    64,   173,    44,    50,    67,    47,    48,    52,     3,
       4,    66,    64,     7,     8,     3,    64,     8,    90,    69,
      69,   192,   193,    64,    66,    97,    69,   204,    66,   111,
     201,    97,    25,   204,   107,   107,   207,     3,     8,   111,
      -1,    -1,    36,     3,     4,   117,    -1,     7,     8,    -1,
     220,    90,   222,    47,   224,   127,   128,    45,    -1,    47,
     132,    49,    -1,    51,    -1,    -1,    54,    55,    56,    57,
      58,    59,    66,    -1,    -1,    -1,    36,    -1,   150,    45,
      68,    47,    -1,    49,     3,    51,   158,    47,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,   169,   170,   171,
       3,   173,    68,     3,     4,    65,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,     0,    -1,    -1,     3,    -1,
     192,   193,    -1,    42,    43,    44,    45,    46,    47,   201,
      -1,    -1,   204,     3,     4,   207,    36,     7,     8,    -1,
      -1,    -1,    45,    -1,    47,    -1,    49,    47,    51,    -1,
      -1,    54,    55,    56,    57,    58,    59,    42,    43,    44,
      45,    46,    47,    -1,    64,    -1,    36,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    47,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      29,    30,    31,    -1,    37,    38,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      41
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,    42,    43,    44,    45,    46,    47,    73,    74,
      75,    76,    78,   102,   103,   104,   107,   110,   111,   113,
     115,   117,   118,   118,   118,   118,     3,     5,     9,     0,
      74,    75,   102,   107,   110,    64,    64,    64,    64,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    29,
      30,    31,    77,    90,    65,   101,     6,    67,    67,   101,
     118,   118,     4,     7,     8,    36,    65,    79,    80,    82,
      84,    86,    87,   103,   112,   114,   115,   116,   118,    66,
     100,   112,   115,   118,   118,    48,    64,    78,   102,   108,
     109,   111,   115,   118,    64,    78,   105,   106,   107,    67,
      91,    65,     7,     8,    79,    35,    36,    81,    32,    33,
      34,    83,    27,    28,    39,    40,    41,    85,    10,    11,
      12,    13,    14,    15,    16,    37,    38,    88,    89,    71,
      71,    66,    70,   102,    64,    48,    68,   102,   108,    64,
      68,   105,   107,    49,    51,    54,    55,    56,    57,    58,
      59,    68,    75,    92,    93,    96,    98,    99,   118,    66,
      82,    84,    86,    87,    87,   118,   118,   112,   102,    65,
      65,    65,    91,    65,    64,    64,    64,   112,    68,    75,
      93,   112,    86,    86,    86,    54,    78,    64,    66,    66,
      66,    66,    65,    64,    91,    94,    67,    91,    86,    86,
      50,    52,    95,    66,    64,    91,   112,    52,    53,    68,
      64,    66,    76,    78,    97,    69,   112,    69,    91,    66,
      92,    69,    92,    91,    92
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    72,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    75,    75,    75,    75,    76,    77,    77,
      78,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      83,    84,    84,    85,    85,    85,    85,    85,    86,    86,
      86,    86,    87,    87,    88,    88,    88,    88,    88,    88,
      89,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    91,    91,    92,    92,    92,    92,
      93,    93,    93,    94,    94,    95,    95,    95,    96,    96,
      97,    97,    98,    98,    98,    98,    99,    99,    99,    99,
     100,   100,   101,   101,   102,   103,   104,   105,   105,   106,
     106,   106,   106,   107,   108,   108,   109,   109,   109,   109,
     109,   109,   110,   111,   112,   112,   112,   112,   112,   112,
     113,   113,   114,   114,   115,   115,   116,   116,   117,   118
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       3,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     1,     1,     2,     2,
       1,     1,     1,     1,     3,     4,     5,     4,     5,     7,
       1,     1,     5,     7,     8,     9,     2,     2,     2,     3,
       1,     3,     2,     3,     4,     2,     7,     1,     2,     1,
       2,     1,     2,     5,     1,     2,     1,     2,     1,     2,
       3,     2,     5,     1,     1,     1,     2,     1,     2,     1,
       1,     3,     1,     1,     1,     1,     3,     3,     3,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "END", "error", "\"invalid token\"", "IDENTIFIER", "STRING_LITERAL",
  "IMPORT_LITERAL", "NSFUNC_CALL", "CONSTANT", "FCONSTANT",
  "NAMESPACE_ATTR", "OP_LE", "OP_GE", "OP_EQ", "OP_NE", "LOGICAL_AND",
  "LOGICAL_OR", "LOGICAL_NOT", "ASSIGN_MUL", "ASSIGN_DIV", "ASSIGN_MOD",
  "ASSIGN_ADD", "ASSIGN_SUB", "ASSIGN_LEFT", "ASSIGN_RIGHT", "ASSIGN_AND",
  "ASSIGN_XOR", "ASSIGN_OR", "ARITH_LEFT", "ARITH_RIGHT", "UNARY_INC",
  "UNARY_DEC", "ASSIGN_EQ", "'*'", "'/'", "'%'", "'+'", "'-'", "'<'",
  "'>'", "'&'", "'^'", "'|'", "NAMESPACE", "UNION", "FUNCTION", "EXTERN",
  "IMPORT", "THIS", "SELF", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT",
  "WHILE", "DO", "FOR", "CONTINUE", "BREAK", "RETURN", "'='", "\"!=\"",
  "\"<=\"", "\">=\"", "';'", "'('", "')'", "'{'", "'}'", "':'", "','",
  "'.'", "$accept", "translation_unit", "import_module", "block",
  "unary_val", "unary", "variable_val", "expression",
  "additive_expression", "add_arithmetic", "multiplicative_expression",
  "mul_arithmetic", "shift_expression", "shift_arithmetic", "conditional",
  "expression_rvalue", "comparison", "logical", "assignment",
  "compound_statement", "compound_block", "statement", "labled_if",
  "labeled_switch", "selection_statement", "for_range",
  "iteration_statement", "jump_statement", "parameter_list",
  "function_parameter", "function_definition", "method_call",
  "extern_call", "union_statement", "union_list", "union_definition",
  "namespace_member", "namespace_body", "namespace_definition",
  "primary_lvalue", "primary_rvalue", "id_func_call_name", "id_ns_gl_name",
  "id_ns_name", "global_union_variable", "namespace_variable",
  "identifier_str", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   158,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   171,   176,   177,   178,   179,   186,   193,   194,
     199,   206,   210,   211,   219,   220,   225,   226,   234,   235,
     236,   240,   241,   248,   249,   250,   251,   252,   258,   259,
     262,   265,   270,   271,   276,   277,   278,   279,   280,   281,
     286,   287,   288,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   309,   310,   315,   316,   317,   318,
     323,   324,   325,   329,   335,   346,   351,   357,   365,   370,
     377,   378,   382,   386,   390,   394,   402,   403,   404,   405,
     412,   413,   417,   418,   422,   430,   436,   443,   444,   452,
     457,   463,   469,   478,   486,   487,   498,   503,   509,   516,
     517,   523,   533,   543,   548,   549,   553,   557,   561,   565,
     573,   574,   585,   586,   591,   592,   597,   605,   618,   628
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
#line 2821 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/generated/e2_bison.cpp"

#line 635 "/Users/vyouzhi/workspace/c_c_plug/Etomc2Lan/e2/src/grammar/e2_bison.y"


/**
* 以后再优化
*/



void yy::Parser::error(const yy::location& l, const std::string& m)
{
    ctx.current_file();
    std::cout<<"script error line: "<< (code_line - 1)<< ".  chars: "<< l<< ". msg: "<< m<< std::endl;
}


