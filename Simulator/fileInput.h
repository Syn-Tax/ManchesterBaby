#ifndef __FILEINPUT_H__
#define __FILEINPUT_H__

#include <stdint.h>
#include <stdio.h>
#include "baby.h"

#define STORE_SIZE 32

void readMachineCode(FILE *fp, Baby *baby);
uint32_t binaryToDecimal(char binary[]);

#endif