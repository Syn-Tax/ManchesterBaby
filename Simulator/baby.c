
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "baby.h"
#include "instructionset.h"
#include "fileInput.h"

int main(int argc, char **argv)
{
	Baby *baby = (Baby *)malloc(sizeof(Baby));
	Instruction *currentInstruction = (Instruction *)malloc(sizeof(Instruction));

	if (currentInstruction == NULL || baby == NULL)
	{
		printf("Memory Allocation error, exiting now\n");
		exit(1);
	}

	if (argc < 2)
	{
		printf("Not enough arguments\nUsage: ./baby [path to machine code]\n");
		exit(1);
	}

	FILE *inputfp = fopen(argv[1], "r");

	if (inputfp == NULL)
	{
		printf("Input file does not exist\n");
	}

	readMachineCode(inputfp, baby);
	baby->CI = 0;
	baby->accumulator = 0;

	// main loop
	while (1)
	{
		baby->CI++;
		decode(baby->store[baby->CI], currentInstruction);
		if (currentInstruction->opcode == STP)
		{
			break;
		}
		execute(currentInstruction, baby);
		displayStore(baby);
		printf("\n\n");
	}
	return 0;
}

void decode(uint32_t line, Instruction *ins)
{
	ins->operand = line % 32;
	ins->opcode = (line >> 13) % 8;
}

void execute(Instruction *ins, Baby *baby)
{
	if (ins->opcode == JMP)
	{
		printf("Instruction: JMP, Operand: %u\n", ins->operand);
		JMP_fn(ins, baby);
	}
	else if (ins->opcode == JRP)
	{
		printf("Instruction: JRP, Operand: %u\n", ins->operand);
		JRP_fn(ins, baby);
	}
	else if (ins->opcode == LDN)
	{
		printf("Instruction: LDN, Operand: %u\n", ins->operand);
		LDN_fn(ins, baby);
	}
	else if (ins->opcode == STO)
	{
		printf("Instruction: STO, Operand: %u\n", ins->operand);
		STO_fn(ins, baby);
	}
	else if (ins->opcode == SUB || ins->opcode == SUB_)
	{
		printf("Instruction: SUB, Operand: %u\n", ins->operand);
		SUB_fn(ins, baby);
	}
	else if (ins->opcode == CMP)
	{
		printf("Instruction: CMP, Operand: %u\n", ins->operand);
		CMP_fn(ins, baby);
	}
	else
	{
		printf("Invalid instruction\n");
	}
}

void displayStore(Baby *baby)
{
	for (int i = 0; i < STORE_SIZE; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			printf("%u", (baby->store[i] >> j) % 2);
		}
		printf("\n");
	}
}
