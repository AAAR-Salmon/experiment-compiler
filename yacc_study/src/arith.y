%{
#include <stdio.h>
#include "arith.tab.h"
extern int yylex();
extern int yyerror();
%}
%token NUMBER PLUS MINUS MULT DIV
%%
expression : series  { printf("= %d\n", $1); }
           ;

series : series '+' term  { $$ = $1 + $3; }
       | series '-' term  { $$ = $1 - $3; }
       | term             { $$ = $1; }
       ;

term : term '*' factor  { $$ = $1 * $3; }
     | term '/' factor  { $$ = $1 / $3; }
     | factor           { $$ = $1; }
     ;

factor : '(' series ')'   { $$ = $2; }
       | NUMBER           { $$ = $1; }
       ;
%%
int main(void) {
  if (yyparse()) {
    fprintf(stderr, "Error\n");
    return 1;
  }
  return 0;
}
