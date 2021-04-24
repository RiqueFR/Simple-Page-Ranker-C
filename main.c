#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Concatena a string dir e a string name para dir_to_write
 * @param dir_to_write    string de resultado
 * @param dir             string do diretorio
 * @param name            string do nome do arquivo
 * 
 * @return string dup das strings dir e name
 */
static void file_name(char *dir_to_write, char *dir, char *name) {
    dir_to_write = strdup(dir);
    strcat(dir_to_write, name);
}

int main(int argc, char *argv[]) {
    //Verifica se a quantidade minima de parametros foram passados
    if (argc < 2) {
        printf("Poucos argumentos fornecidos!\n");
        return 1;
    }
    char *dir = argv[1];

    //concatenate files names to input's diretory
    char *dir_index, *dir_stopwords, *dir_graph;
    file_name(dir_index, dir, "index.txt");
    file_name(dir_stopwords, dir, "stopwords.txt");
    file_name(dir_graph, dir, "graph.txt");

    //try to open the files
    FILE *index, *stopwords, *graph;
    index = fopen(dir_index, "r");
    if (index == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_index);
        return 2;
    }
    stopwords = fopen(dir_stopwords, "r");
    if (index == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_stopwords);
        return 2;
    }
    graph = fopen(dir_graph, "r");
    if (index == NULL) {
        printf("Falha ao abrir o arquivo: %s\n", dir_graph);
        return 2;
    }

    // int size;
    // char arq[200];
    // while (fscanf(graph, "%s %d", arq, &size) == 2) {
    //     for (int i = 0;)
    // }

    //libera a memoria
    free(dir_index);
    free(dir_stopwords);
    free(dir_graph);

    fclose(index);
    fclose(stopwords);
    fclose(graph);

    return 0;
}