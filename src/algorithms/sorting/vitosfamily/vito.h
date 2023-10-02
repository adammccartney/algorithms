#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int stackheight();
int adrand(int l, int r);
void printstack(void);

char* getLine(size_t size);
void pushNums(char* buf, int expect);

void swap(int* l, int* r);
int choosePivot(int* A, int l, int r);
int partition(int* A, int l, int r);
void Quicksort(int* A, int l, int r);

int getStackMedian();

struct stack;
struct stack* initStack(struct stack* s, int size);
struct stack* pushStack(struct stack* s, int item);
struct stack* popStack();
struct stack* freeStack();
