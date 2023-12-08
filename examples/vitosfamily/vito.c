#include "vito.h"

#define MAXRELATIVES 512
#define MAXSTREETNUM 30000
#define SIZE 4096

struct stack {
    int top;
    int size;
    int *items;
};

void initStack(struct stack* s, int size) {
    s->top = -1;
    s->size = size;
    s->items = malloc(s->size * sizeof(*s->items));
    if (!s->items) {
		fprintf(stderr, "malloc error\n");
		exit(1);
    }
}

void resetStack(struct stack* s) {
    while (s->top > -1) {
        s->items[s->top--] = 0;
    }
    s->size = 0;
    free(s->items);
}

void freeStack(struct stack* s) {
    free(s);
}

int popStack(struct stack* s) {
    return s->items[s->top--];
}

void pushStack(struct stack* s, int elem) {
    s->items[++s->top] = elem;
}

/* Find the median element. Note that the first element of items is a duplicate
 * of the stack size struct member, so we don't want to count that. */
int medianStack(struct stack* s) {
    int result;
    if (s->size % 2 == 0) {
        result = s->size / 2;
    } else {
        result = (s->size / 2) + 1;
    }
    return result-1; /* -1 accounts for zero indexing */
}

/* write a minimal sum of distances from the median to each other member */
void printMinDistSum(struct stack* s) {
    int median;
    median = medianStack(s);
    int dist = 0;
    int i;
    for (i = 0; i < median; i++) {
        dist += abs(s->items[i] - s->items[median]);
    }
    for (i = median + 1; i < s->size; i++) {
        dist += abs(s->items[i] - s->items[median]);
    }
    printf("%d\n", dist);
}



int main(int argc, char* argv[]) {
    /* first line gives number of lines to expect  */
    int nlines, numrel, median, result, dist;
    char* buf;
    buf = ad_getline(SIZE);
    nlines = atoi(buf); /* num buffers to allocate */
    free(buf);
    struct stack* s = NULL;
    s = malloc(sizeof *s);
    if (!s) {
        fprintf(stderr, "malloc failed for stack");
        return 1;
    }
    int i;
    for (i = 0; i < nlines; i++) {
        buf = ad_getline(SIZE);
        numrel = atoi(buf); /* size of the array */
        initStack(s, numrel);
        pushNums(buf, s->size, s); /* address of each relative */
        Quicksort(s,0,s->size-1);
        /* now the stack contains the addresses */
        /* the median will tell us the optimal position for vito to live */
        printMinDistSum(s);
        resetStack(s);
        free(buf);
    }
    freeStack(s);
    return 0;
}

/* Function to get a line of input */
char* ad_getline(size_t size) {
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
void pushNums(char* buf, int expect, struct stack* s) {
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
        if (count > 0) { /* we don't want first number */
            pushStack(s, val); /* Push the value onto the stack. */
        }
		count++;
	} while ((!success) && (count <= expect));
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
int choosePivot(struct stack* s, int l, int r) {
    if (l < 0 || r >= s->size || l > r) {
        return -1;
    }
    int rnum = adrand(l, r);
    return rnum;
}

int partition(struct stack* s, int l, int r) {
    int p = s->items[l];
    int i = l + 1;
    int j;
    for (j = l + 1; j <= r; j++) {
        if (s->items[j] < p) {
            swap(&s->items[j], &s->items[i]);
            i++;
        }
    }
    swap(&s->items[l], &s->items[i-1]);
    return i - 1;
}

void Quicksort(struct stack* s, int l, int r) {
    if (l >= r) { /* 0- or 1-element subarray */
        return;
    }
    int i = choosePivot(s, l, r);
    swap(&s->items[l], &s->items[i]); /* make pivot first */

    int j = partition(s, l, r);
    Quicksort(s, l, j-1);
    Quicksort(s, j+1, r);
}
