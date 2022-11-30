#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "util.h"

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("input and/or output file missing\n");
		exit(1);
	}

	char rawLines[MAX_LINES][MAX_LINE_LEN];

	FILE *inputFp = fopen(argv[1], "r");
	FILE *outputFp = fopen(argv[2], "w");

	if (inputFp == NULL)
	{
		printf("Invalid input file\n");
		exit(1);
	}

	if (outputFp == NULL)
	{
		printf("Invalid output file\n");
		exit(1);
	}

	int numLines = inputLines(inputFp, rawLines);

	Line *lines = (Line *)malloc(sizeof(Line) * numLines);
	SymbolTable *symbolTable = (SymbolTable *)malloc(sizeof(SymbolTable));

	if (lines == NULL || symbolTable == NULL)
	{
		printf("Memory Allocation Error\n");
		exit(1);
	}

	for (int lineNum = 0; lineNum < numLines; lineNum++)
	{
		lines[lineNum].linenum = lineNum;
		parseLine(rawLines[lineNum + 1], &lines[lineNum], symbolTable, 1);
	}

	for (int lineNum = 0; lineNum < numLines; lineNum++)
	{
		parseLine(rawLines[lineNum + 1], &lines[lineNum], symbolTable, 0);
	}

	// for (int i = 0; i < numLines; i++)
	// {
	// 	displayBin(saveInstruction(&lines[i]));
	// }

	outputLines(outputFp, lines, numLines);

	return 0;
}