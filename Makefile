CC=gcc
#CC=tcc
CFLAGS=-g -std=c99 -Wall -pedantic -I.
LDFLAGS=-L/usr/lib
#CFLAGS=-g -I.
OBJ=tex80.o cpu.o devices.o instructions.o

all: tex80 tex80_tests

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tex80: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

tex80_tests: tex80_tests.o cpu.o devices.o instructions.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	-rm *.o tex80 tex80_tests
