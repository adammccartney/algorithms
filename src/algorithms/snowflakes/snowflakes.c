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
#define SIZE 100000 

long int stack[SIZE];
int top = -1;
#define pop stack[top--];
#define push(s) stack[++top]=s;

struct SnowflakeNode {
	int snowflake[N_ARMS];
	struct SnowflakeNode* next;
};

struct SnowflakeNode* initSnowflakeNode(struct SnowflakeNode* s)
{
	/* Watch out for zero indexed off by one errors */
	/* N_ARMS is the total length of array (6) indexes are 0-5 */
	for (int i = N_ARMS; i > 0; i--) {
		s->snowflake[i-1] = pop;
	}
	return s;
}

int code(int snowflake[]) 
{
	return (snowflake[0] + snowflake[1] + snowflake[2] + 
		snowflake[3] + snowflake[4] + snowflake[5]) % SIZE; 
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

/* Iterate through the first array comparing the values to the second */
int identical_right(int snow1[], int snow2[], int start)
{
	int offset;
	for(offset = 0; offset < 6; offset++) {
		if (snow1[offset] != snow2[(start + offset) % 6])
			return 0;
	}
	return 1;
}

int identical_left(int snow1[], int snow2[], int start)
{
	int offset, snow2_index;
	for (offset=0; offset<6; offset++) {
		snow2_index = start - offset;
		if (snow2_index < 0)
			snow2_index = snow2_index + 6;
		if (snow1[offset] != snow2[snow2_index])
			return 0;
	}
	return 1;
}

int are_identical(int snow1[], int snow2[]) 
{
	int start;
	for (start = 0; start < 6; start++) {
		if (identical_right(snow1, snow2, start))
			return 1;
		if (identical_left(snow1, snow2, start))
			return 1;
	}
	return 0;
}



void identify_identical(struct SnowflakeNode* snowflakes[])
{
	struct SnowflakeNode *node1, *node2;
	int i;
	for(i = 0; i < SIZE; i++) {
		node1 = snowflakes[i];
		while (node1 != NULL) {
			node2 = node1->next;
			while (node2 != NULL) {
				if (are_identical(node1->snowflake, node2->snowflake)) {
					printf("Twin snowflakes found.\n");
					return;
				}
				node2 = node2->next;
			}
			node1 = node1->next;
		}
	}
	printf("No two snowflakes are alike.\n");
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
	static struct SnowflakeNode* snowflakes[SIZE] = {NULL};
	struct SnowflakeNode* snow;
	int n, i, snowflake_code;

	/* Get n, the number of snowflakes to eat */
	char* flbuf = malloc(sizeof(char) * MAXLEN);
	flbuf = getLine(flbuf); /* got 1 num on stack */
	pushNums(flbuf, 1);
	n = pop;
	if (top != -1) {
		printf("Error: expected an empty stack!\n");
		exit(-1);
	}
	/* Use n to eat the snowflakes */
	for (i = 0; i < n; i++) {
		snow = malloc(sizeof(struct SnowflakeNode));
		if (snow == NULL) {
			fprintf(stderr, "malloc error\n");
			exit(1);
		}
		char* linebuf = malloc(sizeof(char) * MAXLEN);
		linebuf = getLine(linebuf);
		/* expect to read 6 ints from line */
		pushNums(linebuf, N_ARMS);
		/* initialize snowflake from nums on stack */
		snow  = initSnowflakeNode(snow); /* pops numbers off the stack to make snowflake */
		if (top != -1) {
			printf("Error: expected an empty stack!\n");
			printf("Failed to push %s\n", flbuf);
			exit(-1);
		}
		snowflake_code = code(snow->snowflake);
		snow->next = snowflakes[snowflake_code];
		snowflakes[snowflake_code] = snow;
	}
	identify_identical(snowflakes);
	return 0;
}
