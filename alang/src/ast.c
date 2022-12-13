#include <stdlib.h>
#include "ast.h"

AstNode *createNode(enum AstNodeType t, union AstValue v) {
  AstNode *n = malloc(sizeof(AstNode));
  n->nodeType = t;
  n->value = v;
  n->child = NULL;
  n->brother = NULL;
}

void addChild(AstNode *parent, AstNode *child) {
  if (parent->child == NULL) {
    parent->child = child;
    return;
  }

  AstNode *n = parent->child;
  while (n->brother != NULL) {
    n = n->brother;
  }
  n->brother = child;
}

#ifdef MAIN
#include <stdio.h>

printNode(AstNode* n) {
  printf(
      "{id: %p, nodetype: %d, value: %d, child: %p, brother: %p} ",
      n,
      n->nodeType,
      n->value.value,
      n->child,
      n->brother
  );
}

void printTree(AstNode *root) {
  if (root == NULL) return;

  AstNode *child = root->child;
  if (child == NULL) {
    printNode(root);
    return;
  }

  printf("( ");
  printNode(child);
  while (child != NULL) {
    printTree(child);
    child = child->brother;
  }
  printf(")");
}

int main(void) {
  union AstValue v1 = { .varName = "foo" };
  AstNode *p1 = createNode(AST_IDENT, v1);
  AstNode *p2 = createNode(AST_ASSIGN_STMT, AST_VALUE_NULL);
  union AstValue v3 = { .value = 1 };
  AstNode *p3 = createNode(AST_NUMBER, v3);
  AstNode *p4 = createNode(AST_ADD, AST_VALUE_NULL);
  union AstValue v5 = { .value = 2 };
  AstNode *p5 = createNode(AST_NUMBER, v5);

  addChild(p2, p1);
  addChild(p2, p4);
  addChild(p4, p3);
  addChild(p4, p5);

  printTree(p2);
  printf("\n");

  return 0;
}
#endif
