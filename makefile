CC = gcc
CFLAGS = -g -Wall -std=c99

all : toDo

toDo : toDo.o dynamicArray.o task.o
	$(CC) $(CFLAGS) -o $@ $^

dynamicArray.o : dynamicArray.h dynamicArray.c

toDo.o : toDo.c dynamicArray.h task.h

task.o : task.c task.h

.PHONY : clean

clean :
	-rm *.o
	-rm toDo