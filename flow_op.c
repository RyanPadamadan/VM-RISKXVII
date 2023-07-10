#include <stdio.h>
#include <stdint.h>
#include "flow_op.h"

void slt(int R[], int rd, int rs1, int rs2){
    R[rd] = (R[rs1] < R[rs2]) ? 1 : 0;
}

void slti(int R[], int rd, int rs1, int imm){
    R[rd] = (R[rs1] < imm) ? 1 : 0;
}

void sltu(int R[], int rd, int rs1, int rs2){
    uint32_t t1 = 0 | R[rs1];
    uint32_t t2 = 0 | R[rs2];
    R[rd] = (t1 < t2) ? 1 : 0;
}

void sltiu(int R[], int rd, int rs1, int imm){
    uint32_t t1 = 0 | R[rs1];
    uint32_t t2 = 0 | imm;
    R[rd] = (t1 < t2) ? 1 : 0;
}

void beq(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag){
    if(R[rs1] == R[rs2]){
        *pc = *pc + (imm);
        *jmp_flag = 1;
    }
}

void bne(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag){
    if(R[rs1] != R[rs2]){
        *pc = *pc + (imm);
        *jmp_flag = 1;
    }
}

void blt(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag){
    //printf("hi R[%d]:%d R[%d]:%d %08x", rs1, R[rs1], rs2,R[rs2], *pc);
    if(R[rs1] < R[rs2]){
        *pc = *pc + (imm);
        *jmp_flag = 1;
    }
}

void bltu(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag){
    uint32_t t1 = 0 | R[rs1];
    uint32_t t2 = 0 | R[rs2];
    if(t1 < t2){
        *pc = *pc + (imm);
        *jmp_flag = 1;
    }
}

void bge(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag){
    if(R[rs1] >= R[rs2]){
        *pc = *pc + (imm);
        *jmp_flag = 1;
    }
}

void bgeu(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag){
    uint32_t t1 = 0 | R[rs1];
    uint32_t t2 = 0 | R[rs2];
    if(t1 >= t2){
        *pc = *pc + (imm);
        *jmp_flag = 1;
    }

}
void jal(int R[], int rd, int imm, int* pc){
    R[rd] = *pc + 4;
    *pc = *pc + imm ;

}

void jalr(int R[], int rd, int rs1, int imm, int* pc){
    R[rd] = *pc + 4;
    *pc = R[rs1] + imm;
 }