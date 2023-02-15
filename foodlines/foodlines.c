#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

#define MAXLINE 1024
// foodlines.c: see readme for description 

uint8_t getshortest(uint32_t len, uint32_t lines[],
		    uint8_t shortest_i) {
	int i;
	for (i = 0; i < len - 1; i++) {
		if (lines[i] <= lines[i+1])
			shortest_i = i;
	}
	return shortest_i;
}

uint32_t whitespace(char c) 
{
	if ((c == ' ') || (c == '\t')) {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char* argv[])
{
	FILE* f = NULL;
	uint32_t N = 0, M = 0;

	/* read filename from stdin */
	if (argc != 2) 
		printf("Usage: foodlines <input>\n");
	if (argc == 2) 
		f = fopen(argv[1], "r");
	/* It's assumed an input file contains 2 lines */
	/* read the first line */
	/* first line */
	char* line_one = malloc(sizeof(char) * MAXLINE);
	char* line_two = malloc(sizeof(char) * MAXLINE);
        line_one = fgets(line_one, MAXLINE, f);
	printf("line one: %s", line_one);
	/* parse N and M */
	int i = 0;
	while (*line_one++ != '\0') {
		if ((i == 0) && (*line_one != ' ')) {
			N = *line_one;
			i++;
		}
		if ((i == 1) && (*line_one != ' ')) {
			M = *line_one;
			i++;
		}
	}
	printf("N: %c  M: %c\n", N, M);
	/*second line */	
	line_two = fgets(line_two, MAXLINE, f);
	printf("line two: %s", line_two);
	//// N is number of lines 
	//// M number of people arrive
	//uint8_t shortest_i = 2; // start with 2 index as shortest 
	//uint32_t len_ljoined = 0;
	//while (M >= 1) {
	//	shortest_i = getshortest(M, lines, shortest_i);
	//	len_ljoined = lines[shortest_i];
	//	printf("%d\n", len_ljoined);
	//	lines[shortest_i] += 1;
	//	M--;
	//}
	return 0;
}

