#include "ast.h"
#include <stdlib.h>

AstNode *__createNode(enum AstNodeType t, int ivalue, char *svalue) {
  AstNode *n = malloc(sizeof(AstNode));
  n->nodeType = t;
  n->ivalue = ivalue;
  n->svalue = svalue;
  n->child = NULL;
  n->brother = NULL;
  return n;
}

AstNode *createVoidNode(enum AstNodeType t) {
  return __createNode(t, 0, NULL);
}

AstNode *createIntNode(enum AstNodeType t, int ivalue) {
  return __createNode(t, ivalue, NULL);
}

AstNode *createStrNode(enum AstNodeType t, char *svalue) {
  return __createNode(t, 0, svalue);
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

void mergeChildren(AstNode *dst, AstNode *src) {
  if (dst->child == NULL) {
    dst->child = src->child;
    return;
  }

  AstNode *last = dst->child;
  while (last->brother != NULL) {
    last = last->brother;
  }
  last->brother = src->child;
}

int countChildrenOfAstNode(AstNode *node) {
  AstNode *child = node->child;
  int result = 0;

  while (child != NULL) {
    result++;
    child = child->brother;
  }

  return result;
}

#ifdef MAIN
#include <stdio.h>
#include "ast_debug.h"

int main(void) {
  AstNode *p1 = createStrNode(AST_IDENT, "foo");
  AstNode *p2 = createVoidNode(AST_ASSIGN_STMT);
  AstNode *p3 = createIntNode(AST_NUMBER, 1);
  AstNode *p4 = createVoidNode(AST_ADD);
  AstNode *p5 = createIntNode(AST_NUMBER, 2);

  addChild(p2, p1);
  addChild(p2, p4);
  addChild(p4, p3);
  addChild(p4, p5);

  printTree(p2, 0);

  return 0;
}
#endif
