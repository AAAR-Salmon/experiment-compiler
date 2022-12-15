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
  AST_EXPR_STMT,
  AST_EXPR,
  AST_TERM,
  AST_FACTOR,
  AST_LOOP_STMT,
  AST_BRANCH_STMT,
  AST_COND_EXPR,

  AST_IDENT,
  AST_ADD,
  AST_SUB,
  AST_NUMBER
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

#endif
