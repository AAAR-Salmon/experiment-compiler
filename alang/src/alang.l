%{
#include "alang.tab.h"
%}
%%
define  return DEFINE;
array   return ARRAY;
while   return WHILE;
if      return IF;
else    return ELSE;
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
"=="    return EQUAL;
"<"     return LT;
">"     return GT;
[a-zA-Z][a-zA-Z0-9]*  return IDENT;
[0-9][0-9]*           return NUMBER;
[\n\t ] ;
%%