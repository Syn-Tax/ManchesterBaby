#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int parseLine(char str[], Line *line, SymbolTable *symbolTable, int firstPass)
{
	if (line == NULL)
	{
		printf("Function parseLine received a NULL pointer, exiting now\n");
		exit(1);
	}

	char opcode[OPCODE_LEN];
	char operand[MAX_SYMBOL_LEN];
	char label[MAX_SYMBOL_LEN];

	// printf("%s", str);

	if (isspace(str[0]))
	{
		sscanf(str, "%s %s", opcode, operand);
		strcpy(label, "");
		// printf("No Label\n");
	}
	else
	{
		sscanf(str, "%s %s %s", label, opcode, operand);
		// printf("Found Label\n");
	}

	// printf("%s\n", label);

	if (firstPass)
	{
		parseLabel(label, line, symbolTable);
	}
	else
	{
		parseOpcode(opcode, line);
		if (operand[0] != ';')
		{
			parseOperand(operand, line, symbolTable);
		}
	}
	return 0;
}

int parseLabel(char label[], Line *line, SymbolTable *symbolTable)
{
	if (strcmp(label, "") == 0)
	{
		strcpy(line->label, label);
		return 0;
	}
	for (int i = 0; i < MAX_SYMBOL_LEN; i++)
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
	// printf("%s: %s\n", label, line->label);

	for (int i = 0; i < MAX_SYMBOLS; i++)
	{
		if (strcmp(symbolTable->table[i].symbol, line->label) == 0)
		{
			printf("Duplicate definition of symbol %s, exiting now\n", line->label);
			exit(1);
		}
		else if (strlen(symbolTable->table[i].symbol) > 0)
		{
			continue;
		}
		else
		{
			// printf("%d\n", i);
			strcpy(symbolTable->table[i].symbol, line->label);
			symbolTable->table[i].address = line->linenum;
			// printf("added to symbol table\n");
			// printf("%d: %s: %d\n", i, symbolTable->table[i].symbol, symbolTable->table[i].address);
			break;
		}
		// printf("%s: %d\n", symbolTable->table[i].symbol, symbolTable->table[i].address);
	}

	return 0;
}

int parseOpcode(char opcode[], Line *line)
{
	if (strcmp(opcode, "JMP") == 0)
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
		line->opcode = VAR;
	}
	else
	{
		printf("%s is not a valid instruction, exiting now\n", opcode);
		exit(0);
	}

	return 0;
}

int parseOperand(char operand[], Line *line, SymbolTable *symbolTable)
{
	int isNumber = 1;
	for (int i = 0; i < strlen(operand); i++)
	{
		if (!isdigit(operand[i]))
		{
			isNumber = 0;
		}
	}

	if (isNumber)
	{
		line->operand = atoi(operand);
	}
	else
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
		if (!symbolFound)
		{
			printf("%s is not defined\n", operand);
		}
	}
	return 0;
}