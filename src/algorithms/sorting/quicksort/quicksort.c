#include "quicksort.h"

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

