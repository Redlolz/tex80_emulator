#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "cpu.h"
#include "tex80.h"

void help(char *bin_name)
{
    printf("usage: %s [-d] [-f filename]\n", bin_name);
}

int load_file(char *filename, unsigned char *memory)
{
    FILE *fp = fopen(filename, "rb");
    long fsize;

    if (fp == NULL) {
        printf("error\n");
    }

    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp);
    if (fsize > 0xffff) {
        return -1;
    }
    rewind(fp);
    fread(memory, fsize, 1, fp);
    fclose(fp);
    return 0;
}

void start_tex80(_Bool debug, _Bool step_debug, unsigned char *memory)
{
    tex80_registers regs = tex80_registers_default;
    tex80_init(&regs, memory);

    while (memory[regs.pc] != 0x01) {
        if (false) { regs.intr = true; }

        tex80_step(&regs, memory);
        if (debug) {
            tex80_debug(&regs, memory);
            printf("\n");
        }

        if (step_debug) {
            getchar();
        }

        regs.intr = false;

        if (regs.pc > 0xffff) {
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    int opt;
    char *filename = NULL;
    unsigned char memory[0xffff];
    _Bool enable_debug = false;
    _Bool enable_step_debug = false;

    while ((opt = getopt(argc, argv, "f:dD")) != -1) {
        switch (opt) {
            case 'h':
                help(argv[0]);
                exit(0);
                break;
            case 'f':
                filename = optarg;
                break;
            case 'd':
                enable_debug = true;
                break;
            case 'D':
                enable_debug = true;
                enable_step_debug = true;
                break;
            case '?':
                exit(1);
                break;
            default:
                fprintf(stderr, "No options given\n");
                exit(1);
        }
    }
    if (filename == NULL) {
        fprintf(stderr, "No filename given\n");
        help(argv[0]);
        exit(1);
    }
    if (access( filename, F_OK ) != 0) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        help(argv[0]);
        exit(1);
    }
    if (load_file(filename, memory) != 0) {
        fprintf(stderr, "File too large\n");
        help(argv[0]);
        exit(1);
    }
    start_tex80(enable_debug, enable_step_debug, memory);
    return 0;
}
