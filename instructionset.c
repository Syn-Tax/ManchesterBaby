#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "util.h"



void JMP (int address){
    //set CI to content of store location (memory address)
    controlInstruction = Store[memoryAddress];//???
 
    printf("JMP address = ", memoryAddress);
    for(int i = 0; i < 32; i++)
    {
        control[i] = Store[address-1][i];
    }

    // update CI
	for(int j = 0; j < 32; j++)
	{
        controlInstruction[j]=Store[memoryAddress][j];
		printf =("CI = " , controlInstruction[j]);
	}
}


void JRP()
{
 //add content of store location to CI
 controlInstruction = controlInstruction + Store[memoryAddress]
}


void LDN()
{
//load accumulator with negative form of content that is in the store
//if number in store exists, change number into negative counterpart when loaded into accumulator
}




void STO(int memoryAddress)
{
	printf(" Store Memory Address = " , memoryAddress);

	for(int i = 0; i < 32; i++)
	{
		Store[memoryAddress][i]=Accumulator[i];
		printf(Store[memoryAddress][i]);
	}
}




void SUB()
{
//fetch a number from the store and subtract number from number which is in accumulator 
//accumulatorValue = accumulatorValue - storeValue

}




void CMP()
{
	
    if(valueOfAccumulator < 0)  //if value of accumulator is negative then increment the CI
    {
        controlInstruction ++
    }

    else
    {
        //skip to next instruction
    }


}




void STP()
{
	statusOfMachine = stopped;
	printf("The program has stopped");
}




