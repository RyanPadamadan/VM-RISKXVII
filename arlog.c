#include <stdio.h>
#include "arlog.h"


void add(int R[], int rd, int rs1, int rs2){R[rd] = R[rs1] + R[rs2];}
void addi(int R[], int rd, int rs1, int imm) { R[rd] = R[rs1] + imm;}
void sub(int R[], int rd, int rs1, int rs2){R[rd] = R[rs1] - R[rs2];}
void lui(int R[], int rd, int imm){R[rd] = imm;}
void xor(int R[], int rd, int rs1, int rs2){R[rd] = R[rs1] ^ R[rs2];}
void xori(int R[], int rd, int rs1, int imm){R[rd] = R[rs1] ^ imm;}
void or(int R[], int rd, int rs1, int rs2){R[rd] = R[rs1] | R[rs2];}
void ori(int R[], int rd, int rs1, int imm){R[rd] = R[rs1] | imm;}
void and(int R[], int rd, int rs1, int rs2){R[rd] = R[rs1] & R[rs2];}
void andi(int R[], int rd, int rs1, int imm){R[rd] = R[rs1] & imm;}

void sll(int R[], int rd, int rs1, int rs2){
    R[rd] = R[rs1] << R[rs2];
}

void srl(int R[], int rd, int rs1, int rs2){
    unsigned int num = 0|R[rs1];
    num >>= R[rs2];
    R[rd] = num;
}

void sra(int R[], int rd, int rs1, int rs2){
    int shift = R[rs2] % 32;
    int bits_outside = R[rs1] << (32 - shift);
    R[rd] = bits_outside | (R[rs1] >> shift);
}

