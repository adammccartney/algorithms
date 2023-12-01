
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include "bicoloring.h"

#define MAXLINE 255
#define TESTCASES 512

test_case ERR_TC_UNDERFLOW = {1, 1};

/* Queue */

queue* initQueue (int size) {
    queue* q = (queue*) malloc(sizeof(queue) + sizeof(test_case) * size);
    if (!q) {
        fprintf(stderr, "malloc error: failed for queue\n");
        exit(1);
    }
    q->size = size;
    q->top = -1;
    q->items = (test_case*) malloc(sizeof(test_case) * size);
    if (!q->items) {
        printf("malloc error: failed for q->items\n");
        exit(1);
    }
    return q;
}

void freeQueue(queue* q) {
    free(q);
}

void enqueue(queue* q, test_case item) {
    if (q->top >= q->size) { /* Overflow */
        fprintf(stderr, "error: overflow while attempting enqueue\n");
        return;
    }
    q->top++;
    q->items[q->top] = item;
}

test_case dequeue(queue* q) {
    if (q->top <= -1) { /* Underflow */
        fprintf(stderr, "error: underfow while attempting dequeue\n");
        return ERR_TC_UNDERFLOW;
    }
    test_case result = q->items[q->top];
    q->top--;
    return result;
}

static void write_line(char itype, char* line) {
    if ('n' == itype) {  /* read nodes */
        printf("nodes %d\n", atoi(line));
    }
    if ('e' == itype) {  /* read edges */
        printf("edges %d\n", atoi(line));
    }
};

static void getedges(uint16_t l) {
    char* line;
    size_t len = 0;
    ssize_t nread;
    for (int i = 0; i < l; i++) {
        printf("Getting edge %d\n", i);
        nread = getline(&line, &len, stdin);
        if (nread == -1) {
            fprintf(stderr, "Error reading edges\n");
            return;
        }
        printf("line[0]: %c\n", line[0]);
        uint8_t lhs = line[0];
        uint8_t rhs = line[1];
        printf("lhs: %d\n", lhs);
        printf("rhs: %d\n", rhs);
    }
}

int main(int argc, char* argv[]) {

    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    uint8_t iline = 0; /* input line */
    if (argc != 1) {
            fprintf(stderr, "Usage: %s \n", argv[0]);
            exit(EXIT_FAILURE);
    }

    stream = fopen("/dev/stdin", "r");

    queue *tcases = initQueue(TESTCASES);

    /* read structured input:
     * first line: number of nodes
     * second line: number of edges l
     * then follow l lines
     * */
    while ((nread = getline(&line, &len, stream) != -1)) {
        /* nodes */
        /*fwrite(line, nread, 1, stdout);*/
        switch(iline){
            case 0:
                write_line('n', line);
                uint8_t nodes = (uint8_t)atoi(line);
                printf("nodes: %d\n", nodes);
                iline += 1;
                break;
            case 1:
                write_line('e', line);
                uint16_t edges = atoi(line);
                printf("edges: %d\n", edges);
                iline += 1;
                break;
            case 2:
                /*test_case tc = {nodes, edges};*/
                getedges(edges);
                iline = 0;
                break;
            default:
                printf("iline: %d\n", iline);
                continue;
        }
    }

    freeQueue(tcases);
    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
};
