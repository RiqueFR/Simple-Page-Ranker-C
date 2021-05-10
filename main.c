#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "inputread.h"
#include "page.h"
#include "rbt.h"

int compare_word(const void *a, const void *b);

static int binary_search(char **stopwords, int lo, int hi, char *word) {
    if (hi >= lo) {
        int mid = lo + (hi - lo) / 2;

        // Se a palavra esta no meio da stopwords
        //printf("stopword: %s -> %d / palavra: %s\n", stopwords[mid], mid, word);
        if (strcasecmp(stopwords[mid], word) == 0)
            return mid;

        // Se o elemento eh menor que o meio, so pode estar na esquerda
        if (strcasecmp(stopwords[mid], word) > 0)
            return binary_search(stopwords, lo, mid - 1, word);

        // caso contrario, so pode estar na esquerda
        return binary_search(stopwords, mid + 1, hi, word);
    }

    // Se a palavra nao esta presente, retorna -1
    return -1;
}

int main(int argc, char *argv[]) {
    //Verifica se a quantidade minima de parametros foram passados
    if (argc < 2) {
        printf("Poucos argumentos fornecidos!\n");
        return 1;
    }
    char *dir = argv[1];

    //leituras/inputs
    int n_pages = input_read_num_pages(dir);
    Page **pages = input_read_page(dir, n_pages);
    Graph *graph = input_read_graph(dir, n_pages, pages);
    int n_stop_words = input_read_num_stopwords(dir);
    char **stop_words = input_read_stopwords(dir, n_stop_words);

    //ordenar paginas em ordem alfabetica
    qsort(stop_words, n_stop_words, sizeof(char *), compare_word);

    size_t buffer_page_size = 100;
    char *buffer_page = (char *)malloc(sizeof(char) * buffer_page_size);
    char *word;
    RBT **rbts = (RBT **)malloc(sizeof(RBT *) * n_pages);

    for (int i = 0; i < n_pages; i++) {
        char *directory = file_name(dir, get_name_page(pages[i]), 1);
        FILE *arquivo = fopen(directory, "r");
        free(directory);

        rbts[i] = NULL;

        if (arquivo == NULL) {
            printf("Arquivo não encontrado!\n");
            exit(2);
        }

        for (int line_size = getline(&buffer_page, &buffer_page_size, arquivo);
             arquivo && line_size >= 0; line_size = getline(&buffer_page, &buffer_page_size, arquivo)) {
            if (buffer_page[line_size - 1] == '\n')
                buffer_page[line_size - 1] = '\0';

            word = strtok(buffer_page, " ");

            while (word != NULL) {
                if (binary_search(stop_words, 0, n_stop_words - 1, word) == -1) {
                    rbts[i] = RBT_insert(rbts[i], word);
                }
                word = strtok(NULL, " ");
            }
        }
        fclose(arquivo);
    }

    free(buffer_page);

    //calcula PR das paginas
    calc_PR(graph, pages);

    char *buffer;
    size_t bufsize = 100;
    int characters;
    buffer = (char *)malloc(bufsize * sizeof(char));
    Page *pages_verified[n_pages];

    if (buffer == NULL) {
        perror("Unable to allocate buffer");
        exit(1);
    }

    //para cada linha inserida, verificamos se a consulta esta nos arquivos
    while (!feof(stdin)) {
        characters = getline(&buffer, &bufsize, stdin);
        if (characters > 1) {
            if (buffer[characters - 1] == '\n')
                buffer[characters - 1] = '\0';

            //verifica se alguma pagina tem todas palavras da consulta
            verify_query(pages_verified, pages, buffer, n_pages, rbts);

            //ordena em quesito de PR as paginas em que foram encontradas as palavras
            qsort(pages_verified, n_pages, sizeof(Page *), compare_page_rank);

            //imprime resultados
            printf_pages(pages_verified, n_pages);
            printf_prs(pages_verified, n_pages);
        }
    }

    //libera a memoria
    for (int i = 0; i < n_stop_words; i++)
        free(stop_words[i]);
    free(stop_words);

    destroy_graph(graph);
    for (int i = 0; i < n_pages; i++)
        destroy_page(pages[i]);
    free(pages);

    for (int i = 0; i < n_pages; i++) {
        RBT_delete(rbts[i]);
    }
    free(rbts);

    free(buffer);

    return 0;
}

int compare_word(const void *a, const void *b) {
    /*
    * Segundo a ordem alfabética retorna um valor:
    * > 0 -> primeiro parametro maior que o segundo
    * = 0 -> parametros iguais
    * < 0 -> segundo parametro maior que o primeiro
    */
    char *a1 = *(char **)a;
    char *a2 = *(char **)b;

    return strcasecmp(a1, a2);
}
