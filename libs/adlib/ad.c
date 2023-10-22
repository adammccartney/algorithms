#include "adlib.h"

queue* initQueue (int size) {
    queue* q = (queue*) malloc(sizeof(queue) + sizeof(int) * size);
    if (!q) {
        fprintf(stderr, "malloc error: failed for queue\n");
        exit(1);
    }
    q->size = size;
    q->top = -1;
    q->items = (int*) malloc(sizeof(int) * size);
    if (!q->items) {
        printf("malloc error: failed for q->items\n");
        exit(1);
    }
    return q;
}

void freeQueue(queue* q) {
    free(q);
}

void enqueue(queue* q, int item) {
    if (q->top >= q->size) { /* Overflow */
        fprintf(stderr, "error: overflow while attempting enqueue\n");
        return;
    }
    q->top++;
    q->items[q->top] = item;
}

int dequeue(queue* q) {
    if (q->top <= -1) { /* Underflow */
        fprintf(stderr, "error: underfow while attempting dequeue\n");
        return -1;
    }
    int result = q->items[q->top];
    q->top--;
    return result;
}
