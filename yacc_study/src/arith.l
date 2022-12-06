%{
#include <stdlib.h>
#include "arith.tab.h"
%}
%%
([0-9]+\.?)|([0-9]*\.[0-9]+)  { yylval.dval = atof(yytext); return NUMBER; }
[a-z]   { yylval.var_idx = yytext[0] - 'a'; return VAR; }
[\t ]   ;
"$"     return 0;
\n      |
.       return yytext[0];
%%
