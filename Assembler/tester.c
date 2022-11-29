#include "instruction.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Instruction *ins = (Instruction *)malloc(sizeof(Instruction));

	ins->opcode = LDN;
	ins->operand = 7;
	unsigned int instruct = saveInstruction(ins);
	displayBin(instruct);
}