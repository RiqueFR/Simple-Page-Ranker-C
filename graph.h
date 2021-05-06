#ifndef GRAPH_H
#define GRAPH_H

#include "page.h"

typedef struct graph Graph;

/*Inicializa um grafo
 * inputs: quantidade de vertices e um vetor de pages
 * output: ponteiro para a grafo inicializado
 * pre-condicao: inteiro e pages existem
 * pos-condicao: grafo de retorno existe
 */
Graph* init_graph(int n_nodes, Page** pages);

/*Imprime um grafo
 * inputs: um grafo
 * output: nenhum
 * pre-condicao: grafo existe
 * pos-condicao: grafo não é modificado
 */
void print_graph(Graph* graph);

/*Libera memória alocada para o grafo
 * inputs: grafo
 * output: nenhum
 * pre-condicao: grafo existe
 * pos-condicao: toda a memória alocada para o grafo foi liberada
 */
void destroy_graph(Graph* graph);

/*Retorna o numero de nos do grafo
 * inputs: grafo
 * output: um inteiro
 * pre-condicao: grafo existe
 * pos-condicao: grafo não é modificado
 */
int get_n_nodes(Graph* graph);

/*Retorna uma pagina do grafo
 * inputs: grafo e um inteiro
 * output: uma pagina
 * pre-condicao: grafo e inteiro existem
 * pos-condicao: grafo não é modificado
 */
Page* get_page_graph(Graph* graph, int pos);

/*Calcula o PR
 * inputs: um grafo e um vetor de paginas
 * output: nenhum
 * pre-condicao: grafo e vetor de paginas existem
 * pos-condicao: grafo e paginas não sao modificados
 */
void calc_PR(Graph* graph, Page** pages);

#endif  //GRAPH_H