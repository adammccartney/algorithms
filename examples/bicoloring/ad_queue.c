#include "ad_queue.h"
/* Queue */

#define ERR_UNDERFLOW -1

void init_queue (queue* q, size_t size) {
    q = (queue*) malloc(sizeof(queue) + sizeof(uint32_t) * size);
    if (!q) {
        fprintf(stderr, "malloc error: failed for queue\n");
        exit(1);
    }
    q->size = size;
    q->top = -1;
    q->items = (uint32_t*) malloc(sizeof(uint32_t) * size);
    if (!q->items) {
        printf("malloc error: failed for q->items\n");
        exit(EXIT_FAILURE);
    }
}

void free_queue(queue* q) {
    free(q);
}

void enqueue(queue* q, uint32_t item) {
    if (q->top >= q->size) { /* Overflow */
        fprintf(stderr, "error: overflow while attempting enqueue\n");
        return;
    }
    q->top++;
    q->items[q->top] = item;
}

uint32_t dequeue(queue* q) {
    if (q->top <= -1) { /* Underflow */
        fprintf(stderr, "error: underfow while attempting dequeue\n");
        return ERR_UNDERFLOW;
    }
    uint32_t result = q->items[q->top];
    q->top--;
    return result;
}

Boolean empty_queue(queue* q) {
    if (q->top <= -1) {
        return TRUE;
    }
    return FALSE;
}
