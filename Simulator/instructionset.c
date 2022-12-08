#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionset.h"
#include "baby.h"
// #include "lexer.h"
// #include "util.h"

void JMP_fn(Instruction *ins, Baby *baby)
{
    // set CI to content of store location (memory address)
    baby->CI = baby->store[ins->operand];
}

void JRP_fn(Instruction *ins, Baby *baby)
{
    // add content of store location to CI
    baby->CI = baby->CI + baby->store[ins->operand];
}

void LDN_fn(Instruction *ins, Baby *baby)
{
    // load accumulator with negative form of content that is in the store
    // if number in store exists, change number into negative counterpart when loaded into accumulator

    baby->accumulator = -baby->store[ins->operand];
}

void STO_fn(Instruction *ins, Baby *baby)
{
    // store accumulator value in store location
    baby->store[ins->operand] = baby->accumulator;
}

void SUB_fn(Instruction *ins, Baby *baby)
{
    // fetch a number from the store and subtract number from number which is in accumulator
    // accumulatorValue = accumulatorValue - storeValue

    baby->accumulator -= baby->store[ins->operand];
}

void CMP_fn(Instruction *ins, Baby *baby)
{

    if ((baby->accumulator >> 31) == 1) // if value of accumulator is negative then increment the CI
    {
        baby->CI++;
    }
}
