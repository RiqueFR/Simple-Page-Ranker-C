#include "tst.h"
#include <stdlib.h>

struct tst {
	char letter;
	Tst* left;
	Tst* middle;
	Tst* right;
};

Tst* init_empty_tst() {
	return NULL;
}

Tst* init_tst() {
	Tst* tst = (Tst*)malloc(sizeof(Tst));
	tst->letter = '\0';
	tst->left = NULL;
	tst->middle = NULL;
	tst->right = NULL;
	
	return tst;
}

Tst* recursive_insert(Tst* tst, char* palavra, int i) {
	if(tst == NULL) {
		tst = init_tst();
		tst->letter = palavra[i];
	}
	if(palavra[i] < tst->letter)
		tst->left = recursive_insert(tst->left, palavra, i);
	else if(palavra[i] == tst->letter) {
		if(palavra[i] != '\0')
			tst->middle = recursive_insert(tst->middle, palavra, i + 1);
	} else
		tst->right = recursive_insert(tst->right, palavra, i);
	return tst;
}

Tst* insert_tst(Tst *tst, char *word) {
	tst = recursive_insert(tst, word, 0);
	return tst;
}

int get_word_tst(Tst *tst, char *word) {
	Tst* aux = tst;
	int i = 0;
	while(aux != NULL) {
		if(word[i] < aux->letter)
			aux = aux->left;
		else if(word[i] == aux->letter) {
			if(word[i] == '\0') return 1;
			i++;
			aux = aux->middle;
		}
		else
			aux = aux->right;	
	}
	return 0;
}

void destroy_tst(Tst *tst) {
	if(tst == NULL) return;
	destroy_tst(tst->left);
	destroy_tst(tst->right);
	destroy_tst(tst->middle);
	free(tst);
}
