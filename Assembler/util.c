#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "lexer.h"

int displayBin(uint32_t input)
{
	for (int i = 0; i < 32; i++)
	{
		printf("%d", ((input >> i) % 2));
	}
	printf("\n");
	return 0;
}

int outputLines(FILE *fp, Line *lines, int numLines)
{
	if (fp == NULL)
	{
		printf("Function outputLines received a NULL pointer, exiting now\n");
		exit(1);
	}

	for (int i = 0; i < numLines; i++)
	{
		uint32_t ins = saveInstruction(&lines[i]);

		for (int j = 0; j < 32; j++)
		{
			fprintf(fp, "%d", ((ins >> j) % 2));
		}
		fprintf(fp, "\n");
	}
	return 0;
}

int inputLines(FILE *fp, char lines[MAX_LINES][MAX_LINE_LEN])
{
	if (fp == NULL)
	{
		printf("Function inputLines received a NULL pointer, exiting now\n");
		exit(1);
	}

	char *lineBuffer = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
	int lineCounter = 0;

	while (fgets(lineBuffer, MAX_LINE_LEN, fp))
	{
		if (lineBuffer[strspn(lineBuffer, " \f\n\r\t\v")] == ';')
		{
			continue;
		}
		else
		{
			lineCounter++;
			strcpy(lines[lineCounter], lineBuffer);
		}
	}

	return lineCounter;
}

uint32_t saveInstruction(Line *line)
{
	if (line == NULL)
	{
		printf("Function saveInstruction received a NULL pointer, exiting now\n");
		exit(1);
	}

	uint32_t output = 0;

	if (line->opcode == VAR)
	{
		output |= line->operand;
	}
	else
	{
		output |= line->opcode << 13;
		output |= line->operand;
	}
	return output;
}