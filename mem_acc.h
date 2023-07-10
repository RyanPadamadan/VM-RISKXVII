#ifndef MEM_ACCESS_H
#define MEM_ACCESS_H
#include "blob.h"
#include "heap_bank.h"

int lb(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr);
int lh(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr);
int lw(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr);
int lbu(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr);
int lhu(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr);
int sb(int R[], struct blob* blob, int rs1, int rs2, int imm, struct Bank* bank_ptr, int* pc);
int sh(int R[], struct blob* blob, int rs1, int rs2, int imm, struct Bank* bank_ptr, int* pc);
int sw(int R[], struct blob* blob, int rs1, int rs2, int imm, struct Bank* bank_ptr, int* pc);
int virtual_routine_load(int R[], int num_stored,struct blob* blob,int mem_add, struct Bank* bank_ptr, int* pc);
void virtual_routine_store(int R[], int rd, int mem_add, struct Bank* bank_ptr);
void dump_reg(int R[]);
void dump_pc(int* pc);
#endif //
