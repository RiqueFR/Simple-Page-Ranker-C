#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 1
#define BLACK 0

struct node {
    char* value;
    int color;
    RBT *l, *r;
};

RBT* create_node(char* value, int n) {
    RBT* novo = (RBT*)malloc(sizeof(RBT));
    novo->value = strdup(value);
    novo->color = n;
    novo->l = NULL;
    novo->r = NULL;

    return novo;
}

RBT* RBT_insert(RBT* rbt, char* value) {
    // Insert at bottom and color it red.
    if (rbt == NULL) {
        return create_node(value, RED);
    }

    int cmp = strcasecmp(value, rbt->value);
    if (cmp < 0) {
        rbt->l = RBT_insert(rbt->l, value);
    } else if (cmp > 0) {
        rbt->r = RBT_insert(rbt->r, value);
    }
    // else /*cmp == 0*/ {
    //     rbt->value = value;
    // }
    /*   
    Aqui pra baixo já está fazendo o fixup dos casos se o avô do nó estivesse 
    com cores diferentes, pra mantar a propriedade da árvore rubro negra
    */

    // Lean left.
    if (is_red(rbt->r) && !is_red(rbt->l)) {
        rbt = rotate_left(rbt);
    }
    // Balance 4-node.
    if (is_red(rbt->l) && is_red(rbt->l->l)) {
        rbt = rotate_right(rbt);
    }
    // Split 4-node.
    if (is_red(rbt->l) && is_red(rbt->r)) {
        flip_colors(rbt);
    }
    return rbt;
}

int search(RBT* rbt, char* key) {
    while (rbt != NULL) {
        int cmp;
        cmp = strcasecmp(key, rbt->value);
        if (cmp < 0)
            rbt = rbt->l;
        else if (cmp > 0)
            rbt = rbt->r;
        else
            return 1;
    }
    return 0;
}

int is_red(RBT* rbt) {
    if (rbt == NULL) return BLACK;
    return rbt->color;  //RED == true
}

RBT* rotate_left(RBT* rbt) {
    RBT* x = rbt->r;
    rbt->r = x->l;
    x->l = rbt;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

RBT* rotate_right(RBT* rbt) {
    RBT* x = rbt->l;
    rbt->l = x->r;
    x->r = rbt;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors(RBT* h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

void RBT_delete(RBT* rbt) {
    if (rbt) {
        RBT_delete(rbt->l);
        RBT_delete(rbt->r);
        if (rbt->value)
            free(rbt->value);
        free(rbt);
    }
}
/*
void imprime_rbt(RBT* rbt) {
    printf("Palavras inseridas")
    if (rbt) {
        imprime_rbt(rbt->l);
        printf("palavra: %s\n", rbt->value);
        imprime_rbt(rbt->r);
    }
}
*/