#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define N_ARMS 6 /* snowflake has 6 arms */
#define MAX_SPACES 5
#define D_UINT32_MAX 10 /* digits in UINT32 MAX */
#define MAXLEN ((D_UINT32_MAX * 6) + MAX_SPACES) /* Max line length */
#define MAXNUMS 100000 

long int stack[MAXNUMS];
int top = -1;
#define pop stack[top--];
#define push(s) stack[++top]=s;

struct Snowflake {
	unsigned int arms[N_ARMS];
};

void initSnowflake(struct Snowflake s)
{
	for (int i = N_ARMS; i > 0; i--) {
		s.arms[i] = pop;
	}
}

/* Snowflake list */
struct Node {
	struct Snowflake sf;
	struct Node* next;
};

void initNode(struct Node node, struct Snowflake sf)
{
	node.sf = sf;
	node.next = NULL;
}

void appendNode(struct Node node, struct Node* new)
{
	node.next = new;
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

void identify_identical(int values[], int n)
{
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = i+1; j < n; j++) {
			if (values[i] == values[j]) {
				printf("Twin integers found.\n");
				return;
			}
		}
	}
	printf("No two integers are alike.\n");
}


char* getLine(char* line)
{
	char buf[MAXLEN]; // remember to copy whitespace!
	if(!fgets(buf, MAXLEN, stdin))
	{
		// reading input failed.
		exit(1);
	}
	memcpy(line, buf, MAXLEN);
	return line;
}

int main(int argc, char* argv[])
{
	int a[5] = {1, 2, 3, 1, 5};
	identify_identical(a, 5);
	return 0;
}

//int main(int argc, char* argv[])
//{
//	/* Get first line containing count of remaining lines. */
//	char* flbuf = malloc(sizeof(char) * MAXLEN);
//	flbuf = getLine(flbuf); /* got 1 num on stack */
//	pushNums(flbuf, 1);
//	int remaining = pop;
//	if (top != -1) {
//		printf("Error: expected an empty stack!\n");
//		exit(-1);
//	}
//	/* allocate memory for remaining */
//	struct Snowflake sflks[remaining];
//	do 
//	{
//		char* linebuf = malloc(sizeof(char) * MAXLEN);
//		linebuf = getLine(linebuf);
//		/* expect to read 6 ints from line */
//		pushNums(linebuf, N_ARMS);
//		/* need to initialize the snowflakes here */
//
//		/* initialize snowflake from line */
//		struct Snowflake sf = { .arms = {0, 0, 0, 0, 0, 0} };
//		initSnowflake(sf); /* pops numbers off the stack */
//		if (top != -1) {
//			printf("Error: expected an empty stack!\n");
//			printf("Failed to push %s\n", flbuf);
//			exit(-1);
//		}
//		/* store this snowflake in array */
//		sflks[remaining] = sf;
//	} while (remaining > 0);
//
//	/* Outer loop generates a permutation matrix */
//
//	/* Inner loop compares rows to control snowflake */
//
//	return 0;
//}
