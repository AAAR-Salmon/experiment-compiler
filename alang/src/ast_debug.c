#include "ast_debug.h"

void printNode(AstNode* n, int depth) {
  static char ws[100];
  int i;
  for (i = 0; i < depth; i++) {
    ws[i] = ' ';
  }
  ws[i] = '\0';

  printf(
      "%s{ nodetype: %d, value: %d }\n",
      ws,
      n->nodeType,
      n->value.value
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
