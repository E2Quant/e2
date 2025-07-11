%require "3.7"
// define

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* write out a header file containing the token defines */
/*%defines*/

/* namespace to enclose parser in */
%define api.prefix {yy}
/* set the parser's class identifier */
%define api.parser.class {Parser}

/* it will generate a location class which can be used in your lexer */
%locations

/* use the constructor for each token, and make_TOKENNAME functions will be generated */
%define api.token.constructor

/* use the variant type for $1~$n and $$ those variables */
%define api.value.type variant


%define parse.trace
%define parse.error verbose

%code requires
{
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
}

%code
{

yy::Parser::symbol_type yylex(void* yyscanner,
                         yy::location& loc,
                         class e2::ParserCtx& ctx);
}

// token
%token END 0;
%token <std::string> IDENTIFIER STRING_LITERAL IMPORT_LITERAL 
%token <std::int64_t>  CONSTANT
%token <float>  FCONSTANT


%token <int> OP_LE OP_GE OP_EQ OP_NE
%token <int> LOGICAL_AND LOGICAL_OR LOGICAL_NOT

%token <int> ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD ASSIGN_ADD
%token <int> ASSIGN_SUB ASSIGN_LEFT ASSIGN_RIGHT ASSIGN_AND
%token <int> ASSIGN_XOR ASSIGN_OR  
%token <int> ARITH_LEFT ARITH_RIGHT
%token <int> UNARY_INC UNARY_DEC
%token <int> ASSIGN_EQ
%token <int> '*' '/' '%' '+' '-' '<' '>' '&' '^' '|'

%token  UNION FUNCTION EXTERN IMPORT

%token IF ELSE SWITCH CASE DEFAULT WHILE DO FOR CONTINUE BREAK RETURN

//type
%type <e2::Block *> translation_unit

%type <e2::Statement *> block
%type <e2::Expression *> expression multiplicative_expression additive_expression
%type <e2::Expression *> conditional shift_expression 

%type <int> add_arithmetic mul_arithmetic shift_arithmetic
%type <int> comparison logical  unary assignment

%type <e2::LabledBlock *> labled_if labeled_switch
%type <e2::Statement *> selection_statement for_range 
%type <e2::IterStatement *> iteration_statement
%type <e2::Statement *> jump_statement 

%type <e2::Block *> compound_statement compound_block
%type <e2::Statement *> statement

%type <e2::UnaryOperator *> unary_val

%type <e2::FunctionDeclaration *> function_definition
%type <e2::MethodCall *> method_call 

%type <e2::ExternDeclaration *>  extern_call

%type <e2::Identifier *> identifier_list
%type <e2::Expression *>  primary_rvalue  
%type <e2::Expression *> expression_rvalue
%type <e2::ExpressionList *> parameter_list function_parameter

%type <e2::VariableStatement *> variable_val
%type <e2::VariableStatement *> union_statement 
%type <e2::Block *> union_list 
%type <e2::UnionDeclaration *> union_definition

%type <e2::ImportModule *> import_module

//left
%left '<' '>' '=' "!=" "<=" ">="
%left '+' '-'
%left '*' '/' '%'

%nonassoc ELSE

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%lex-param {void *scanner} {yy::location& loc} { class e2::ParserCtx& ctx }
%parse-param {void *scanner} {yy::location& loc} { class e2::ParserCtx& ctx }


%start translation_unit

%%

translation_unit 
    : /* 入口  block 1, 变量，函数调用,2,   function_definition: 函数定义， 3. union 声明   */
      block     { ctx.RootBlock()->push_back($1);}
    | import_module { if($1!=nullptr) ctx.RootBlock()->push_back($1); } 
    | function_definition  { ctx.RootBlock()->push_back($1);} 
    | union_definition     { ctx.RootBlock()->push_back($1);} 
    | translation_unit block  { ctx.RootBlock()->push_back($2);} 
    | translation_unit function_definition  { ctx.RootBlock()->push_back($2);} 
    | translation_unit union_definition     { ctx.RootBlock()->push_back($2);} 
    | translation_unit import_module { if($2!=nullptr)ctx.RootBlock()->push_back($2); } 
    ;

import_module:        /* empty */ 
         IMPORT IMPORT_LITERAL {$$ = MALLOC( e2::ImportModule,$2);}        
        ;

block
    : /* block */
      variable_val ';'  {$$ = $1; } 
    | method_call  ';'  {$$ = $1; } 	
    | extern_call ';'  {$$ = $1;}
    | unary_val ';'  {$$ = $1;}
    ;

variable_val
    : /* Statement 变量 赋值*/
      identifier_list assignment expression {
            $$ = MALLOC( e2::VariableStatement,$1,$2, $3,code_line, ctx.path());
            } 
    ;

unary_val
    : identifier_list unary {
        $$ = MALLOC(e2::UnaryOperator,$1,$2,code_line, ctx.path()); 
         }
    ;

expression
    : /* expression 计算  表达式 入口  [ a ? b : c ]  = rhs */ 
      additive_expression {$$=$1;}  
    ;

additive_expression
	: multiplicative_expression {$$=$1;}
	| additive_expression add_arithmetic multiplicative_expression {
            $$ = MALLOC(e2::BinaryOperator,$1,$2,$3, code_line, ctx.path());
            }
	;


add_arithmetic
    : /* expression [? ~ :]  a + b; a - b; a * b  */      
      '+' {$$='+';}
    | '-' {$$='-';}        
    ;


multiplicative_expression
	: shift_expression {$$=$1;} 
	| multiplicative_expression mul_arithmetic shift_expression {
            $$ = MALLOC(e2::BinaryOperator,$1,$2,$3, code_line, ctx.path());
         }

	;

mul_arithmetic
    :
      '*' {$$='*';} 
    | '/' {$$='/';}
    | '%' {$$='%';}
    ;

shift_expression
    : conditional {$$ = $1;   }
    | shift_expression shift_arithmetic conditional {
        $$ = MALLOC(e2::BinaryOperator,$1,$2,$3, code_line, ctx.path());        
        } 
    ;

shift_arithmetic
    :
      ARITH_LEFT {$$= token::ARITH_LEFT;}
    | ARITH_RIGHT {$$=token::ARITH_RIGHT;}
    | '&' {$$='&';}
    | '^' {$$='^';}
    | '|' {$$='|';} 
    ;
    

conditional
    : /* expression 判断的条件 */
      expression_rvalue  {$$ = $1; }
    | expression_rvalue comparison expression_rvalue {
            $$ = MALLOC(e2::CompOperator,$1,$2,$3, code_line, ctx.path() ); 
         }    
    | expression_rvalue logical expression_rvalue {
            $$ = MALLOC(e2::BinaryOperator,$1,$2,$3, code_line, ctx.path()); 
         }            
    | method_call {$$=$1;} 
    ;

expression_rvalue
    : /* expression 右则运算式 */
      primary_rvalue {$$ = $1;} 
    | '('  expression ')' {$$ = $2;}
    ;

comparison
    : /* expression a != b ; a < b ;  a >= b   */ 
      OP_LE {$$ = token::OP_LE;}
    | OP_GE {$$ = token::OP_GE;}
    | OP_EQ {$$ = token::OP_EQ;}
    | OP_NE {$$ = token::OP_NE;}
    | '<' {$$='<';}
    | '>' {$$='>';}
    ;

logical
    : /* expression !a ; a && b ; a || b  */
      LOGICAL_NOT {$$ = token::LOGICAL_NOT;}
    | LOGICAL_AND {$$ = token::LOGICAL_AND;} 
    | LOGICAL_OR {$$ = token::LOGICAL_OR;}
    ;

unary
    : /* ++a ; a-- */
      UNARY_INC {$$= token::UNARY_INC;}
    | UNARY_DEC {$$= token::UNARY_DEC;}
    ;
    
assignment
    : /* a = b;  a += b; a *= b */
      ASSIGN_EQ    {$$= token::ASSIGN_EQ;}
    | ASSIGN_MUL   {$$= token::ASSIGN_MUL;} 
    | ASSIGN_DIV   {$$= token::ASSIGN_DIV;}
    | ASSIGN_MOD   {$$= token::ASSIGN_MOD;}
    | ASSIGN_ADD   {$$= token::ASSIGN_ADD;}
    | ASSIGN_SUB   {$$= token::ASSIGN_SUB;}
    | ASSIGN_LEFT  {$$= token::ASSIGN_LEFT;}
    | ASSIGN_RIGHT {$$= token::ASSIGN_RIGHT;}
    | ASSIGN_AND   {$$= token::ASSIGN_AND;}
    | ASSIGN_XOR   {$$= token::ASSIGN_XOR;}
    | ASSIGN_OR    {$$= token::ASSIGN_OR;}
    ;

compound_statement
	: '{' '}'  {$$ = nullptr;}
	| '{' compound_block '}' {$$ = $2;}
	;

compound_block
     :/* blocks */ 
      block                     {$$ = MALLOC(e2::Block, "decl_vari", code_line, ctx.path() );$$->push_back($1);}  
    | statement                 {$$ = MALLOC(e2::Block, "decl_statement", code_line, ctx.path() ); $$->push_back($1);}
    | compound_block block      {$$ = $1; $1->push_back($2);}
    | compound_block statement  {$$ = $1; $1->push_back($2);}
    ;	

statement
	: /* statement compound_statement */ 	  
	  selection_statement {$$ = $1;}
	| iteration_statement {$$ = $1;}
	| jump_statement {$$ = $1;}
	;

labled_if
    : compound_statement 
        {
            $$ = MALLOC(e2::LabledBlock, "labled_if", code_line, ctx.path()); 
            $$->push($1, e2::Selection::_then);

        }
    | compound_statement ELSE compound_statement 
        {  

            $$ = MALLOC(e2::LabledBlock,"labled_if", code_line, ctx.path()); 
            $$->push($1, e2::Selection::_then);

            $$->push($3, e2::Selection::_else);
        }
    ;

labeled_switch
	: CASE primary_rvalue ':' compound_block
        {
            $$ = MALLOC(e2::LabledBlock, "labeled_switch", code_line, ctx.path());
            $$->push($2,$4, e2::Selection::_case) ;
        } 
    | labeled_switch CASE primary_rvalue ':' compound_block
        { 
            $$ = $1;  
            $1->push($3,$5, e2::Selection::_case) ;
            
        } 
	| labeled_switch  DEFAULT ':' compound_block
        { 
            $$ = $1;
            $1->push($4,e2::Selection::_default);
        }
	;

selection_statement
	: IF '(' conditional ')'  labled_if 
        {
            $$ = MALLOC(e2::IFStatement, $3,$5, code_line, ctx.path());
        }
    
	| SWITCH '(' conditional ')' '{' labeled_switch '}'
        {
            $$ = MALLOC(e2::SwitchStatement, $3,$6);
        }
	;

for_range
    : unary_val {$$ = $1;}
    | variable_val {$$ = $1;}
    ;

iteration_statement
	: WHILE '(' conditional ')' compound_statement 
        {   
            $$ = MALLOC(e2::IterStatement, $3,$5,e2::IterType::_while);
        }
	| DO compound_statement WHILE '(' conditional ')' ';' 
        {
            $$ = MALLOC(e2::IterStatement,$5,$2,e2::IterType::_do);
        }
	| FOR '(' variable_val ';' conditional ';' ')' compound_statement 
        {
            $$ = MALLOC(e2::IterStatement,$3,$5,$8,e2::IterType::_for);
        }
	| FOR '(' variable_val ';' conditional ';' for_range ')' compound_statement 
        {
            $$ = MALLOC(e2::IterStatement,$3,$5,$7,$9,e2::IterType::_forfull);
        }
	;

jump_statement
	:  
	  CONTINUE ';'           {$$ = nullptr;}
	| BREAK ';'             {$$ = MALLOC(e2::BreakStatement) ;}
    | RETURN ';' {$$ = MALLOC(e2::ReturnStatement, code_line, ctx.path());} 
	| RETURN primary_rvalue ';' {$$ = MALLOC(e2::ReturnStatement,$2, code_line, ctx.path());}
	;

parameter_list	
    :   /* 参数可以为空 */
      primary_rvalue {$$ = MALLOC(e2::ExpressionList);$$->push_back($1);}     
    | parameter_list ',' primary_rvalue {$$=$1;  $1->push_back($3);}     
    ;

function_parameter
    : '(' ')' {$$ = nullptr;}
    | '(' parameter_list ')' {$$ = $2;}
    ;

function_definition
    : FUNCTION IDENTIFIER function_parameter compound_statement {$$ = MALLOC(e2::FunctionDeclaration,$2, $3, $4);} 
    ;

method_call
    : /* method call */
     IDENTIFIER function_parameter {
            $$ = MALLOC(e2::MethodCall, $1, $2, code_line, ctx.path());
        } 
    ;

extern_call
    : EXTERN IDENTIFIER  IDENTIFIER '(' IDENTIFIER primary_rvalue ')' { 
        e2::ExpressionList *el = MALLOC(e2::ExpressionList); 
         el->push_back($6); 
         $$ = MALLOC(e2::ExternDeclaration,$3,el);}
    ;

union_statement
    : ';' {$$ = nullptr; }	
    | variable_val ';' {$$ = $1;}
    ;

union_list
    : union_statement               {$$ = MALLOC(e2::Block, "union_list", code_line, ctx.path() ); $$->push_back($1);}
    | union_list union_statement    {$$ = $1; $1->push_back($2);}
    | union_definition              {$$ = MALLOC(e2::Block, "union_def", code_line, ctx.path() ); $$->push_back($1);}
    | union_list union_definition   {$$ = $1; $1->push_back($2);} 
    ;

union_definition
    : UNION IDENTIFIER '{' union_list '}' {  $$ = MALLOC(e2::UnionDeclaration,$2,$4);} 
    ;

primary_rvalue 
    : /* 变量名, 数字 */
      identifier_list {$$ = $1;} 
    | CONSTANT  {$$ = MALLOC(e2::Number,$1);}
    | '-' CONSTANT  {$$ = MALLOC(e2::Number,$2, true); }
    | FCONSTANT  {$$ = MALLOC(e2::Number,$1);}    
    | '-' FCONSTANT  {$$ = MALLOC(e2::Number,$2, true);}    
    | STRING_LITERAL {$$ = MALLOC(e2::StrObj, $1, code_line, ctx.path()); }
    ;

identifier_list
    : IDENTIFIER  {
                $$ = MALLOC(e2::Identifier, $1, e2::IDType::_normal);
                $$->codeLine(code_line);
                $$->codePath(ctx.path());
                } 
    | identifier_list '.' IDENTIFIER {
                $$=$1;  
                $1->push_back($3);
                $1->idType(e2::IDType::_global);
                $1->codeLine(code_line);
                $1->codePath(ctx.path());

                }
    ;

%%

/**
* 以后再优化
*/



void yy::Parser::error(const yy::location& l, const std::string& m)
{
    ctx.current_file();
    std::cout<<"script error line: "<< (code_line - 1)<< ".  chars: "<< l<< ". msg: "<< m<< std::endl;
}


