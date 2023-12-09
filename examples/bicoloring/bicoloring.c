#include "bicoloring.h"
#define MAXLINE 255
#define TESTCASES 512

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

        graph* g = NULL;
        g = (graph*)malloc(sizeof(graph));
        if (!g) {
            fprintf(stderr, "malloc error: graph\n");
            exit(EXIT_FAILURE);
        }
        read_graph(g, FALSE, nodes, edges, line, len);
        print_graph(g);

    }
    free(line);
    exit(EXIT_SUCCESS);
};
