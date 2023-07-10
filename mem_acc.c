#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mem_acc.h"
#include "heap_bank.h"

int lb(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr){
    int mem_add = R[rs1] + imm;

    if(mem_add < 0){
        printf("Illegal Operation Error\n");
        return 1;
        exit(1);
    }

    else if(mem_add == 0x0812 || mem_add == 0x0816){
        virtual_routine_store(R,rd, mem_add, bank_ptr);
        return 0;
    }

    else if(mem_add >= 0xb700 && mem_add <= 0xd700){
        return lb_h(bank_ptr,mem_add,R,rd);
    }

    unsigned char* reader = (blob -> inst_mem) + mem_add;
    unsigned char byte = *reader;
    R[rd] = 0|byte;
    R[rd] <<= 24;
    R[rd] >>= 24;
    return 0;
}

int lh(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr){
    int mem_add = R[rs1] + imm;
    if(mem_add < 0 ){
        printf("Illegal Operation Error\n");
        return 1;
        exit(1);
    }

    else if(mem_add == 0x0812 || mem_add == 0x0816){
        virtual_routine_store(R,rd, mem_add, bank_ptr);
        return 0;
    }

    else if(mem_add >= 0xb700 && mem_add <= 0xd700){
        return lh_h(bank_ptr,mem_add,R,rd);
    }

    unsigned char* reader = blob -> inst_mem + mem_add;
    unsigned char byte1 = *reader++;
    unsigned char byte2 = *reader;

    R[rd] = 0|byte2;
    R[rd] <<= 8;
    R[rd] |= byte1;
    R[rd] <<= 16;
    R[rd] >>= 16;
    return 0;
}

int lw(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr){
    int mem_add = R[rs1] + imm;

    if(mem_add < 0){
        printf("Illegal Operation Error\n");
        return 1;
        exit(1);
    }

    else if(mem_add == 0x0812 || mem_add == 0x0816){
        virtual_routine_store(R,rd, mem_add, bank_ptr);
        return 0;
    }

    else if(mem_add >= 0xb700 && mem_add <= 0xd700){
        return lw_h(bank_ptr,mem_add,R,rd);
    }

    unsigned char* reader = (blob -> inst_mem) + mem_add;

    unsigned char b1 = *reader++;
    unsigned char b2 = *reader++;
    unsigned char b3 = *reader++;
    unsigned char b4 = *reader;
    R[rd] = 0;
    R[rd] |= b4;
    R[rd] <<= 8;
    R[rd] |= b3;
    R[rd] <<= 8;
    R[rd] |= b2;
    R[rd] <<= 8;
    R[rd] |= b1;
    return 0;
}

int lbu(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr){
    int mem_add = R[rs1] + imm;

    if(mem_add < 0){
        printf("Illegal Operation Error\n");
        return 1;
        exit(1);
    }

    else if(mem_add == 0x0812 || mem_add == 0x0816){
        virtual_routine_store(R,rd, mem_add, bank_ptr);
        return 0;
    }

    else if(mem_add >= 0xb700 && mem_add <= 0xd700){
        return lbu_h(bank_ptr,mem_add,R,rd);
    }


    unsigned char* reader = blob -> inst_mem + mem_add;
    R[rd] = 0|(*reader);
    return 0;
}

int lhu(int R[], struct blob* blob, int rd, int rs1, int imm, struct Bank* bank_ptr){
    int mem_add = R[rs1] + imm;

    if(mem_add < 0 ){
        printf("Illegal Operation Error\n");
        return 1;
        exit(1);
    }

    else if(mem_add == 0x0812 || mem_add == 0x0816){
        virtual_routine_store(R,rd, mem_add, bank_ptr);
        return 1;
    }

    else if(mem_add >= 0xb700 && mem_add <= 0xd700){
        return lhu_h(bank_ptr,mem_add,R,rd);
    }


    unsigned char* reader = blob -> inst_mem + mem_add;
    unsigned char byte1 = *reader++;
    unsigned char byte2 = *reader;
    R[rd] = 0 | byte1;
    R[rd] <<= 8;
    R[rd] |= byte2;
    return 0;
}

int sb(int R[], struct blob* blob, int rs1, int rs2, int imm, struct Bank* bank_ptr, int* pc){
    int mem_add = R[rs1] + imm;


    if(mem_add < 1024){
        printf("Illegal Operation Error");
        //pc dump
        //reg dump
        return 1;
        exit(1);
    }

    else if(mem_add >= 0x0800 && mem_add <= 0x0834){
        return virtual_routine_load(R, R[rs2],blob, mem_add, bank_ptr, pc);
    }

    else if(mem_add >= 0xb700 && mem_add <= 0xd700){
        return sb_h(bank_ptr,R[rs2],mem_add);
    }



    unsigned char* reader = blob -> data_mem + mem_add;
    *reader = 0;
    *reader = *reader | R[rs2];
    return 0;
}

int sh(int R[], struct blob* blob, int rs1, int rs2, int imm, struct Bank* bank_ptr, int* pc){
    int mem_add = R[rs1] + imm;

    if(mem_add < 1024 ){
        printf("Illegal Operation Error");
        //pc dump
        //reg dump
        return 1;
        exit(1);
    }

    else if(mem_add >= 0x0800 && mem_add <= 0x0834){
        return virtual_routine_load(R, R[rs2],blob, mem_add, bank_ptr, pc);
    }

    else if(mem_add >= 0xb700 && mem_add <= 0xd700){
        return sh_h(bank_ptr,R[rs2],mem_add);
    }

    unsigned char* reader = blob -> inst_mem + mem_add;
    int temp = R[rs2];
    temp >>= 8;
    *reader = 0 | R[rs2];
    reader++;
    *reader = 0 | temp;
    return 0;

}

int sw(int R[], struct blob* blob, int rs1, int rs2, int imm, struct Bank* bank_ptr, int* pc){
    int mem_add = R[rs1] + imm;

    if(mem_add < 1024){
        printf("Illegal Operation Error");
        return 1;
    }

    else if(mem_add >= 0x0800 && mem_add <= 0x0834){
        return virtual_routine_load(R, R[rs2],blob, mem_add, bank_ptr, pc);
    }

    else if(mem_add >= 0xb700 && mem_add <= 0xd700){
        return sw_h(bank_ptr,R[rs2],mem_add);
    }

    unsigned char* reader = (blob -> inst_mem) + mem_add;
    int temp = R[rs2];
    temp >>= 8;
    *reader = 0;
    *reader = *reader | R[rs2];
    reader++;
    *reader = 0 | temp;
    temp >>= 8;
    reader++;
    *reader = 0 | temp;
    temp >>= 8;
    reader++;
    *reader = 0 | temp;
    return 0;
}

int virtual_routine_load(int R[], int num_stored,struct blob* blob,int mem_add, struct Bank* bank_ptr, int* pc){
    if(mem_add == 0x0800){
        printf("%c", num_stored);
    }

    else if(mem_add == 0x0804){
        printf("%d", num_stored);
    }

    else if(mem_add == 0x0808){
        uint32_t number = 0 | num_stored;
        printf("%x", number);
    }

    else if(mem_add == 0x080C){
        printf("CPU Halt Requested\n");
        exit(0);
        //leaves
    }

    else if(mem_add == 0x0820){
        dump_pc(pc);
    }

    else if(mem_add == 0x0824){
        dump_reg(R);
    }

    else if(mem_add == 0x0828){
        unsigned int to_dump = 0;
        unsigned char* reader = blob -> inst_mem + num_stored;
        unsigned char b1 = *reader++;
        unsigned char b2 = *reader++;
        unsigned char b3 = *reader++;
        unsigned char b4 = *reader;
        to_dump = 0;
        to_dump |= b4;
        to_dump <<= 8;
        to_dump |= b3;
        to_dump <<= 8;
        to_dump |= b2;
        to_dump <<= 8;
        to_dump |= b1;
        printf("%x", to_dump);
    }

    else if(mem_add == 0x0830){
        R[28] = malloc_h(bank_ptr, num_stored);
    }

    else if(mem_add == 0x0834){
        return free_h(bank_ptr, num_stored);
    }
    
    return 0;
}

void virtual_routine_store(int R[], int rd, int mem_add, struct Bank* bank_ptr){
    if(mem_add == 0x0812){
        R[rd] = 0;
        char c;
        scanf("%c", &c);
        R[rd] |= c;
    }
    else if(mem_add == 0x0816){
        scanf("%d", &R[rd]);
    }
}

void dump_reg(int R[]){
    for(int i = 0; i < 32; i++){
        printf("R[%d] = 0x%08x;\n", i, R[i]);
    }
}

void dump_pc(int *pc){
    printf("PC = 0x%08x\n", *pc);
}