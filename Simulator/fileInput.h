#ifndef __FILEINPUT_H__
#define __FILEINPUT_H__

#include <stdint.h>
#include <stdio.h>

#define STORE_SIZE 32

void readMachineCode(FILE *fp, uint32_t *store);
uint32_t binaryToDecimal(char binary[]);

#endif