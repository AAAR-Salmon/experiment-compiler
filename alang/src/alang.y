%{
#include "ast.h"
#include "alang.tab.h"
extern int yylex();
extern int yyerror();
%}

%union {
  AstNode *ast;
  char *sval;
  int ival;
}

%token DEFINE ARRAY WHILE IF ELSE
%token SEMICORON
%token LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE
%token ASSIGN ADD SUB MUL DIV
%token EQUAL LT GT LEQ GEQ
%token<sval> IDENT
%token<ival> NUMBER
%%
program : declarations statements
        ;

declarations : decl_stmt declarations
             | decl_stmt
             ;

decl_stmt : DEFINE IDENT SEMICORON
          | ARRAY IDENT LBRACKET NUMBER RBRACKET SEMICORON
          ;

statements : statement statements
           | statement
           ;

statement : expression_stmt
          | assign_stmt
          | loop_stmt
          | branch_stmt
          ;

assign_stmt : IDENT ASSIGN expression SEMICORON
            | IDENT LBRACKET expression RBRACKET ASSIGN expression SEMICORON
            ;

expression_stmt : expression SEMICORON
                ;

expression : expression ADD term
           | expression SUB term
           | term
           ;

term : term MUL factor
     | term DIV factor
     | factor
     ;

factor : IDENT
       | NUMBER
       | IDENT LBRACKET expression RBRACKET
       | LPAREN expression RPAREN
       ;

loop_stmt : WHILE LPAREN cond_expr RPAREN LBRACE statements RBRACE
          ;

branch_stmt : IF LPAREN cond_expr RPAREN LBRACE statements RBRACE
            | IF LPAREN cond_expr RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE
            ;

cond_expr : expression EQUAL expression
          | expression LT expression
          | expression GT expression
          | expression LEQ expression
          | expression GEQ expression
          ;
%%
int main(void) {
  if (yyparse()) {
    yyerror();
    return 1;
  }
  return 0;
}
