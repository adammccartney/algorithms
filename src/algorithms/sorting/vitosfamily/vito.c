#include "vito.h"

#define MAXRELATIVES 500
#define MAXSTREETNUM 30000
#define SIZE 512

int stack[SIZE];
int top = -1;
#define pop stack[top--];
#define push(s) stack[++top]=s;

struct stack {
    int *items;
    int size;
    int top;
};

struct stack* initStack(struct stack* s, int size) {
    s->items = malloc(sizeof(int) * size);
    if (s->items == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
    }
    s->top = -1;
    return s;
}

/*  find the length of the stack */
int stackheight() {
    int result = top + 1;
    return result;
}

void emptyStack() {
    while (top > -1) {
        pop;
    }
}

/*  return the index of the median element */
/*  If the stack has an odd number of elements, it returns exactly the middle */
/*  element. If even, it returns a floor division. */
int getStackMedian() {
    int height = stackheight();
    int result;
    if (height % 2 == 0) {
        result = height / 2;
    } else {
        result = (height / 2) + 1;
    }
    return stack[result - 1];
}

int main(int argc, char* argv[]) {
    /* first line gives number of lines to expect  */
    int nlines, numrel, median, result;
    char* buf = getLine(SIZE);
    nlines = atoi(buf); /* num buffers to allocate */
    free(buf);
    int i;
    for (i = 0; i < nlines; i++) {
        buf = getLine(SIZE);
        numrel = atoi(buf); /* size of the array */
        pushNums(buf+1, numrel); /* address of each relative */
        Quicksort(stack,0,numrel-1);
        /* now the stack contains the addresses */
        /* the median will tell us the optimal position for vito to live */
        result = getStackMedian();
        printf("%d\n", result);
        emptyStack();
    }
    return 0;
}

/* Function to get a line of input */
char* getLine(size_t size) {
	char* input = NULL;
	char* buf;
	buf = malloc(size);  /* allocate the min number of bytes */
	if (buf == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
    size_t len = 0, newlen = 0;
	do {
		/* read at most size bytes */
		if(!fgets(buf, size, stdin))
		{
			/* read null bytes */
			buf[0] = '\0';
			return buf;
		}
		newlen = strlen(buf); /* check length of string to be copied */
		if (newlen > 0 && buf[newlen-1] == '\n') {
			buf[--newlen] = '\0'; /* remove the trailing newline if present */
		}
		if (newlen == size-1) { /* we're not finished */
			size *= 2;   /* Double the size    */
		}
		input = realloc(input, size);
		if (input == NULL) {
			fprintf(stderr, "realloc error\n");
			exit(1);
		}
		memcpy(input + len, buf, newlen+1); /* begin to write at byte 0, else */
		len += newlen;
		size += newlen;
	} while (buf[newlen] && buf[newlen-1]!='\n' && buf[newlen-1]!=EOF);
	return input;
}


/* Read a line and push at most n (expected) numbers onto the stack */
void pushNums(char* buf, int expect) {
	long val;
	int success;
	int count = 0;
	/* Use the initial char in the line first.
	 * There might be more numbers coming down the pipe.*/
	char *endptr = buf;
	do {
		/* convert our line to integers */
		errno = 0; /* reset error number */
		val = strtol(endptr, &endptr, 10);
		if (errno == ERANGE) {
			printf("Sorry, number too big or too small.");
			success = 0;
		} else if (endptr == buf) {
			/* no char read */
			success = 0;
		} else if (*endptr && *endptr != '\n') {
			/*  *endptr is neither end of string or newline
			 * so we didn't get the whole input */
			success = 0;
			/* endptr is the address of the first invalid char */
		} else {
			success = 1;
		}
		count++;
		push(val); /* Push the last value onto the stack. */
	} while ((!success) && (count < expect));
}

/*  swap two integers in place using xor */
void swap(int* l, int* r) {
    if (*l == *r) {
        return;
    }
    *r = *l ^ *r;
    *l = *l ^ *r;
    *r = *r ^ *l;
}


/*  generate a random number between l and r */
int adrand(int l, int r) {
    int res = (rand() % (r - l + 1)) + l;
    return res;
}

/*  choose a random pivot point in array A */
int choosePivot(int* A, int l, int r) {
    if (l < 0 || r >= stackheight() || l > r) {
        return -1;
    }
    int rnum = adrand(l, r);
    return rnum;
}

int partition(int* A, int l, int r) {
    int p = A[l];
    int i = l + 1;
    int j;
    for (j = l + 1; j <= r; j++) {
        if (A[j] < p) {
            swap(&A[j], &A[i]);
            i++;
        }
    }
    swap(&A[l], &A[i-1]);
    return i - 1;
}

void Quicksort(int* A, int l, int r) {
    if (l >= r) { /* 0- or 1-element subarray */
        return;
    }
    int i = choosePivot(A, l, r);
    swap(&A[l], &A[i]); /* make pivot first */

    int j = partition(A, l, r);
    Quicksort(A, l, j-1);
    Quicksort(A, j+1, r);
}


