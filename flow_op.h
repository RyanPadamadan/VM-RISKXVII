#ifndef FLOW_OP
#define FLOW_OP

void slt(int R[], int rd, int rs1, int rs2);
void slti(int R[], int rd, int rs1, int imm);
void sltu(int R[], int rd, int rs1, int rs2);
void sltiu(int R[], int rd, int rs1, int imm);
void beq(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag);
void bne(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag);
void blt(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag);
void bltu(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag);
void bge(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag);
void bgeu(int R[], int rs1, int rs2, int imm, int* pc, int* jmp_flag);
void jal(int R[], int rd, int imm, int* pc);
void jalr(int R[], int rd, int rs1, int imm, int* pc);
#endif // !


