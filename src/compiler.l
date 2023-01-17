%{
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "compiler.tab.h"
%}
%%
define  return DEFINE;
array   return ARRAY;
while   return WHILE;
if      return IF;
else    return ELSE;
and     return AND;
or      return OR;
not     return NOT;
";"     return SEMICORON;
"["     return LBRACKET;
"]"     return RBRACKET;
"("     return LPAREN;
")"     return RPAREN;
"{"     return LBRACE;
"}"     return RBRACE;
"="     return ASSIGN;
"+"     return ADD;
"-"     return SUB;
"*"     return MUL;
"/"     return DIV;
"%"     return MOD;
"=="    return EQUAL;
"!="    return NEQ;
"<"     return LT;
">"     return GT;
"<="    return LEQ;
">="    return GEQ;
[a-zA-Z][a-zA-Z0-9]*  {
  char *varName = malloc(sizeof(char) * (yyleng+1));
  strncpy(varName, yytext, yyleng);
  varName[yyleng] = '\0';
  yylval.sval = varName;
  return IDENT;
}
[0-9][0-9]*   { yylval.ival=atoi(yytext); return NUMBER; }
[\n\t ] ;
#.*$    ; /* comments */
%%
