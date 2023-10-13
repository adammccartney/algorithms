#include <stdlib.h>

typedef struct {
    int size;
    int* head;
    int* tail;
    int* items;
} queue;

queue* initQueue (int size);
void freeQueue(queue* q);
void enqueue (queue* q, int item);
void dequeue (queue* q, int item);
