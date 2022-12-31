#ifndef AST_DEBUG_H
#define AST_DEBUG_H

#include "ast.h"

void printNode(AstNode *n, int depth);
void printTree(AstNode *root, int depth);
char *nodeTypeToString(enum AstNodeType t);

#endif
