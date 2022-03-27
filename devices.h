#ifndef DEVICES_H
#define DEVICES_H

//unsigned char DEVR_empty();

//void DEVW_empty(unsigned char operand);

//void DEVW_tty(unsigned char operand);

unsigned char read_device(unsigned char dev);
void write_device(unsigned char dev, unsigned char operand);

#endif
