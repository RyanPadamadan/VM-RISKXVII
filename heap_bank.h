#ifndef HEAP_BANK_H
#define HEAP_BANK_H
#include <stdio.h>
#include <stdint.h>

struct Node{
  uint32_t addr;
  int size; //size requested by client
  int num_banks; //size / 64 + 1
  unsigned char* memory;
  struct Node* next; // Has to be of size.
};

struct Bank{
  struct Node* head;
  int banks_allocated;
};

int sb_h(struct Bank* bank_ptr,int value, int mem_add);
int sh_h(struct Bank* bank_ptr, int value, int mem_add);
int sw_h(struct Bank* bank_ptr, int value, int mem_add);

int lb_h(struct Bank* bank_ptr, int mem_add, int R[], int rd);
int lh_h(struct Bank* bank_ptr, int mem_add, int R[], int rd);
int lw_h(struct Bank* bank_ptr, int mem_add, int R[], int rd);
int lbu_h(struct Bank* bank_ptr, int mem_add, int R[], int rd);
int lhu_h(struct Bank* bank_ptr, int mem_add, int R[], int rd);

uint32_t malloc_h(struct Bank* bank_ptr, int size);
int free_h(struct Bank* bank_ptr, uint32_t mem_add);
void insert_after(struct Node** head, struct Node* node, uint32_t addr, int size);
void delete_node(struct Node** head, struct Node* node);

int get_banks(int size);
#endif