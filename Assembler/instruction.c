#include "instruction.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int saveInstruction(Instruction *ins)
{
	if (ins == NULL)
	{
		printf("Function saveInstruction received a NULL pointer, exiting now");
		exit(1);
	}
	unsigned int output = 0;
	output |= ins->opcode << 13;
	output |= ins->operand;
	return output;
}