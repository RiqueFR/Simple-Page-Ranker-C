#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "inputread.h"
#include "page.h"

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

    calc_PR(graph, pages);
    Page **pages_verified = verificar_consultas(pages, "ruim abacate", n_pages, dir);
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