#ifndef ADGRAPH_H
#define ADGRAPH_H

#include "common.h"

#define BLACK 0
#define WHITE 1
#define UNCOLORED 2


/* Steve Skienna's Implementation */

#define MAXV 255         /* Max num vertices */
#define MAXNODE_INT_SIZE 8
#define MAXEDGE_INT_SIZE 16

typedef struct edgenode edgenode;
struct edgenode {
    uint32_t y;             /* adjacency info */
    uint32_t weight;        /* edge weight, if any */
    edgenode* next;  /* next edge in list */
};

typedef struct {
    edgenode *edges[MAXV+1];   /* adjacency info */
    uint32_t degree[MAXV+1];   /* outdegree of each vertex */
    uint32_t nvertices;        /* number of vertices in graph */
    uint32_t nedges;           /* number of edges in graph */
    Boolean directed;             /* is the graph directed? */
} graph;

void initialize_graph(graph *g, Boolean directed);
void free_graph(graph *g);
void read_graph(graph *g, Boolean directed, uint32_t nodes, uint32_t nedges, char* line, size_t len);
void insert_edge(graph *g, uint32_t x, uint32_t y, Boolean directed);
void print_graph(graph *g);

/* BFS implementation */
void initialize_search(graph* g);
void bfs(graph* g, int start);

/* bicoloring */
void twocolor(graph* g);
void process_edge(uint32_t x, uint32_t y);
uint32_t complement(uint32_t color);

#endif
