#include "inputread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *file_name(char *dir, char *name, int is_page) {
    if (is_page) {
        int size_str = strlen(dir) + strlen(name) + strlen("pages/") + 1;
        char *dir_to_write = (char *)malloc(sizeof(char) * size_str);
        dir_to_write[0] = '\0';
        strcat(dir_to_write, dir);
        strcat(dir_to_write, "pages/");
        strcat(dir_to_write, name);
        return dir_to_write;
    } else {
        int size_str = strlen(dir) + strlen(name) + 1;
        char *dir_to_write = (char *)malloc(sizeof(char) * size_str);
        dir_to_write[0] = '\0';
        strcat(dir_to_write, dir);
        strcat(dir_to_write, name);
        return dir_to_write;
    }
}

int input_read_num_pages(char *dir) {
    char *dir_index;
    int n_pages = 0;

    dir_index = file_name(dir, "index.txt", 0);

    FILE *index_file;

    index_file = fopen(dir_index, "r");

    if (index_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_index);
        exit(2);
    }

    char name[200];
    // faz a leitura no arquivo index para ver a quantidade de paginas
    while (fscanf(index_file, "%s", name) == 1) n_pages++;

    fclose(index_file);
    free(dir_index);

    return n_pages;
}

Page **input_read_page(char *dir, int n_pages) {
    char *dir_index;

    dir_index = file_name(dir, "index.txt", 0);

    FILE *index_file;

    index_file = fopen(dir_index, "r");

    if (index_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_index);
        exit(2);
    }

    char name[200];
    int i = 0;

    // le o arquivo index novamente, adicionando as paginas em um vetor de paginas
    Page **pages = (Page **)malloc(sizeof(Page *) * n_pages);
    for (i = 0; fscanf(index_file, "%s", name) == 1; i++) {
        pages[i] = init_page(name);
    }

    qsort(pages, n_pages, sizeof(Page *), compare_page_name);

    fclose(index_file);
    free(dir_index);

    return pages;
}

int input_read_num_stopwords(char *dir) {
    char *dir_stopwords;
    int n_stopwords = 0;
    dir_stopwords = file_name(dir, "stopwords.txt", 0);

    FILE *stopwords_file;
    stopwords_file = fopen(dir_stopwords, "r");
    if (stopwords_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_stopwords);
        exit(2);
    }

    char name[200];
    // faz a leitura no arquivo stopwords para ver a quantidade de stopwords
    while (fscanf(stopwords_file, "%s", name) == 1) n_stopwords++;

    fclose(stopwords_file);
    free(dir_stopwords);

    return n_stopwords;
}

char **input_read_stopwords(char *dir, int n_stopwords) {
    char name[200];
    char *dir_stopwords;
    char **stop_words = (char **)malloc(sizeof(char *) * n_stopwords);
    int i = 0;
    dir_stopwords = file_name(dir, "stopwords.txt", 0);

    FILE *stopwords_file;
    stopwords_file = fopen(dir_stopwords, "r");
    if (stopwords_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_stopwords);
        exit(2);
    }

    for (i = 0; fscanf(stopwords_file, "%s", name) == 1; i++) {
        stop_words[i] = strdup(name);
    }

    fclose(stopwords_file);
    free(dir_stopwords);

    return stop_words;
}

Graph *input_read_graph(char *dir, int n_pages, Page **pages) {
    char name[200];
    char *dir_graph;
    dir_graph = file_name(dir, "graph.txt", 0);

    FILE *graph_file;
    graph_file = fopen(dir_graph, "r");

    if (graph_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_graph);
        exit(2);
    }

    int size;
    char name_link[300];
    int i = 0;
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

    fclose(graph_file);
    free(dir_graph);

    return graph;
}