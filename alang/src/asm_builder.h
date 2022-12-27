#ifndef ASM_BUILDER_H
#define ASM_BUILDER_H

typedef enum {
  REG_ZERO = 0,
  REG_AT = 1,
  REG_V0 = 2,
  REG_V1 = 3,
  REG_A0 = 4,
  REG_A1 = 5,
  REG_A2 = 6,
  REG_A3 = 7,
  REG_T0 = 8,
  REG_T1 = 9,
  REG_T2 = 10,
  REG_T3 = 11,
  REG_T4 = 12,
  REG_T5 = 13,
  REG_T6 = 14,
  REG_T7 = 15,
  REG_S0 = 16,
  REG_S1 = 17,
  REG_S2 = 18,
  REG_S3 = 19,
  REG_S4 = 20,
  REG_S5 = 21,
  REG_S6 = 22,
  REG_S7 = 23,
  REG_T8 = 24,
  REG_T9 = 25,
  REG_K0 = 26,
  REG_K1 = 27,
  REG_GP = 28,
  REG_SP = 29,
  REG_FP = 30,
  REG_RA = 31
} P32Register;

/**
 * @brief add two registers (raises overflow exception)
 *
 * @param dest destination to store `src1 + src2`
 * @param src1
 * @param src2
 */
void write_inst_add(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief add a register and a immediate (raises overflow exception)
 *
 * @param dest destination to store `src1 + immediate`
 * @param src1
 * @param immediate as signed 16bit integer
 */
void write_inst_addi(P32Register dest, P32Register src1, short immediate);

/**
 * @brief add two registers
 *
 * @param dest destination to store `src1 + src2`
 * @param src1
 * @param src2
 */
void write_inst_addu(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief add a register and a immediate
 *
 * @param dest destination to store `src1 + immediate`
 * @param src1
 * @param immediate as signed 16bit integer
 */
void write_inst_addiu(P32Register dest, P32Register src1, short immediate);

/**
 * @brief subtract a register from a register (raises overflow exception)
 *
 * @param dest destination to store `src1 - src2`
 * @param src1
 * @param src2
 */
void write_inst_sub(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief subtract a register from a register
 *
 * @param dest destination to store `src1 - src2`
 * @param src1
 * @param src2
 */
void write_inst_subu(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief multiply two registers (as signed)
 *
 * @attention As the result is stored in hi/lo registers,
 *            execute mfhi/mflo instructions to use the value.
 *
 * @param src1 as signed 32bit integer
 * @param src2 as signed 32bit integer
 */
void write_inst_mult(P32Register src1, P32Register src2);

/**
 * @brief multiply two registers (as unsigned)
 *
 * @attention As the result is stored in hi/lo registers,
 *            execute mfhi/mflo instructions to use the value.
 *
 * @param src1 as unsigned 32bit integer
 * @param src2 as unsigned 32bit integer
 */
void write_inst_multu(P32Register src1, P32Register src2);

/**
 * @brief divide a register by a register (as signed)
 *
 * @attention As the result is stored in hi/lo registers,
 *            execute mfhi/mflo instructions to use the value.
 *            lo = src1 / src2, hi = src1 % src2.
 *
 * @param src1 as signed 32bit integer
 * @param src2 as signed 32bit integer
 */
void write_inst_div(P32Register src1, P32Register src2);

/**
 * @brief divide a register by a register (as unsigned)
 *
 * @attention As the result is stored in hi/lo registers,
 *            execute mfhi/mflo instructions to use the value.
 *            lo = src1 / src2, hi = src1 % src2.
 *
 * @param src1 as unsigned 32bit integer
 * @param src2 as unsigned 32bit integer
 */
void write_inst_divu(P32Register src1, P32Register src2);

/**
 * @brief logical and bitwise among two registers
 *
 * @param dest destination to store `src1 & src2`
 * @param src1
 * @param src2
 */
void write_inst_and(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief logical and bitwise between a register and a immediate
 *
 * @param dest destination to store `src1 & immediate`
 * @param src1
 * @param immediate as unsigned 16bit integer
 */
void write_inst_andi(P32Register dest, P32Register src1, short immediate);

/**
 * @brief logical or bitwise among two registers
 *
 * @param dest destination to store `src1 | src2`
 * @param src1
 * @param src2
 */
void write_inst_or(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief logical or bitwise between a register and a immediate
 *
 * @param dest destination to store `src1 | immediate`
 * @param src1
 * @param immediate as unsigned 16bit integer
 */
void write_inst_ori(P32Register dest, P32Register src1, short immediate);

/**
 * @brief logical exclusive or bitwise among two registers
 *
 * @param dest destination to store `src1 ^ src2`
 * @param src1
 * @param src2
 */
void write_inst_xor(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief logical exclusive or bitwise between a register and a immediate
 *
 * @param dest destination to store `src1 ^ immediate`
 * @param src1
 * @param immediate as unsigned 16bit integer
 */
void write_inst_xori(P32Register dest, P32Register src1, short immediate);

/**
 * @brief logical nor bitwise among two registers
 *
 * @param dest destination to store `src1 nor src2`
 * @param src1
 * @param src2
 */
void write_inst_nor(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief shift logically a register to left by a constant
 *
 * @param dest  destination to store `src1 << shamt`
 * @param src1
 * @param shamt 5bit integer
 */
void write_inst_sll(P32Register dest, P32Register src1, unsigned int shamt);

/**
 * @brief shift logically a register to right by a constant
 *
 * @param dest  destination to store `src1 >>> shamt`
 * @param src1
 * @param shamt 5bit integer
 */
void write_inst_srl(P32Register dest, P32Register src1, unsigned int shamt);

/**
 * @brief shift arithmetically a register to right by a constant
 *
 * @param dest  destination to store `src1 >> shamt`
 * @param src1
 * @param shamt 5bit integer
 */
void write_inst_sra(P32Register dest, P32Register src1, unsigned int shamt);

/**
 * @brief shift logically a register to left by a register
 *
 * @param dest destination to store `src1 << src2`
 * @param src1
 * @param src2 5bit integer (27bit from MSB is ignored)
 */
void write_inst_sllv(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief shift logically a register to right by a register
 *
 * @param dest destination to store `src1 >>> src2`
 * @param src1
 * @param src2 5bit integer (27bit from MSB is ignored)
 */
void write_inst_srlv(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief shift arithmetically a register to right by a register
 *
 * @param dest destination to store `src1 >> src2`
 * @param src1
 * @param src2 5bit integer (27bit from MSB is ignored)
 */
void write_inst_srav(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief set whether a register is less than a register (as signed)
 *
 * @param dest destination to store 1 if `src1 < src2`, or 0
 * @param src1 as signed 32bit integer
 * @param src2 as signed 32bit integer
 */
void write_inst_slt(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief set whether a register is less than a register (as unsigned)
 *
 * @param dest destination to store 1 if `src1 < src2`, or 0
 * @param src1 as unsigned 32bit integer
 * @param src2 as unsigned 32bit integer
 */
void write_inst_sltu(P32Register dest, P32Register src1, P32Register src2);

/**
 * @brief set whether a register is less than a immediate (as signed)
 *
 * @param dest destination to store 1 if `src1 < src2`, or 0
 * @param src1 as signed 32bit integer
 * @param immediate as signed 16bit integer
 */
void write_inst_slti(P32Register dest, P32Register src1, short immediate);

/**
 * @brief set whether a register is less than a immediate (as unsigned)
 *
 * @param dest destination to store 1 if `src1 < src2`, or 0
 * @param src1 as unsigned 32bit integer
 * @param immediate as **signed** 16bit integer
 */
void write_inst_sltiu(P32Register dest, P32Register src1, short immediate);

/**
 * @brief load a signed byte value in memory to a register
 *
 * @attention data loading is delayed by one instruction
 *
 * @param dest destination to store `*(base + offset)`
 * @param base
 * @param offset
 */
void write_inst_lb(P32Register dest, P32Register base, short offset);

/**
 * @brief load a 32bit integer in memory to a register
 *
 * @attention data loading is delayed by one instruction
 *
 * @param dest destination to store `*(base + offset)`
 * @param base
 * @param offset
 */
void write_inst_lw(P32Register dest, P32Register base, short offset);

/**
 * @brief store a byte value to memory
 *
 * @param src value to be stored (masked as `src & 0x000000ff`)
 * @param base
 * @param offset
 */
void write_inst_sb(P32Register src, P32Register base, short offset);

/**
 * @brief store a 32bit integer to memory
 *
 * @param src value to be stored
 * @param base
 * @param offset
 */
void write_inst_sw(P32Register src, P32Register base, short offset);

/**
 * @brief jump to label if `src1 == src2`
 *
 * @attention jump is delayed by one instruction
 *
 * @param src1
 * @param src2
 * @param label
 */
void write_inst_beq(P32Register src1, P32Register src2, char *label);

/**
 * @brief jump to label if `src1 != src2`
 *
 * @attention jump is delayed by one instruction
 *
 * @param src1
 * @param src2
 * @param label
 */
void write_inst_bne(P32Register src1, P32Register src2, char *label);

/**
 * @brief jump to label
 *
 * @attention jump is delayed by one instruction
 *
 * @param label
 */
void write_inst_j(char *label);

/**
 * @brief jump to label and store caller address to $ra
 *
 * @attention jump is delayed by one instruction
 *
 * @param label
 */
void write_inst_jal(char *label);

/**
 * @brief jump to stored address
 *
 * @attention jump is delayed by one instruction
 *
 * @param target
 */
void write_inst_jr(P32Register target);

/**
 * @brief jump to stored address ands store caller address to $ra
 *
 * @attention jump is delayed by one instruction
 *
 * @param target
 */
void write_inst_jalr(P32Register target);

/**
 * @brief store immediate to upper bits of register
 *
 * @param dest destination to store `immediate << 16`
 * @param immediate as unsigned 16bit integer
 */
void write_inst_lui(P32Register dest, short immediate);

/**
 * @brief move the value from the special register hi
 *
 * @param dest destination to store `hi`
 */
void write_inst_mfhi(P32Register dest);

/**
 * @brief move the value from the special register lo
 *
 * @param dest destination to store `lo`
 */
void write_inst_mflo(P32Register dest);

/**
 * @brief jump to syscall handler
 */
void write_inst_syscall();

/**
 * @brief store immediate to register
 *
 * @param dest
 * @param immediate as 32bit immediate
 */
void write_pseudo_inst_li(P32Register dest, int immediate);

/**
 * @brief do nothing
 */
void write_pseudo_inst_nop();

/**
 * @brief place following instructions text space
 */
void write_dot_inst_text();

/**
 * @brief place following instructions specified addressed space
 *
 * @param addr
 */
void write_dot_inst_text_with_address(unsigned int addr);

/**
 * @brief place following allocations data space
 */
void write_dot_inst_data();

/**
 * @brief place following allocations specified addressed space
 *
 * @param addr
 */
void write_dot_inst_data_with_address(unsigned int addr);

/**
 * @brief place data of a word
 *
 * @param data
 */
void write_dot_inst_word(int data);

/**
 * @brief place data of byte
 *
 * @param data
 */
void write_dot_inst_byte(char data);

#endif
