#ifndef AST_H
#define AST_H

enum AstNodeType {
  AST_PROGRAM,
  AST_DECLS,
  AST_DECL_VAR,
  AST_DECL_ARRAY,
  AST_STMTS,
  AST_STMT,
  AST_ASSIGN_STMT,
  AST_REFERENCE,
  AST_WHILE,
  AST_IF,
  AST_IF_ELSE,
  AST_IDENT,
  AST_ADD,
  AST_SUB,
  AST_MUL,
  AST_DIV,
  AST_NUMBER,
  AST_EQUAL,
  AST_NEQ,
  AST_LT,
  AST_LEQ,
  AST_GT,
  AST_GEQ
};

typedef struct _AstNode {
  enum AstNodeType nodeType;
  int ivalue;
  char *svalue;
  struct _AstNode *child;
  struct _AstNode *brother;
} AstNode;

AstNode *createVoidNode(enum AstNodeType t);
AstNode *createIntNode(enum AstNodeType t, int ivalue);
AstNode *createStrNode(enum AstNodeType t, char *svalue);
void addChild(AstNode *parent, AstNode *child);
void mergeChildren(AstNode *dst, AstNode *src);
int countChildrenOfAstNode(AstNode *node);

#endif
