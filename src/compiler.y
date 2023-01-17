%{
#include "ast.h"
#include "compiler.tab.h"
extern int yylex();
extern int yyerror();

AstNode *root;
%}

%union {
  AstNode *ast;
  char *sval;
  int ival;
}

%token DEFINE ARRAY WHILE IF ELSE
%token SEMICORON
%token LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE
%token ASSIGN AND OR NOT EQUAL NEQ LT GT LEQ GEQ
%token ADD SUB MUL DIV MOD
%token<sval> IDENT
%token<ival> NUMBER

%type<ast> program declarations decl_stmt statements statement
%type<ast> assign_stmt loop_stmt branch_stmt
%type<ast> reference expression conditional_expr additional_expr multiplicational_expr primitive_expr
%%
program:
  declarations statements {
    root = createVoidNode(AST_PROGRAM);
    addChild(root, $1);
    addChild(root, $2);
  }
;

declarations:
  decl_stmt declarations {
    AstNode *declsNode = createVoidNode(AST_DECLS);
    addChild(declsNode, $1);
    mergeChildren(declsNode, $2);
    $$ = declsNode;
  } | decl_stmt {
    AstNode *declsNode = createVoidNode(AST_DECLS);
    addChild(declsNode, $1);
    $$ = declsNode;
  }
;

decl_stmt:
  DEFINE IDENT SEMICORON {
    AstNode *declNode = createVoidNode(AST_DECL_VAR);
    AstNode *identNode = createStrNode(AST_IDENT, $2);
    addChild(declNode, identNode);
    $$ = declNode;
  } | ARRAY IDENT LBRACKET NUMBER RBRACKET SEMICORON {
    AstNode *declNode = createVoidNode(AST_DECL_ARRAY);
    AstNode *identNode = createStrNode(AST_IDENT, $2);
    AstNode *dimNode = createIntNode(AST_NUMBER, $4);
    addChild(declNode, identNode);
    addChild(declNode, dimNode);
    $$ = declNode;
  }
;

statements:
  statement statements {
    AstNode *stmtsNode = createVoidNode(AST_STMTS);
    addChild(stmtsNode, $1);
    mergeChildren(stmtsNode, $2);
    $$ = stmtsNode;
  } | statement {
    AstNode *stmtsNode = createVoidNode(AST_STMTS);
    addChild(stmtsNode, $1);
    $$ = stmtsNode;
  }
;

statement:
  assign_stmt
  | loop_stmt
  | branch_stmt
;

assign_stmt:
  reference ASSIGN expression SEMICORON {
    AstNode *assignStmtNode = createVoidNode(AST_ASSIGN_STMT);
    addChild(assignStmtNode, $1);
    addChild(assignStmtNode, $3);
    $$ = assignStmtNode;
  }
;

reference:
  IDENT {
    AstNode *referenceNode = createVoidNode(AST_REFERENCE);
    AstNode *identNode = createStrNode(AST_IDENT, $1);
    addChild(referenceNode, identNode);
    $$ = referenceNode;
  } | IDENT LBRACKET expression RBRACKET {
    AstNode *referenceNode = createVoidNode(AST_REFERENCE);
    AstNode *identNode = createStrNode(AST_IDENT, $1);
    addChild(referenceNode, identNode);
    addChild(referenceNode, $3);
    $$ = referenceNode;
  }
;

expression:
  expression AND conditional_expr {
    AstNode *andNode = createVoidNode(AST_AND);
    addChild(andNode, $1);
    addChild(andNode, $3);
    $$ = andNode;
  } | expression OR conditional_expr {
    AstNode *orNode = createVoidNode(AST_OR);
    addChild(orNode, $1);
    addChild(orNode, $3);
    $$ = orNode;
  } | NOT conditional_expr {
    AstNode *notNode = createVoidNode(AST_NOT);
    addChild(notNode, $2);
    $$ = notNode;
  } | conditional_expr {
    $$ = $1;
  }
;

conditional_expr:
  additional_expr EQUAL additional_expr {
    AstNode *equalNode = createVoidNode(AST_EQ);
    addChild(equalNode, $1);
    addChild(equalNode, $3);
    $$ = equalNode;
  } | additional_expr NEQ additional_expr {
    AstNode *neqNode = createVoidNode(AST_NEQ);
    addChild(neqNode, $1);
    addChild(neqNode, $3);
    $$ = neqNode;
  } | additional_expr LT additional_expr {
    AstNode *ltNode = createVoidNode(AST_LT);
    addChild(ltNode, $1);
    addChild(ltNode, $3);
    $$ = ltNode;
  } | additional_expr LEQ additional_expr {
    AstNode *leqNode = createVoidNode(AST_LEQ);
    addChild(leqNode, $1);
    addChild(leqNode, $3);
    $$ = leqNode;
  } | additional_expr GT additional_expr {
    AstNode *gtNode = createVoidNode(AST_GT);
    addChild(gtNode, $1);
    addChild(gtNode, $3);
    $$ = gtNode;
  } | additional_expr GEQ additional_expr {
    AstNode *geqNode = createVoidNode(AST_GEQ);
    addChild(geqNode, $1);
    addChild(geqNode, $3);
    $$ = geqNode;
  } | additional_expr {
    $$ = $1;
  }
;

additional_expr:
  additional_expr ADD multiplicational_expr {
    AstNode *addNode = createVoidNode(AST_ADD);
    addChild(addNode, $1);
    addChild(addNode, $3);
    $$ = addNode;
  } | additional_expr SUB multiplicational_expr {
    AstNode *subNode = createVoidNode(AST_SUB);
    addChild(subNode, $1);
    addChild(subNode, $3);
    $$ = subNode;
  } | multiplicational_expr {
    $$ = $1;
  }
;

multiplicational_expr:
  multiplicational_expr MUL primitive_expr {
    AstNode *mulNode = createVoidNode(AST_MUL);
    addChild(mulNode, $1);
    addChild(mulNode, $3);
    $$ = mulNode;
  } | multiplicational_expr DIV primitive_expr {
    AstNode *divNode = createVoidNode(AST_DIV);
    addChild(divNode, $1);
    addChild(divNode, $3);
    $$ = divNode;
  } | multiplicational_expr MOD primitive_expr {
    AstNode *modNode = createVoidNode(AST_MOD);
    addChild(modNode, $1);
    addChild(modNode, $3);
    $$ = modNode;
  } | primitive_expr {
    $$ = $1;
  }
;

primitive_expr:
  reference {
    $$ = $1;
  } | NUMBER {
    AstNode *numberNode = createIntNode(AST_NUMBER, $1);
    $$ = numberNode;
  } | LPAREN expression RPAREN {
    $$ = $2;
  }
;

loop_stmt:
  WHILE LPAREN expression RPAREN LBRACE statements RBRACE {
    AstNode *whileNode = createVoidNode(AST_WHILE);
    addChild(whileNode, $3);
    addChild(whileNode, $6);
    $$ = whileNode;
  }
;

branch_stmt:
  IF LPAREN expression RPAREN LBRACE statements RBRACE {
    AstNode *ifNode = createVoidNode(AST_IF);
    addChild(ifNode, $3);
    addChild(ifNode, $6);
    $$ = ifNode;
  } | IF LPAREN expression RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE {
    AstNode *ifElseNode = createVoidNode(AST_IF_ELSE);
    addChild(ifElseNode, $3);
    addChild(ifElseNode, $6);
    addChild(ifElseNode, $10);
    $$ = ifElseNode;
  }
;
%%
#include <stdio.h>
#include "ast_debug.h"
#include "codegen.h"

extern FILE *fp_out;

int main(void) {
  if (yyparse()) {
    yyerror();
    return 1;
  }

  fp_out = stdout;

  codegenProgram(root);
  return 0;
}
