#include <stdio.h>
#include <string.h>
#include <math.h>

// Runs with command: gcc fileInput.c -lm 
// needs "BabyTest1-MC.txt" in same folder

int power(int base, int exponent);
void readMachineCode(FILE* fp);
int binaryToDecimal(char binary[]);

char Store[32] = {};
char binary[32] = {};

int main() {

    readMachineCode(fopen("BabyTest1-MC.txt", "r"));
    printf("\nPrint store:\n");
    for (int n=0; n<32; ++n) {
        printf("%u ", Store[n]);
    }
    printf("\n");
}

// idea for this method is that I read in each character individually and append to binary char[]
// after filling the char[], I use binaryToDecimal() and store output in Store[].
void readMachineCode(FILE* fp) {
    
    if (fp != NULL) {

        // counts characters
        int counter=0;
        // counts every 32 characters
        int sCounter=0;

        char ch;

        while (ch != EOF) {
            // gets new character
            ch = fgetc(fp);

            // if valid binary char
            if ((ch == '0') || (ch == '1')) {
                //append char to binary[]
                strncat(binary, &ch, 1);
                ++counter;
                //if binary has 32 values (i.e., entire line has been read)
                if (counter == 32) {
                    //print for debug
                    printf("Printing line #%d:%s\n", sCounter, binary);
                    //convert line to integer and store int in Store[]
                    unsigned int output = binaryToDecimal(binary);
                    Store[sCounter] = output;
                    //update counters and clear binary[]
                    counter=0;
                    ++sCounter; 
                    memset(binary, 0, 255);
                    printf("\n");
                }   
            }
        }

        fclose(fp);

    }
    else {
        // should give error really but file should always exist
    }

}

// takes char[] of binary characters and outputs corresponding decimal value
int binaryToDecimal(char binary[]) {

    int decimal = 0;

    for (int i=0; i<32; ++i) {
        if (binary[i] == '1') {
            decimal = decimal + (pow(2, 31-i));
        }
    }
    printf("Decimal output:%u", decimal);
    return decimal;
}


