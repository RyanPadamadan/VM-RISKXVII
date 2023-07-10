#include "heap_bank.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BANK_SIZE 64
#define MAX_BANKS 128

int sb_h(struct Bank *bank_ptr, int value, int mem_add) {
  // get correct node in which
  struct Node *ptr = bank_ptr->head;
  int required_index = 0;
  if (!ptr) {
    return 1;
  }
  struct Node *next_node = bank_ptr->head->next;
  if (!next_node) {
    if (!(ptr->addr <= mem_add && (ptr->size + ptr->addr) > mem_add)) {
      return 1;
    } else {
      required_index = mem_add - ptr->addr;
    }
  }

  while (ptr && next_node) {
    if (ptr->addr <= mem_add && next_node->addr > mem_add) {
      if (!(ptr->addr <= mem_add && (ptr->size + ptr->addr) > mem_add)) {
        return 1;
      } else {
        required_index = mem_add - ptr->addr;
        break;
      }
    }
    ptr = ptr->next;
    next_node = ptr->next;
  }
  unsigned char *reader = ptr->memory + required_index;
  *reader = 0;
  *reader = *reader | value;
  return 0;
}

int sh_h(struct Bank *bank_ptr, int value, int mem_add) {
  struct Node *ptr = bank_ptr->head;
  int required_index = 0;
  if (!ptr) {
    return 1;
  }
  struct Node *next_node = bank_ptr->head->next;
  if (!next_node) {
    if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
      return 1;
    } else {
      required_index = mem_add - ptr->addr;
    }
  }

  while (ptr && next_node) {
    if (ptr->addr <= mem_add && next_node->addr > mem_add) {
      if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
        return 1;
      } else {
        required_index = mem_add - ptr->addr;
        if (ptr->size - 1 <= required_index + 1) {
          return 1;
        }
        break;
      }
    }
    ptr = ptr->next;
    next_node = ptr->next;
  }
  unsigned char *reader = ptr->memory + required_index;
  int temp = value;
  temp >>= 8;
  *reader = 0 | value;
  // // printf(" M[%d]:%02x ", mem_add, *reader);
  reader++;
  *reader = 0 | temp;
  return 0;
}

int sw_h(struct Bank *bank_ptr, int value, int mem_add) {
  struct Node *ptr = bank_ptr->head;
  int required_index = 0;
  if (!ptr) {
    return 1;
  }
  struct Node *next_node = bank_ptr->head->next;
  if (!next_node) {
    if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
      return 1;
    } else {
      required_index = mem_add - ptr->addr;
    }
  }

  while (ptr && next_node) {
    if (ptr->addr <= mem_add && next_node->addr > mem_add) {
      if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
        return 1;
      } else {
        required_index = mem_add - ptr->addr;
        if (ptr->size - 1 <= required_index + 3) {
          return 1;
        }
        break;
      }
    }
    ptr = ptr->next;
    next_node = ptr->next;
  }
  unsigned char *reader = ptr->memory + required_index;
  int temp = value;
  temp >>= 8;
  *reader = 0;
  *reader = *reader | value;
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

int lb_h(struct Bank *bank_ptr, int mem_add, int R[], int rd) {
  struct Node *ptr = bank_ptr->head;
  int required_index = 0;
  if (!ptr) {
    return 1;
  }
  struct Node *next_node = bank_ptr->head->next;
  if (!next_node) {
    if (!(ptr->addr <= mem_add && (ptr->size + ptr->addr) > mem_add)) {
      return 1;
    } else {
      required_index = mem_add - ptr->addr;
    }
  }

  while (ptr && next_node) {
    if (ptr->addr <= mem_add && next_node->addr > mem_add) {
      if (!(ptr->addr <= mem_add && (ptr->size + ptr->addr) > mem_add)) {
        return 1;
      } else {
        required_index = mem_add - ptr->addr;
        break;
      }
    }
    ptr = ptr->next;
    next_node = ptr->next;
  }
  unsigned char *reader = ptr->memory + required_index;
  unsigned char byte = *reader;
  R[rd] = 0 | byte;
  R[rd] <<= 24;
  R[rd] >>= 24;
  return 0;
}

int lh_h(struct Bank *bank_ptr, int mem_add, int R[], int rd) {
  struct Node *ptr = bank_ptr->head;
  int required_index = 0;
  if (!ptr) {
    return 1;
  }
  struct Node *next_node = bank_ptr->head->next;
  if (!next_node) {
    if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
      return 1;
    } else {
      required_index = mem_add - ptr->addr;
    }
  }

  while (ptr && next_node) {
    if (ptr->addr <= mem_add && next_node->addr > mem_add) {
      if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
        return 1;
      } else {
        required_index = mem_add - ptr->addr;
        if (ptr->size - 1 <= required_index + 1) {
          return 1;
        }
        break;
      }
    }
    ptr = ptr->next;
    next_node = ptr->next;
  }
  unsigned char *reader = ptr->memory + required_index;
  unsigned char byte1 = *reader++;
  unsigned char byte2 = *reader;

  R[rd] = 0 | byte2;
  R[rd] <<= 8;
  R[rd] |= byte1;
  R[rd] <<= 16;
  R[rd] >>= 16;
  return 0;
}

int lw_h(struct Bank *bank_ptr, int mem_add, int R[], int rd) {
  struct Node *ptr = bank_ptr->head;
  int required_index = 0;
  if (!ptr) {
    return 1;
  }
  struct Node *next_node = bank_ptr->head->next;
  if (!next_node) {
    if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
      return 1;
    } else {
      required_index = mem_add - ptr->addr;
    }
  }

  while (ptr && next_node) {
    if (ptr->addr <= mem_add && next_node->addr > mem_add) {
      if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
        return 1;
      } else {
        required_index = mem_add - ptr->addr;
        if (ptr->size - 1 <= required_index + 3) {
          return 1;
        }
        break;
      }
    }
    ptr = ptr->next;
    next_node = ptr->next;
  }
  unsigned char *reader = ptr->memory + required_index;
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

int lbu_h(struct Bank *bank_ptr, int mem_add, int R[], int rd) {
  struct Node *ptr = bank_ptr->head;
  int required_index = 0;
  if (!ptr) {
    return 1;
  }
  struct Node *next_node = bank_ptr->head->next;
  if (!next_node) {
    if (!(ptr->addr <= mem_add && (ptr->size + ptr->addr) > mem_add)) {
      return 1;
    } else {
      required_index = mem_add - ptr->addr;
    }
  }

  while (ptr && next_node) {
    if (ptr->addr <= mem_add && next_node->addr > mem_add) {
      if (!(ptr->addr <= mem_add && (ptr->size + ptr->addr) > mem_add)) {
        return 1;
      } else {
        required_index = mem_add - ptr->addr;
        break;
      }
    }
    ptr = ptr->next;
    next_node = ptr->next;
  }
  unsigned char *reader = ptr->memory + required_index;
  R[rd] = 0 | (*reader);
  return 0;
}

int lhu_h(struct Bank *bank_ptr, int mem_add, int R[], int rd) {
  struct Node *ptr = bank_ptr->head;
  int required_index = 0;
  if (!ptr) {
    return 1;
  }
  struct Node *next_node = bank_ptr->head->next;
  if (!next_node) {
    if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
      return 1;
    } else {
      required_index = mem_add - ptr->addr;
    }
  }

  while (ptr && next_node) {
    if (ptr->addr <= mem_add && next_node->addr > mem_add) {
      if (!(ptr->addr <= mem_add && ptr->size + ptr->addr > mem_add)) {
        return 1;
      } else {
        required_index = mem_add - ptr->addr;
        if (ptr->size - 1 <= required_index + 1) {
          return 1;
        }
        break;
      }
    }
    ptr = ptr->next;
    next_node = ptr->next;
  }
  unsigned char *reader = ptr->memory + required_index;
  unsigned char byte1 = *reader++;
  unsigned char byte2 = *reader;
  R[rd] = 0 | byte1;
  R[rd] <<= 8;
  R[rd] |= byte2;
  return 0;
}

uint32_t malloc_h(struct Bank *bank_ptr, int size) {
  // if head is null then create new head
  // if there are no banks left or the number of banks left is not enough
  // immediate reject loop through list of banks insert in between elements if
  // there is space insert at end if we reach the end and there is space
  uint32_t curr_address = 0;
  int curr_banks = 0;
  // printf("%d\n", size);
  if (get_banks(size) > MAX_BANKS) {
    return 0;
  }

  if (!bank_ptr->head) {
    struct Node *node = calloc(1, sizeof(struct Node));
    node->addr = 0xb700;
    node->size = size;
    node->num_banks = get_banks(size);
    node->memory = (unsigned char *)malloc(sizeof(char) * size);
    bank_ptr->head = node;
    bank_ptr->banks_allocated = node->num_banks;
    return node->addr;
  }

  else if (get_banks(size) > MAX_BANKS - bank_ptr->banks_allocated) {
    return 0;
  }

  else {
    struct Node *ptr = bank_ptr->head;
    while (ptr) {
      curr_address = ptr->addr;
      curr_banks = get_banks(ptr->size);
      if (!(ptr->next)) {
        // 0xd700 is 0xb700 + 8192

        if ((0xd700 - curr_address) / 64 < get_banks(size)) {
          return 0;
        }

        insert_after(&(bank_ptr->head), ptr,
                     curr_address + BANK_SIZE * curr_banks, size);
        bank_ptr->banks_allocated += get_banks(size);
        break;
      }

      struct Node *next = ptr->next;
      int diff =
          (next->addr - (ptr->addr + (get_banks(ptr->size)) * BANK_SIZE)) / 64;
      if (diff >= get_banks(size)) {
        insert_after(&(bank_ptr->head), ptr,
                     curr_address + BANK_SIZE * curr_banks, size);
        bank_ptr->banks_allocated += get_banks(size);
        break;
      }

      ptr = ptr->next;
    }
  }
  return curr_address + BANK_SIZE * curr_banks;
}

int free_h(struct Bank *bank_ptr, uint32_t mem_add) {
  // if mem_add is not the first address of an allocation/mem_add is just wrong
  // lol then it is invalid delete the node at which mem_add is the first
  // address of an allocation
  struct Node *ptr = bank_ptr->head;
  while (ptr) {
    if (ptr->addr == mem_add) {
      bank_ptr->banks_allocated -= ptr->num_banks;
      delete_node(&(bank_ptr->head), ptr);
      return 0;
    }
  }
  return 1;
}

void insert_after(struct Node **head, struct Node *prev, uint32_t addr,
                  int size) {
  struct Node *node = *head;

  while (node != prev) {
    node = node->next;
  }

  // Create the new node.
  struct Node *temp = prev->next;
  node->next = calloc(1, sizeof(struct Node));
  node->next->addr = addr;
  node->next->size = size;
  node->next->num_banks = get_banks(size);
  node->next->memory = (unsigned char *)malloc(sizeof(char) * size);
  node->next->next = temp;
  return;
}

void delete_node(struct Node **head, struct Node *node) {
  if (node == *head) {
    *head = node->next;
    free(node->memory);
    free(node);
    return;
  }

  struct Node *before = *head;
  while (before->next != node) {
    before = before->next;
  }

  before->next = node->next;

  free(node->memory);
  free(node);

  return;
}

int get_banks(int size) {
  if (size % 64 == 0) {
    return size / 64;
  }
  if (size == 0)
    return 0;
  return size / 64 + 1;
}
