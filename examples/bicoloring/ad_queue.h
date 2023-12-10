#ifndef AD_QUEUE_H
#define AD_QUEUE_H
#include "common.h"

typedef struct {
    int32_t front;
    int32_t back;
    int32_t size;
    int32_t capacity;
    uint32_t* items;
} queue;

queue* init_queue(uint32_t capacity);
void free_queue(queue* q);
void enqueue (queue* q, uint32_t item);
uint32_t dequeue (queue* q);
Boolean empty_queue(queue* q);

#endif
