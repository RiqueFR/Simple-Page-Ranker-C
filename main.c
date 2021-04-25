#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "page.h"

/**
 * Concatena a string dir e a string name para dir_to_write
 * @param dir_to_write    string de resultado
 * @param dir             string do diretorio
 * @param name            string do nome do arquivo
 * 
 * @return string dup das strings dir e name
 */
static char *file_name(char *dir, char *name);

static int compare_page(const void *a, const void *b);

static Page *find_page(Page **pages, int size, char *name_page);

int main(int argc, char *argv[]) {
    //Verifica se a quantidade minima de parametros foram passados
    if (argc < 2) {
        printf("Poucos argumentos fornecidos!\n");
        return 1;
    }
    char *dir = argv[1];
    //concatenate files names to input's diretory
    char *dir_index, *dir_stopwords, *dir_graph;
    dir_index = file_name(dir, "index.txt");
    dir_stopwords = file_name(dir, "stopwords.txt");
    dir_graph = file_name(dir, "graph.txt");

    //printf("%s %s %s\n", dir_index, dir_graph, dir_stopwords);
    //try to open the files
    FILE *index_file,
        *stopwords_file, *graph_file;
    index_file = fopen(dir_index, "r");
    if (index_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_index);
        return 2;
    }
    stopwords_file = fopen(dir_stopwords, "r");
    if (stopwords_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_stopwords);
        return 2;
    }
    graph_file = fopen(dir_graph, "r");
    if (graph_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_graph);
        return 2;
    }
    char name[200];
    int i = 0;
    int n_pages = 0;

    // faz a leitura no arquivo index para ver a quantidade de paginas
    while (fscanf(index_file, "%s", name) == 1) n_pages++;

    // le o arquivo index novamente, adicionando as paginas em um vetor de paginas
    rewind(index_file);
    Page **pages = (Page **)malloc(sizeof(Page *) * n_pages);
    for (i = 0; fscanf(index_file, "%s", name) == 1; i++) {
        pages[i] = init_page(name);
    }

    qsort(pages, n_pages, sizeof(Page *), compare_page);

    int size;
    char name_link[300];
    i = 0;
    while (fscanf(graph_file, "%s %d", name, &size) == 2) {
        Page *page = find_page(pages, n_pages, name);
        set_n_links(page, size);
        for (int i = 0; i < size; i++) {
            fscanf(graph_file, "%s", name_link);
            Page *link = find_page(pages, n_pages, name_link);
            insert_page_link(page, link);
        }
    }

    Graph *graph = init_graph(n_pages, pages);
    print_graph(graph);

    //libera a memoria
    destroy_graph(graph);
    for (int i = 0; i < n_pages; i++)
        destroy_page(pages[i]);
    free(pages);

    free(dir_index);
    free(dir_stopwords);
    free(dir_graph);

    fclose(index_file);
    fclose(stopwords_file);
    fclose(graph_file);

    return 0;
}

static char *file_name(char *dir, char *name) {
    int size_str = strlen(dir) + strlen(name) + 1;
    char *dir_to_write = (char *)malloc(sizeof(char) * size_str);
    dir_to_write[0] = '\0';
    strcat(dir_to_write, dir);
    strcat(dir_to_write, name);
    return dir_to_write;
}

static int compare_page(const void *a, const void *b) {
    /*
    * Segundo a ordem alfabética retorna um valor:
    * > 0 -> primeiro parametro maior que o segundo
    * = 0 -> parametros iguais
    * < 0 -> segundo parametro maior que o primeiro
    */
    Page *a1 = *(Page **)a;
    Page *a2 = *(Page **)b;

    return strcmp(get_name_page(a1), get_name_page(a2));
}

//binary search
static Page *find_page(Page **pages, int size, char *name_page) {
    int hi = size, lo = 0;
    int cmp;

    do {
        cmp = strcmp(name_page, get_name_page(pages[(hi + lo) / 2]));

        if (cmp == 0) break;

        if (strcmp(name_page, get_name_page(pages[(hi + lo) / 2])) > 0)
            lo = (hi + lo) / 2;
        else
            hi = (hi + lo) / 2;
    } while (cmp != 0);

    return pages[(hi + lo) / 2];
}