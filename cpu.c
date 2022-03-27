#include <stdio.h>
#include <stdbool.h>
#include "cpu.h"
#include "registers.h"
#include "instructions.h"

typedef void (*instruction)(tex80_registers*, unsigned char*);
instruction instruction_table[] = {
/*0x00*/    INST_NOP,        INST_HALT,       INST_NOP,        INST_NOP,
/*0x04*/    INST_IN_A_X,     INST_IN_B_X,     INST_IN_G_X,     INST_IN_D_X,
/*0x08*/    INST_OUT_X_A,    INST_OUT_X_B,    INST_OUT_X_G,    INST_OUT_X_D,
/*0x0c*/    INST_PUSH_AB,    INST_PUSH_GD,    INST_POP_AB,     INST_POP_GD,
/*0x10*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x14*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x18*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x1c*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x20*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x24*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x28*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x2c*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x30*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x34*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x38*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x3c*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x40*/    INST_ADD_A_B,    INST_ADDC_A_B,   INST_SUB_A_B,    INST_SUBC_A_B,
/*0x44*/    INST_INC_A,      INST_INC_B,      INST_INC_G,      INST_INC_D,
/*0x48*/    INST_DEC_A,      INST_DEC_B,      INST_DEC_G,      INST_DEC_D,
/*0x4c*/    INST_NOT_A,      INST_AND_A_B,    INST_OR_A_B,     INST_XOR_A_B,
/*0x50*/    INST_ADD_A_X,    INST_ADDC_A_X,   INST_SUB_A_X,    INST_SUBC_A_X,
/*0x54*/    INST_NOP,        INST_COMP_A_B,   INST_COMP_A_G,   INST_COMP_A_D,
/*0x58*/    INST_COMP_B_A,   INST_NOP,        INST_COMP_B_G,   INST_COMP_B_D,
/*0x5c*/    INST_NOP,        INST_AND_A_X,    INST_OR_A_X,     INST_XOR_A_X,
/*0x60*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x64*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x68*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x6c*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x70*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x74*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x78*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x7c*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x80*/    INST_JP_XX,      INST_JPZ_XX,     INST_JPC_XX,     INST_JPT_XX,
/*0x84*/    INST_NOP,        INST_JPNZ_XX,    INST_JPNC_XX,    INST_JPNT_XX,
/*0x88*/    INST_JP_GD,      INST_JPZ_GD,     INST_JPC_GD,     INST_JPT_GD,
/*0x8c*/    INST_NOP,        INST_JPNZ_GD,    INST_JPNC_GD,    INST_JPNT_GD,
/*0x90*/    INST_RET,        INST_CALL_XX,    INST_NOP,        INST_NOP,
/*0x94*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x98*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0x9c*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0xa0*/    INST_JB_D,       INST_JBZ_D,      INST_JBC_D,      INST_JBT_D,
/*0xa4*/    INST_NOP,        INST_JBNZ_D,     INST_JBNC_D,     INST_JBNT_D,
/*0xa8*/    INST_JF_D,       INST_JFZ_D,      INST_JFC_D,      INST_JFT_D,
/*0xac*/    INST_NOP,        INST_JFNZ_D,     INST_JFNC_D,     INST_JFNT_D,
/*0xb0*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0xb4*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0xb8*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0xbc*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0xc0*/    INST_LOAD_A_X,   INST_LOAD_B_X,   INST_LOAD_G_X,   INST_LOAD_D_X, 
/*0xc4*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0xc8*/    INST_NOP,        INST_NOP,        INST_NOP,        INST_NOP,
/*0xcc*/    INST_LOAD_SP_GD, INST_LOAD_IP_GD, INST_LOAD_GD_SP, INST_LOAD_GD_IP,
/*0xd0*/    INST_LOAD_A_A,   INST_LOAD_B_A,   INST_LOAD_G_A,   INST_LOAD_D_A, 
/*0xd4*/    INST_LOAD_A_B,   INST_LOAD_B_B,   INST_LOAD_G_B,   INST_LOAD_D_B, 
/*0xd8*/    INST_LOAD_A_G,   INST_LOAD_B_G,   INST_LOAD_G_G,   INST_LOAD_D_G, 
/*0xdc*/    INST_LOAD_A_D,   INST_LOAD_B_D,   INST_LOAD_G_D,   INST_LOAD_D_D, 
/*0xe0*/    INST_STR_AB_A,   INST_STR_XX_A,   INST_NOP,        INST_STR_GD_A,
/*0xe4*/    INST_STR_AB_B,   INST_STR_XX_B,   INST_NOP,        INST_STR_GD_B,
/*0xe8*/    INST_STR_AB_G,   INST_STR_XX_G,   INST_NOP,        INST_STR_GD_G,
/*0xec*/    INST_STR_AB_D,   INST_STR_XX_D,   INST_NOP,        INST_STR_GD_D,
/*0xf0*/    INST_LOAD_A_AB,  INST_LOAD_A_XX,  INST_NOP,        INST_LOAD_A_GD,
/*0xf4*/    INST_LOAD_B_AB,  INST_LOAD_B_XX,  INST_NOP,        INST_LOAD_B_GD,
/*0xf8*/    INST_LOAD_G_AB,  INST_LOAD_G_XX,  INST_NOP,        INST_LOAD_G_GD,
/*0xfc*/    INST_LOAD_D_AB,  INST_LOAD_D_XX,  INST_NOP,        INST_LOAD_D_GD,
};

int instruction_pc_add[] = {
    1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 
    1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 
};

void tex80_init(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = 0;
    regs->beta  = 0;
    regs->gamma = 0;
    regs->delta = 0;
    
    regs->flag_zero  = 0;
    regs->flag_carry = 0;
    regs->flag_true  = 0;

    regs->sp = 0x07ff;
    regs->pc = 0;
}

void tex80_debug(tex80_registers *regs, unsigned char *memory)
{
    printf("ALPHA: 0x%02X\nBETA:  0x%02X\nGAMMA: 0x%02X\nDELTA: 0x%02X\n",
            regs->alpha, regs->beta, regs->gamma, regs->delta);
    printf("FLAG ZERO:  0x%02X\nFLAG CARRY: 0x%02X\nFLAG TRUE:  0x%02X\n",
            regs->flag_zero, regs->flag_carry, regs->flag_true);
    printf("SP: 0x%04X\nPC: 0x%04X\n", regs->sp, regs->pc);
}

void tex80_step(tex80_registers *regs, unsigned char *memory)
{
    regs->intr_ack = false;
    if (regs->intr == true) {
        regs->intr_ack = true;

        memory[regs->sp] = regs->pc >> 8;
        regs->sp--;
        memory[regs->sp] = regs->pc & 0x00ff;
        regs->sp--;
        regs->pc = regs->ip;
    }
    unsigned char current_inst = memory[regs->pc];
    instruction_table[current_inst](regs, memory);
    regs->pc += instruction_pc_add[current_inst];
}
