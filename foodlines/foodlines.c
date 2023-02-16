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

struct Scanner {
  const char *start;
  const char *current;
};

struct Scanner scanner;

void initScanner(const char *decl) 
{
  scanner.start = decl;
  scanner.current = decl;
}

static char advance() 
{
	scanner.current++;
	return scanner.current[-1];
}

static _Bool isAtEnd() 
{
	return *scanner.current == '\0';
}


static char peek() { return *scanner.current; }

static char peekNext() 
{ 
	if (isAtEnd()) return '\0';
	return scanner.current[1];
}

_Bool xisalpha(char c)
{
	return c>='a' && c<='Z';
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
    case ' ':
    case '\t':
      advance();
      break;
    default:
      return;
    }
  }
}

_Bool xiswhitespace(char c)
{
	if ((c == ' ') || (c == '\t'))
		return true;
	else
		return false;
}

_Bool xisnum(char c)
{
	if ((c >= 0) || (c <= 9))
		return true;
	else
		return false;
}

/* Information about how the program will run. 
 * numlines is the total number of lines (N).
 * npersons is the number of people that join. 
 * */
struct FoodlineInfo {
	long int numlines;
	long int npersons;
};

struct FoodlineInfo flinfo;

/* Use the two numbers pushed onto the stack to initialize. */
void initFoodlineInfo(const long int stack[])
{
	flinfo.npersons = pop;
	flinfo.numlines = pop;
}

/* Verbose routine to convert a character buffer to long int */
void chtol(long int dest, char* src)
{
	int success;
	char* endptrone;
	errno = 0;
	dest = strtol(src, &endptrone, 10);
	if (errno == ERANGE)
	{
		printf("Error: number of lines or number of persons joining\n");
		printf("     : too small or too large.\n"); 
		success = 0;
	}
	else if (endptrone == src)
	{
		// no character was read 
		success = 0;
	}
	else if (*endptrone && *endptrone != '\n') 
	{
		// *endptrone neither end of string nor newline,
		// did not convert the *whole* input
		success = 0;
	}
	else 
	{
		success = 1;
	}
}



/* Invariable for scanning the first line */
/* We know that we want to read exactly two numbers from line one */
void scanLine(int expected)
{
	int consumed = 0;
	int numdigits = 0;
	while (((peek() != '\0') && (peek() != '\n')) 
	       && (consumed < expected)) {
		/* Here we want to read until we find a whitespace */
		/* count how many digits we read */
		if (xisnum(peek())) { 
			numdigits++;
			advance();
		}
		if ((peekNext() == '\0') || 
		    (xiswhitespace(peek()) && numdigits != 0)) {
			/* Found an integer > 9 */
			/* copy numdigits to buf */
			char buf[MAXLINE];
			long int prginfo = 0;
			memcpy(buf, scanner.start, numdigits);
			chtol(prginfo, buf);
			push(prginfo);
			consumed++;
			numdigits = 0; // reset
			advance(); // past current whitespace
			scanner.start = scanner.current;
		}
		skipWhitespace();
	}
}


struct TwoLines {
	char first[MAXLINE];
	char second[MAXLINE];
};

struct Foodlines {
	long int* lns;
};

struct Foodlines foodlines;

/* Use knowledge about the number of lines to pop needed values off the stack */
void initFoodlines(long int numlines)
{
	foodlines.lns = malloc(sizeof(long int) * numlines);
	for (int i=0; i < numlines; i++)
	{
		foodlines.lns[i] = pop
	}
}

void freeFoodlines()
{
	free(foodlines.lns);
}

/* Read exactly two lines of input from stdin */
int initTwoLines(struct TwoLines lines)
{
	/* TODO: improve error handling */
	int read = 0;
	char *dest = NULL;
	char buf[MAXLINE];
	do 
	{
		if (!fgets(buf, MAXLINE, stdin))
		{
			// reading input failed.
			return 1;
		}
		read++;
		if (read == 1)
			dest = lines.first;
		if (read == 2)
			dest = lines.second;
		memcpy(dest, buf, MAXLINE);
	} while (read < 2);
	return 0;
}


uint8_t getshortest(uint32_t len, long int lines[],
		    uint32_t shortest_i) {
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
	struct TwoLines lines;
	/* It's assumed an input file contains 2 lines */
	initTwoLines(lines);
	/* Extract numeric data from first line */
	const int expected = 2;
	scanLine(expected);
	/* The first line contains data about how to parse the second. 
	 * The second line contains all the info about the length of the lines.
	 * */
	scanLine(flinfo.numlines);
	
	//// N is number of lines 
	//// M number of people arrive
	uint8_t shortest_i = 2; // start with 2 index as shortest 
	uint32_t len_ljoined = 0;
	do {
		shortest_i = getshortest(flinfo.numlines, foodlines.lns, shortest_i);
		len_ljoined = foodlines.lns[shortest_i];
		printf("%d\n", len_ljoined);
		foodlines.lns[shortest_i] += 1;
	} while (flinfo.numlines-- >= 1);
	return 0;
}

