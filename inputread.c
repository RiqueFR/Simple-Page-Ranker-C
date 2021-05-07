#include "inputread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_buffer_line_breaker(char *buffer, int size);

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
    size_t buffer_size = 100;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));

    if (buffer == NULL) {
        printf("Falha ao alocar!\n");
        exit(2);
    }

    dir_index = file_name(dir, "index.txt", 0);

    FILE *index_file;

    index_file = fopen(dir_index, "r");
    if (index_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_index);
        exit(2);
    }

    // faz a leitura no arquivo index para ver a quantidade de paginas
    for (int line_size = getline(&buffer, &buffer_size, index_file);
         line_size >= 0; line_size = getline(&buffer, &buffer_size, index_file)) {
        n_pages++;
    }

    fclose(index_file);
    free(dir_index);
    free(buffer);

    return n_pages;
}

Page **input_read_page(char *dir, int n_pages) {
    char *dir_index;
    char *buffer;
    size_t buffer_size = 100;
    buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        printf("Erro ao alocar memoria do buffer!\n");
        exit(2);
    }

    dir_index = file_name(dir, "index.txt", 0);

    FILE *index_file;

    index_file = fopen(dir_index, "r");
    if (index_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_index);
        exit(2);
    }
    int i = 0;
    // le o arquivo index novamente, adicionando as paginas em um vetor de paginas
    Page **pages = (Page **)malloc(sizeof(Page *) * n_pages);
    if (pages == NULL) {
        printf("Erro ao alocar memoria da lista de paginas!\n");
        exit(2);
    }
    for (int line_size = getline(&buffer, &buffer_size, index_file);
         line_size >= 0; line_size = getline(&buffer, &buffer_size, index_file), i++) {
        remove_buffer_line_breaker(buffer, line_size);
        pages[i] = init_page(buffer);
    }

    qsort(pages, n_pages, sizeof(Page *), compare_page_name);

    fclose(index_file);
    free(buffer);
    free(dir_index);

    return pages;
}

int input_read_num_stopwords(char *dir) {
    char *dir_stopwords;
    int n_stopwords = 0;
    size_t buffer_size = 100;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));

    dir_stopwords = file_name(dir, "stopwords.txt", 0);

    FILE *stopwords_file;
    stopwords_file = fopen(dir_stopwords, "r");
    if (stopwords_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_stopwords);
        exit(2);
    }

    // faz a leitura no arquivo stopwords para ver a quantidade de stopwords
    for (int line_size = getline(&buffer, &buffer_size, stopwords_file);
         line_size >= 0; line_size = getline(&buffer, &buffer_size, stopwords_file)) {
        n_stopwords++;
    }

    fclose(stopwords_file);
    free(dir_stopwords);
    free(buffer);

    return n_stopwords;
}

char **input_read_stopwords(char *dir, int n_stopwords) {
    char *dir_stopwords;
    char **stop_words = (char **)malloc(sizeof(char *) * n_stopwords);
    int i = 0;
    char *buffer;
    size_t buffer_size = 100;
    buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        printf("Erro ao alocar memoria do buffer!\n");
        exit(2);
    }

    dir_stopwords = file_name(dir, "stopwords.txt", 0);

    FILE *stopwords_file;
    stopwords_file = fopen(dir_stopwords, "r");
    if (stopwords_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_stopwords);
        exit(2);
    }

    for (int line_size = getline(&buffer, &buffer_size, stopwords_file);
         line_size >= 0; line_size = getline(&buffer, &buffer_size, stopwords_file), i++) {
        remove_buffer_line_breaker(buffer, line_size);
        stop_words[i] = strdup(buffer);
    }

    fclose(stopwords_file);
    free(dir_stopwords);
    free(buffer);

    return stop_words;
}

Graph *input_read_graph(char *dir, int n_pages, Page **pages) {
    char *dir_graph;
    dir_graph = file_name(dir, "graph.txt", 0);

    FILE *graph_file;
    graph_file = fopen(dir_graph, "r");

    if (graph_file == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_graph);
        exit(2);
    }

    int size;
    char *name_page;
    char *name_link;
    int n_links;

    char *buffer;
    size_t buffer_size = 100;
    buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        printf("Erro ao alocar memoria do buffer!\n");
        exit(2);
    }

    for (int line_size = getline(&buffer, &buffer_size, graph_file);
         line_size >= 0; line_size = getline(&buffer, &buffer_size, graph_file)) {
        remove_buffer_line_breaker(buffer, line_size);

        //Pega o nome da coordenada
        name_page = strtok(buffer, " ");
        Page *page = find_page(pages, 0, n_pages - 1, name_page);

        //Pega as coodernadas
        n_links = atoi(strtok(NULL, " "));
        set_n_links(page, n_links);
        name_link = strtok(NULL, " ");
        while (name_link != NULL) {
            Page *link = find_page(pages, 0, n_pages - 1, name_link);
            insert_page_link(page, link);
            name_link = strtok(NULL, " ");
        }
    }

    Graph *graph = init_graph(n_pages, pages);

    fclose(graph_file);
    free(dir_graph);
    free(buffer);

    return graph;
}

void printf_pages(Page **pages, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        Page *now = pages[i];
        if (i != 0 && now)
            printf(" ");
        if (now) {
            count++;
            printf("%s", get_name_page(now));
        } else
            break;
    }
    if (count > 0) printf("\n");
}

void printf_prs(Page **pages, int size) {
    for (int i = 0; i < size; i++) {
        Page *now = pages[i];
        if (i != 0 && now)
            printf(" ");
        if (now)
            printf("%.8lf", get_page_rank(now));
        else
            break;
    }
    printf("\n");
}

static void remove_buffer_line_breaker(char *buffer, int size) {
    buffer[size - 1] = '\0';
    if (buffer[size - 2] == '\r')
        buffer[size - 2] = '\0';
}