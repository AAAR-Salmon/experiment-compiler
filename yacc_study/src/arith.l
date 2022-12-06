%{
#include <stdlib.h>
#define YYSTYPE double
#include "arith.tab.h"
extern double yylval;
%}
%%
([0-9]+\.?)|([0-9]*\.[0-9]+)  { yylval = atof(yytext); return NUMBER; }
[\t ]   ;
\n      return 0;
.       return yytext[0];
%%
