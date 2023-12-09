#include "ad_graph.h"
#include "ad_queue.h"

void initialize_graph(graph *g, Boolean directed) {
    int i;

    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (i=1; i<=MAXV; i++) g->degree[i] = 0;
    for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
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

void read_graph(graph *g, Boolean directed, uint32_t nodes, uint32_t nedges, char* line, size_t len) {
    uint32_t x, y;      /* vertices in edge (x, y) */

    initialize_graph(g, directed);

    g->nvertices = nodes;

    uint32_t i;
    const uint8_t e = 2; /* N1->N2 (edge between two nodes per line) */
    for (i = 0; i < nedges; i++) {
        line = ad_getline(len);
        uint32_t nums[e];
        ad_copynums(nums, line);
        printf("%d->%d\n", nums[0], nums[1]);
        x = nums[0];
        y = nums[1];
        insert_edge(g,x,y,directed);
    }
}

void insert_edge(graph *g, uint32_t x, uint32_t y, Boolean directed) {
    edgenode *p;                               /* temporary pointer */

    p = (edgenode*)malloc(sizeof(edgenode));   /* allocate edgenode */

    if (!p) {
        fprintf(stderr, "malloc error: edgenode\n");
        exit(1);
    }

    p->weight = 0;
    p->y = y;
    p->next = g->edges[x];

    g->edges[x] = p;                /* insert the head of the list */

    g->degree[x] ++;

    if (directed == FALSE)
        insert_edge(g,y,x,TRUE);
    else
        g->nedges++;
}

void print_graph(graph *g) {
    uint32_t i;
    edgenode *p;

    for (i = 0; i < g->nvertices; i++) {
        printf("%d: ", i);
        p = g->edges[i];
        while(p != NULL) {
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}

/* BFS implementation */
Boolean processed[MAXV+1];
Boolean discovered[MAXV+1];   /* found */
uint32_t parent[MAXV+1];      /* discovery relation */

void initialize_search(graph* g) {
    uint32_t i;
    for (i = 0; i < g->nvertices; i++) {
        processed[i] = discovered[i] = FALSE;
        parent[i] = -1;
    }
}

static void process_vertex_early(uint32_t v) {
    printf("processed vertex %d\n", v);
}

static void process_edge(uint32_t x, uint32_t y) {
    printf("processed edge (%d,%d)\n",x,y);
}


void bfs(graph* g, int start) {
    queue q;              /* queue of nodes to visit */
    uint32_t v;           /* current vertex (node) */
    uint32_t y;           /* successor to visit */
    edgenode *p;          /* temporary pointer */

    init_queue(&q, g->nvertices);
    enqueue(&q,start);
    discovered[start] = TRUE;

    while (empty_queue(&q) == FALSE) {
        v = dequeue(&q);
        process_vertex_early(v);
        processed[v] = TRUE;
        p = g->edges[v];
        while (p != NULL) {
            y = p->y;
            if ((processed[y] == FALSE) || g->directed)
                process_edge(v,y);
            if (discovered[y] == FALSE) {
                enqueue(&q,y);
                discovered[y] = TRUE;
                parent[y] = TRUE;
                parent[y] = v;
            }
            p = p->next;
        }
    }
}


