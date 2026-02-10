D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*


%{
    /* include */
    #include <iostream>
    #include <string>

    #include<stdio.h>
    #include "e2_bison.hpp"
   
    int code_line=1;

#define YY_DECL yy::Parser::symbol_type yylex(yyscan_t yyscanner, yy::location& loc, class e2::ParserCtx& ctx)

#define YY_USER_ACTION loc.lines(yyleng);
//#define YY_USER_ACTION loc.first_line = loc.last_line = yylineno;

#define yyterminate() return Parser::make_END(loc)

using namespace yy;
typedef yy::Parser::token token;
typedef yy::Parser::token_type token_type;

%}

%option reentrant noyywrap nounput  batch debug noinput
/* %option debug verbose */


%%

%{
	loc.step();
%}

"extern"        {return Parser::make_EXTERN(loc);}
"namespace"		{return Parser::make_NAMESPACE(loc);}
"union"			{return Parser::make_UNION(loc);}
"func"			{return Parser::make_FUNCTION(loc);}
"import"		{return Parser::make_IMPORT(loc);}
"this"          {return Parser::make_THIS(loc);}  
"self"          {return Parser::make_SELF(loc);}

"switch"		{return  Parser::make_SWITCH(loc);}
"case"			{return Parser::make_CASE(loc);}	
"default"		{return Parser::make_DEFAULT(loc);}

"if"			{return Parser::make_IF(loc);}
"else"			{return Parser::make_ELSE(loc);}

"for"			{return Parser::make_FOR(loc);}
"do"			{return Parser::make_DO(loc);}
"while"			{return Parser::make_WHILE(loc);}

"continue"		{return Parser::make_CONTINUE(loc);}
"break"			{return Parser::make_BREAK(loc);}
"return"		{return Parser::make_RETURN(loc);}

0[xX]{H}+{IS}?		    { return Parser::make_CONSTANT(std::stod(yytext,0), loc);}
0{D}+{IS}?		        { return Parser::make_CONSTANT(std::stod(yytext,0), loc);}
{D}+{IS}?		        { return Parser::make_CONSTANT(std::stod(yytext,0), loc);}
L?'(\\.|[^\\'])+'	    { return Parser::make_CONSTANT(std::stod(yytext,0), loc);}

{D}+{E}{FS}?		    { return Parser::make_CONSTANT(std::stod(yytext,0), loc);}
{D}*"."{D}+({E})?{FS}?	{ return Parser::make_FCONSTANT(std::stod(yytext,0), loc);}
{D}+"."{D}*({E})?{FS}?	{ return Parser::make_FCONSTANT(std::stod(yytext,0), loc);}

{L}({L}|{D})*		{ 
            return Parser::make_IDENTIFIER(yytext, loc);
}

L?\"(\\.|[^\\"])*\"	    { return Parser::make_STRING_LITERAL(yytext, loc);}

"::"		{ return Parser::symbol_type( token::NAMESPACE_ATTR, loc);}

"++"		{ return Parser::symbol_type( token::UNARY_INC, loc);}
"--"		{ return Parser::symbol_type( token::UNARY_DEC, loc);}

">>="		{ return Parser::symbol_type( token::ASSIGN_RIGHT, loc);}
"<<="		{ return Parser::symbol_type( token::ASSIGN_LEFT, loc);}
"+="		{ return Parser::symbol_type( token::ASSIGN_ADD, loc);}
"-="		{ return Parser::symbol_type( token::ASSIGN_SUB, loc);}
"*="		{ return Parser::symbol_type( token::ASSIGN_MUL, loc);}
"/="		{ return Parser::symbol_type( token::ASSIGN_DIV, loc);}
"%="		{ return Parser::symbol_type( token::ASSIGN_MOD, loc);}
"&="		{ return Parser::symbol_type( token::ASSIGN_AND, loc);}
"^="		{ return Parser::symbol_type( token::ASSIGN_XOR, loc);}
"|="		{ return Parser::symbol_type( token::ASSIGN_OR, loc);}
"="		    { return Parser::symbol_type( token::ASSIGN_EQ,loc);}

"&&"		{ return Parser::symbol_type( token::LOGICAL_AND, loc);}
"||"		{ return Parser::symbol_type( token::LOGICAL_OR, loc);}
"!"		    { return Parser::symbol_type( token::LOGICAL_NOT,loc);}

"<="		{ return Parser::symbol_type( token::OP_LE, loc);}
">="		{ return Parser::symbol_type( token::OP_GE, loc);}
"=="		{ return Parser::symbol_type( token::OP_EQ, loc);}
"!="		{ return Parser::symbol_type( token::OP_NE, loc);}
"<"			{ return Parser::symbol_type( token_type('<'),loc);}
">"			{ return Parser::symbol_type( token_type('>'),loc);}

">>"		{ return Parser::symbol_type( token::ARITH_RIGHT, loc);}
"<<"		{ return Parser::symbol_type( token::ARITH_LEFT, loc);}
"&"			{ return Parser::symbol_type( token_type('&'),loc);}
"-"			{ return Parser::symbol_type( token_type('-'),loc);}
"+"			{ return Parser::symbol_type( token_type('+'),loc);}
"*"			{ return Parser::symbol_type( token_type('*'),loc);}
"/"			{ return Parser::symbol_type( token_type('/'),loc);}
"%"			{ return Parser::symbol_type( token_type('%'),loc);}
"^"			{ return Parser::symbol_type( token_type('^'),loc);}
"|"			{ return Parser::symbol_type( token_type('|'),loc);}

"?"			{ return Parser::symbol_type( token_type('?'),loc);}
"~"			{ return Parser::symbol_type( token_type('~'),loc);}
":"			{ return Parser::symbol_type( token_type(':'),loc);}

","			{ return Parser::symbol_type( token_type(','),loc);}
"."			{ return Parser::symbol_type( token_type('.'),loc);}
";"			{ return Parser::symbol_type( token_type(';'),loc);}

"("			{ return Parser::symbol_type( token_type('('),loc);}
")"			{ return Parser::symbol_type( token_type(')'),loc);}

("{")		{ return Parser::symbol_type( token_type('{'),loc);}
("}")		{ return Parser::symbol_type( token_type('}'),loc);}

"//"(\\.|[^\n])*[\n]  {  /* comments */ } 
#.*         { /* comments */ }

(<.*\.e2>)      { return Parser::make_IMPORT_LITERAL(yytext, loc);}

(<.*>::)      { return Parser::make_NSFUNC_CALL(yytext, loc);}

[ \v\f\t]	    {  }
[\n]      { code_line++; }

.			{ /* ignore bad characters */ }

%%


/*
* 代表 val 前 10 个值的相加，相减。。。
* 第二个版本再开始这些的语法吧
// val[10]+;  val[10]-;  val[10]*;
//(\[{D}\])       { return Parser::make_ARRAY(yytext, loc);  }
*/

//extern "C" {

/* int yywrap(void) */
/* { */
/*     return 1; */
/* } */

/* int column = 0; */

/* void count(void) */
/* { */
/* 	int i; */

/* 	for (i = 0; yytext[i] != '\0'; i++) */
/* 		if (yytext[i] == '\n') */
/* 			column = 0; */
/* 		else if (yytext[i] == '\t') */
/* 			column += 8 - (column % 8;*/
/* 		else */
/* 			column++; */

/* 	//ECHO; */
	
/* } */



//int check_type()
//{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return TYPE_NAME);
*
*	return IDENTIFIER);
*/

/*
*	it actually will only return IDENTIFIER
*/

//	return IDENTIFIER);
//}
//}
