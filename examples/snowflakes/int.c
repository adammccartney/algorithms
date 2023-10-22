#include <math.h>
#include <stdio.h>
#include <stdint.h>
/* Show the maximum value of a 32bit unsigned int */


int main(void)
{
	double exp = 32;
	double base = 2;
	unsigned int result = pow(base, exp) - 1;
	if (result != UINT32_MAX)
		printf("Error: did not compute the correct value for uint32.\n");
	else
		printf("max val int: %u\n", result);
	return 0;
}
