#ifndef __BABY_H__
#define __BABY_H__

#include <stdint.h>
#include "instructionset.h"

// opcode definitions (to make our lives easier)
#define JMP 0
#define JRP 1
#define LDN 2
#define STO 3
#define SUB 4
#define SUB_ 5
#define CMP 6
#define STP 7

/** Function to decode binary integer into Instruction datastructure
 *  @param line: input integer
 *  @param ins: pointer to output datastructure
 *  @returns void
 */
void decode(uint32_t line, Instruction *ins);

/** Function to execute the desired instruction
 *  @param ins: pointer to input instruction object
 *  @param baby: pointer to baby object
 *  @returns void
 */
void execute(Instruction *ins, Baby *baby);

/** Function to display the store
 *  @param baby: pointer to baby object
 *  @returns void
 */
void displayStore(Baby *baby);

#endif