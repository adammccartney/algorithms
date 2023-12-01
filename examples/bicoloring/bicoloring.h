#ifndef BICOLORING_H
#define BICOLORING_H
#include <stdint.h>

typedef struct test_case test_case;
typedef struct test_case {
    uint8_t  nodes;
    uint16_t edges;
} test_case;


typedef struct {
    int size;
    int top;
    test_case *tail;
    test_case *items;
} queue;

queue* initQueue (int size);
void freeQueue(queue* q);
void enqueue (queue* q, test_case item);
test_case dequeue (queue* q);

#endif
