#include "asm_builder.h"

#include <stdio.h>

FILE *fp_out;

void write_inst_add(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tadd     $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_addi(P32Register dest, P32Register src1, short immediate) {
  fprintf(fp_out, "\taddi    $%d, $%d, %d\n", dest, src1, immediate);
}

void write_inst_addu(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\taddu    $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_addiu(P32Register dest, P32Register src1, short immediate) {
  fprintf(fp_out, "\taddiu   $%d, $%d, %d\n", dest, src1, immediate);
}

void write_inst_sub(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tsub     $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_subu(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tsubu    $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_mult(P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tmult    $%d, $%d\n", src1, src2);
}

void write_inst_div(P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tdiv     $%d, $%d\n", src1, src2);
}

void write_inst_divu(P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tdivu    $%d, $%d\n", src1, src2);
}

void write_inst_and(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tand     $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_andi(P32Register dest, P32Register src1, short immediate) {
  fprintf(fp_out, "\tandi    $%d, $%d, %#04x\n", dest, src1, immediate);
}

void write_inst_or(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tor      $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_ori(P32Register dest, P32Register src1, short immediate) {
  fprintf(fp_out, "\tori     $%d, $%d, %#04x\n", dest, src1, immediate);
}

void write_inst_xor(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\txor     $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_xori(P32Register dest, P32Register src1, short immediate) {
  fprintf(fp_out, "\txori    $%d, $%d, %#04x\n", dest, src1, immediate);
}

void write_inst_nor(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tnor     $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_sll(P32Register dest, P32Register src1, unsigned int shamt) {
  shamt = shamt & 0b11111;
  fprintf(fp_out, "\tsll     $%d, $%d, %d\n", dest, src1, shamt);
}

void write_inst_srl(P32Register dest, P32Register src1, unsigned int shamt) {
  shamt = shamt & 0b11111;
  fprintf(fp_out, "\tsrl     $%d, $%d, %d\n", dest, src1, shamt);
}

void write_inst_sra(P32Register dest, P32Register src1, unsigned int shamt) {
  shamt = shamt & 0b11111;
  fprintf(fp_out, "\tsra     $%d, $%d, %d\n", dest, src1, shamt);
}

void write_inst_sllv(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tsllv    $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_srlv(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tsrlv    $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_srav(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tsrav    $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_slt(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tslt     $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_sltu(P32Register dest, P32Register src1, P32Register src2) {
  fprintf(fp_out, "\tsltu    $%d, $%d, $%d\n", dest, src1, src2);
}

void write_inst_slti(P32Register dest, P32Register src1, short immediate) {
  fprintf(fp_out, "\tslti    $%d, $%d, %d\n", dest, src1, immediate);
}

void write_inst_sltiu(P32Register dest, P32Register src1, short immediate) {
  fprintf(fp_out, "\tsltiu   $%d, $%d, %d\n", dest, src1, immediate);
}

void write_inst_lb(P32Register dest, P32Register base, short offset) {
  fprintf(fp_out, "\tlb      $%d, %d($%d)\n", dest, offset, base);
}

void write_inst_lw(P32Register dest, P32Register base, short offset) {
  fprintf(fp_out, "\tlw      $%d, %d($%d)\n", dest, offset, base);
}

void write_inst_sb(P32Register dest, P32Register base, short offset) {
  fprintf(fp_out, "\tsb      $%d, %d($%d)\n", dest, offset, base);
}

void write_inst_sw(P32Register dest, P32Register base, short offset) {
  fprintf(fp_out, "\tsw      $%d, %d($%d)\n", dest, offset, base);
}

void write_inst_beq(P32Register src1, P32Register src2, char *label) {
  fprintf(fp_out, "\tbeq     $%d, $%d, %s\n", src1, src2, label);
}

void write_inst_bne(P32Register src1, P32Register src2, char *label) {
  fprintf(fp_out, "\tbeq     $%d, $%d, %s\n", src1, src2, label);
}

void write_inst_j(char *label) {
  fprintf(fp_out, "\tj       %s\n", label);
}

void write_inst_jal(char *label) {
  fprintf(fp_out, "\tjal     %s\n", label);
}

void write_inst_jr(P32Register target) {
  fprintf(fp_out, "\tjr      $%d\n", target);
}

void write_inst_jalr(P32Register target) {
  fprintf(fp_out, "\tjalr    $%d\n", target);
}

void write_inst_lui(P32Register dest, short immediate) {
  fprintf(fp_out, "\tlui     $%d, %d\n", dest, immediate);
}

void write_inst_mfhi(P32Register dest) {
  fprintf(fp_out, "\tmfhi    $%d\n", dest);
}

void write_inst_mflo(P32Register dest) {
  fprintf(fp_out, "\tmflo    $%d\n", dest);
}

void write_inst_syscall() {
  fprintf(fp_out, "\tsyscall\n");
}

void write_label(char *label) {
  fprintf(fp_out, "%s:\n", label);
}

void write_pseudo_inst_li(P32Register dest, int immediate) {
  write_inst_lui(dest, (short)(immediate >> 16 & 0xffff));
  write_inst_ori(dest, dest, (short)(immediate & 0xffff));
}

void write_pseudo_inst_nop() {
  write_inst_sll(REG_ZERO, REG_ZERO, 0u);
}

void write_dot_inst_text() {
  fprintf(fp_out, "\t.text\n");
}

void write_dot_inst_text_with_address(unsigned int addr) {
  fprintf(fp_out, "\t.text   %#08x\n", addr);
}

void write_dot_inst_data() {
  fprintf(fp_out, "\t.data\n");
}

void write_dot_inst_data_with_address(unsigned int addr) {
  fprintf(fp_out, "\t.text   %#08x\n", addr);
}

void write_dot_inst_word(int data) {
  fprintf(fp_out, "\t.word   %d\n", data);
}

void write_dot_inst_byte(char data) {
  fprintf(fp_out, "\t.byte   %d\n", data);
}
