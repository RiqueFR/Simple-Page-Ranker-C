#ifndef INPUTREAD_H_
#define INPUTREAD_H_

#include "graph.h"
#include "page.h"

char *file_name(char *dir, char *name, int is_page);

int input_read_num_pages(char *dir);

Page **input_read_page(char *dir, int n_pages);

int input_read_num_stopwords(char *dir);

char **input_read_stopwords(char *dir, int n_stopwords);

Graph *input_read_graph(char *dir, int n_pages, Page **pages);

#endif