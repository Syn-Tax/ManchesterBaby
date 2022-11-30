#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdint.h>

#define MAX_SYMBOL_LEN 32
#define MAX_SYMBOLS 32
#define OPCODE_LEN 4

// opcode definitions (to make our lives easier)
#define JMP 0
#define JRP 1
#define LDN 2
#define STO 3
#define SUB 4
#define SUB_ 5
#define CMP 6
#define STP 7
#define VAR 8

typedef struct line
{
	char label[MAX_SYMBOL_LEN];
	uint8_t opcode;
	uint32_t operand; // 32 bits for var declaration
	int linenum;
} Line;

typedef struct symbol
{
	char symbol[MAX_SYMBOL_LEN];
	int address;
} Symbol;

typedef struct symbol_table
{
	Symbol table[MAX_SYMBOLS];
} SymbolTable;

int parseLine(char str[], Line *line, SymbolTable *symbolTable, int firstpass);
int parseLabel(char label[], Line *line, SymbolTable *symbolTable);
int parseOpcode(char opcode[], Line *line);
int parseOperand(char operand[], Line *line, SymbolTable *symbolTable);

#endif