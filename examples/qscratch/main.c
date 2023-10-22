#include "ad.h"

int main() {
    queue* q = initQueue(10);

    int i;
    for (i = 0; i < 10; i++) {
        enqueue(q, i);
    }
    int res;
    for (i = 0; i < 10; i++) {
        res = dequeue(q);
        printf("%d\n", res);
    }
    freeQueue(q);
    return 0;
}
