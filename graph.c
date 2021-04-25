#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

struct graph {
    Page** pages;
    int n_nodes;
    int n_edges;
};

Graph* init_graph(int n_nodes, Page** pages) {
    Graph* new_graph = (Graph*)malloc(sizeof(Graph));
    if (new_graph == NULL) {
        printf("Erro de alocacao do graph!\n");
        exit(3);
    }

    new_graph->n_nodes = n_nodes;
    new_graph->pages = pages;

    return new_graph;
}

void print_graph(Graph* graph) {
    for (int i = 0; i < graph->n_nodes; i++) {
        print_page(graph->pages[i]);
    }
}

void destroy_graph(Graph* graph) {
    free(graph);
}