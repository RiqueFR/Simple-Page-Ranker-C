#include "wordlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wordlist {
    Wordlist* next;
    char* word;
};

Wordlist* init_wordlist() {
    Wordlist* new_wordlist = (Wordlist*)malloc(sizeof(Wordlist));
    new_wordlist->next = NULL;
    new_wordlist->word = NULL;

    return new_wordlist;
}

char* get_word(Wordlist* wordlist) {
    return wordlist->word;
}

Wordlist* get_next(Wordlist* wordlist) {
    if (wordlist != NULL)
        return wordlist->next;
}

void insert_wordlist(Wordlist* wordlist, char* word) {
    if (wordlist->word == NULL) {
        wordlist->word = strdup(word);
        return;
    }
    Wordlist* next = (Wordlist*)malloc(sizeof(Wordlist));
    next->word = strdup(word);
    next->next = NULL;
    wordlist->next = next;
}

void destroy_wordlist(Wordlist* wordlists) {
    Wordlist* aux;
    while (wordlists != NULL) {
        aux = wordlists;
        wordlists = wordlists->next;
        if (aux != NULL) {
            if (aux->word != NULL)
                free(aux->word);
            free(aux);
        }
    }
    free(wordlists);
}