#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <termios.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "devices.h"

/* Empty devices */
static unsigned char DEVR_empty()
{
    return 0;
}

static void DEVW_empty(unsigned char operand)
{}

/* TTY registers */
static void set_mode(int want_key)
{
    static struct termios old, new;
    if (!want_key) {
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return;
    }

    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

static int get_key()
{
    int c = 0;
    struct pollfd pfd[1];
    pfd[0].fd = STDIN_FILENO;
    pfd[0].events = POLLIN;

    poll(pfd, 1, 0);

    if ((pfd[0].revents & (POLLIN|POLLHUP))) {
        c = getchar();
        set_mode(0);
    }
    return c;
}
static unsigned char DEVR_tty()
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 10000;
    nanosleep(&ts, 0);
    set_mode(1);
    return get_key();
}

static void DEVW_tty(unsigned char operand)
{
    putchar(operand);
}

read_dev read_device_table[] = {
/*0x00*/  DEVR_empty, DEVR_tty, DEVR_empty, DEVR_empty,
/*0x04*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x08*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x0c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x10*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x14*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x18*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x1c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x20*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x24*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x28*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x2c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x30*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x34*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x38*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x3c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x40*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x44*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x48*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x4c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x50*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x54*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x58*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x5c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x60*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x64*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x68*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x6c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x70*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x74*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x78*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x7c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x80*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x84*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x88*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x8c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x90*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x94*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x98*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0x9c*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xa0*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xa4*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xa8*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xac*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xb0*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xb4*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xb8*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xbc*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xc0*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xc4*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xc8*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xcc*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xd0*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xd4*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xd8*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xdc*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xe0*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xe4*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xe8*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xec*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xf0*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xf4*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xf8*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
/*0xfc*/  DEVR_empty, DEVR_empty, DEVR_empty, DEVR_empty,
};

write_dev write_device_table[] = {
/*0x00*/  DEVW_empty, DEVW_tty, DEVW_empty, DEVW_empty,
/*0x04*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x08*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x0c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x10*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x14*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x18*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x1c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x20*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x24*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x28*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x2c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x30*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x34*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x38*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x3c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x40*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x44*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x48*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x4c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x50*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x54*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x58*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x5c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x60*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x64*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x68*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x6c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x70*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x74*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x78*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x7c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x80*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x84*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x88*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x8c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x90*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x94*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x98*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0x9c*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xa0*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xa4*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xa8*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xac*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xb0*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xb4*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xb8*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xbc*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xc0*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xc4*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xc8*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xcc*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xd0*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xd4*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xd8*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xdc*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xe0*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xe4*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xe8*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xec*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xf0*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xf4*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xf8*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
/*0xfc*/  DEVW_empty, DEVW_empty, DEVW_empty, DEVW_empty,
};

unsigned char read_device(unsigned char dev)
{
    return read_device_table[dev]();
}

void write_device(unsigned char dev, unsigned char operand)
{
    write_device_table[dev](operand);
}

