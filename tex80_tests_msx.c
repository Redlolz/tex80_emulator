#include <stdio.h>
#include <string.h>
#include "cpu.h"

typedef struct {
    int code;
    char func[64];
} test_result;

void compare_reg_value(unsigned int reg, int value, int *errcode) {
    if (reg != value) { *errcode = 1; }
}

test_result test_addition(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0xff;
    regs->beta = 0x01;
    memory[0] = 0x40; // ADD A,B
    tex80_step(regs, memory);
    
    if (regs->alpha != 0x00 || regs->flag_zero != 1 || regs->flag_carry != 0) {
        result.code = 1;
    }

    return result;
}

test_result test_addition_carry(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0xff;
    regs->beta = 0x01;
    memory[0] = 0x41; // ADDC A,B
    tex80_step(regs, memory);

    if (regs->alpha != 0x00 || regs->flag_zero != 1 || regs->flag_carry != 1) {
        result.code = 1;
    }

    return result;
}

test_result test_addition_immediate(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0xff;
    memory[0] = 0x50; // ADD A,X
    memory[1] = 0x01;
    tex80_step(regs, memory);
    
    if (regs->alpha != 0x00 && regs->flag_zero != 0 && regs->flag_carry != 0) {
        result.code = 1;
    }

    return result;
}

test_result test_addition_carry_immediate(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0xff;
    memory[0] = 0x51; // ADDC A,X
    memory[1] = 0x01;
    tex80_step(regs, memory);

    if (regs->alpha != 0x00 || regs->flag_zero != 1 || regs->flag_carry != 1) {
        result.code = 1;
    }

    return result;
}

test_result test_subtraction(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x00;
    regs->beta = 0x01;
    memory[0] = 0x42; // SUB A,B
    tex80_step(regs, memory);

    if (regs->alpha != 0xff || regs->flag_zero != 0 || regs->flag_carry != 0) {
        result.code = 1;
    }

    return result;
}

test_result test_subtraction_carry(tex80_registers *regs, 
        unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x00;
    regs->beta = 0x01;
    memory[0] = 0x43; // SUBC A,B
    tex80_step(regs, memory);

    if (regs->alpha != 0xff || regs->flag_zero != 0 || regs->flag_carry != 1) {
        result.code = 1;
    }

    return result;
}

test_result test_subtraction_immediate(tex80_registers *regs, 
        unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x00;
    memory[0] = 0x52; // SUB A,X
    memory[1] = 0x01;
    tex80_step(regs, memory);

    if (regs->alpha != 0xff || regs->flag_zero != 0 || regs->flag_carry != 0) {
        result.code = 1;
    }

    return result;
}

test_result test_subtraction_carry_immediate(tex80_registers *regs, 
        unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x00;
    memory[0] = 0x53; // SUBC A,X
    memory[1] = 0x01;
    tex80_step(regs, memory);

    if (regs->alpha != 0xff || regs->flag_zero != 0 || regs->flag_carry != 1) {
        result.code = 1;
    }

    return result;
}

test_result test_increment(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    memory[0] = 0x44; // INC A
    memory[1] = 0x45; // INC B
    memory[2] = 0x46; // INC G
    memory[3] = 0x47; // INC D
    // Step for every instruction
    for (int i=0; i < 4; i++) { tex80_step(regs, memory); }

    if (regs->alpha != 1 || regs->beta != 1 || regs->gamma != 1 
            || regs->delta != 1) {
        result.code = 1;
    }

    return result;
}

test_result test_decrement(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    memory[0] = 0x48; // DEC A
    memory[1] = 0x49; // DEC B
    memory[2] = 0x4a; // DEC G
    memory[3] = 0x4b; // DEC D
    // Step for every instruction
    for (int i=0; i < 4; i++) { tex80_step(regs, memory); }

    if (regs->alpha != 0xff || regs->beta != 0xff || regs->gamma != 0xff 
            || regs->delta != 0xff) {
        result.code = 1;
    }

    return result;
}

test_result test_compare_a(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0xaa;
    regs->beta  = 0xaa;
    regs->gamma = 0xaa;
    regs->delta = 0xaa;
    memory[0] = 0x55; // COMP A,B
    memory[1] = 0x56; // COMP A,G
    memory[2] = 0x57; // COMP A,D
    // Step for every instruction
    for (int i=0; i < 3; i++) {
        tex80_step(regs, memory);
        compare_reg_value(regs->flag_true, 1, &result.code);
    }
    return result;
}

test_result test_compare_b(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0xaa;
    regs->beta  = 0xaa;
    regs->gamma = 0xaa;
    regs->delta = 0xaa;
    memory[0] = 0x58; // COMP B,A
    memory[1] = 0x5a; // COMP B,G
    memory[2] = 0x5b; // COMP B,D
    // Step for every instruction
    for (int i=0; i < 3; i++) {
        tex80_step(regs, memory);
        compare_reg_value(regs->flag_true, 1, &result.code);
    }
    return result;
}

test_result test_logical_not(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x00;
    memory[0] = 0x4c; // NOT A

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0xff, &result.code);

    return result;
}

test_result test_logical_and(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta  = 0x01;
    memory[0] = 0x4d; // AND A,B
    memory[1] = 0x4d; // AND A,B

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 1, &result.code);

    regs->beta  = 0x00;
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0, &result.code);

    return result;
}

test_result test_logical_and_immediate(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    memory[0] = 0x5d; // AND A,X
    memory[1] = 0x01;
    memory[2] = 0x5d; // AND A,X
    memory[3] = 0x00;

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 1, &result.code);

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0, &result.code);

    return result;
}

test_result test_logical_or(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta  = 0x01;
    memory[0] = 0x4e; // OR A,B
    memory[1] = 0x4e; // OR A,B

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 1, &result.code);

    regs->beta  = 0x00;
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 1, &result.code);

    return result;
}

test_result test_logical_or_immediate(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    memory[0] = 0x5e; // OR A,X
    memory[1] = 0x01;
    memory[2] = 0x5e; // OR A,X
    memory[3] = 0x00;

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 1, &result.code);

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 1, &result.code);

    return result;
}

test_result test_logical_xor(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta = 0x00;
    memory[0] = 0x4f; // XOR A,B
    memory[1] = 0x4f; // XOR A,B

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 1, &result.code);

    regs->beta = 0x01;
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0, &result.code);

    return result;
}

test_result test_logical_xor_immediate(tex80_registers *regs, 
        unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    memory[0] = 0x5f; // XOR A,B
    memory[1] = 0x00;
    memory[2] = 0x5f; // XOR A,B
    memory[3] = 0x01;

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 1, &result.code);

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0, &result.code);

    return result;
}

test_result test_jump(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    memory[0] = 0x80; // JP XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    return result;
}

test_result test_jump_zero(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_zero = 1;
    memory[0] = 0x81; // JPZ XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    tex80_init(regs, memory);
    regs->flag_zero = 0;
    memory[0] = 0x81; // JPZ XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0003, &result.code);

    return result;
}

test_result test_jump_carry(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_carry = 1;
    memory[0] = 0x82; // JPC XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    tex80_init(regs, memory);
    regs->flag_carry = 0;
    memory[0] = 0x82; // JPC XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0003, &result.code);

    return result;
}

test_result test_jump_true(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_true = 1;
    memory[0] = 0x83; // JPT XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    tex80_init(regs, memory);
    regs->flag_true = 0;
    memory[0] = 0x83; // JPT XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0003, &result.code);

    return result;
}

test_result test_jump_not_zero(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_zero = 1;
    memory[0] = 0x85; // JPNZ XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0003, &result.code);

    tex80_init(regs, memory);
    regs->flag_zero = 0;
    memory[0] = 0x85; // JPNZ XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    return result;
}

test_result test_jump_not_carry(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_carry = 1;
    memory[0] = 0x86; // JPNC XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0003, &result.code);

    tex80_init(regs, memory);
    regs->flag_carry = 0;
    memory[0] = 0x86; // JPNC XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    return result;
}

test_result test_jump_not_true(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_true = 1;
    memory[0] = 0x87; // JPNT XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0003, &result.code);

    tex80_init(regs, memory);
    regs->flag_true = 0;
    memory[0] = 0x87; // JPNT XX
    memory[1] = 0x01;
    memory[2] = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    return result;
}

test_result test_jump_gd(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    memory[0] = 0x88; // JP (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    return result;
}

test_result test_jump_zero_gd(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_zero = 1;
    memory[0] = 0x89; // JPZ (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    tex80_init(regs, memory);
    regs->flag_zero = 0;
    memory[0] = 0x89; // JPZ (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0001, &result.code);

    return result;
}

test_result test_jump_carry_gd(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_carry = 1;
    memory[0] = 0x8a; // JPC (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    tex80_init(regs, memory);
    regs->flag_carry = 0;
    memory[0] = 0x8a; // JPC (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0001, &result.code);

    return result;
}

test_result test_jump_true_gd(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_true = 1;
    memory[0] = 0x8b; // JPT (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    tex80_init(regs, memory);
    regs->flag_true = 0;
    memory[0] = 0x8b; // JPT (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0001, &result.code);

    return result;
}

test_result test_jump_not_zero_gd(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_zero = 1;
    memory[0] = 0x8d; // JPNZ (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0001, &result.code);

    tex80_init(regs, memory);
    regs->flag_zero = 0;
    memory[0] = 0x8d; // JPNZ (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    return result;
}

test_result test_jump_not_carry_gd(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_carry = 1;
    memory[0] = 0x8e; // JPNC (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0001, &result.code);

    tex80_init(regs, memory);
    regs->flag_carry = 0;
    memory[0] = 0x8e; // JPNC (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    return result;
}

test_result test_jump_not_true_gd(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->flag_true = 1;
    memory[0] = 0x8f; // JPNT (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0001, &result.code);

    tex80_init(regs, memory);
    regs->flag_true = 0;
    memory[0] = 0x8f; // JPNT (GD)
    regs->gamma = 0x01;
    regs->delta = 0x11;

    tex80_step(regs, memory);
    compare_reg_value(regs->pc, 0x0111, &result.code);

    return result;
}

test_result test_load_immediate(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    memory[0] = 0xc0; // LOAD A,X
    memory[1] = 0x11;
    memory[2] = 0xc1; // LOAD B,X
    memory[3] = 0x22;
    memory[4] = 0xc2; // LOAD G,X
    memory[5] = 0x33;
    memory[6] = 0xc3; // LOAD D,X
    memory[7] = 0x44;

    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0x11, &result.code);

    tex80_step(regs, memory);
    compare_reg_value(regs->beta, 0x22, &result.code);

    tex80_step(regs, memory);
    compare_reg_value(regs->gamma, 0x33, &result.code);

    tex80_step(regs, memory);
    compare_reg_value(regs->delta, 0x44, &result.code);

    return result;
}

test_result test_load_into_a(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x11;
    memory[0] = 0xd0; // LOAD A,A
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0x11, &result.code);

    tex80_init(regs, memory);
    regs->beta = 0x22;
    memory[0] = 0xd4; // LOAD A,B
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0x22, &result.code);

    tex80_init(regs, memory);
    regs->gamma = 0x33;
    memory[0] = 0xd8; // LOAD A,G
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0x33, &result.code);

    tex80_init(regs, memory);
    regs->delta = 0x44;
    memory[0] = 0xdc; // LOAD A,D
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0x44, &result.code);

    return result;
}

test_result test_load_into_b(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x11;
    memory[0] = 0xd1; // LOAD B,A
    tex80_step(regs, memory);
    compare_reg_value(regs->beta, 0x11, &result.code);

    tex80_init(regs, memory);
    regs->beta = 0x22;
    memory[0] = 0xd5; // LOAD B,B
    tex80_step(regs, memory);
    compare_reg_value(regs->beta, 0x22, &result.code);

    tex80_init(regs, memory);
    regs->gamma = 0x33;
    memory[0] = 0xd9; // LOAD B,G
    tex80_step(regs, memory);
    compare_reg_value(regs->beta, 0x33, &result.code);

    tex80_init(regs, memory);
    regs->delta = 0x44;
    memory[0] = 0xdd; // LOAD B,D
    tex80_step(regs, memory);
    compare_reg_value(regs->beta, 0x44, &result.code);

    return result;
}

test_result test_load_into_g(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x11;
    memory[0] = 0xd2; // LOAD G,A
    tex80_step(regs, memory);
    compare_reg_value(regs->gamma, 0x11, &result.code);

    tex80_init(regs, memory);
    regs->beta = 0x22;
    memory[0] = 0xd6; // LOAD G,B
    tex80_step(regs, memory);
    compare_reg_value(regs->gamma, 0x22, &result.code);

    tex80_init(regs, memory);
    regs->gamma = 0x33;
    memory[0] = 0xda; // LOAD G,G
    tex80_step(regs, memory);
    compare_reg_value(regs->gamma, 0x33, &result.code);

    tex80_init(regs, memory);
    regs->delta = 0x44;
    memory[0] = 0xde; // LOAD G,D
    tex80_step(regs, memory);
    compare_reg_value(regs->gamma, 0x44, &result.code);

    return result;
}

test_result test_load_into_d(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x11;
    memory[0] = 0xd3; // LOAD D,A
    tex80_step(regs, memory);
    compare_reg_value(regs->delta, 0x11, &result.code);

    tex80_init(regs, memory);
    regs->beta = 0x22;
    memory[0] = 0xd7; // LOAD D,B
    tex80_step(regs, memory);
    compare_reg_value(regs->delta, 0x22, &result.code);

    tex80_init(regs, memory);
    regs->gamma = 0x33;
    memory[0] = 0xdb; // LOAD D,G
    tex80_step(regs, memory);
    compare_reg_value(regs->delta, 0x33, &result.code);

    tex80_init(regs, memory);
    regs->delta = 0x44;
    memory[0] = 0xdf; // LOAD D,D
    tex80_step(regs, memory);
    compare_reg_value(regs->delta, 0x44, &result.code);

    return result;
}

test_result test_store_a(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta  = 0x00;
    memory[0] = 0xe0; // STR (AB),A
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0100], 0x01, &result.code);
    memory[0x0100] = 0x00; // reset memory value

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->gamma = 0x01;
    regs->delta = 0x00;
    memory[0] = 0xe3; // STR (GD),A
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0100], 0x01, &result.code);
    memory[0x0100] = 0x00; // reset memory value

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    memory[0] = 0xe1; // STR (XX),A
    memory[1] = 0x01;
    memory[2] = 0x11;
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0111], 0x01, &result.code);
    memory[0x0111] = 0x00; // reset memory value

    return result;
}

test_result test_store_b(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta  = 0x01;
    memory[0] = 0xe4; // STR (AB),B
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0101], 0x01, &result.code);
    memory[0x0101] = 0x00; // reset memory value

    tex80_init(regs, memory);
    regs->beta = 0x01;
    regs->gamma = 0x01;
    regs->delta = 0x00;
    memory[0] = 0xe7; // STR (GD),B
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0100], 0x01, &result.code);
    memory[0x0100] = 0x00; // reset memory value

    tex80_init(regs, memory);
    regs->beta = 0x01;
    memory[0] = 0xe5; // STR (XX),B
    memory[1] = 0x01;
    memory[2] = 0x11;
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0111], 0x01, &result.code);
    memory[0x0111] = 0x00; // reset memory value

    return result;
}

test_result test_store_g(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->gamma = 0x01;
    regs->alpha = 0x01;
    regs->beta  = 0x00;
    memory[0] = 0xe8; // STR (AB),G
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0100], 0x01, &result.code);
    memory[0x0100] = 0x00; // reset memory value

    tex80_init(regs, memory);
    regs->gamma = 0x01;
    regs->delta = 0x01;
    memory[0] = 0xeb; // STR (GD),G
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0101], 0x01, &result.code);
    memory[0x0101] = 0x00; // reset memory value

    tex80_init(regs, memory);
    regs->gamma = 0x01;
    memory[0] = 0xe9; // STR (XX),G
    memory[1] = 0x01;
    memory[2] = 0x11;
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0111], 0x01, &result.code);
    memory[0x0111] = 0x00; // reset memory value

    return result;
}

test_result test_store_d(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->delta = 0x01;
    regs->alpha = 0x01;
    regs->beta  = 0x00;
    memory[0] = 0xec; // STR (AB),D
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0100], 0x01, &result.code);
    memory[0x0100] = 0x00; // reset memory value

    tex80_init(regs, memory);
    regs->gamma = 0x01;
    regs->delta = 0x01;
    memory[0] = 0xef; // STR (GD),D
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0101], 0x01, &result.code);
    memory[0x0101] = 0x00; // reset memory value

    tex80_init(regs, memory);
    regs->delta = 0x01;
    memory[0] = 0xed; // STR (XX),D
    memory[1] = 0x01;
    memory[2] = 0x11;
    tex80_step(regs, memory);
    compare_reg_value(memory[0x0111], 0x01, &result.code);
    memory[0x0111] = 0x00; // reset memory value

    return result;
}

test_result test_load_a(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta  = 0x00;
    memory[0x0100] = 0x11;
    memory[0] = 0xf0; // LOAD A,(AB)
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0x11, &result.code);

    tex80_init(regs, memory);
    regs->gamma = 0x01;
    regs->delta = 0x00;
    memory[0x0100] = 0x11;
    memory[0] = 0xf3; // LOAD A,(GD)
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0x11, &result.code);

    tex80_init(regs, memory);
    memory[0x0100] = 0x11;
    memory[0] = 0xf1; // LOAD A,(XX)
    memory[1] = 0x01;
    memory[2] = 0x00;
    tex80_step(regs, memory);
    compare_reg_value(regs->alpha, 0x11, &result.code);

    return result;
}

test_result test_load_b(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta  = 0x00;
    memory[0x0100] = 0x11;
    memory[0] = 0xf4; // LOAD B,(AB)
    tex80_step(regs, memory);
    compare_reg_value(regs->beta, 0x11, &result.code);

    tex80_init(regs, memory);
    regs->gamma = 0x01;
    regs->delta = 0x00;
    memory[0x0100] = 0x11;
    memory[0] = 0xf7; // LOAD B,(GD)
    tex80_step(regs, memory);
    compare_reg_value(regs->beta, 0x11, &result.code);

    tex80_init(regs, memory);
    memory[0x0100] = 0x11;
    memory[0] = 0xf5; // LOAD B,(XX)
    memory[1] = 0x01;
    memory[2] = 0x00;
    tex80_step(regs, memory);
    compare_reg_value(regs->beta, 0x11, &result.code);

    return result;
}

test_result test_load_g(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta  = 0x00;
    memory[0x0100] = 0x11;
    memory[0] = 0xf8; // LOADG,(AB)
    tex80_step(regs, memory);
    compare_reg_value(regs->gamma, 0x11, &result.code);

    tex80_init(regs, memory);
    regs->gamma = 0x01;
    regs->delta = 0x00;
    memory[0x0100] = 0x11;
    memory[0] = 0xfb; // LOAD G,(GD)
    tex80_step(regs, memory);
    compare_reg_value(regs->gamma, 0x11, &result.code);

    tex80_init(regs, memory);
    memory[0x0100] = 0x11;
    memory[0] = 0xf9; // LOAD G,(XX)
    memory[1] = 0x01;
    memory[2] = 0x00;
    tex80_step(regs, memory);
    compare_reg_value(regs->gamma, 0x11, &result.code);

    return result;
}

test_result test_load_d(tex80_registers *regs, unsigned char *memory) {
    test_result result = { 0 };
    strcpy(result.func, __func__);

    tex80_init(regs, memory);
    regs->alpha = 0x01;
    regs->beta  = 0x00;
    memory[0x0100] = 0x11;
    memory[0] = 0xfc; // LOAD D,(AB)
    tex80_step(regs, memory);
    compare_reg_value(regs->delta, 0x11, &result.code);

    tex80_init(regs, memory);
    regs->gamma = 0x01;
    regs->delta = 0x00;
    memory[0x0100] = 0x11;
    memory[0] = 0xff; // LOAD D,(GD)
    tex80_step(regs, memory);
    compare_reg_value(regs->delta, 0x11, &result.code);

    tex80_init(regs, memory);
    memory[0x0100] = 0x11;
    memory[0] = 0xfd; // LOAD D,(XX)
    memory[1] = 0x01;
    memory[2] = 0x00;
    tex80_step(regs, memory);
    compare_reg_value(regs->delta, 0x11, &result.code);

    return result;
}

int main() {
    tex80_registers regs = { 0 };
    unsigned char memory[2048] = { 0x00 };
    test_result result = {0};
    
    // result = test_addition(&regs, memory);
    printf("[%d] %s\n", test_addition(&regs, memory)->code, result.func);
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  
    printf("[%d] %s\n",  

    return 0;
}
