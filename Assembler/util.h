#ifndef __UTIL__H__
#define __UTIL__H__

#include "lexer.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_LINE_LEN 128
#define MAX_LINES 64

int displayBin(uint32_t input);
int outputLines(FILE *fp, Line *lines, int numLines);
int inputLines(FILE *fp, char lines[MAX_LINES][MAX_LINE_LEN]);
uint32_t saveInstruction(Line *line);

#endif