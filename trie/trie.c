#include "trie.h"

#include <stdio.h>
#include <stdlib.h>

// Define the character size
#define CHAR_SIZE 26

// Data structure to store a Trie node
struct trie {
    int isLeaf;  // 1 when the node is a leaf node
    Trie* character[CHAR_SIZE];
};

// Function that returns a new Trie node
Trie* getNewTrieNode() {
    Trie* node = (Trie*)malloc(sizeof(Trie));
    node->isLeaf = 0;

    for (int i = 0; i < CHAR_SIZE; i++) {
        node->character[i] = NULL;
    }

    return node;
}

// Iterative function to insert a string into a Trie
void insert(Trie* head, char* str) {
    // start from the root node
    Trie* curr = head;
    while (*str) {
        // modificação para inserir apenas minúsculo
        char c = *str;

        if (c >= 'A' && c <= 'Z')
            c += ('a' - 'A');

        // create a new node if the path doesn't exist
        if (curr->character[c - 'a'] == NULL) {
            curr->character[c - 'a'] = getNewTrieNode();
        }

        // go to the next node
        curr = curr->character[c - 'a'];

        // move to the next character
        str++;
    }

    // mark the current node as a leaf
    curr->isLeaf = 1;
}

// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search(Trie* head, char* str) {
    // return 0 if Trie is empty
    if (head == NULL) {
        return 0;
    }

    Trie* curr = head;
    while (*str) {
        char c = *str;

        // verifica se a letra eh minuscula
        if (c >= 'A' && c <= 'Z')
            c += ('a' - 'A');
        // go to the next node
        curr = curr->character[c - 'a'];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == NULL) {
            return 0;
        }

        // move to the next character
        str++;
    }

    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns 1 if a given Trie node has any children
int hasChildren(Trie* curr) {
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (curr->character[i]) {
            return 1;  // child found
        }
    }

    return 0;
}

// Recursive function to delete a string from a Trie
int deletion(Trie** curr, char* str) {
    // return 0 if Trie is empty
    if (*curr == NULL) {
        return 0;
    }

    // if the end of the string is not reached
    if (*str) {
        char c = *str;

        if (c >= 'A' && c <= 'Z')
            c += ('a' - 'A');
        // recur for the node corresponding to the next character in
        // the string and if it returns 1, delete the current node
        // (if it is non-leaf)
        if (*curr != NULL && (*curr)->character[c - 'a'] != NULL &&
            deletion(&((*curr)->character[c - 'a']), str + 1) &&
            (*curr)->isLeaf == 0) {
            if (!hasChildren(*curr)) {
                free(*curr);
                (*curr) = NULL;
                return 1;
            } else {
                return 0;
            }
        }
    }

    // if the end of the string is reached
    if (*str == '\0' && (*curr)->isLeaf) {
        // if the current node is a leaf node and doesn't have any children
        if (!hasChildren(*curr)) {
            free(*curr);  // delete the current node
            (*curr) = NULL;
            return 1;  // delete the non-leaf parent nodes
        }

        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            (*curr)->isLeaf = 0;
            return 0;  // don't delete its parent nodes
        }
    }

    return 0;
}

// Delete all trie
void deleteAllTrie(Trie* curr) {
    //Free the trienode sequence
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (curr->character[i] != NULL) {
            deleteAllTrie(curr->character[i]);
        } else {
            continue;
        }
    }
    free(curr);
}