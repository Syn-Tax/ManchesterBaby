#include <stdio.h>
#include "util.h"

void displayBin(unsigned int input)
{
	for (int i = 0; i < 32; i++)
	{
		printf("%d", ((input >> i) % 2));
	}
	printf("\n");
}