#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int adrand(int l, int r);
void printstack(void);

struct stack;
void initStack(struct stack* s, int size);
void pushStack(struct stack* s, int item);
int popStack(struct stack* s);
void resetStack(struct stack* s);
void freeStack(struct stack* s);
int medianStack(struct stack* s);

void Quicksort(struct stack* s, int l, int r);
void swap(int* l, int* r);
int choosePivot(struct stack* s, int l, int r);
int partition(struct stack* s, int l, int r);

