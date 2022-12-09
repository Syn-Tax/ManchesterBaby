// Group Number - 4
// Jackson Stewart, Oscar Morris, Ross McBride, Thomas Laland-Brown, Will Adams
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "lexer.h"

/** Function to print integer as binary value (USED FOR TESTING AND DEBUGGING)
 *  @param input: unsigned 32 bit integer
 *  @returns nothing of use
 */
int displayBin(uint32_t input)
{
	for (int i = 0; i < INS_LEN; i++) // loop through every bit and print it
	{
		printf("%d", ((input >> i) % 2)); // print ith bit
	}
	printf("\n");
	return 0; // return success if reached
}

/** Function to output lines array to file (as machine code)
 *  @param fp: file pointer to output file
 *  @param lines: array of Line objects to be written to file
 *  @param numLines: total number of lines
 *  @returns nothing of use
 */
int outputLines(FILE *fp, Line *lines, int numLines)
{
	if (fp == NULL) // check for null pointer, print error message and exit
	{
		printf("Function outputLines received a NULL pointer, exiting now\n");
		exit(1);
	}

	// loop through each line and save it to file
	for (int i = 0; i < numLines; i++)
	{
		uint32_t ins = saveInstruction(&lines[i]); // get the integer form of the instruction

		// write each bit to file
		for (int j = 0; j < INS_LEN; j++)
		{
			fprintf(fp, "%d", ((ins >> j) % 2)); // write jth bit to file
		}
		fprintf(fp, "\n");
	}
	return 0; // return success if reached
}

/** Function to read in file
 *  @param fp: filepointer
 *  @param lines: array of strings as output
 *  @returns number of lines read in
 */
int inputLines(FILE *fp, char lines[MAX_LINES][MAX_LINE_LEN])
{
	if (fp == NULL) // check for null pointer, prent error message and exit
	{
		printf("Function inputLines received a NULL pointer, exiting now\n");
		exit(1);
	}

	// allocate memory for buffer
	char *lineBuffer = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
	int lineCounter = 0;

	if (lineBuffer == NULL) // check for null pointer
	{
		printf("Memory Allocation Error, exiting now\n");
		exit(1);
	}

	while (fgets(lineBuffer, MAX_LINE_LEN, fp)) // read in lines using while loop
	{
		if (lineBuffer[strspn(lineBuffer, " \f\n\r\t\v")] == ';') // if line starts with a comment (first non-whitespace character), ignore it and continue
		{
			continue;
		}
		else // otherwise, increment lineCounter and copy into lines
		{
			lineCounter++;
			strcpy(lines[lineCounter], lineBuffer);
		}
	}

	return lineCounter; // return number of lines read in
}

/** Function to convert Line object into instruction integer
 *  @param line: pointer to Line object to be outputted
 *  @returns integer instruction (as unsigned, 32 bit integer)
 */
uint32_t saveInstruction(Line *line)
{
	if (line == NULL) // check for null pointer, display error message and exit
	{
		printf("Function saveInstruction received a NULL pointer, exiting now\n");
		exit(1);
	}

	// create output variable
	uint32_t output = 0U;

	if (line->opcode == VAR) // if the opcode is a variable
	{
		output |= line->operand; // output the line's operand (i.e. variable value)
	}
	else // otherwise output operand and output (from SSEM-Manual section 2.5)
	{
		output |= line->opcode << 13;
		output |= line->operand;
	}
	return output; // return the output
}
