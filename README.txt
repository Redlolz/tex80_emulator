TEX80 EMULATOR
==============

An emulator for the TEX80 processor.


COMPILING
---------

Make sure you are in a POSIX compliant environment and have a C99 compiler.
Compile with make.


USAGE
-----

Normal execution
    ./tex80 -f programs/helloworld.bin

Debug output
    ./tex80 -d -f programs/shift_n_rotate.bin

Single step mode
    ./tex80 -D -f programs/shift_n_rotate.bin
