#ifndef __INSTRUCTIONSET_H__
#define __INSTRUCTIONSET_H__

#include <stdint.h>
// #include "baby.h"

#define STORE_SIZE 32
typedef struct instruction
{
	uint8_t opcode;
	uint8_t operand;

} Instruction;

typedef struct baby
{
	uint32_t store[STORE_SIZE];
	uint32_t accumulator;
	uint8_t CI;

} Baby;

void JMP_fn(Instruction *ins, Baby *baby);
void JRP_fn(Instruction *ins, Baby *baby);
void LDN_fn(Instruction *ins, Baby *baby);
void STO_fn(Instruction *ins, Baby *baby);
void SUB_fn(Instruction *ins, Baby *baby);
void CMP_fn(Instruction *ins, Baby *baby);

#endif