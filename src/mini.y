/* The first section of a bison file contains:
 *    1. A code section for includes and other arbitrary C code. Copied to the parser verbatim
 *    2. Definition of the yylval union
 *    3. Definition of the tokens
 *    4. Precedence directives
 *    5. The start token
 *    6. Parser options
 */

/* Code section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Reference to the line number generated by the scanner
extern int yylineno;
extern Node *root;
extern char* mode;

// Reference to the yylex function to quiet a compiler warning
int yylex();

// The yyerror function is called on any syntax error. When using %error-verbose, this function
// takes a single argument (a string) which contains a detailed explanation of the error.
// Otherwise it takes no arguments and it is up to the user to format the error using a minimal
// description provided in yytext.
void yyerror(const char *s) {
	if (strcmp(mode, "parse") == 0){
		fprintf(stderr, "Error: (line %d) %s\n", yylineno, s);
		exit(1);
	}
}
%}


%code requires
{
	#include "tree.h"
}


/* The union directive defines the yylval union used for associating (a) terminals (tokens)
 * returned by flex with additional scanning data (such as identifier/constant values); and
 * optionally (b) non-terminals (variables in productions) with AST information if any.
 */
%union {
	int int_val;
	double float_val;
	char *string_val;
	Node *node;
}

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can eb defined per directive by using a list
 * of identifiers separated by spaces.
 */
%token <int_val> tINTVAL
%token <float_val> tFLOATVAL
%token <string_val> tIDENTIFIER
%token <string_val> tSTRINGVAL

/* token without semantic values
 * most are reserved words
 */
%token tVAR
%token tINT
%token tBOOLEAN
%token tFLOAT
%token tSTRING

%token tWHILE
%token tIF
%token tELSE

%token tTRUE
%token tFALSE

%token tPRINT
%token tREAD




/* Precedence directives resolve grammar ambiguities by breaking ties between shift/reduce
 * operations. Tokens are grouped into precendence levels, with lower precedence coming first
 * and then higher precedence in later directives. Tokens specified in the same directive have
 * the same precedence. Ties at the same level are broken using either %left or %right, which
 * denote left-associative and right-associative respectively.
 */

%token tEQUAL "=="
%token tNOTEQUAL "!="
%token tAND	"&&"
%token tOR "||"
%left '+' '-'
%left '*' '/'

%type <node> program
%type <node> declarations
%type <node> declaration
%type <node> statements
%type <node> statement
%type <node> else_statement
%type <node> expression

%type <node> var_type

/* Start token (by default if this is missing it takes the first production */
%start program

/* Generate the yylloc structure used for storing line numbers with tokens */
%locations
/* Generate detailed error messages */
%error-verbose

/* The second section of a bison file contains the productions. Note that rules with the
 * same LHS may be joined together and separated with a pipe.
 */
%%

program: declarations statements
	;

/* A variable declaration consists of the keyword var, an identifier, the variable type, and an initial
value (may be compound, by compound it means valid expression). The identifier and type are separated by a colon, and the declaration
ends with a semicolon. */
declarations:	/* empty */
	| declarations declaration
	;

declaration: tVAR tIDENTIFIER ':' var_type '='	expression	';'	/* always use left recursion for Bison*/
	;

var_type:	tINT
	| tBOOLEAN
	| tFLOAT
	| tSTRING
	;


statements: /* empty */
	| statements statement
	;

statement:	tREAD tIDENTIFIER ';'
	| tPRINT expression ';'
	| tIDENTIFIER '=' expression ';'
	| tIF expression '{' statements '}' else_statement
	| tWHILE expression '{' statements '}'
	;

else_statement: /* empty */
	| tELSE '{' statements '}'
	;

expression:	tINTVAL
	| tFLOATVAL
	| tSTRINGVAL
	| tIDENTIFIER
	| '-' expression
	| '!' expression
	| expression '*' expression
	| expression '/' expression
	| expression '+' expression
	| expression '-' expression
	| expression "==" expression
	| expression "!=" expression
	| expression "&&" expression
	| expression "||" expression
	| '(' expression ')'
	;

%%
