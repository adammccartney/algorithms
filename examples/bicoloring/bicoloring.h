#ifndef BICOLORING_H
#define BICOLORING_H
#include "common.h"
#include "ad_graph.h"

#define BLACK 0
#define WHITE 1
#define UNCOLORED 2

void twocolor(graph* g);
void process_edge(uint32_t x, uint32_t y);
uint32_t complement(uint32_t color);

#endif
