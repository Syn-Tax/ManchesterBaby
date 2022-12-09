// Group Number - 4
// Jackson Stewart, Oscar Morris, Ross McBride, Thomas Laland-Brown, Will Adams
#ifndef __INSTRUCTIONSET_H__
#define __INSTRUCTIONSET_H__

#include <stdint.h>

#define STORE_SIZE 32 // number of 32 bit integers in the store

// instruction datastructure
typedef struct instruction
{
	uint8_t opcode;
	uint8_t operand;

} Instruction;

// baby datastructure (in here rather than baby.h to remove circular includes)
typedef struct baby
{
	uint32_t store[STORE_SIZE];
	uint32_t accumulator;
	uint8_t CI;

} Baby;

/** Function for opcodes
 *  @param ins: pointer to instruction object
 *  @param baby: pointer to baby object
 *  @returns void
 */
void JMP_fn(Instruction *ins, Baby *baby);
void JRP_fn(Instruction *ins, Baby *baby);
void LDN_fn(Instruction *ins, Baby *baby);
void STO_fn(Instruction *ins, Baby *baby);
void SUB_fn(Instruction *ins, Baby *baby);
void CMP_fn(Instruction *ins, Baby *baby);

#endif
