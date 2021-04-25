#ifndef PAGES_H
#define PAGES_H

typedef struct page Page;

Page* init_page(char* nome);

void set_n_links(Page* page, int n_links);

char* get_name_page(Page* page);

void insert_page_link(Page* page, Page* link);

void print_page(Page* page);

void destroy_page(Page* page);

#endif  //PAGES_H