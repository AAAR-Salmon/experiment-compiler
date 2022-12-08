#include <stdio.h>
#include <stdlib.h>

enum TokenType {
  Number,
  Variable,
  Plus,
  Multiple
};

struct Node {
  enum TokenType type;
  char *token;
  struct Node *lchild;
  struct Node *rchild;
};

struct Node createNode(
  enum TokenType type,
  char *token
) {
  struct Node node;
  node.type = type;
  node.token = token;
  node.lchild = NULL;
  node.rchild = NULL;
  return node;
}

void setLchild(struct Node *parent, struct Node *lchild) {
  parent->lchild = lchild;
}

void setRchild(struct Node *parent, struct Node *rchild) {
  parent->rchild = rchild;
}

void printAstPostfix(struct Node *root) {
  if (root == NULL) return;
  printAstPostfix(root->lchild);
  printAstPostfix(root->rchild);
  printf("%s ", root->token);
}

int main() {
  struct Node *nodes = malloc(sizeof(struct Node) * 5);
  nodes[0] = createNode(Variable, "x");
  nodes[1] = createNode(Plus, "+");
  nodes[2] = createNode(Number, "3");
  nodes[3] = createNode(Multiple, "*");
  nodes[4] = createNode(Number, "10");

  setLchild(&nodes[1], &nodes[0]);
  setRchild(&nodes[1], &nodes[3]);
  setLchild(&nodes[3], &nodes[2]);
  setRchild(&nodes[3], &nodes[4]);

  printAstPostfix(&nodes[1]);
  printf("\n");

  free(nodes);
  return 0;
}
