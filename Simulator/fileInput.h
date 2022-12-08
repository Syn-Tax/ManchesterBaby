#ifndef __FILEINPUT_H__
#define __FILEINPUT_H__

#include <stdint.h>
#include <stdio.h>
#include "instructionset.h"

void readMachineCode(FILE *fp, Baby *baby);
uint32_t binaryToDecimal(char binary[]);

#endif