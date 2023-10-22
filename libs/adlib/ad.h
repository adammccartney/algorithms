#include <error.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int top;
    int* tail;
    int* items;
} queue;

queue* initQueue (int size);
void freeQueue(queue* q);
void enqueue (queue* q, int item);
int dequeue (queue* q);
