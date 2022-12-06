%{
#include <stdio.h>
#include "arith.tab.h"
extern int yylex();
extern int yyerror();

double var_table[26];
%}

%union {
  double dval;
  int var_idx;
}
%token <dval> NUMBER
%token <var_idx> VAR
%type <dval> expression term factor
%%
statement_list : statement_list statement '\n'
               | statement '\n'
               ;

statement : VAR '=' expression
            { var_table[$1] = $3; printf("%c = %f\n", 'a' + $1, $3); }
          | expression
            { printf("@ = %f\n", $1); }
          ;

expression : expression '+' term  { $$ = $1 + $3; }
       | expression '-' term      { $$ = $1 - $3; }
       | term                     { $$ = $1; }
       ;

term : term '*' factor  { $$ = $1 * $3; }
     | term '/' factor  { $$ = $1 / $3; }
     | factor           { $$ = $1; }
     ;

factor : '(' expression ')'   { $$ = $2; }
       | NUMBER               { $$ = $1; }
       | VAR                  { $$ = var_table[$1]; }
       ;
%%
int main(void) {
  if (yyparse()) {
    yyerror();
    return 1;
  }
  return 0;
}
