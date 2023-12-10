#include "bicoloring.h"
#include "ad_graph.h"
#define MAXLINE 255
#define TESTCASES 512

int main(int argc, char* argv[]) {

    size_t len = 0;
    if (argc != 1) {
            fprintf(stderr, "Usage: %s \n", argv[0]);
            exit(EXIT_FAILURE);
    }

    /* read structured input:
     * first line: number of nodes
     * second line: number of edges l
     * then follow l lines
     * */
    uint16_t nodes;
    uint16_t edges;

    Boolean finished = FALSE;

    char* buf = NULL;
    len = MAXNODE_INT_SIZE;
    buf = (char*)malloc(sizeof(char) * len);

    graph* g = NULL;
    g = (graph*)malloc(sizeof(graph));
    if (!g) {
            fprintf(stderr, "malloc error: graph\n");
            exit(EXIT_FAILURE);
    }

    while (!finished) {
        /* get nodes */
        ad_getline_min(buf, len);
        nodes = (uint32_t)atoi(buf);
        if (0 == nodes) {  /* last line, means we're done */
            finished = TRUE;
            break;
        }
        buf[0] = '\0'; /* reset buffer */

        /* get edges */
        ad_getline_min(buf, len);
        edges = (uint32_t)atoi(buf);

        read_graph(g, FALSE, nodes, edges, buf, len);
        twocolor(g);
    }
    free_graph(g);
    free(buf);
    exit(EXIT_SUCCESS);
};
