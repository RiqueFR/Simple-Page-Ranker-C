#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph Graph;

Graph* init_graph(int n_nodes, Pagina** pages);

void destroy_graph(Graph* graph);

#endif  //GRAPH_H