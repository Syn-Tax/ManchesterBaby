#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdint.h>

// length definitions
#define MAX_SYMBOL_LEN 32
#define MAX_SYMBOLS 32
#define OPCODE_LEN 4 // length to include null terminator

// opcode definitions (to make our lives easier)
#define JMP 0
#define JRP 1
#define LDN 2
#define STO 3
#define SUB 4
#define SUB_ 5 // secondary SUB opcode - not used
#define CMP 6
#define STP 7
#define VAR 8

// line datatype
typedef struct line
{
	char label[MAX_SYMBOL_LEN];
	uint8_t opcode;	  // 8 bits because it's the smallest available
	uint32_t operand; // 32 bits for var declaration
	int linenum;	  // number of the line (useful for symbol table addresses)
} Line;

// symbol datatype - for use in symbol table
typedef struct symbol
{
	char symbol[MAX_SYMBOL_LEN];
	int address; // same datatype as line.linenum
} Symbol;

// symbol table datatype
typedef struct symbol_table
{
	Symbol table[MAX_SYMBOLS];
} SymbolTable;

/** Function to parse each line
 * @param str: string of the line of assembly
 * @param line: pointer to Line object as the output
 * @param symbolTable: pointer to the symbol table to be written to (on the first pass) or read from (on the second pass)
 * @param firstpass: boolean value set to true if it's the first pass
 * @returns nothing of use
 */
int parseLine(char str[], Line *line, SymbolTable *symbolTable, int firstpass);

/** Function to parse the label portion of each line, only run on the first pass
 *  @param label: string representation of the label (including ending ':')
 *  @param line: pointer to the line object as the output
 *  @param symbolTable: pointer to the symbol table as the output
 *  @returns nothing of use
 */
int parseLabel(char label[], Line *line, SymbolTable *symbolTable);

/** Function to parse the opcode (i.e. instruction)
 *  @param opcode: string representation of the opcode
 *  @param line: pointer to Line object as the output
 *  @returns nothing of use
 */
int parseOpcode(char opcode[], Line *line);

/** Function to parse the operand
 *  @param operand: string representation of the operand
 *  @param line: pointer to Line object as output
 *  @param symbolTable: pointer to symbol table to read symbols from
 *  @returns nothing of use
 */
int parseOperand(char operand[], Line *line, SymbolTable *symbolTable);

#endif