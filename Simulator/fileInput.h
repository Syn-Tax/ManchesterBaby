#ifndef __FILEINPUT_H__
#define __FILEINPUT_H__

#include <stdint.h>
#include <stdio.h>
#include "instructionset.h"

/** Function to read machine code into the store of the baby object
 *  @param fp: file pointer to input machine code file
 *  @param baby: pointer to output baby object
 *  @returns void
 */
void readMachineCode(FILE *fp, Baby *baby);

/** Function to convert binary string to integer
 *  @param binary: binary string
 *  @returns 32 bit unsigned int as output
 */
uint32_t binaryToDecimal(char binary[]);

#endif