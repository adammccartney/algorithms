#include "adlib.h"

queue* initQueue (int size) {
    queue* q = (queue*) malloc(sizeof(queue) + sizeof(int) * size);
    return q;
}

void freeQueue(queue* q) {
    free(q);
}
