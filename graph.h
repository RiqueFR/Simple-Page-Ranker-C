#ifndef GRAPH_H
#define GRAPH_H

#include "page.h"

typedef struct graph Graph;

Graph* init_graph(int n_nodes, Page** pages);

void print_graph(Graph* graph);

void destroy_graph(Graph* graph);

#endif  //GRAPH_H