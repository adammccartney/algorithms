#include <assert.h>
#include <errno.h>
#include <math.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int adrand(int l, int r);
void printstack(void);

char* getLine(size_t size);

struct stack;
void initStack(struct stack* s, int size);
void pushStack(struct stack* s, int item);
int popStack(struct stack* s);
void resetStack(struct stack* s);
void freeStack(struct stack* s);
void pushNums(char* buf, int expect, struct stack* s);
int medianStack(struct stack* s);
void printMinDistSum(struct stack* s);

void Quicksort(struct stack* s, int l, int r);
void swap(int* l, int* r);
int choosePivot(struct stack* s, int l, int r);

int partition(struct stack* s, int l, int r, int p);

int Rselect(struct stack* s, int l, int r, int k);
void rMinDist(struct stack* s, int median, int statmed);
