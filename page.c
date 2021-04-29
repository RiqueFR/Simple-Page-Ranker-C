#include "page.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordlist.h"

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
    int k = 1;
    int str[n_pages];
    char temp[256];
    char* word;
    int i = 0;

    for (int i = 0; i < n_pages; i++) {
        str[i] = 0;
    }

    word = strtok(a, " ");
    Wordlist* wordlist = init_wordlist();
    Wordlist* start = wordlist;

    while (word != NULL) {
        insert_wordlist(wordlist, word);
        word = strtok(NULL, " ");
    }

    /**
     * para cada arquivo:
     *  flag = 0;
     *  para cada palavra
     *      if palavra no arquivo:
     *          continue
     *      else:
     *          flag = 1
     *          break
     *  if flag == 0:
     *      adiciono pagina vetor;
     */
    for (int i = 0; i < n_pages; i++) {
        wordlist = start;

        int has_all_words = 1;
        Trie* head = getNewTrieNode();

        FILE* arquivo = fopen(page[i]->nome_pagina, "r");
        if (arquivo == NULL) {
            printf("Arquivo não encontrado!\n");
            exit(2);
        }
        while (arquivo && fscanf(arquivo, "%s", temp) == 1) {
            insert(head, temp);
        }

        while (wordlist != NULL) {
            word = get_word(wordlist);
            if (search(head, word)) {
                wordlist = get_next(wordlist);
                continue;
            } else {
                has_all_words = 0;
                break;
            }
        }
        // printf(" - %d\n", has_all_words);
        if (has_all_words == 1) {
            str[i] = 1;
        }

        deleteAllTrie(head);

        // while (ptr != NULL) {
        //     for (int i = 0; i < n_pages; i++) {

        //         FILE* arquivo = fopen(page[i]->nome_pagina, "r");

        //         if (arquivo != NULL) {
        //             //insert(Trie* head, char* str)

        //             // search(Trie* head, char* str)

        //             while (arquivo && fscanf(arquivo, "%s", temp) == 1) {
        //                 if (strstr(temp, ptr)) {
        //                     str[i] += 1;
        //                 }
        //             }
        //         }
        //     }
        // printf("\nA palavra eh: %s \n", ptr);
        // printf("Vetor esta assim: \n");
        // for (int j = 0; j < n_pages; j++) {
        //     printf("%d ", str[j]);
        // }
        // k++;
        // ptr = strtok(NULL, delim);
        
    }
    printf("\n");
    printf("paginas que tem as palavras %s sao: ", consulta);
    for (int i = 0; i < n_pages; i++) {
        if (str[i] == 1) {
            printf("%s ", page[i]->nome_pagina);
        }
    }
    printf("\n");
    destroy_wordlist(start);
    free(a);
}

// if (i > 0) {
//     while (arquivo && fgets(temp, sizeof(temp), arquivo)) {
//         if (strstr(temp, ptr)) {
//             if (str[i] == 1) {  // blz
//                 str[i] = 1;
//             } else {
//                 str[i] = 0;
//             }
//         } else {
//             str[i] = 0;
//         }
//     }
// }