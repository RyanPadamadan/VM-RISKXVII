TARGET = vm_riskxvii 

CC = gcc

CFLAGS     = -c -Wall -Os -O0 -std=c11 -Oz #-pie -flto 
SRC        = vm_riskxvii.c arlog.c flow_op.c mem_acc.c heap_bank.c
OBJ        = $(SRC:.c=.o)

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) -o $@ $(OBJ) 

.SUFFIXES: .c .o

.c.o:
	 $(CC) $(CFLAGS) $<

run:
	./$(TARGET)

test:
	echo what are we testing?!

clean:
	rm -f *.o *.obj $(TARGET)
