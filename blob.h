#ifndef BLOB_H
#define BLOB_H
#include <stdio.h>
#include <stdint.h>

#define INST_MEM_SIZE 1024
#define DATA_MEM_SIZE 1024

struct blob {
  unsigned char inst_mem[INST_MEM_SIZE];
  unsigned char data_mem[DATA_MEM_SIZE];
};

#endif