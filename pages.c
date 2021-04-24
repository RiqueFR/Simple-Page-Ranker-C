#include "pages.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pagina {
    char* nomePagina;
};
/**Page:
 * name
 * n_links
 * Page **links
*/

struct pages {
    Pagina** pages;
    int n_pages;
};

Pagina* ini_pagina(char* nome) {
    Pagina* page = (Pagina*)malloc(sizeof(Pagina));
    page->nomePagina = strdup(nome);
    return page;
}

Pages* ini_pages(FILE* index) {
    Pages* mainPage = (Pages*)malloc(sizeof(Pages));

    int i = 0;
    char palavra[30];
    char c;
    for (c = getc(index); c != EOF; c = getc(index))
        if (c == '\n')  // Increment count if this character is newline
            i = i + 1;

    mainPage->n_pages = i;
    while (i < mainPage->n_pages && (!feof(index))) {
        fscanf(index, "%s", palavra);
        mainPage->pages = ini_pagina(palavra);
        i++;
    }

    fclose(index);
    return mainPage;
}

void destroy_page(Pages* page) {
}