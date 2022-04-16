#ifndef DEVICES_H
#define DEVICES_H

typedef unsigned char (*read_dev)(void);
typedef void (*write_dev)(unsigned char);

unsigned char read_device(unsigned char dev);
void write_device(unsigned char dev, unsigned char operand);

#endif
