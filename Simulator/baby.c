// Group Number - 4
// Jackson Stewart, Oscar Morris, Ross McBride, Thomas Laland-Brown, Will Adams
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "baby.h"
#include "instructionset.h"
#include "fileInput.h"

int main(int argc, char **argv)
{
	// allocate memory for datastructures
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

	// initialise datastructures and read machine code
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
			printf("Execution finished\n");
			break;
		}
		printf("CI: %u\n", baby->CI);
		execute(currentInstruction, baby);
		displayStore(baby);
		printf("\n\n");
	}
	return 0;
}

/** Function to decode binary integer into Instruction datastructure
 *  @param line: input integer
 *  @param ins: pointer to output datastructure
 *  @returns void
 */
void decode(uint32_t line, Instruction *ins)
{
	ins->operand = line % 32;
	ins->opcode = (line >> 13) % 8;
}

/** Function to execute the desired instruction
 *  @param ins: pointer to input instruction object
 *  @param baby: pointer to baby object
 *  @returns void
 */
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

/** Function to display the store
 *  @param baby: pointer to baby object
 *  @returns void
 */
void displayStore(Baby *baby)
{
	for (int i = 0; i < STORE_SIZE; i++)
	{
		for (int j = 0; j < 31; j++)
		{
			printf("%u", (baby->store[i] >> j) % 2);
		}
		printf("\n");
	}
}
