#ifndef ADGRAPH_H
#define ADGRAPH_H

#include "common.h"

/* Steve Skienna's Implementation */

#define MAXV 1000         /* Max num vertices */
#define MAXNODE_INT_SIZE 8
#define MAXEDGE_INT_SIZE 16

typedef struct edgenode edgenode;
struct edgenode {
    uint32_t y;             /* adjacency info */
    uint32_t weight;        /* edge weight, if any */
    struct edgenode* next;  /* next edge in list */
};

typedef struct {
    edgenode *edges[MAXV+1];   /* adjacency info */
    uint32_t degree[MAXV+1];   /* outdegree of each vertex */
    uint32_t nvertices;        /* number of vertices in graph */
    uint32_t nedges;           /* number of edges in graph */
    Boolean directed;             /* is the graph directed? */
} graph;

void initialize_graph(graph *g, Boolean directed);
void read_graph(graph *g, Boolean directed, uint32_t nodes, uint32_t nedges, char* line, size_t len);
void insert_edge(graph *g, uint32_t x, uint32_t y, Boolean directed);
void print_graph(graph *g);

/* BFS implementation */
void initialize_search(graph* g);
void bfs(graph* g, int start);


#endif
