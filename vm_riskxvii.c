#include <stdint.h>
#include <stdio.h>

#include "arlog.h"
#include "blob.h"
#include "flow_op.h"
#include "heap_bank.h"
#include "mem_acc.h"

// all the minor helper functions will stay in the main file
// ALl the operations will be stored in three files and will be accessed by the
// header files

uint32_t get_opcode(uint32_t num);
int get_func3(uint32_t instruction);
int get_func7(uint32_t instruction);
int get_imm_I(uint32_t instruction);
int get_rs1(uint32_t instruction);
int get_rs2(uint32_t instruction);
int get_rd(uint32_t instruction);
int get_imm_S(uint32_t instruction);
int get_imm_SB(uint32_t instruction);
int get_imm_U(uint32_t instruction);
int get_imm_UJ(uint32_t instruction);
void dump_registers(int R[]);
void dump_counter(int *pc);

int main(int argc, char *argv[]) {
  int registers[32] = {0};
  int counter = 0;
  int jmp = 0;
  int *pc = &counter;
  int *jmp_flag = &jmp;
  // read in file
  FILE *ptr;
  char *file_path;
  if (argc == 2)
    file_path = argv[1];
  else {
    printf("Not the right number of arguments\n");
    return 1;
  }

  ptr = fopen(file_path, "rb");
  if (!ptr) {
    printf("Couldn't open file\n");
    return 1;
  }

  struct blob instructions;
  struct Bank bank = {NULL, 0};
  struct blob *inst_ptr = &instructions;
  struct Bank *bank_ptr = &bank;

  uint32_t reader[512];
  // reading instructions as array of 32 bit instructions
  fread(reader, 4, 512, ptr);
  fclose(ptr);

  unsigned char *instr = inst_ptr->inst_mem;
  unsigned char *data = inst_ptr->inst_mem;

  // saving instruction and data memory in little endian
  for (int i = 0; i < 512; i++) {
    if (i < 256) {
      uint32_t elem1 = reader[i];
      instr[4 * i] = 0;
      instr[4 * i] |= elem1;

      uint32_t elem2 = reader[i];
      elem2 = (elem2 << 16) >> 24;
      instr[4 * i + 1] = 0;
      instr[4 * i + 1] |= elem2;

      uint32_t elem3 = reader[i];
      elem3 = (elem3 << 8) >> 24;
      instr[4 * i + 2] = 0;
      instr[4 * i + 2] |= elem3;

      uint32_t elem4 = reader[i];
      elem4 = elem4 >> 24;
      instr[4 * i + 3] = 0;
      instr[4 * i + 3] |= elem4;
    } else {
      uint32_t elem1 = reader[i];
      data[4 * i] = 0;
      data[4 * i] |= elem1;

      uint32_t elem2 = reader[i];
      elem2 = (elem2 << 16) >> 24;
      data[4 * i + 1] = 0;
      data[4 * i + 1] |= elem2;

      uint32_t elem3 = reader[i];
      elem3 = (elem3 << 8) >> 24;
      data[4 * i + 2] = 0;
      data[4 * i + 2] |= elem3;

      uint32_t elem4 = reader[i];
      elem4 = elem4 >> 24;
      data[4 * i + 3] = 0;
      data[4 * i + 3] |= elem4;
    }
  }
  // main loop reading the instructions
  while (1) {
    registers[0] = 0;
    uint32_t instruction = reader[(*pc) / 4];
    uint32_t opcode = get_opcode(instruction);
    if (opcode == 3) {
      int func3 = get_func3(instruction);
      int imm = get_imm_I(instruction);
      int rd = get_rd(instruction);
      int rs1 = get_rs1(instruction);
      if (func3 == 0) {
        if (lb(registers, inst_ptr, rd, rs1, imm, bank_ptr)) {
          printf("Illegal Operation: 0x%08x\n", instruction);
          dump_counter(pc);
          dump_registers(registers);
          return 1;
        }

      } else if (func3 == 1) {
        if (lh(registers, inst_ptr, rd, rs1, imm, bank_ptr)) {
          printf("Illegal Operation: 0x%08x\n", instruction);
          dump_counter(pc);
          dump_registers(registers);
          return 1;
        }
      } else if (func3 == 2) {
        if (lw(registers, inst_ptr, rd, rs1, imm, bank_ptr)) {
          printf("Illegal Operation: 0x%08x\n", instruction);
          dump_counter(pc);
          dump_registers(registers);
          return 1;
        }
      } else if (func3 == 4) {
        if (lbu(registers, inst_ptr, rd, rs1, imm, bank_ptr)) {
          printf("Illegal Operation: 0x%08x\n", instruction);
          dump_counter(pc);
          dump_registers(registers);
          return 1;
        }
      } else if (func3 == 5) {
        if (lhu(registers, inst_ptr, rd, rs1, imm, bank_ptr)) {
          printf("Illegal Operation: 0x%08x\n", instruction);
          dump_counter(pc);
          dump_registers(registers);
          return 1;
        }
      } else {
        printf("Instruction Not Implemented: 0x%08x\n", instruction);
        dump_counter(pc);
        dump_registers(registers);
        // pc and reg dump
        return 1;
      }

    }

    else if (opcode == 19) {
      int func3 = get_func3(instruction);
      int imm = get_imm_I(instruction);
      int rd = get_rd(instruction);
      int rs1 = get_rs1(instruction);
      if (func3 == 0) {
        addi(registers, rd, rs1, imm);
      }

      else if (func3 == 4) {
        xori(registers, rd, rs1, imm);
      }

      else if (func3 == 6) {
        or (registers, rd, rs1, imm);
      }

      else if (func3 == 7) {
        andi(registers, rd, rs1, imm);
      }

      else if (func3 == 2) {
        slti(registers, rd, rs1, imm);
      }

      else if (func3 == 3) {
        sltiu(registers, rd, rs1, imm);
      }

      else {
        printf("Instruction Not Implemented: 0x%08x\n", instruction);
        dump_counter(pc);
        dump_registers(registers);
        return 1;
      }
    }

    else if (opcode == 35) {
      int func3 = get_func3(instruction);
      int rs1 = get_rs1(instruction);
      int rs2 = get_rs2(instruction);
      int imm = get_imm_S(instruction);
      if (func3 == 0) {
        if (sb(registers, inst_ptr, rs1, rs2, imm, bank_ptr, pc)) {
          printf("Illegal Operation: 0x%08x\n", instruction);
          dump_counter(pc);
          dump_registers(registers);
          return 1;
        }
      }

      else if (func3 == 1) {
        if (sh(registers, inst_ptr, rs1, rs2, imm, bank_ptr, pc)) {
          printf("Illegal Operation: 0x%08x\n", instruction);
          dump_counter(pc);
          dump_registers(registers);
          return 1;
        }
      }

      else if (func3 == 2) {
        if (sw(registers, inst_ptr, rs1, rs2, imm, bank_ptr, pc)) {
          printf("Illegal Operation: 0x%08x\n", instruction);
          dump_counter(pc);
          dump_registers(registers);
          return 1;
        }
      } else {
        printf("Instruction Not Implemented: 0x%08x\n", instruction);
        dump_counter(pc);
        dump_registers(registers);
        return 1;
      }
    }

    else if (opcode == 51) {
      int func3 = get_func3(instruction);
      int func7 = get_func7(instruction);
      int rd = get_rd(instruction);
      int rs1 = get_rs1(instruction);
      int rs2 = get_rs2(instruction);

      if (func3 == 0 && func7 == 0) {
        add(registers, rd, rs1, rs2);
      }

      else if (func3 == 0 && func7 == 32) {
        sub(registers, rd, rs1, rs2);
      }

      else if (func3 == 4 && func7 == 0) {
        xor(registers, rd, rs1, rs2);
      }

      else if (func3 == 6 && func7 == 0) {
        or (registers, rd, rs1, rs2);
      }

      else if (func3 == 7 && func7 == 0) {
        and(registers, rd, rs1, rs2);
      }

      else if (func3 == 1 && func7 == 0) {
        sll(registers, rd, rs1, rs2);
      }

      else if (func3 == 5 && func7 == 0) {
        srl(registers, rd, rs1, rs2);
      }

      else if (func3 == 5 && func7 == 32) {
        sra(registers, rd, rs1, rs2);
      }

      else if (func3 == 2 && func7 == 0) {
        slt(registers, rd, rs1, rs2);
      }

      else if (func3 == 3 && func7 == 0) {
        sltu(registers, rd, rs1, rs2);
      } else {
        printf("Instruction Not Implemented: 0x%08x\n", instruction);
        dump_counter(pc);
        dump_registers(registers);
        return 1;
      }
    }

    else if (opcode == 55) {
      int imm = get_imm_U(instruction);
      int rd = get_rd(instruction);
      lui(registers, rd, imm);
    }

    else if (opcode == 99) {
      int func3 = get_func3(instruction);
      int rs1 = get_rs1(instruction);
      int rs2 = get_rs2(instruction);
      int imm = get_imm_SB(instruction);

      if (func3 == 0) {
        beq(registers, rs1, rs2, imm, pc, jmp_flag);
      }

      else if (func3 == 1) {
        bne(registers, rs1, rs2, imm, pc, jmp_flag);
      }

      else if (func3 == 4) {
        blt(registers, rs1, rs2, imm, pc, jmp_flag);
      }

      else if (func3 == 6) {
        bltu(registers, rs1, rs2, imm, pc, jmp_flag);
      }

      else if (func3 == 5) {
        bge(registers, rs1, rs2, imm, pc, jmp_flag);
      }

      else if (func3 == 7) {
        bgeu(registers, rs1, rs2, imm, pc, jmp_flag);
      }

      else {
        printf("Instruction Not Implemented: 0x%08x\n", instruction);
        dump_counter(pc);
        dump_registers(registers);
        return 1;
      }

    }

    else if (opcode == 103) {
      int imm = get_imm_I(instruction);
      int rd = get_rd(instruction);
      int rs1 = get_rs1(instruction);
      jalr(registers, rd, rs1, imm, pc);
      *jmp_flag = 1;
    }

    else if (opcode == 111) {
      int imm = get_imm_UJ(instruction);
      int rd = get_rd(instruction);
      jal(registers, rd, imm, pc);
      *jmp_flag = 1;
    }

    else {
      printf("Instruction Not Implemented: 0x%08x\n", instruction);
      dump_counter(pc);
      dump_registers(registers);
      return 1;
    }
    if (!(*jmp_flag)) {
      (*pc) += 4;
    } else {
      *jmp_flag = 0;
    }
  }

  return 0;
}

uint32_t get_opcode(uint32_t num) { return num & 127; }

int get_imm_I(uint32_t instruction) {
  int imm = instruction;
  imm = imm >> 20;
  return imm;
}

int get_func3(uint32_t instruction) {
  uint32_t func3 = (instruction >> 12);
  func3 <<= 29;
  func3 >>= 29;
  return func3;
}

int get_func7(uint32_t instruction) {
  uint32_t func7 = instruction >> 25;
  return func7;
}

int get_rs1(uint32_t instruction) {
  uint32_t rs1 = instruction;
  rs1 <<= 12;
  rs1 >>= 27;
  return rs1;
}

int get_rs2(uint32_t instruction) {
  uint32_t rs2 = instruction;
  rs2 <<= 7;
  rs2 >>= 27;
  return rs2;
}

int get_rd(uint32_t instruction) {
  uint32_t rd = instruction;
  rd <<= 20;
  rd >>= 27;
  return rd;
}

int get_imm_S(uint32_t instruction) {
  int imm = instruction;
  imm = (imm >> 25) << 5;
  uint32_t temp1 = (instruction << 20) >> 27;
  return imm | temp1;
}

int get_imm_SB(uint32_t instruction) {
  int imm = instruction;
  imm = ((imm >> 31) << 12);
  uint32_t temp1 = instruction;
  temp1 = ((temp1 << 1) >> 26) << 5;
  uint32_t temp2 = instruction;
  temp2 = ((temp2 >> 8) << 28) >> 27;
  uint32_t temp3 = instruction;
  temp3 = ((temp3 >> 7) << 31) >> 20;
  imm |= temp1 | temp2 | temp3;
  return imm;
}

int get_imm_U(uint32_t instruction) {
  int imm = (instruction >> 12) << 12;
  return imm;
}

int get_imm_UJ(uint32_t instruction) {
  int imm = instruction;
  imm = (imm >> 31) << 20;
  uint32_t temp1 = ((instruction << 1) >> 22) << 1;
  uint32_t temp2 = (((instruction << 11) >> 31) << 11);
  uint32_t temp3 = ((instruction << 12) >> 24) << 12;
  return imm | temp1 | temp2 | temp3;
}

void dump_registers(int R[]) {
  for (int i = 0; i < 32; i++) {
    printf("R[%d] = 0x%08x;\n", i, R[i]);
  }
}

void dump_counter(int *pc) { printf("PC = 0x%08x;\n", *pc); }
