#include <stdio.h>
#include <stdlib.h>

#include "asm_builder.h"
#include "ast.h"
#include "symbol_table.h"

extern FILE *fp_out;

SymbolTable *symbolTable;

void codegenDecls(AstNode *n);
void codegenDeclVar(AstNode *n);
void codegenDeclArray(AstNode *n);
void codegenStmts(AstNode *n);
void codegenAssignStmt(AstNode *n);
void codegenWhileStmt(AstNode *n);
void codegenIfStmt(AstNode *n);
void codegenIfElseStmt(AstNode *n);
void codegenReference(AstNode *n);
void codegenCondExpr(AstNode *n);
void codegenExpr(AstNode *n);

void codegenProgram(AstNode *root) {
  fp_out = stdout;

  symbolTable = createSymbolTable();
  codegenDecls(root->child);

  fprintf(fp_out,
          "INITIAL_GP = 0x10008000\n"
          "INITIAL_SP = 0x7ffffffc\n"
          "stop_service = 99\n");
  write_dot_inst_text_with_address(0u);
  write_label("init");
  write_pseudo_inst_la(REG_GP, "INITIAL_GP");
  write_pseudo_inst_la(REG_SP, "INITIAL_SP");
  write_inst_jal("main");
  write_pseudo_inst_nop();
  fprintf(fp_out, "\tli      $%d, %s\n", REG_V0, "stop_service");
  write_inst_syscall();
  fprintf(fp_out, "\n");

  write_label("stop");
  write_inst_j("stop");
  write_pseudo_inst_nop();
  fprintf(fp_out, "\n");

  write_dot_inst_text_with_address(0x00001000u);
  write_label("main");
  codegenStmts(root->child->brother);
  write_inst_jr(REG_RA);
  write_pseudo_inst_nop();
}

void codegenDecls(AstNode *n) {
  AstNode *decl = n->child;
  while (decl != NULL) {
    switch (decl->nodeType) {
      case AST_DECL_VAR:
        codegenDeclVar(decl);
        break;
      case AST_DECL_ARRAY:
        codegenDeclArray(decl);
        break;
    }
    decl = decl->brother;
  }
}

void codegenDeclVar(AstNode *n) {
  char *varName = n->child->svalue;
  symbolTable = addSymbol(symbolTable, varName, 4);
}

void codegenDeclArray(AstNode *n) {
  char *varName = n->child->svalue;
  int length = n->child->brother->ivalue;
  symbolTable = addSymbol(symbolTable, varName, length * 4);
}

void codegenStmts(AstNode *n) {
  AstNode *stmt = n->child;
  while (stmt != NULL) {
    switch (stmt->nodeType) {
      case AST_ASSIGN_STMT:
        codegenAssignStmt(stmt);
        break;
      case AST_WHILE:
        codegenWhileStmt(stmt);
        break;
      case AST_IF:
        codegenIfStmt(stmt);
        break;
      case AST_IF_ELSE:
        codegenIfElseStmt(stmt);
        break;
    }
    stmt = stmt->brother;
  }
}

void codegenAssignStmt(AstNode *n) {
  AstNode *left = n->child;
  AstNode *right = n->child->brother;

  codegenExpr(right);
  write_pseudo_inst_move(REG_V1, REG_V0);
  codegenReference(left);

  write_inst_sw(REG_V1, REG_T0, 0);
}

void codegenReference(AstNode *n) {
  SymbolTable *symbol = searchSymbol(symbolTable, n->child->svalue);

  switch (countChildrenOfAstNode(n)) {
    case 1:
      write_pseudo_inst_li(REG_T0, symbol->offset);
      write_inst_addu(REG_T0, REG_GP, REG_T0);
      break;
    case 2:
      codegenExpr(n->child->brother); /* index */
      write_inst_sll(REG_V0, REG_V0, 2);

      write_pseudo_inst_li(REG_T0, symbol->offset);
      write_inst_addu(REG_T0, REG_T0, REG_V0);
      write_inst_addu(REG_T0, REG_GP, REG_T0);
      break;
    default:
      fprintf(stderr, "ERROR: unexpected count children of Reference: %d\n",
              countChildrenOfAstNode(n));
      exit(1);
  }
}

static int auto_label_cnt = 0;

void codegenWhileStmt(AstNode *n) {
  AstNode *cond = n->child;
  AstNode *stmts = n->child->brother;
  char label_begin_while[10];
  char label_condition_while[10];
  snprintf(label_begin_while, 10, "$WB%x", auto_label_cnt);
  snprintf(label_condition_while, 10, "$WC%x", auto_label_cnt);
  auto_label_cnt++;

  write_inst_j(label_condition_while);
  write_pseudo_inst_nop();

  write_label(label_begin_while);
  codegenStmts(stmts);

  write_label(label_condition_while);
  codegenCondExpr(cond);
  write_inst_bne(REG_V0, REG_ZERO, label_begin_while);
  write_pseudo_inst_nop();
}

void codegenIfStmt(AstNode *n) {
  AstNode *cond = n->child;
  AstNode *stmts = n->child->brother;
  char label_end_if[10];
  snprintf(label_end_if, 10, "$IE%x", auto_label_cnt);
  auto_label_cnt++;

  codegenCondExpr(cond);
  write_inst_beq(REG_V0, REG_ZERO, label_end_if);
  write_pseudo_inst_nop();

  codegenStmts(stmts);
  write_label(label_end_if);
}

void codegenIfElseStmt(AstNode *n) {
  AstNode *cond = n->child;
  AstNode *thenStmts = n->child->brother;
  AstNode *elseStmts = n->child->brother->brother;
  char label_begin_else[10];
  char label_end_if[10];
  snprintf(label_begin_else, 10, "$EB%x", auto_label_cnt);
  snprintf(label_end_if, 10, "$IE%x", auto_label_cnt);
  auto_label_cnt++;

  codegenCondExpr(cond);
  write_inst_beq(REG_V0, REG_ZERO, label_begin_else);
  write_pseudo_inst_nop();

  codegenStmts(thenStmts);
  write_inst_j(label_end_if);
  write_pseudo_inst_nop();

  write_label(label_begin_else);
  codegenStmts(elseStmts);

  write_label(label_end_if);
}

void codegenCondExpr(AstNode *n) {
  AstNode *left = n->child;
  AstNode *right = n->child->brother;

  codegenExpr(left);

  write_pseudo_inst_push(REG_V0, REG_SP);

  codegenExpr(right);

  write_pseudo_inst_pop(REG_V1, REG_SP);

  switch (n->nodeType) {
    case AST_EQUAL:
      /* $v1 == $v0  ->  !($v1 xor $v0) */
      write_inst_xor(REG_V0, REG_V1, REG_V0);
      write_inst_sltiu(REG_V0, REG_V0, 1);
      break;
    case AST_NEQ:
      /* $v1 != $v0  ->  $v1 xor $v0 */
      write_inst_xor(REG_V0, REG_V1, REG_V0);
      break;
    case AST_LT:
      /* $v1 < $v0 */
      write_inst_slt(REG_V0, REG_V1, REG_V0);
      break;
    case AST_LEQ:
      /* $v1 <= $v0  ->  !($v0 < $v1) */
      write_inst_slt(REG_V0, REG_V0, REG_V1);
      write_inst_sltiu(REG_V0, REG_V0, 1);
      break;
    case AST_GT:
      /* $v1 > $v0  ->  $v0 < $v1 */
      write_inst_slt(REG_V0, REG_V0, REG_V1);
      break;
    case AST_GEQ:
      /* $v1 >= $v0  ->  !($v1 < $v0) */
      write_inst_slt(REG_V0, REG_V1, REG_V0);
      write_inst_sltiu(REG_V0, REG_V0, 1);
      break;
  }
}

void codegenExpr(AstNode *n) {
  switch (n->nodeType) {
    case AST_NUMBER:
      write_pseudo_inst_li(REG_V0, n->ivalue);
      return;
    case AST_REFERENCE:
      codegenReference(n);
      write_inst_lw(REG_V0, REG_T0, 0);
      write_pseudo_inst_nop();
      return;
  }

  AstNode *left = n->child;
  AstNode *right = n->child->brother;

  codegenExpr(left);

  write_pseudo_inst_push(REG_V0, REG_SP);

  codegenExpr(right);

  write_pseudo_inst_pop(REG_V1, REG_SP);

  switch (n->nodeType) {
    case AST_ADD:
      write_inst_add(REG_V0, REG_V1, REG_V0);
      break;
    case AST_SUB:
      write_inst_sub(REG_V0, REG_V1, REG_V0);
      break;
    case AST_MUL:
      write_inst_mult(REG_V1, REG_V0);
      write_inst_mflo(REG_V0);
      break;
    case AST_DIV:
      write_inst_div(REG_V1, REG_V0);
      write_inst_mflo(REG_V0);
      break;
    case AST_MOD:
      write_inst_div(REG_V1, REG_V0);
      write_inst_mfhi(REG_V0);
      break;
  }
}
