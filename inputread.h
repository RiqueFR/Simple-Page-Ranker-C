#ifndef INPUTREAD_H_
#define INPUTREAD_H_

#include "graph.h"
#include "page.h"
#include "rbt.h"

/*Retorna o caminho do diretorio do arquivo
 * inputs: duas strings e um inteiro
 * output: ponteiro para char
 * pre-condicao: as duas strings e o inteiro existem
 * pos-condicao: ponteiro para char de retorno existe
 */
char *file_name(char *dir, char *name, int is_page);

/*Retorna o numero de paginas que serao lidas
 * inputs: ponteiro para char
 * output: um inteiro
 * pre-condicao: ponteiro para char existe
 * pos-condicao: ponteiro para char nao eh modificado
 */
int input_read_num_pages(char *dir);

/*Retorna um vetor de pages
 * inputs: um ponteiro para char e um inteiro
 * output: um vetor de paginas
 * pre-condicao: ponteiro para char com o caminho do arquivo de leitura existe
 * pos-condicao: vetor de pages de retorno existe
 */
Page **input_read_page(char *dir, int n_pages);

/*Retorna o numero de stopwords que serao lidas
 * inputs: ponteiro para char
 * output: um inteiro
 * pre-condicao: ponteiro para char existe
 * pos-condicao: ponteiro para char nao eh modificado
 */
int input_read_num_stopwords(char *dir);

/*Retorna um vetor de stopwords (strings)
 * inputs: um ponteiro para char e um inteiro
 * output: um vetor de strings
 * pre-condicao: ponteiro para char com o caminho do arquivo de leitura existe
 * pos-condicao: vetor de strings de retorno existe
 */
char **input_read_stopwords(char *dir, int n_stopwords);

/*Retorna um grafo
 * inputs: uma string, um inteiro e um vetor de pages
 * output: um grafo
 * pre-condicao: a string, o inteiro (numero de pages) e o vetor de pages existem
 * pos-condicao: ponteiro para o grafo de retorno existe
 */
Graph *input_read_graph(char *dir, int n_pages, Page **pages);

/*Retorna um vetor de RBTs
 * inputs: uma string, um vetor de pages, um inteiro, um vetor de vetor de char e um inteiro
 * output: um vetor de de todas as rbts para cada arquivo
 * pre-condicao: o dir deve ser um diretório válido, vetor de páginas devidamente inicializado,
 *  número de paginas condizente com o vetor de paginas, stopwords devidamente inicializadas e
 *  número de stopwords condizentes com o vetor de stopwords
 * pos-condicao: ponteiro para o vetor de RBTs de retorno existe
 */
RBT **input_read_files(char *dir, Page **pages, int n_pages, char **stopwords, int n_stopwords);

/*Imprime os nomes de um vetor de pages
 * inputs: um vetor de pages e o tamanho
 * output: nenhum
 * pre-condicao: vetor de pages existe
 * pos-condicao: vetor de pages não é modificado
 */
void printf_pages(Page **pages, int size);

/*Imprime os prs de um vetor de pages
 * inputs: um vetor de pages e o tamanho
 * output: nenhum
 * pre-condicao: vetor de pages existe
 * pos-condicao: vetor de pages não é modificado
 */
void printf_prs(Page **pages, int size);

#endif