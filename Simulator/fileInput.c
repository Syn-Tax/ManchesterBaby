// Group Number - 4
// Jackson Stewart, Oscar Morris, Ross McBride, Thomas Laland-Brown, Will Adams
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "fileInput.h"
#include "baby.h"

/** Function to read machine code into the store of the baby object
 *  @param fp: file pointer to input machine code file
 *  @param baby: pointer to output baby object
 *  @returns void
 */
void readMachineCode(FILE *fp, Baby *baby)
{

    if (fp != NULL)
    {
        char buffer[35]; // I have no idea why this number needs to be 35, but it does
        int counter = 0;

        while (fgets(buffer, 35, fp)) // same with the 35 here
        {
            // printf("%s\n", buffer);
            uint32_t output = binaryToDecimal(buffer);
            baby->store[counter] = output;
            counter++;
        }

        fclose(fp);
    }
    else
    {
        printf("Function readMachineCode received a null pointer, exiting now\n");
        exit(1);
    }
}

/** Function to convert binary string to integer
 *  @param binary: binary string
 *  @returns 32 bit unsigned int as output
 */
uint32_t binaryToDecimal(char binary[])
{

    uint32_t decimal = 0;

    for (int i = 31; i >= 0; i--)
    {
        if (binary[i] == '1')
        {
            decimal |= 1U << i;
        }
    }
    return decimal;
}
