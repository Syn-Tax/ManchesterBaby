#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "util.h"

/** main function - program entrypoint
 *  @param argc: number of command line arguments
 *  @param argv: array of all arguments
 *  @returns error code
 */
int main(int argc, char **argv)
{
	if (argc < 3) // if the number of arguments < 3, not all necessary arguments specified, show error and exit
	{
		printf("input and/or output file missing\n");
		exit(1);
	}

	// setup buffer for all lines in the assembly code
	char rawLines[MAX_LINES][MAX_LINE_LEN];

	// create filepointers from command line arguments
	FILE *inputFp = fopen(argv[1], "r");
	FILE *outputFp = fopen(argv[2], "w");

	// if either file pointer is null, file doesn't exist, show error and exit
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

	// read in lines
	int numLines = inputLines(inputFp, rawLines);

	// allocate memory for array of Line datatype and symbol table
	Line *lines = (Line *)malloc(sizeof(Line) * numLines);
	SymbolTable *symbolTable = (SymbolTable *)malloc(sizeof(SymbolTable));

	// check for memory allocation error
	if (lines == NULL || symbolTable == NULL)
	{
		printf("Memory Allocation Error\n");
		exit(1);
	}

	// FIRST PASS
	for (int lineNum = 0; lineNum < numLines; lineNum++)
	{
		lines[lineNum].linenum = lineNum;								   // set line number (0 indexed)
		parseLine(rawLines[lineNum + 1], &lines[lineNum], symbolTable, 1); // parse each line, setting firstpass to true, not sure why rawLines[lineNum] doesn't work, but this fixes it
	}

	// SECOND PASS
	for (int lineNum = 0; lineNum < numLines; lineNum++)
	{
		parseLine(rawLines[lineNum + 1], &lines[lineNum], symbolTable, 0); // parse each line, setting firstpass to false
	}

	outputLines(outputFp, lines, numLines); // output lines datastructures to the output file

	return 0; // return success if reached
}