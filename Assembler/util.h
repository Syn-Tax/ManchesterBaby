#ifndef __UTIL__H__
#define __UTIL__H__

#include "lexer.h"
#include <stdint.h>
#include <stdio.h>

// define buffer sizes
#define MAX_LINE_LEN 128
#define MAX_LINES 64
#define INS_LEN 32 // number of bits per line

/** Function to print integer as binary value (USED FOR TESTING AND DEBUGGING)
 *  @param input: unsigned 32 bit integer
 *  @returns nothing of use
 */
int displayBin(uint32_t input);

/** Function to output lines array to file (as machine code)
 *  @param fp: file pointer to output file
 *  @param lines: array of Line objects to be written to file
 *  @param numLines: total number of lines
 *  @returns nothing of use
 */
int outputLines(FILE *fp, Line *lines, int numLines);

/** Function to read in file
 *  @param fp: filepointer
 *  @param lines: array of strings as output
 *  @returns number of lines read in
 */
int inputLines(FILE *fp, char lines[MAX_LINES][MAX_LINE_LEN]);

/** Function to convert Line object into instruction integer
 *  @param line: pointer to Line object to be outputted
 *  @returns integer instruction (as unsigned, 32 bit integer)
 */
uint32_t saveInstruction(Line *line);

#endif