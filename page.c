#include "page.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inputread.h"
#include "rbt.h"
#include "wordlist.h"

struct page {
    char* nome_pagina;
    int n;
    int n_links;
    Page** links;
    double page_rank;
};

Page* init_page(char* nome) {
    Page* page = (Page*)malloc(sizeof(Page));
    if (page == NULL) {
        printf("Erro de alocação de pagina\n");
        exit(2);
    }
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

int compare_page_name(const void* a, const void* b) {
    /*
    * Segundo a ordem alfabética retorna um valor:
    * > 0 -> primeiro parametro maior que o segundo
    * = 0 -> parametros iguais
    * < 0 -> segundo parametro maior que o primeiro
    */
    /**
 * verifica se o noh eh vermelho
 * 
 * @param {RBT* rbt} noh da arvore.
 * 
 * @pre rbt nao null.
 * @post caso possua retorna 0 se nao 1
 * 
 * @return arvore atualizada.
 */
    Page* a1 = *(Page**)a;
    Page* a2 = *(Page**)b;
    return strcmp(get_name_page(a1), get_name_page(a2));
}

int compare_page_rank(const void* a, const void* b) {
    /*
    * Segundo a ordem alfabética retorna um valor:
    * > 0 -> primeiro parametro maior que o segundo
    * = 0 -> parametros iguais
    * < 0 -> segundo parametro maior que o primeiro
    */
    Page* a1 = *(Page**)a;
    Page* a2 = *(Page**)b;

    if (a1 == NULL && a2) return 1;
    if (a1 && a2 == NULL) return -1;
    if (a1 == NULL && a2 == NULL) return 0;

    double res = a1->page_rank - a2->page_rank;

    if (res > 0)
        return -1;
    if (res < 0)
        return 1;
    else
        return 0;
}

void print_page(Page* page) {
    if (!page) return;
    printf("%s -> ", page->nome_pagina);
    for (int i = 0; i < page->n; i++) {
        printf(" %s", page->links[i]->nome_pagina);
    }
    printf("\n");
    printf("page_rank: %lf\n", page->page_rank);
}

void destroy_page(Page* page) {
    free(page->nome_pagina);
    if (page->links != NULL) {
        free(page->links);
    }
    free(page);
}

static int binary_search(char** stopwords, int lo, int hi, char* word) {
    if (hi >= lo) {
        int mid = lo + (hi - lo) / 2;

        // Se a palavra esta no meio da stopwords
        //printf("stopword: %s -> %d / palavra: %s\n", stopwords[mid], mid, word);
        if (strcasecmp(stopwords[mid], word) == 0)
            return mid;

        // Se o elemento eh menor que o meio, so pode estar na esquerda
        if (strcasecmp(stopwords[mid], word) > 0)
            return binary_search(stopwords, lo, mid - 1, word);

        // caso contrario, so pode estar na esquerda
        return binary_search(stopwords, mid + 1, hi, word);
    }

    // Se a palavra nao esta presente, retorna -1
    return -1;
}

Page** verify_query(Page** pages_verified, Page** page, char* consulta, int n_pages, char** stopwords, int stopwords_size, char* default_directory) {
    char* a = strdup(consulta);
    int k = 1;
    int str[n_pages];
    char temp[256];
    char* word;
    int i = 0;
    size_t buffer_size = 100;
    char* buffer_page = (char*)malloc(sizeof(char) * buffer_size);

    for (int i = 0; i < n_pages; i++) {
        str[i] = 0;
    }

    word = strtok(a, " ");
    Wordlist* wordlist = init_wordlist();

    while (word != NULL) {
        wordlist = insert_wordlist(wordlist, word);
        word = strtok(NULL, " ");
    }

    Wordlist* start = wordlist;

    for (int i = 0; i < n_pages; i++) {
        wordlist = start;

        RBT* rbt = NULL;
        int has_all_words = 1;

        char* directory = file_name(default_directory, page[i]->nome_pagina, 1);
        FILE* arquivo = fopen(directory, "r");
        free(directory);

        if (arquivo == NULL) {
            printf("Arquivo não encontrado!\n");
            exit(2);
        }

        for (int line_size = getline(&buffer_page, &buffer_size, arquivo);
             arquivo && line_size >= 0; line_size = getline(&buffer_page, &buffer_size, arquivo)) {
            if (buffer_page[line_size - 1] == '\n')
                buffer_page[line_size - 1] = '\0';

            word = strtok(buffer_page, " ");

            while (word != NULL) {
                if (binary_search(stopwords, 0, stopwords_size - 1, word) == -1) {
                    rbt = RBT_insert(rbt, word);
                }
                word = strtok(NULL, " ");
            }
        }

        while (wordlist != NULL) {
            word = get_word(wordlist);
            //verificar se esta na stopwords
            //se a palavra atual for uma stopword, pula para proxima
            if (!search(rbt, word)) {
                has_all_words = 0;
                break;
            }
            wordlist = get_next(wordlist);
        }
        if (has_all_words == 1) {
            str[i] = 1;
        }
        fclose(arquivo);
        RBT_delete(rbt);
    }

    destroy_wordlist(start);
    free(a);
    free(buffer_page);

    for (int i = 0; i < n_pages; i++) {
        if (str[i] == 1) {
            pages_verified[i] = page[i];
        } else {
            pages_verified[i] = NULL;
        }
    }
    return pages_verified;
}

Page* find_page(Page** pages, int lo, int hi, char* name_page) {
    if (hi >= lo) {
        int mid = lo + (hi - lo) / 2;

        // Se a pagina esta no meio das paginas
        if (strcasecmp(get_name_page(pages[mid]), name_page) == 0)
            return pages[mid];

        // Se o elemento eh menor que o meio, so pode estar na esquerda
        if (strcasecmp(get_name_page(pages[mid]), name_page) > 0)
            return find_page(pages, lo, mid - 1, name_page);

        // caso contrario, so pode estar na esquerda
        return find_page(pages, mid + 1, hi, name_page);
    }

    // Se a pagina nao esta presente, retorna NULL
    return NULL;
}