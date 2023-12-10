#include "ad_queue.h"
/* Queue */

#define MAXV 255
#define ERR_UNDERFLOW INT_MIN

queue* init_queue (uint32_t capacity) {
    queue* q = (queue*)malloc(sizeof(queue));
    if (!q) {
        fprintf(stderr, "malloc error: queue\n");
        exit(1);
    }
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;

    q->back = capacity - 1;
    q->items = (uint32_t*)malloc(q->capacity * sizeof(uint32_t));
    return q;
}

void free_queue(queue* q) {
    free(q->items);
    free(q);
}

Boolean full_queue(queue* q) {
    if (q->size == q->capacity)
        return TRUE;
    return FALSE;
}


Boolean empty_queue(queue* q) {
    if (q->size == 0)
        return TRUE;
    return FALSE;
}

void enqueue(queue* q, uint32_t item) {
    if (full_queue(q)) { /* Overflow */
        fprintf(stderr, "error: overflow while attempting enqueue\n");
        return;
    }
    q->back = (q->back + 1) % q->capacity;
    q->items[q->back] = item;
    q->size = q->size + 1;
}

uint32_t dequeue(queue* q) {
    if (empty_queue(q)) { /* Underflow */
        fprintf(stderr, "error: underfow while attempting dequeue\n");
        return ERR_UNDERFLOW;
    }
    uint32_t res = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size = q->size - 1;
    return res;
}

