CC=cc
CFLAGS=-g -std=c99 -Wall -pedantic -I.
LDFLAGS=-L/usr/lib
OBJ=tex80.o cpu.o devices.o instructions.o

all: tex80 tex80_tests

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tex80: $(OBJ)
	$(CC) -o $@ tex80.o cpu.o devices.o instructions.o $(CFLAGS) $(LDFLAGS)

tex80_tests: tex80_tests.o cpu.o devices.o instructions.o
	$(CC) -o $@ tex80_tests.o cpu.o devices.o instructions.o $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	-rm *.o tex80 tex80_tests
