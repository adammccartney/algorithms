
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include "bicoloring.h"
#include  "adio.h"

#define MAXLINE 255
#define TESTCASES 512
#define MAXNODE_INT_SIZE 8
#define MAXEDGE_INT_SIZE 16

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

static void write_line(char itype, uint16_t v) {
    if ('n' == itype) {  /* read nodes */
        printf("nodes %d\n", v);
    }
    if ('e' == itype) {  /* read edges */
        printf("edges %d\n", v);
    }
};

static void getedges(uint16_t e, uint32_t l_count) {
    printf("Processing line: %d\n", l_count);
    printf("got %d edges\n", e);
}

static void ad_copynums(uint32_t *nums, char* line) {
    /* get N contiguos char bytes from a line buffer and convert them to numbers
     * store them into the nums array. Each number is delimited by a whitespace. */
    char nbuf[MAXNODE_INT_SIZE] = {'\0'};
    char* rp = line;
    size_t idx = 0; /* index for numbuffer */
    size_t n_idx = 0;  /* index for storing numbers */
    for (; *rp != '\0'; rp++) {
        if ((*rp >= '0') && (*rp <= '9')) {
            nbuf[idx] = *rp;
        }
        idx++;
        char* peek = rp+1;
        if (' ' == *rp || '\0' == *peek) {  /* found the end of char block containing number */
            nums[n_idx] = (uint32_t)atoi(nbuf); /* convert the numbers we've read */
            n_idx++;  /* increment index of chars copied */
            nbuf[0] = '\0';  /* reset the char buffer */
            idx = 0; /* reset numbuf index */
            continue;
        }
    }
}

int main(int argc, char* argv[]) {

    char *line = NULL;
    size_t len = 0;
    if (argc != 1) {
            fprintf(stderr, "Usage: %s \n", argv[0]);
            exit(EXIT_FAILURE);
    }

    queue *tcases = initQueue(TESTCASES);

    /* read structured input:
     * first line: number of nodes
     * second line: number of edges l
     * then follow l lines
     * */
    uint16_t nodes;
    uint16_t edges;

    Boolean finished = FALSE;

    while (!finished) {
        /* get nodes */
        len = MAXNODE_INT_SIZE;
        line = ad_getline(len);
        nodes = (uint32_t)atoi(line);
        if (0 == nodes) {  /* last line, means we're done */
            finished = TRUE;
            break;
        }
        printf("nodes: %d\n", nodes);

        /* get edges */
        len = MAXEDGE_INT_SIZE;
        line = ad_getline(len);
        edges = (uint32_t)atoi(line);
        printf("edges: %d\n", edges);

        int i;
        const uint8_t e = 2; /* N1->N2 (edge between two nodes per line) */
        for (i = 0; i < edges; i++) {
            line = ad_getline(len);
            uint32_t nums[e];
            ad_copynums(nums, line);
            printf("%d->%d\n", nums[0], nums[1]);
        }
    }
    freeQueue(tcases);
    free(line);
    exit(EXIT_SUCCESS);
};
