#ifndef AD_H
#define AD_H

#include <stdbool.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

/* Possibly free up TRUE and FALSE keywords if they have been defined by system */
#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

typedef struct {
    int size;
    int top;
    int* tail;
    int* items;
} queue;

queue* initQueue (int size);
void freeQueue(queue* q);
void enqueue (queue* q, int item);
int dequeue (queue* q);

/* ########################### Graph ########################### */
/* See [Skiena 2012] for reference */

#define MAXV 1000               /* maximum number of vertices */

typedef struct edgenode edgenode;
struct edgenode {
    int y;                      /* adjacency info */
    int weight;                 /* edge weight, if any */
    edgenode* next;             /* next edge in list */
};

typedef struct graph graph;
struct graph {
    edgenode* edges[MAXV+1];    /* adjacency info */
    int degree[MAXV+1];         /* outedges of vertices in graph */
    int nvertices;              /* number of vertices in graph */
    int nedges;                 /* number of edges in graph */
    bool directed;              /* is the graph directed? */
};

void initialize_graph(graph* g, bool directed);
void read_graph(graph* g, bool directed);
void insert_edge(graph* g, int x, int y, bool directed);
void print_graph(graph* g);

#endif
