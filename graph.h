#ifndef GRAPH_H
#define GRAPH_H

#include "page.h"

typedef struct graph Graph;

Graph* init_graph(int n_nodes, Page** pages);

void print_graph(Graph* graph);

void destroy_graph(Graph* graph);

int get_n_nodes(Graph* graph);

Page* get_page_graph(Graph* graph, int pos);

void calc_PR(Graph* graph, Page** pages);

#endif  //GRAPH_H