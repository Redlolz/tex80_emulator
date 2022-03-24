#CC=gcc
CC=tcc
CFLAGS=-g -std=c99 -Wall -pedantic -I.
#CFLAGS=-g -I.
OBJ=tex80.o cpu.o instructions.o

all: tex80 tex80_tests

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tex80: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

tex80_tests: tex80_tests.o cpu.o instructions.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	-rm *.o tex80 tex80_tests
