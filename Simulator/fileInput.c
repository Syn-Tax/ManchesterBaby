#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "fileInput.h"

// Runs with command: gcc fileInput.c
// needs "BabyTest1-MC.txt" in same folder

int main()
{
    uint32_t *store = (uint32_t *)malloc(sizeof(uint32_t) * STORE_SIZE);

    if (store == NULL)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    readMachineCode(fopen("BabyTest1-MC.txt", "r"), store);
    printf("\nPrint store:\n");
    for (int n = 0; n < STORE_SIZE; n++)
    {
        printf("%u ", store[n]);
    }
    printf("\n");
}

// idea for this method is that I read in each character individually and append to binary char[]
// after filling the char[], I use binaryToDecimal() and store output in Store[].
void readMachineCode(FILE *fp, uint32_t *store)
{

    if (fp != NULL)
    {
        char buffer[35]; // I have no idea why this number needs to be 35, but it does
        int counter = 0;

        while (fgets(buffer, 35, fp)) // same with the 35 here
        {
            // printf("%s\n", buffer);
            uint32_t output = binaryToDecimal(buffer);
            store[counter] = output;
            counter++;
        }

        fclose(fp);
    }
    else
    {
        // should give error really but file should always exist
    }
}

// takes char[] of binary characters and outputs corresponding decimal value
uint32_t binaryToDecimal(char binary[])
{

    uint32_t decimal = 0;

    for (int i = 0; i < 32; ++i)
    {
        if (binary[i] == '1')
        {
            decimal |= 1U << 31 - i;
        }
    }
    printf("Decimal output:%u\n", decimal);
    return decimal;
}
