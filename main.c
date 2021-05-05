#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "inputread.h"
#include "page.h"

int compare_word(const void *a, const void *b);

int main(int argc, char *argv[]) {
    //Verifica se a quantidade minima de parametros foram passados
    if (argc < 2) {
        printf("Poucos argumentos fornecidos!\n");
        return 1;
    }
    char *dir = argv[1];

    int n_pages = input_read_num_pages(dir);
    Page **pages = input_read_page(dir, n_pages);
    Graph *graph = input_read_graph(dir, n_pages, pages);
    int n_stop_words = input_read_num_stopwords(dir);
    char **stop_words = input_read_stopwords(dir, n_stop_words);

    qsort(stop_words, n_stop_words, sizeof(char *), compare_word);

    calc_PR(graph, pages);

    Page **pages_verified = verificar_consultas(pages, "que e de abacate o Maca abacate uma eu", n_pages, stop_words, n_stop_words, dir);

    qsort(pages_verified, n_pages, sizeof(Page *), compare_page_rank);

    int count = 0;
    for (int i = 0; i < n_pages; i++) {
        Page *now = pages_verified[i];
        if (i != 0 && now)
            printf(" ");
        if (now) {
            count++;
            printf("%s", get_name_page(now));
        } else
            break;
    }
    if (count > 0) printf("\n");
    for (int i = 0; i < n_pages; i++) {
        Page *now = pages_verified[i];
        if (i != 0 && now)
            printf(" ");
        if (now)
            printf("%.8lf", get_page_rank(now));
        else
            break;
    }
    printf("\n");

    //libera a memoria
    for (int i = 0; i < n_stop_words; i++)
        free(stop_words[i]);
    free(stop_words);

    destroy_graph(graph);
    for (int i = 0; i < n_pages; i++)
        destroy_page(pages[i]);
    free(pages);
    free(pages_verified);

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
