#ifndef AD_QUEUE_H
#define AD_QUEUE_H
#include "common.h"

typedef struct {
    int32_t size;
    int32_t top;
    uint32_t *tail;
    uint32_t *items;
} queue;

void init_queue (queue* q, size_t size);
void free_queue(queue* q);
void enqueue (queue* q, uint32_t start);
uint32_t dequeue (queue* q);
Boolean empty_queue(queue* q);

#endif
