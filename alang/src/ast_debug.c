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
    case AST_PROGRAM:       return "PROGRAM";
    case AST_DECLS:         return "DECLS";
    case AST_DECL_VAR:      return "DECL_VAR";
    case AST_DECL_ARRAY:    return "DECL_ARRAY";
    case AST_STMTS:         return "STMTS";
    case AST_STMT:          return "STMT";
    case AST_ASSIGN_STMT:   return "ASSIGN_STMT";
    case AST_EXPR_STMT:     return "EXPR_STMT";
    case AST_EXPR:          return "EXPR";
    case AST_TERM:          return "TERM";
    case AST_FACTOR:        return "FACTOR";
    case AST_LOOP_STMT:     return "LOOP_STMT";
    case AST_BRANCH_STMT:   return "BRANCH_STMT";
    case AST_COND_EXPR:     return "COND_EXPR";
    case AST_IDENT:         return "IDENT";
    case AST_ADD:           return "ADD";
    case AST_SUB:           return "SUB";
    case AST_NUMBER:        return "NUMBER";
    default:                return "!!UNKNOWN!!";
  }
}
