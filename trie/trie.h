#ifndef TRIE_H
#define TRIE_H

typedef struct trie Trie;

Trie* getNewTrieNode();

void insert(Trie* head, char* str);

int search(Trie* head, char* str);

int hasChildren(Trie* curr);

int deletion(Trie** curr, char* str);

void deleteAllTrie(Trie* curr);

#endif