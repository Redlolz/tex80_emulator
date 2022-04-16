#ifndef CPU_H
#define CPU_H
#include "registers.h"
#include "instructions.h"

typedef void (*instruction)(tex80_registers*, unsigned char*);

void tex80_init(tex80_registers *regs, unsigned char *memory);
void tex80_debug(tex80_registers *regs, unsigned char *memory);
void tex80_step(tex80_registers *regs, unsigned char *memory);

#endif
