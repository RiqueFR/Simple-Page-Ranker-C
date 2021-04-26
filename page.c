#include "page.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page {
    char* nome_pagina;
    int n;
    int n_links;
    Page** links;
    double page_rank;
};
/**Page:
 * name
 * n_links
 * Page **links
 * int n
*/

Page* init_page(char* nome) {
    Page* page = (Page*)malloc(sizeof(Page));
    page->nome_pagina = strdup(nome);
    page->n = 0;
    return page;
}

char* get_name_page(Page* page) {
    if (page) {
        return page->nome_pagina;
    }
}

double get_page_rank(Page* page) {
    if (page)
        return page->page_rank;
}

void set_n_links(Page* page, int n_links) {
    page->n_links = n_links;
    page->links = (Page**)malloc(sizeof(Page*) * n_links);
    if (page->links == NULL) {
        printf("Problema ao alocar memoria de links no graph!\n");
        exit(3);
    }
}

int get_n_links(Page* page) {
    return page->n_links;
}

void set_page_rank(Page* page, double page_rank) {
    page->page_rank = page_rank;
}

void insert_page_link(Page* page, Page* link) {
    if (page->n == page->n_links) {
        return;
    }

    page->links[page->n] = link;
    page->n++;
}

Page* search_link(Page* page, Page** pages, int* i, int n_pages) {
    for (; (*i) < n_pages;) {
        for (int j = 0; j < pages[(*i)]->n_links; j++) {
            if (pages[(*i)]->links[j] == page) {
                return pages[(*i)];
            }
        }
        *i = (*i) + 1;
    }
    return NULL;
}

void print_page(Page* page) {
    if (!page) return;
    printf("%s -> ", page->nome_pagina);
    for (int i = 0; i < page->n; i++) {
        printf(" %s", page->links[i]->nome_pagina);
    }
    printf("\n");
}

void destroy_page(Page* page) {
    free(page->nome_pagina);
    if (page->links != NULL) {
        free(page->links);
    }
    free(page);
}

/*
busca palavra(palavra, paginas)

verifica arquivos(frase)
int flag
for arquivos
    forpalavras
        flag = busca palavra
        break
    if flag
        add pagina vetor


    FALTA IMPLEMENTAR
*/
void verificar_consultas(Page** page, char* consulta, int n_pages) {
    int v = strlen(consulta);
    char* a = strdup(consulta);
    char str[n_pages];
    char delim[] = " ";
    char temp[256];

    char* ptr = strtok(a, delim);
    while (ptr != NULL) {
        for (int i = 0; i < n_pages; i++) {
            FILE* arquivo = fopen(page[i]->nome_pagina, "r");
            if (arquivo != NULL) {
                while (arquivo && fgets(temp, sizeof(temp), arquivo)) {
                    if (strstr(temp, ptr)) {
                        str[i] = 1;
                    } else {
                        str[i] = 0;
                    }
                }
            }
        }

        ptr = strtok(NULL, delim);
    }
    printf("paginas que tem as palavras %s sao: ", consulta);
    for (int i = 0; i < n_pages; i++) {
        if (str[i] == 1) {
            printf("%s ", page[i]->nome_pagina);
        }
    }
    free(a);
}