int getLineNumber(int rowNumber) {
    int lineNumber = 0;
    int num1 = inputFile[rowNumber][0];
    int num2 = inputFile[rowNumber][1];
    int num3 = inputFile[rowNumber][2];
    int num4 = inputFile[rowNumber][3];
    int num5 = inputFile[rowNumber][4];
    if (num1 == 1) {
        lineNumber = lineNumber + 1;
    }
    if (num2 == 1) {
        lineNumber = lineNumber + 2;
    }
    if (num3 == 1) {
        lineNumber = lineNumber + 4;
    }
    if (num4 == 1) {
        lineNumber = lineNumber + 8;
    }
    if (num5 == 1) {
        lineNumber = lineNumber + 16;
    }
    return lineNumber;
}

int getInstructionNumber(int rowNumber) {
    int instructionNumber = 0;
    int num1 = inputFile[rowNumber][13];
    int num2 = inputFile[rowNumber][14];
    int num3 = inputFile[rowNumber][15];
    if (num1 == 1) {
        instructionNumber = instructionNumber + 1;
    }
    if (num2 == 1) {
        instructionNumber = instructionNumber + 2;
    }
    if (num3 == 1) {
        instructionNumber = instructionNumber + 4;
    }
    return instructionNumber;
}

int main() {
    inputFile[0][2] = 1;
    displayCurrentInputFile();
    int test = getLineNumber(0);
    printf("%d\n", test);
    return 0;
}