#include "ast_debug.h"
#include "ast.h"
#include <stdio.h>

void printNode(AstNode *n, int depth) {
  static char ws[100];
  int i;
  for (i = 0; i < depth; i++) {
    ws[i] = ' ';
  }
  ws[i] = '\0';

  printf(
      "%s{ nodetype: %s, ivalue: %d, svalue: %s }\n",
      ws,
      nodeTypeToString(n->nodeType),
      n->ivalue,
      n->svalue
      );
}

void printTree(AstNode *root, int depth) {
  if (root == NULL) return;

  AstNode *child = root->child;
  if (child == NULL) {
    printNode(root, depth);
    return;
  }

  printNode(root, depth);
  while (child != NULL) {
    printTree(child, depth + 1);
    child = child->brother;
  }
}

char *nodeTypeToString(enum AstNodeType t) {
  switch (t) {
    case AST_PROGRAM:       return "AST_PROGRAM";
    case AST_DECLS:         return "AST_DECLS";
    case AST_DECL_VAR:      return "AST_DECL_VAR";
    case AST_DECL_ARRAY:    return "AST_DECL_ARRAY";
    case AST_STMTS:         return "AST_STMTS";
    case AST_STMT:          return "AST_STMT";
    case AST_ASSIGN_STMT:   return "AST_ASSIGN_STMT";
    case AST_REFERENCE:     return "AST_REFERENCE";
    case AST_WHILE:         return "AST_WHILE";
    case AST_IF:            return "AST_IF";
    case AST_IF_ELSE:       return "AST_IF_ELSE";
    case AST_IDENT:         return "AST_IDENT";
    case AST_AND:           return "AST_AND";
    case AST_OR:            return "AST_OR";
    case AST_NOT:           return "AST_NOT";
    case AST_EQ:            return "AST_EQ";
    case AST_NEQ:           return "AST_NEQ";
    case AST_LT:            return "AST_LT";
    case AST_LEQ:           return "AST_LEQ";
    case AST_GT:            return "AST_GT";
    case AST_GEQ:           return "AST_GEQ";
    case AST_ADD:           return "AST_ADD";
    case AST_SUB:           return "AST_SUB";
    case AST_MUL:           return "AST_MUL";
    case AST_DIV:           return "AST_DIV";
    case AST_MOD:           return "AST_MOD";
    case AST_NUMBER:        return "AST_NUMBER";
    default:                return "!!UNKNOWN!!";
  }
}
