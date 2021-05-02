#ifndef WORDLIST_H
#define WORDLIST_H

typedef struct wordlist Wordlist;

/**
 * Inicializa uma lista de Wordlist nao vazia.
 * 
 * @param {int dest} No destino da aresta direcionada.
 * @param {double weight} Peso da aresta direcionada.
 *
 * @pre valores de dest e weight sao conhecidos.
 * @post lista de Wordlist eh inicializada e nao vazia.
 * 
 * @return lista de Wordlist inicializada com um item
 */
Wordlist* init_wordlist();

/**
 * Retorna o valor de peso do Wordlist.
 * 
 * @param {Wordlist* wordlist} lista de arestas.
 * 
 * @pre lista de Wordlist inicializada com pelo menos um item inicializado.
 * @post nenhuma.
 * 
 * @return peso do primeiro item da lista de Wordlist.
 */
char* get_word(Wordlist* wordlist);

/**
 * Retorna o segundo item da lista de Wordlist.
 * 
 * @param {Wordlist* wordlist} lista de Wordlist.
 * 
 * @pre lista de Wordlist inicializada com pelo menos um item inicializado.
 * @post nenhuma.
 * 
 * @return segundo item da lista de Wordlist.
 */
Wordlist* get_next(Wordlist* wordlist);

/**
 * Configura a proxima aresta da estrutura Wordlist.
 * 
 * @param {Wordlist* wordlist} lista de Wordlist que o proximo item sera modificado.
 * @param {Wordlist* next} lista de Wordlist que vai ser adicionada a Wordlist.
 * 
 * @pre listas de Wordlist existem e possuem pelo menos um item inicializado.
 * @post o proximo item da lista aponta para lista de Wordlist next.
 */
void insert_wordlist(Wordlist* wordlist, char* word);

/**
 * Libera memoria alocada da lista de de Wordlist
 * 
 * @param {Wordlist* wordlist} lista de Wordlist que memoria sera liberada
 * 
 * @pre lista de Wordlist inicializada
 * @post memoria alocada por lista de Wordlist liberada
 */
void destroy_wordlist(Wordlist* wordlist);

#endif