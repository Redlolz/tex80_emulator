#ifndef REGISTERS_H
#define REGISTERS_H

typedef struct {
        unsigned char alpha;
        unsigned char beta;
        unsigned char gamma;
        unsigned char delta;

        _Bool flag_zero;
        _Bool flag_carry;
        _Bool flag_true;

        _Bool intr;
        _Bool intr_ack;

        unsigned int  pc;
        unsigned int  sp;
        unsigned int  ip;
        _Bool halt;
} tex80_registers;

#endif
