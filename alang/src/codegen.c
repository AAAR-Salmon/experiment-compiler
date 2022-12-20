#include "ast.h"
#include "symbol_table.h"
#include <stdio.h>

SymbolTable *symbolTable;

void _codegen(FILE *fout, AstNode *root) {
  AstNode *n;
  switch (root->nodeType) {
  case AST_DECL_VAR:
    break;
  case AST_DECL_ARRAY:
    break;
  case AST_ASSIGN_STMT:
    break;
  case AST_REFERENCE:
    break;
  case AST_WHILE:
    break;
  case AST_IF:
    break;
  case AST_IF_ELSE:
    break;
  case AST_COND_EXPR:
    break;
  case AST_IDENT:
    break;
  case AST_ADD:
    break;
  case AST_SUB:
    break;
  case AST_MUL:
    break;
  case AST_DIV:
    break;
  case AST_NUMBER:
    break;
  case AST_EQUAL:
    break;
  case AST_NEQ:
    break;
  case AST_LT:
    break;
  case AST_LEQ:
    break;
  case AST_GT:
    break;
  case AST_GEQ:
    break;
  default:
    n = root->child;
    while (n != NULL) {
      _codegen(fout, n);
      n = n->brother;
    }
    break;
  }
}

void codegen(FILE *fout, AstNode *root) {
  symbolTable = createSymbolTable();
  _codegen(fout, root);
}
