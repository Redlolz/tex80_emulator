#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "registers.h"

/* 0x00 - Does nothing */
/* NOP */
void INST_NOP(tex80_registers *regs, unsigned char *memory);
    
/* 0x01 - Stops the processor */
/* HALT */
void INST_HALT(tex80_registers *regs, unsigned char *memory);
    
/* 0x04 - Store data from device X in Alpha */
/* IN A,X */
void INST_IN_A_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x05 - Store data from device X in Beta */
/* IN B,X */
void INST_IN_B_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x06 - Store data from device X in Gamma */
/* IN G,X */
void INST_IN_G_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x07 - Store data from device X in Delta */
/* IN D,X */
void INST_IN_D_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x08 - Store data from Alpha in device X */
/* OUT X,A */
void INST_OUT_X_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x09 - Store data from Beta in device X */
/* OUT X,B */
void INST_OUT_X_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x0A - Store data from Gamma in device X */
/* OUT X,G */
void INST_OUT_X_G(tex80_registers *regs, unsigned char *memory);
    
/* 0x0B - Store data from Delta in device X */
/* OUT X,D */
void INST_OUT_X_D(tex80_registers *regs, unsigned char *memory);
    
/* 0x0C - Push the value of combined register AlphaBeta on top of the stack */
/* PUSH AB */
void INST_PUSH_AB(tex80_registers *regs, unsigned char *memory);
    
/* 0x0D - Push the value of combined register GammaDelta on top of the stack */
/* PUSH GD */
void INST_PUSH_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x0E - Pop the topmost word from the stack into combined register AlphaBeta */
/* POP AB */
void INST_POP_AB(tex80_registers *regs, unsigned char *memory);
    
/* 0x0F - Pop the topmost word from the stack into combined register GammaDelta */
/* POP GD */
void INST_POP_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x40 - Add Beta to Alpha */
/* ADD A,B */
void INST_ADD_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x41 - Add Beta to Alpha with carry */
/* ADDC A,B */
void INST_ADDC_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x42 - Subtract Beta from Alpha */
/* SUB A,B */
void INST_SUB_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x43 - Subtract Beta from Alpha with carry */
/* SUBC A,B */
void INST_SUBC_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x44 - Increments Alpha */
/* INC A */
void INST_INC_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x45 - Increments Beta */
/* INC B */
void INST_INC_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x46 - Increments Gamma */
/* INC G */
void INST_INC_G(tex80_registers *regs, unsigned char *memory);
    
/* 0x47 - Increments Delta */
/* INC D */
void INST_INC_D(tex80_registers *regs, unsigned char *memory);
    
/* 0x48 - Decrements Alpha */
/* DEC A */
void INST_DEC_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x49 - Decrements Beta */
/* DEC B */
void INST_DEC_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x4A - Decrements Gamma */
/* DEC G */
void INST_DEC_G(tex80_registers *regs, unsigned char *memory);
    
/* 0x4B - Decrements Delta */
/* DEC D */
void INST_DEC_D(tex80_registers *regs, unsigned char *memory);
    
/* 0x4C - Performs a logical NOT on Alpha */
/* NOT A */
void INST_NOT_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x4D - Performs a logical AND on Alpha and Beta, stores the result in Alpha */
/* AND A,B */
void INST_AND_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x4E - Performs a logical OR on Alpha and Beta, stores the result in Alpha */
/* OR A,B */
void INST_OR_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x4F - Performs a logical XOR on Alpha and Beta, stores the result in Alpha */
/* XOR A,B */
void INST_XOR_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x50 - Add X to Alpha */
/* ADD A,X */
void INST_ADD_A_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x51 - Add X to Alpha with carry */
/* ADDC A,X */
void INST_ADDC_A_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x52 - Subtract X from A */
/* SUB A,X */
void INST_SUB_A_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x53 - Subtract X from A with carry */
/* SUBC A,X */
void INST_SUBC_A_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x55 - Compares Alpha to Beta */
/* COMP A,B */
void INST_COMP_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0x56 - Compares Alpha to Gamma */
/* COMP A,G */
void INST_COMP_A_G(tex80_registers *regs, unsigned char *memory);
    
/* 0x57 - Compares Alpha to Delta */
/* COMP A,D */
void INST_COMP_A_D(tex80_registers *regs, unsigned char *memory);
    
/* 0x58 - Compares Beta to Alpha */
/* COMP B,A */
void INST_COMP_B_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x5A - Compares Beta to Gamma */
/* COMP B,G */
void INST_COMP_B_G(tex80_registers *regs, unsigned char *memory);
    
/* 0x5B - Compares Beta to Delta */
/* COMP B,D */
void INST_COMP_B_D(tex80_registers *regs, unsigned char *memory);
    
/* 0x5D - Performs a logical AND on Alpha and X, stores the result in Alpha */
/* AND A,X */
void INST_AND_A_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x5E - Performs a logical OR on Alpha and X, stores the result in Alpha */
/* OR A,X */
void INST_OR_A_X(tex80_registers *regs, unsigned char *memory);
    
/* 0x5F - Performs a logical XOR on Alpha and X, stores the result in Alpha */
/* XOR A,X */
void INST_XOR_A_X(tex80_registers *regs, unsigned char *memory);

/* 0x60 - Shifts the value currently stored in Alpha to the left */
/* SHL A */
void INST_SHL_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x61 - Rotates the value currently stored in Alpha to the left */
/* ROL A */
void INST_ROL_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x62 - Shifts the value currently stored in Alpha to the right */
/* SHR A */
void INST_SHR_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x63 - Rotates the value currently stored in Alpha to the right */
/* ROR A */
void INST_ROR_A(tex80_registers *regs, unsigned char *memory);
    
/* 0x80 - Jump to XX */
/* JP XX */
void INST_JP_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0x81 - Jump to XX if zero flag is set */
/* JPZ XX */
void INST_JPZ_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0x82 - Jump to XX if carry flag is set */
/* JPC XX */
void INST_JPC_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0x83 - Jump to XX if true flag is set */
/* JPT XX */
void INST_JPT_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0x85 - Jump to XX if zero flag is not set */
/* JPNZ XX */
void INST_JPNZ_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0x86 - Jump to XX if carry flag is not set */
/* JPNC XX */
void INST_JPNC_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0x87 - Jump to XX if true flag is not set */
/* JPNT XX */
void INST_JPNT_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0x88 - Jump to combined register GammaDelta */
/* JP (GD) */
void INST_JP_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x89 - Jump to combined register GammaDelta if zero flag is set */
/* JPZ (GD) */
void INST_JPZ_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x8A - Jump to combined register GammaDelta if carry flag is set */
/* JPC (GD) */
void INST_JPC_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x8B - Jump to combined register GammaDelta if true flag is set */
/* JPT (GD) */
void INST_JPT_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x8D - Jump to combined register GammaDelta if zero flag is not set */
/* JPNZ (GD) */
void INST_JPNZ_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x8E - Jump to combined register GammaDelta if carry flag is not set */
/* JPNC (GD) */
void INST_JPNC_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x8F - Jump to combined register GammaDelta if true flag is not set */
/* JPNT (GD) */
void INST_JPNT_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0x90 - Pops topmost word of stack into the PC */
/* RET */
void INST_RET(tex80_registers *regs, unsigned char *memory);
    
/* 0x91 - Increments PC by 3, places PC on top of stack and jumps to XX */
/* CALL XX */
void INST_CALL_XX(tex80_registers *regs, unsigned char *memory);

/* 0xA0 - Jump backwards to (PC - Delta) */
/* JB D */
void INST_JB_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xA1 - Jump backwards to (PC - Delta) if zero flag is set */
/* JBZ D */
void INST_JBZ_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xA2 - Jump backwards to (PC - Delta) if carry flag is set */
/* JBC D */
void INST_JBC_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xA3 - Jump backwards to (PC - Delta) if true flag is set */
/* JBT D */
void INST_JBT_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xA5 - Jump backwards to (PC - Delta) if zero flag is not set */
/* JBNZ D */
void INST_JBNZ_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xA6 - Jump backwards to (PC - Delta) if carry flag is not set */
/* JBNC D */
void INST_JBNC_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xA7 - Jump backwards to (PC - Delta) if true flag is not set */
/* JBNT D */
void INST_JBNT_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xA8 - Jump forwards to (PC + Delta) GammaDelta */
/* JF D */
void INST_JF_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xA9 - Jump forwards to (PC + Delta) if zero flag is set */
/* JFZ D */
void INST_JFZ_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xAA - Jump forwards to (PC + Delta) if carry flag is set */
/* JFC D */
void INST_JFC_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xAB - Jump forwards to (PC + Delta) if true flag is set */
/* JFT D */
void INST_JFT_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xAD - Jump forwards to (PC + Delta) if zero flag is not set */
/* JFNZ D */
void INST_JFNZ_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xAE - Jump forwards to (PC + Delta) if carry flag is not set */
/* JFNC D */
void INST_JFNC_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xAF - Jump forwards to (PC + Delta) if true flag is not set */
/* JFNT D */
void INST_JFNT_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xC0 - Store X in Alpha */
/* LOAD A,X */
void INST_LOAD_A_X(tex80_registers *regs, unsigned char *memory);
    
/* 0xC1 - Store X in Beta */
/* LOAD B,X */
void INST_LOAD_B_X(tex80_registers *regs, unsigned char *memory);
    
/* 0xC2 - Store X in Gamma */
/* LOAD G,X */
void INST_LOAD_G_X(tex80_registers *regs, unsigned char *memory);
    
/* 0xC3 - Store X in Delta */
/* LOAD D,X */
void INST_LOAD_D_X(tex80_registers *regs, unsigned char *memory);
    
/* 0xCC - Store the combined register GammaDelta in the Stack Pointer */
/* LOAD SP,GD */
void INST_LOAD_SP_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0xCD - Store the combined register GammaDelta in the Interrupt Pointer */
/* LOAD IP,GD */
void INST_LOAD_IP_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0xCE - Store the Stack Pointer in combined register GammaDelta */
/* LOAD GD,SP */
void INST_LOAD_GD_SP(tex80_registers *regs, unsigned char *memory);
    
/* 0xCF - Store the Interrupt Pointer in combined register GammaDelta */
/* LOAD GD,IP */
void INST_LOAD_GD_IP(tex80_registers *regs, unsigned char *memory);
    
/* 0xD0 - Store Alpha in Alpha */
/* LOAD A,A */
void INST_LOAD_A_A(tex80_registers *regs, unsigned char *memory);
    
/* 0xD1 - Store Alpha in Beta */
/* LOAD B,A */
void INST_LOAD_B_A(tex80_registers *regs, unsigned char *memory);
    
/* 0xD2 - Store Alpha in Gamma */
/* LOAD G,A */
void INST_LOAD_G_A(tex80_registers *regs, unsigned char *memory);
    
/* 0xD3 - Store Alpha in Delta */
/* LOAD D,A */
void INST_LOAD_D_A(tex80_registers *regs, unsigned char *memory);
    
/* 0xD4 - Store Beta in Alpha */
/* LOAD A,B */
void INST_LOAD_A_B(tex80_registers *regs, unsigned char *memory);
    
/* 0xD5 - Store Beta in Beta */
/* LOAD B,B */
void INST_LOAD_B_B(tex80_registers *regs, unsigned char *memory);
    
/* 0xD6 - Store Beta in Gamma */
/* LOAD G,B */
void INST_LOAD_G_B(tex80_registers *regs, unsigned char *memory);
    
/* 0xD7 - Store Beta in Delta */
/* LOAD D,B */
void INST_LOAD_D_B(tex80_registers *regs, unsigned char *memory);
    
/* 0xD8 - Store Gamma in Alpha */
/* LOAD A,G */
void INST_LOAD_A_G(tex80_registers *regs, unsigned char *memory);
    
/* 0xD9 - Store Gamma in Beta */
/* LOAD B,G */
void INST_LOAD_B_G(tex80_registers *regs, unsigned char *memory);
    
/* 0xDA - Store Gamma in Gamma */
/* LOAD G,G */
void INST_LOAD_G_G(tex80_registers *regs, unsigned char *memory);
    
/* 0xDB - Store Gamma in Delta */
/* LOAD D,G */
void INST_LOAD_D_G(tex80_registers *regs, unsigned char *memory);
    
/* 0xDC - Store Delta in Alpha */
/* LOAD A,D */
void INST_LOAD_A_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xDD - Store Delta in Beta */
/* LOAD B,D */
void INST_LOAD_B_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xDE - Store Delta in Gamma */
/* LOAD G,D */
void INST_LOAD_G_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xDF - Store Delta in Delta */
/* LOAD D,D */
void INST_LOAD_D_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xE0 - Store Alpha in memory location from combined register AlphaBeta */
/* STR (AB),A */
void INST_STR_AB_A(tex80_registers *regs, unsigned char *memory);
    
/* 0xE1 - Store Alpha in memory location XX */
/* STR (XX),A */
void INST_STR_XX_A(tex80_registers *regs, unsigned char *memory);
    
/* 0xE3 - Store Alpha in memory location from combined register GammaDelta */
/* STR (GD),A */
void INST_STR_GD_A(tex80_registers *regs, unsigned char *memory);
    
/* 0xE4 - Store Beta in memory location from combined register AlphaBeta */
/* STR (AB),B */
void INST_STR_AB_B(tex80_registers *regs, unsigned char *memory);
    
/* 0xE5 - Store Beta in memory location XX */
/* STR (XX),B */
void INST_STR_XX_B(tex80_registers *regs, unsigned char *memory);
    
/* 0xE7 - Store Beta in memory location from combined register GammaDelta */
/* STR (GD),B */
void INST_STR_GD_B(tex80_registers *regs, unsigned char *memory);
    
/* 0xE8 - Store Gamma in memory location from combined register AlphaBeta */
/* STR (AB),G */
void INST_STR_AB_G(tex80_registers *regs, unsigned char *memory);
    
/* 0xE9 - Store Gamma in memory location XX */
/* STR (XX),G */
void INST_STR_XX_G(tex80_registers *regs, unsigned char *memory);
    
/* 0xEB - Store Gamma in memory location from combined register GammaDelta */
/* STR (GD),G */
void INST_STR_GD_G(tex80_registers *regs, unsigned char *memory);
    
/* 0xEC - Store Delta in memory location from combined register AlphaBeta */
/* STR (AB),D */
void INST_STR_AB_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xED - Store Delta in memory location XX */
/* STR (XX),D */
void INST_STR_XX_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xEF - Store Delta in memory location from combined register GammaDelta */
/* STR (GD),D */
void INST_STR_GD_D(tex80_registers *regs, unsigned char *memory);
    
/* 0xF0 - Load data from the memory location of combined register AlphaBeta in Alpha */
/* LOAD A,(AB) */
void INST_LOAD_A_AB(tex80_registers *regs, unsigned char *memory);
    
/* 0xF1 - Load data from memory location XX */
/* LOAD A,(XX) */
void INST_LOAD_A_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0xF3 - Load data from the memory location of combined register GammaDelta in Alpha */
/* LOAD A,(GD) */
void INST_LOAD_A_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0xF4 - Load data from the memory location of combined register AlphaBeta in Beta */
/* LOAD B,(AB) */
void INST_LOAD_B_AB(tex80_registers *regs, unsigned char *memory);
    
/* 0xF5 - Load data from memory location XX */
/* LOAD B,(XX) */
void INST_LOAD_B_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0xF7 - Load data from the memory location of combined register GammaDelta in Beta */
/* LOAD B,(GD) */
void INST_LOAD_B_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0xF8 - Load data from the memory location of combined register AlphaBeta in Gamma */
/* LOAD G,(AB) */
void INST_LOAD_G_AB(tex80_registers *regs, unsigned char *memory);
    
/* 0xF9 - Load data from memory location XX */
/* LOAD G,(XX) */
void INST_LOAD_G_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0xFB - Load data from the memory location of combined register GammaDelta in Gamma */
/* LOAD G,(GD) */
void INST_LOAD_G_GD(tex80_registers *regs, unsigned char *memory);
    
/* 0xFC - Load data from the memory location of combined register AlphaBeta in Delta */
/* LOAD D,(AB) */
void INST_LOAD_D_AB(tex80_registers *regs, unsigned char *memory);
    
/* 0xFD - Load data from memory location XX */
/* LOAD D,(XX) */
void INST_LOAD_D_XX(tex80_registers *regs, unsigned char *memory);
    
/* 0xFF - Load data from the memory location of combined register GammaDelta in Delta */
/* LOAD D,(GD) */
void INST_LOAD_D_GD(tex80_registers *regs, unsigned char *memory);
    
#endif
