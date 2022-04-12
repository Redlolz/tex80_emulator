#include <stdio.h>
#include "instructions.h"
#include "registers.h"
#include "devices.h"

static void set_zero_flag(_Bool *zero_flag, unsigned char *reg)
{
    if (*reg == 0) { *zero_flag = 1; } else { *zero_flag = 0; }
}

static void overflow_check_carry(unsigned char *reg1, unsigned char reg2,
        _Bool *carry_flag, unsigned char pos_or_neg)
{
    if (pos_or_neg == 1 && *reg1 + reg2 > 255) {
        *carry_flag = 1;
    } else if (pos_or_neg == 0 && *reg1 - reg2 < 0) {
        *carry_flag = 1;
    } else { *carry_flag = 0; }
}

// Misc instructions
void INST_NOP(tex80_registers *regs, unsigned char *memory)
{}

void INST_HALT(tex80_registers *regs, unsigned char *memory)
{
    regs->halt = 1;
}

// IO instructions
void INST_IN_A_X(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = read_device(memory[regs->pc+1]);
}
void INST_IN_B_X(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = read_device(memory[regs->pc+1]);
}
void INST_IN_G_X(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = read_device(memory[regs->pc+1]);
}
void INST_IN_D_X(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = read_device(memory[regs->pc+1]);
}

void INST_OUT_X_A(tex80_registers *regs, unsigned char *memory)
{
    write_device(memory[regs->pc+1], regs->alpha);
}

void INST_OUT_X_B(tex80_registers *regs, unsigned char *memory)
{
    write_device(memory[regs->pc+1], regs->beta);
}

void INST_OUT_X_G(tex80_registers *regs, unsigned char *memory)
{
    write_device(memory[regs->pc+1], regs->gamma);
}

void INST_OUT_X_D(tex80_registers *regs, unsigned char *memory)
{
    write_device(memory[regs->pc+1], regs->delta);
}

// Push and pop instructions
void INST_PUSH_AB(tex80_registers *regs, unsigned char *memory)
{
    memory[regs->sp] = regs->alpha;
    regs->sp--;
    memory[regs->sp] = regs->beta;
    regs->sp--;
}
void INST_PUSH_GD(tex80_registers *regs, unsigned char *memory)
{
    memory[regs->sp] = regs->gamma;
    regs->sp--;
    memory[regs->sp] = regs->delta;
    regs->sp--;
}
void INST_POP_AB(tex80_registers *regs, unsigned char *memory)
{
    regs->sp++;
    regs->beta = memory[regs->sp];
    regs->sp++;
    regs->alpha = memory[regs->sp];
}
void INST_POP_GD(tex80_registers *regs, unsigned char *memory)
{
    regs->sp++;
    regs->delta = memory[regs->sp];
    regs->sp++;
    regs->gamma = memory[regs->sp];
}

// Arithmetic instructions
void INST_ADD_A_B(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha += regs->beta;
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}
    
void INST_ADDC_A_B(tex80_registers *regs, unsigned char *memory)
{
    overflow_check_carry(&regs->alpha, regs->beta, &regs->flag_carry, 1);
    regs->alpha += regs->beta;
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}
    
void INST_SUB_A_B(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha -= regs->beta;
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}
    
void INST_SUBC_A_B(tex80_registers *regs, unsigned char *memory)
{
    overflow_check_carry(&regs->alpha, regs->beta, &regs->flag_carry, 0);
    regs->alpha -= regs->beta;
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}

// Increment and decrement instructions
void INST_INC_A(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha++;
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}

void INST_INC_B(tex80_registers *regs, unsigned char *memory)
{
    regs->beta++;
    set_zero_flag(&regs->flag_zero, &regs->beta);
}

void INST_INC_G(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma++;
    set_zero_flag(&regs->flag_zero, &regs->gamma);
}

void INST_INC_D(tex80_registers *regs, unsigned char *memory)
{
    regs->delta++;
    set_zero_flag(&regs->flag_zero, &regs->delta);
}

void INST_DEC_A(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha--;
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}

void INST_DEC_B(tex80_registers *regs, unsigned char *memory)
{
    regs->beta--;
    set_zero_flag(&regs->flag_zero, &regs->beta);
}

void INST_DEC_G(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma--;
    set_zero_flag(&regs->flag_zero, &regs->gamma);
}

void INST_DEC_D(tex80_registers *regs, unsigned char *memory)
{
    regs->delta--;
    set_zero_flag(&regs->flag_zero, &regs->delta);
}

// Logic instructions
void INST_NOT_A(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = ~regs->alpha;
}

void INST_AND_A_B(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = regs->alpha & regs->beta;
}

void INST_OR_A_B(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = regs->alpha | regs->beta;
}

void INST_XOR_A_B(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = (regs->alpha | regs->beta) & (~regs->alpha | ~regs->beta);
}

// Arithmetic immediate instructions
void INST_ADD_A_X(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha += memory[regs->pc+1];
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}

void INST_ADDC_A_X(tex80_registers *regs, unsigned char *memory)
{
    overflow_check_carry(&regs->alpha, memory[regs->pc+1], &regs->flag_carry, 1);
    regs->alpha += memory[regs->pc+1];
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}

void INST_SUB_A_X(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha -= memory[regs->pc+1];
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}

void INST_SUBC_A_X(tex80_registers *regs, unsigned char *memory)
{
    overflow_check_carry(&regs->alpha, memory[regs->pc+1], &regs->flag_carry, 0);
    regs->alpha -= memory[regs->pc+1];
    set_zero_flag(&regs->flag_zero, &regs->alpha);
}

// COMP instructions
void INST_COMP_A_B(tex80_registers *regs, unsigned char *memory)
{
    if (regs->alpha == regs->beta) {
        regs->flag_true = 1;
    } else {
        regs->flag_true = 0;
    }
}

void INST_COMP_A_G(tex80_registers *regs, unsigned char *memory)
{
    if (regs->alpha == regs->gamma) {
        regs->flag_true = 1;
    } else {
        regs->flag_true = 0;
    }
}

void INST_COMP_A_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->alpha == regs->delta) {
        regs->flag_true = 1;
    } else {
        regs->flag_true = 0;
    }
}

void INST_COMP_B_A(tex80_registers *regs, unsigned char *memory)
{
    if (regs->beta == regs->alpha) {
        regs->flag_true = 1;
    } else {
        regs->flag_true = 0;
    }
}

void INST_COMP_B_G(tex80_registers *regs, unsigned char *memory)
{
    if (regs->beta == regs->gamma) {
        regs->flag_true = 1;
    } else {
        regs->flag_true = 0;
    }
}

void INST_COMP_B_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->beta == regs->delta) {
        regs->flag_true = 1;
    } else {
        regs->flag_true = 0;
    }
}

// Logic immediate instructions
void INST_AND_A_X(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = regs->alpha & memory[regs->pc+1];
}

void INST_OR_A_X(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = regs->alpha | memory[regs->pc+1];
}

void INST_XOR_A_X(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = (regs->alpha | memory[regs->pc+1]) &
        (~regs->alpha | ~memory[regs->pc+1]);
}

// Shift instructions
void INST_SHL_A(tex80_registers *regs, unsigned char *memory)
{
    if ((regs->alpha & 0x80) == 0x80)
        regs->flag_carry = 1;
    else
        regs->flag_carry = 0;
    regs->alpha <<= 1;
}
    
void INST_ROL_A(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = (regs->alpha << 1) | (regs->alpha >> 7);
}
    
void INST_SHR_A(tex80_registers *regs, unsigned char *memory)
{
    if ((regs->alpha & 0x01) == 0x01)
        regs->flag_carry = 1;
    else
        regs->flag_carry = 0;
    regs->alpha >>= 1;
}
    
void INST_ROR_A(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = (regs->alpha >> 1) | (regs->alpha << 7);
}

// Jump instructions
void INST_JP_XX(tex80_registers *regs, unsigned char *memory)
{
    regs->pc = (memory[regs->pc+1] << 8) + memory[regs->pc+2];
}

void INST_JPZ_XX(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_zero == 1) {
        regs->pc = (memory[regs->pc+1] << 8) + memory[regs->pc+2];
    } else {
        /* Since this is a conditional jump, we need to manually increment
         * the program counter. This is the same for every other conditional
         * jump 
         */
        regs->pc += 3;
    }
}

void INST_JPC_XX(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_carry == 1) {
        regs->pc = (memory[regs->pc+1] << 8) + memory[regs->pc+2];
    } else { regs->pc += 3; }
}

void INST_JPT_XX(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_true == 1) {
        regs->pc = (memory[regs->pc+1] << 8) + memory[regs->pc+2];
    } else { regs->pc += 3; }
}

void INST_JPNZ_XX(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_zero != 1) {
        regs->pc = (memory[regs->pc+1] << 8) + memory[regs->pc+2];
    } else { regs->pc += 3; }
}

void INST_JPNC_XX(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_carry != 1) {
        regs->pc = (memory[regs->pc+1] << 8) + memory[regs->pc+2];
    } else { regs->pc += 3; }
}

void INST_JPNT_XX(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_true != 1) {
        regs->pc = (memory[regs->pc+1] << 8) + memory[regs->pc+2];
    } else { regs->pc += 3; }
}

void INST_JP_GD(tex80_registers *regs, unsigned char *memory)
{
    regs->pc = (regs->gamma << 8) + regs->delta;
}

void INST_JPZ_GD(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_zero == 1) {
        regs->pc = (regs->gamma << 8) + regs->delta;
    } else { regs->pc += 1; }
}

void INST_JPC_GD(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_carry == 1) {
        regs->pc = (regs->gamma << 8) + regs->delta;
    } else { regs->pc += 1; }
}

void INST_JPT_GD(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_true == 1) {
        regs->pc = (regs->gamma << 8) + regs->delta;
    } else { regs->pc += 1; }
}

void INST_JPNZ_GD(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_zero != 1) {
        regs->pc = (regs->gamma << 8) + regs->delta;
    } else { regs->pc += 1; }
}

void INST_JPNC_GD(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_carry != 1) {
        regs->pc = (regs->gamma << 8) + regs->delta;
    } else { regs->pc += 1; }
}

void INST_JPNT_GD(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_true != 1) {
        regs->pc = (regs->gamma << 8) + regs->delta;
    } else { regs->pc += 1; }
}

// Subroutine instructions
void INST_CALL_XX(tex80_registers *regs, unsigned char *memory)
{
    regs->pc = regs->pc + 3;
    memory[regs->sp] = regs->pc >> 8;
    memory[regs->sp-1] = regs->pc & 0x00ff;
    regs->pc = regs->pc - 3;
    regs->pc = (memory[regs->pc+1] << 8) + memory[regs->pc+2];
    regs->sp = regs->sp - 2;
}

void INST_RET(tex80_registers *regs, unsigned char *memory)
{
    regs->pc = (memory[regs->sp+2] << 8) + memory[regs->sp+1];
    regs->sp = regs->sp + 2;
}

// Relative jump instructions
void INST_JB_D(tex80_registers *regs, unsigned char *memory)
{
    regs->pc = regs->pc - regs->delta;
}
    
void INST_JBZ_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_zero == 1) {
        regs->pc = regs->pc - regs->delta;
    } else {
        // Since this is a conditional jump, we need to manually increment the
        // program counter. This is the same for every other conditional jump
        regs->pc += 1;
    }
}
    
void INST_JBC_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_carry == 1) {
        regs->pc = regs->pc - regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JBT_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_true == 1) {
        regs->pc = regs->pc - regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JBNZ_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_zero != 1) {
        regs->pc = regs->pc - regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JBNC_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_carry != 1) {
        regs->pc = regs->pc - regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JBNT_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_true != 1) {
        regs->pc = regs->pc - regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JF_D(tex80_registers *regs, unsigned char *memory)
{
    regs->pc = regs->pc + regs->delta;
}
    
void INST_JFZ_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_zero == 1) {
        regs->pc = regs->pc + regs->delta;
    } else {
        // Since this is a conditional jump, we need to manually increment the
        // program counter. This is the same for every other conditional jump
        regs->pc += 1;
    }
}
    
void INST_JFC_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_carry == 1) {
        regs->pc = regs->pc + regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JFT_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_true == 1) {
        regs->pc = regs->pc + regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JFNZ_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_zero != 1) {
        regs->pc = regs->pc + regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JFNC_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_carry != 1) {
        regs->pc = regs->pc + regs->delta;
    } else { regs->pc += 1; }
}
    
void INST_JFNT_D(tex80_registers *regs, unsigned char *memory)
{
    if (regs->flag_true != 1) {
        regs->pc = regs->pc + regs->delta;
    } else { regs->pc += 1; }
}

// Load instructions
void INST_LOAD_A_X(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = memory[regs->pc+1];
}

void INST_LOAD_B_X(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = memory[regs->pc+1];
}

void INST_LOAD_G_X(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = memory[regs->pc+1];
}

void INST_LOAD_D_X(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = memory[regs->pc+1];
}

void INST_LOAD_SP_GD(tex80_registers *regs, unsigned char *memory)
{
    regs->sp = (regs->gamma << 8) + regs->delta;
}
    
void INST_LOAD_IP_GD(tex80_registers *regs, unsigned char *memory)
{
    regs->ip = (regs->gamma << 8) + regs->delta;
}
    
void INST_LOAD_GD_SP(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = (regs->sp & 0xff00) >> 8;
    regs->delta = regs->sp & 0x00ff;
}
    
void INST_LOAD_GD_IP(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = (regs->ip & 0xff00) >> 8;
    regs->delta = regs->ip & 0x00ff;
}

void INST_LOAD_A_A(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = regs->alpha;
}

void INST_LOAD_B_A(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = regs->alpha;
}

void INST_LOAD_G_A(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = regs->alpha;
}

void INST_LOAD_D_A(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = regs->alpha;
}

void INST_LOAD_A_B(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = regs->beta;
}

void INST_LOAD_B_B(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = regs->beta;
}

void INST_LOAD_G_B(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = regs->beta;
}

void INST_LOAD_D_B(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = regs->beta;
}

void INST_LOAD_A_G(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = regs->gamma;
}

void INST_LOAD_B_G(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = regs->gamma;
}

void INST_LOAD_G_G(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = regs->gamma;
}

void INST_LOAD_D_G(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = regs->gamma;
}

void INST_LOAD_A_D(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = regs->delta;
}

void INST_LOAD_B_D(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = regs->delta;
}

void INST_LOAD_G_D(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = regs->delta;
}

void INST_LOAD_D_D(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = regs->delta;
}

// Memory Store instructions
void INST_STR_AB_A(tex80_registers *regs, unsigned char *memory)
{
    memory[(regs->alpha << 8) + regs->beta] = regs->alpha;
}

void INST_STR_XX_A(tex80_registers *regs, unsigned char *memory)
{
    memory[(memory[regs->pc+1] << 8) + memory[regs->pc+2]] = regs->alpha;
}

void INST_STR_GD_A(tex80_registers *regs, unsigned char *memory)
{
    memory[(regs->gamma << 8) + regs->delta] = regs->alpha;
}

void INST_STR_AB_B(tex80_registers *regs, unsigned char *memory)
{
    memory[(regs->alpha << 8) + regs->beta] = regs->beta;
}

void INST_STR_XX_B(tex80_registers *regs, unsigned char *memory)
{
    memory[(memory[regs->pc+1] << 8) + memory[regs->pc+2]] = regs->beta;
}

void INST_STR_GD_B(tex80_registers *regs, unsigned char *memory)
{
    memory[(regs->gamma << 8) + regs->delta] = regs->beta;
}

void INST_STR_AB_G(tex80_registers *regs, unsigned char *memory)
{
    memory[(regs->alpha << 8) + regs->beta] = regs->gamma;
}

void INST_STR_XX_G(tex80_registers *regs, unsigned char *memory)
{
    memory[(memory[regs->pc+1] << 8) + memory[regs->pc+2]] = regs->gamma;
}

void INST_STR_GD_G(tex80_registers *regs, unsigned char *memory)
{
    memory[(regs->gamma << 8) + regs->delta] = regs->gamma;
}

void INST_STR_AB_D(tex80_registers *regs, unsigned char *memory)
{
    memory[(regs->alpha << 8) + regs->beta] = regs->delta;
}

void INST_STR_XX_D(tex80_registers *regs, unsigned char *memory)
{
    memory[(memory[regs->pc+1] << 8) + memory[regs->pc+2]] = regs->delta;
}

void INST_STR_GD_D(tex80_registers *regs, unsigned char *memory)
{
    memory[(regs->gamma << 8) + regs->delta] = regs->delta;
}

// Memory Load instructions
void INST_LOAD_A_AB(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = memory[(regs->alpha << 8) + regs->beta];
}

void INST_LOAD_A_XX(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = memory[(memory[regs->pc+1] << 8) + memory[regs->pc+2]];
}

void INST_LOAD_A_GD(tex80_registers *regs, unsigned char *memory)
{
    regs->alpha = memory[(regs->gamma << 8) + regs->delta];
}

void INST_LOAD_B_AB(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = memory[(regs->alpha << 8) + regs->beta];
}

void INST_LOAD_B_XX(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = memory[(memory[regs->pc+1] << 8) + memory[regs->pc+2]];
}

void INST_LOAD_B_GD(tex80_registers *regs, unsigned char *memory)
{
    regs->beta = memory[(regs->gamma << 8) + regs->delta];
}

void INST_LOAD_G_AB(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = memory[(regs->alpha << 8) + regs->beta];
}

void INST_LOAD_G_XX(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = memory[(memory[regs->pc+1] << 8) + memory[regs->pc+2]];
}

void INST_LOAD_G_GD(tex80_registers *regs, unsigned char *memory)
{
    regs->gamma = memory[(regs->gamma << 8) + regs->delta];
}

void INST_LOAD_D_AB(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = memory[(regs->alpha << 8) + regs->beta];
}

void INST_LOAD_D_XX(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = memory[(memory[regs->pc+1] << 8) + memory[regs->pc+2]];
}

void INST_LOAD_D_GD(tex80_registers *regs, unsigned char *memory)
{
    regs->delta = memory[(regs->gamma << 8) + regs->delta];
}
