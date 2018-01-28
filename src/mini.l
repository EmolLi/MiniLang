/* The first section of a flex file contains:
 *    1. A code section for includes and other arbitrary C code. Copied to the scanner verbatim
 *    2. Helper definitions for regexes
 *    3. Scanner options
 */

/* Code section */
%{
#include <stdio.h>
#include <string.h>

#include "parser.tab.h"
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}

/* Helper definitions */
DIGIT [0-9]
INT 0|([1-9]{DIGIT}*)
SPACE [ \t]+
ALPHA [a-zA-Z]
SYMBOL "~"|"@"|"#"|"%"|"^"|"&"|"*"|"-"|"+"|"/"|"`"|"<"|">"|"="|"_"|"|"|"'"|"."|","|";"|":"|"!"|"?"|"{"|"}"|"["|"]"|"("|")"
ESCAPE \\a|\\b|\\f|\\n|\\r|\\t|\\v|\\\"|\\\\

/* Scanner options, line number generation */
%option yylineno
%option noinput
%option nounput

/* The second section of a flex file contains the regular expressions, using helper definitions
 * where appropriate ({<helper name>}). Sections in flex are divided by %%.
 *
 * Each line contains the regex, followed by the scanner action. Actions are executed when
 * a token is matched. A missing action is treated as a NOP.
 */

/* Note the use of 3 keywords:
 *    - yyleng: Length of the scanned token
 *    - yytext: Matched text
 *    - yylineno: Convenience variable for the line number provided by %option yylineno
 */
%%
[\r\n]+
{SPACE}      /* ignore white space*/

var         {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tVAR;
            }
while       {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tWHILE;
            }
boolean     {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tBOOLEAN;
            }
float       {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tFLOAT;
            }
if          {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tIF;
            }
else        {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tELSE;
            }
TRUE        {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tTRUE;
            }
FALSE       {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tFALSE;
            }
int         {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tINT;
            }
print       {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tPRINT;
            }
string      {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tSTRING;
            }
read        {
                if (mode == tokens) printf( "Reserved word: %s\n", yytext );
                return tREAD;
            }


"+"         {
                if (mode == tokens) printf( "%s\n", yytext);
                return '+';
            }
"-"         {
                if (mode == tokens) printf( "%s\n", yytext);
                return '-';
            }
"*"         {
                if (mode == tokens) printf( "%s\n", yytext);
                return '*';
            }
"/"         {
                if (mode == tokens) printf( "%s\n", yytext);
                return '/';
            }
"("         {
                if (mode == tokens) printf( "%s\n", yytext);
                return '(';
            }
")"         {
                if (mode == tokens) printf( "%s\n", yytext);
                return ')';
            }
":"         {
                if (mode == tokens) printf( "%s\n", yytext);
                return ':';
            }
";"         {
                if (mode == tokens) printf( "%s\n", yytext);
                return ';';
            }
"="         {
                if (mode == tokens) printf( "%s\n", yytext);
                return '=';
            }
"!"         {
                if (mode == tokens) printf( "%s\n", yytext);
                return '!';
            }

"=="        {
                if (mode == tokens) printf( "%s\n", yytext);
                return "==";
            }
"!="        {
                if (mode == tokens) printf( "%s\n", yytext);
                return "!=";
            }
"&&"        {
                if (mode == tokens) printf( "%s\n", yytext);
                return "&&";
            }
"||"        {
                if (mode == tokens) printf( "%s\n", yytext);
                return "||";
            }

{INT}       {
	            if (mode == tokens) printf ("Integer constant: %s\n", yytext);
                yylval.int_val = atoi(yytext);
	            return tINTVAL;
            }

{INT}"."{DIGIT}+	{
                if (mode == tokens) printf ("Float constant: %s\n", yytext);
                yylval.float_val = atof(yytext);
			    return tFLOATVAL;
            }

[a-zA-Z_][a-zA-Z0-9_]* {
                if (mode == tokens) printf ("Identifier: %s\n", yytext);
                yylval.string_val = strdup(yytext);
	            return tIDENTIFIER;
            }

"//"[^\n]*"\n"	/* comment */

"\""({ALPHA}|{DIGIT}|{SPACE}|{SYMBOL}|{ESCAPE})*"\"" {
                if (mode == tokens) printf("String: %s\n", yytext);
                yylval.string_val = strdup(yytext);
                return tSTRINGVAL;
            }


. 	         { fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%
