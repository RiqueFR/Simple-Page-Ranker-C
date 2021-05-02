#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patriciaTrieNoh {
    int n_palavras;
    char* data;
    struct patriciaTrieNoh* esq;
    struct patriciaTrieNoh* dir;
};

typedef struct patriciaTrieNoh Patricia;

Patricia* nascimentoDaPatricia() {
    Patricia* bebe = (Patricia*)malloc(sizeof(Patricia));
    bebe->esq = NULL;
    bebe->dir = NULL;
    return bebe;
}

int PatriciaSolteira(Patricia* trie) {
    if (!trie) {
        return 1;
    } else {
        return 0;
    }
}
