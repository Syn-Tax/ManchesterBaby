#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#define MAX_LINE_LEN 64

// opcode definitions
#define JMP 0
#define JRP 1
#define LDN 2
#define STO 3
#define SUB 4
#define SUB_ 5
#define CMP 6
#define STOP 7

typedef struct instruction
{
	int opcode;
	int operand;
} Instruction;

unsigned int saveInstruction(Instruction *ins);

#endif