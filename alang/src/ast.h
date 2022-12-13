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

union AstValue {
  char *varName;
  int value;
};

union AstValue AST_VALUE_NULL;

typedef struct _AstNode {
  enum AstNodeType nodeType;
  union AstValue value;
  struct _AstNode *child;
  struct _AstNode *brother;
} AstNode;

AstNode *createNode(enum AstNodeType t, union AstValue v);
void addChild(AstNode *parent, AstNode *child);

#endif
