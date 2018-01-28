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

var          return tVAR;
while        return tWHILE;
boolean      return tBOOLEAN;
float        return tFLOAT;
if           return tIF;
else         return tELSE;
TRUE         return tTRUE;
FALSE        return tFALSE;
int          return tINT;
print        return tPRINT;
string       return tSTRING;
read         return tREAD;


"+"         return '+';
"-"         return '-';
"*"         return '*';
"/"         return '/';
"("         return '(';
")"         return ')';
":"         return ':';
";"         return ';';
"="         return '=';
"!"         return '!';

"=="        return "==";
"!="        return "!=";
"&&"        return "&&";
"||"        return "||";

{INT} {
      yylval.int_val = atoi(yytext);
	    return tINTVAL;
}

{INT}"."{DIGIT}+	{
      yylval.float_val = atof(yytext);
			return tFLOATVAL;
}

[a-zA-Z_][a-zA-Z0-9_]* {
      yylval.string_val = strdup(yytext);
	    return tIDENTIFIER;
}

"//"[^\n]*"\n"	/* comment */

"\""({ALPHA}|{DIGIT}|{SPACE}|{SYMBOL}|{ESCAPE})*"\"" {
      yylval.string_val = strdup(yytext);
      return tSTRINGVAL;
}


. 	    { fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%
