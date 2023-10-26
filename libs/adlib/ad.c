#include "ad.h"

/* Queue */

queue* initQueue (int size) {
    queue* q = (queue*) malloc(sizeof(queue) + sizeof(int) * size);
    if (!q) {
        fprintf(stderr, "malloc error: failed for queue\n");
        exit(1);
    }
    q->size = size;
    q->top = -1;
    q->items = (int*) malloc(sizeof(int) * size);
    if (!q->items) {
        printf("malloc error: failed for q->items\n");
        exit(1);
    }
    return q;
}

void freeQueue(queue* q) {
    free(q);
}

void enqueue(queue* q, int item) {
    if (q->top >= q->size) { /* Overflow */
        fprintf(stderr, "error: overflow while attempting enqueue\n");
        return;
    }
    q->top++;
    q->items[q->top] = item;
}

int dequeue(queue* q) {
    if (q->top <= -1) { /* Underflow */
        fprintf(stderr, "error: underfow while attempting dequeue\n");
        return -1;
    }
    int result = q->items[q->top];
    q->top--;
    return result;
}

/* Graph */

void initialize_graph(graph* g, bool directed) {
    int i;                 /* Counter */
    
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (i=1; i<=MAXV; i++) g->degree[i] = 0;
    for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

void read_graph(graph* g, bool directed) {
    int i;                 /* Counter */
    int m;                 /* number of edges */
    int x, y;              /* vertices in edge (x,y) */

    initialize_graph(g, directed);

    scanf("%d %d",&(g->nvertices),&m);

    for (i=1; i<=m; i++) {
        scanf("%d %d",&x,&y);
        insert_edge(g,x,y,directed);
    }
}

void insert_edge(graph* g, int x, int y, bool directed) {
    edgenode* p;           /* temporary pointer */

    p = malloc(sizeof(edgenode)); /* allocate edgenode storage */

    p->weight = 0;
    p->y = y;
    p->next = g->edges[x];

    g->edges[x] = p;       /* insert at head of list */

    g->degree[x]++;

    if (directed == FALSE)
        insert_edge(g,y,x,TRUE);
    else
        g->nedges++;
}

void print_graph(graph* g) {
    int i;               /* Counter */
    edgenode *p;         /* temporary pointer */

    for (i=1; i<=g->nvertices; i++) {
        printf("%d: ", i);
        p = g->edges[i];
        while (p != NULL) {
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}


