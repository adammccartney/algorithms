#include "vito.h"

#define MAXRELATIVES 512
#define MAXSTREETNUM 30000
#define SIZE 4096

struct stack {
    struct stack* next;
    int top;
    int size;
    int* items;
};

struct stack* append (struct stack* head, struct stack* tail) {
    tail->next = head;
    head = tail;
    return head;
}

struct stack* initStack(struct stack* s, int size) {
    s->top = -1;
    s->size = size;
    s->items = (int*) malloc(s->size * sizeof(*s->items));
    if (!s->items) {
		fprintf(stderr, "malloc error\n");
		exit(1);
    }
    return s;
}

/* initialize a linked list of len stacks */
struct stack* allocStackList(int len) {
    struct stack* top = (struct stack*) malloc(sizeof(struct stack*));
    top->next = NULL;
    if (len == 1) {
        return top;
    }
    int i;
    for (i = 1; i < len; i++) {
        struct stack* snew = (struct stack*) malloc(sizeof(struct stack*));
        snew->next = NULL;
        if (!snew) {
            fprintf(stderr, "malloc failed for stack");
            return NULL;
        }
        top = append(top, snew);
    }
    return top;
}

void resetStack(struct stack* s) {
    while (s->top > -1) {
        s->items[s->top--] = 0;
    }
    s->size = 0;
    free(s->items);
}

void freeStackList(struct stack* start) {
    struct stack* p;
    struct stack* tmp;
    for (p=start; p; p=tmp) {
        tmp=p->next;
        free(p);
    }
}

int popStack(struct stack* s) {
    return s->items[s->top--];
}

void pushStack(struct stack* s, int elem) {
    s->top += 1;
    s->items[s->top] = elem;
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


void rMinDist(struct stack* s, int median, int statmed) {
    int dist = 0;
    int i;
    for (i = 0; i < median; i++) {
        dist += abs(s->items[i] - statmed);
    }
    for (i = median + 1; i < s->size; i++) {
        dist += abs(s->items[i] - statmed);
    }
    printf("%d\n", dist);
}


int main(int argc, char* argv[]) {
    /* first line gives number of lines to expect  */
    int nlines, numrel;
    char* line;
    line = getLine(SIZE);
    nlines = atoi(line); /* num buffers to allocate */
    free(line);
    int i, k, kstat, l, r;
    /* initialize a list of stacks, one for each line of input */
    struct stack* node = allocStackList(nlines);
    struct stack* top = node;
    while (node != NULL) {
        char* buf = getLine(SIZE);
        numrel = atoi(buf); /* size of the array */
        node = initStack(node, numrel);
        pushNums(buf, node->size, node); /* address of each relative */
        free(buf);
        k = medianStack(node);
        l = 0;
        r = node->size - 1;
        kstat = Rselect(node, l, r, k);
        rMinDist(node, k, kstat);
        node = node->next;
    }
    /* free all the memory we allocated for the stack list */
    freeStackList(top);
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

int partition(struct stack* s, int l, int r, int p) {
    int pval = s->items[p];
    swap(&s->items[p], &s->items[r]);
    int storeIndex = l;
    int i;
    for (i = l; i < r; i++) {
        if (s->items[i] < pval) {
            swap(&s->items[storeIndex], &s->items[i]);
            storeIndex += 1;
        }
    }
    swap(&s->items[r], &s->items[storeIndex]);
    return storeIndex;
}


/* rselect performs a linear time selection
 * returns statistical i from array
 * guarantees that i will be in correct position before being returned */
int Rselect(struct stack* s, int l, int r, int k) {
    int p, j;
    if (l == r) { /* list only contains 1 item */
        return s->items[l];
    }
    p = l + floor(rand() % (r - l + 1));
    j = partition(s, l, r, p);
    if (k == j) { /* got lucky */
        return s->items[k];
    } else if (k < j) {
        return Rselect(s, l, j - 1, k);
    } else {
        return Rselect(s, l + 1, r, k);
    }
}
