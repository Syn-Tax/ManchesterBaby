#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** Function to parse each line
 * @param str: string of the line of assembly
 * @param line: pointer to Line object as the output
 * @param symbolTable: pointer to the symbol table to be written to (on the first pass) or read from (on the second pass)
 * @param firstpass: boolean value set to true if it's the first pass
 * @returns nothing of use
 */
int parseLine(char str[], Line *line, SymbolTable *symbolTable, int firstPass)
{
	// check for null pointers
	if (line == NULL || symbolTable == NULL)
	{
		printf("Function parseLine received a NULL pointer, exiting now\n");
		exit(1);
	}

	// define buffers for each section of a line - comment can be ignored
	char opcode[OPCODE_LEN];
	char operand[MAX_SYMBOL_LEN];
	char label[MAX_SYMBOL_LEN];

	if (isspace(str[0])) // if the first character is a space, only read in the opcode and operand, set label to an empty string
	{
		sscanf(str, "%s %s", opcode, operand);
		strcpy(label, "");
	}
	else // otherwise read in label, opcode and operand
	{
		sscanf(str, "%s %s %s", label, opcode, operand);
	}

	if (firstPass) // if it's the first pass, only read the labels (everything else done on second pass)
	{
		parseLabel(label, line, symbolTable);
	}
	else // if it's the second pass, only parse the opcode and operand - symbol table is populated in the first pass
	{
		parseOpcode(opcode, line); // parse the opcode
		if (operand[0] != ';')	   // if the operand is the comment (i.e. no operand) then parse the operand
		{
			parseOperand(operand, line, symbolTable);
		}
	}
	return 0; // return success if reached
}

/** Function to parse the label portion of each line, only run on the first pass
 *  @param label: string representation of the label (including ending ':')
 *  @param line: pointer to the line object as the output
 *  @param symbolTable: pointer to the symbol table as the output
 *  @returns nothing of use
 */
int parseLabel(char label[], Line *line, SymbolTable *symbolTable)
{
	if (strcmp(label, "") == 0) // if there is no label, set line->label to an empty string and return success
	{
		strcpy(line->label, label);
		return 0;
	}

	for (int i = 0; i < MAX_SYMBOL_LEN; i++) // otherwise, remove the ':' and any characters beyond it
	{
		if (label[i] == ':')
		{
			break;
		}
		else
		{
			line->label[i] = label[i];
		}
	}

	for (int i = 0; i < MAX_SYMBOLS; i++) // find the next empty space in the symbol table to insert the symbol
	{
		if (strcmp(symbolTable->table[i].symbol, line->label) == 0) // if the symbol already exists, show an error message and exit
		{
			printf("Duplicate definition of symbol %s, exiting now\n", line->label);
			exit(1);
		}
		else if (strlen(symbolTable->table[i].symbol) > 0) // if there is a symbol in this space (i.e. it's length is > 0), continue
		{
			continue;
		}
		else // otherwise insert symbol into the table and break out of the loop
		{
			strcpy(symbolTable->table[i].symbol, line->label);
			symbolTable->table[i].address = line->linenum;
			break;
		}
	}

	return 0; // return success if reached
}

/** Function to parse the opcode (i.e. instruction)
 *  @param opcode: string representation of the opcode
 *  @param line: pointer to Line object as the output
 *  @returns nothing of use
 */
int parseOpcode(char opcode[], Line *line)
{
	if (strcmp(opcode, "JMP") == 0) // set the opcode of the line (I wish strings worked in switch statements)
	{
		line->opcode = JMP;
	}
	else if (strcmp(opcode, "JRP") == 0)
	{
		line->opcode = JRP;
	}
	else if (strcmp(opcode, "LDN") == 0)
	{
		line->opcode = LDN;
	}
	else if (strcmp(opcode, "STO") == 0)
	{
		line->opcode = STO;
	}
	else if (strcmp(opcode, "SUB") == 0)
	{
		line->opcode = SUB;
	}
	else if (strcmp(opcode, "CMP") == 0)
	{
		line->opcode = CMP;
	}
	else if (strcmp(opcode, "STP") == 0)
	{
		line->opcode = STP;
	}
	else if (strcmp(opcode, "VAR") == 0)
	{
		line->opcode = VAR; // use VAR as temp assembler instruction (number 8)
	}
	else // if opcode isn't valid, display an error message and exit
	{
		printf("%s is not a valid instruction, exiting now\n", opcode);
		exit(1);
	}

	return 0; // return success if reached
}

/** Function to parse the operand
 *  @param operand: string representation of the operand
 *  @param line: pointer to Line object as output
 *  @param symbolTable: pointer to symbol table to read symbols from
 *  @returns nothing of use
 */
int parseOperand(char operand[], Line *line, SymbolTable *symbolTable)
{
	// check if every character is a number
	int isNumber = 1;
	for (int i = 0; i < strlen(operand); i++)
	{
		if (!isdigit(operand[i]))
		{
			isNumber = 0;
		}
	}

	if (isNumber) // if the operand is a number, convert it to an integer and store as the line's operand
	{
		line->operand = atoi(operand);
	}
	else // otherwise search the symbol table for the required symbol and insert it's memory address as the line's operand
	{
		int symbolFound = 0;
		for (int i = 0; i < MAX_SYMBOLS; i++)
		{
			if (strcmp(symbolTable->table[i].symbol, operand) == 0)
			{
				line->operand = (uint32_t)symbolTable->table[i].address;
				symbolFound = 1;
			}
		}
		if (!symbolFound) // if the symbol is not in the symbol table show an error and exit
		{
			printf("%s is not defined\n", operand);
			exit(1);
		}
	}
	return 0; // return success if reached
}