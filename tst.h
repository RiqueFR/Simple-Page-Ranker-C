#ifndef TST_H
#define TST_H

typedef struct tst Tst;

Tst* init_empty_tst();

Tst* init_tst();

Tst* insert_tst(Tst* tst, char* word);

int get_word_tst(Tst* tst, char* word);

void destroy_tst(Tst* tst);

#endif //TST_H
