#ifndef ARLOG_H
#define ARLOG_H

void add(int R[], int rd, int rs1, int rs2);
void addi(int R[], int rd, int rs1, int imm);
void sub(int R[], int rd, int rs1, int rs2);
void lui(int R[], int rd, int imm);
void xor(int R[], int rd, int rs1, int rs2);
void xori(int R[], int rd, int rs1, int imm);
void or(int R[], int rd, int rs1, int rs2);
void ori(int R[], int rd, int rs1, int imm);
void and(int R[], int rd, int rs1, int rs2);
void andi(int R[], int rd, int rs1, int imm);
void sll(int R[], int rd, int rs1, int rs2);
void srl(int R[], int rd, int rs1, int rs2);
void sra(int R[], int rd, int rs1, int rs2);
#endif //
