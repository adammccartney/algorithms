#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <errno.h>

#define MAXLINE 1024
#define MAXNUMS  2
// foodlines.c: see readme for description 


/* The following is a scanner implementation 
 * We're including it the old fashioned way! 
 * */

long int stack[MAXNUMS];
int top = -1;
#define pop stack[top--];
#define push(s) stack[++top]=s;

/* Information about how the program will run. 
 * numlines is the total number of lines (N).
 * npersons is the number of people that join. 
 * */
struct FoodlineInfo {
	long int numlines;
	long int npersons;
};


/* Use the two numbers pushed onto the stack to initialize. */
struct FoodlineInfo initFoodlineInfo(struct FoodlineInfo flinfo)
{
	flinfo.npersons = pop;
	flinfo.numlines = pop;
	return flinfo; 
}

struct TwoLines {
	char first[MAXLINE];
	char second[MAXLINE];
};

struct Foodlines {
	long int* lns;
	int len;
};

/* Use knowledge about the number of lines to pop needed values off the stack */
struct Foodlines initFoodlines(struct Foodlines flines,
			       int numlines)
{
	flines.len = numlines;
	flines.lns = malloc(sizeof(long int) * flines.len);
	for (int i=numlines - 1; i >= 0; i--) // stack is upside-down
	{
		flines.lns[i] = pop
	}
	return flines;
}

void freeFoodlines(struct Foodlines flines)
{
	free(flines.lns);
}

/* Read exactly two lines of input from stdin */
struct TwoLines initTwoLines(struct TwoLines lines)
{
	/* TODO: improve error handling */
	int read = 0;
	char buf[MAXLINE];
	do 
	{
		if (!fgets(buf, MAXLINE, stdin))
		{
			// reading input failed.
			exit(1);
		}
		if (read == 0)
			memcpy(lines.first, buf, MAXLINE);
		if (read == 1)
			memcpy(lines.second, buf, MAXLINE);
	} while (++read < 2);
	return lines;
}

uint8_t getshortest(uint32_t len, long int lines[],
		    uint32_t shortest_i) {
	int i;
	int min = lines[0];
	for (i = 0; i < len; i++) {
		if (lines[i] < min)
			shortest_i = i;
	}
	return shortest_i;
}

/* Read a line and push at most n (expected) numbers onto the stack */
void pushNums(char* buf, int expect)
{
	long val;
	int success;
	int count = 0;

	/* Use the initial char in the line first. 
	 * There might be more numbers coming down the pipe.*/
	char *endptr = buf; 
	do 
	{
		// convert our line to integers
		errno = 0; // reset error number

		val = strtol(endptr, &endptr, 10);
		if (errno == ERANGE)
		{
			printf("Sorry, number too big or too small.");
			success = 0;
		}
		else if (endptr == buf)
		{
			// no char read
			success = 0;
		}
		else if (*endptr && *endptr != '\n')
		{
			// *endptr is neither end of string or newline
			// so we didn't get the whole input
			success = 0;
			/* endptr is the address of the first invalid char */
		}
		else 
		{
			success = 1;
		}
		count++;
		push(val); /* Push the last value onto the stack. */
	} while ((!success) && (count < expect));
	
}


int main(int argc, char* argv[])
{
	struct TwoLines lines;
	/* It's assumed an input file contains 2 lines */
	lines = initTwoLines(lines);
	/* Extract numeric data from first line */
	int expected = 2;
	pushNums(lines.first, expected);
	/* The first line contains data about how to parse the second. */
	struct FoodlineInfo flinfo;
	flinfo = initFoodlineInfo(flinfo); // pop what values we need
	/* The second line contains all the info about the length of the lines.*/
	pushNums(lines.second, flinfo.numlines);
	struct Foodlines flines;
	flines = initFoodlines(flines, flinfo.numlines);
	
	int len_ljoined = 0;
        int shortest_i = 0; // init with index 0
        do {
                shortest_i = getshortest(flinfo.numlines, flines.lns, shortest_i);
                len_ljoined = flines.lns[shortest_i];
                printf("%d\n", len_ljoined);
                flines.lns[shortest_i] += 1;
        } while (--flinfo.npersons > 0);

	freeFoodlines(flines);
	return 0;
}
