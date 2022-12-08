#ifndef __BABY_H__
#define __BABY_H__

#include <stdint.h>
#include "instructionset.h"

#define STORE_SIZE 32

// opcode definitions (to make our lives easier)
#define JMP 0
#define JRP 1
#define LDN 2
#define STO 3
#define SUB 4
#define SUB_ 5
#define CMP 6
#define STP 7

typedef struct baby
{
	uint32_t store[STORE_SIZE];
	uint32_t accumulator;
	uint8_t CI;

} Baby;

void decode(uint32_t line, Instruction *ins);
void execute(Instruction *ins, Baby *baby);
void displayStore(Baby *baby);

#endif