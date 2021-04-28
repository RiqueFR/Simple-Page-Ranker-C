#ifndef PAGES_H
#define PAGES_H

#include "trie.h"

typedef struct page Page;

Page* init_page(char* nome);

char* get_name_page(Page* page);

double get_page_rank(Page* page);

void set_n_links(Page* page, int n_links);

int get_n_links(Page* page);

void set_page_rank(Page* page, double page_rank);

void insert_page_link(Page* page, Page* link);

Page* search_link(Page* page, Page** pages, int* i, int n_pages);

void print_page(Page* page);

void destroy_page(Page* page);

void verificar_consultas(Page** page, char* consulta, int n_pages);

#endif  //PAGES_H