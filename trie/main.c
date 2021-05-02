#include <stdio.h>
#include <string.h>

#include "trie.h"

int main() {
    char* busca = "Henrique Paulino Cruz";
    char* word;
    int i = 0;

    Trie* head = getNewTrieNode();

    insert(head, "Hello");
    printf("%d ", search(head, "hello"));  // print 1

    insert(head, "helloworld");
    printf("%d ", search(head, "helloworld"));  // print 1

    printf("%d ", search(head, "helll"));  // print 0 (Not present)

    insert(head, "hell");
    printf("%d ", search(head, "hell"));  // print 1

    insert(head, "h");
    printf("%d \n", search(head, "h"));  // print 1 + newline

    // deletion(&head, "hello");
    printf("%d ", search(head, "hello"));       // print 0 (hello deleted)
    printf("%d ", search(head, "helloworld"));  // print 1
    printf("%d \n", search(head, "hell"));      // print 1 + newline

    // deletion(&head, "h");
    printf("%d ", search(head, "h"));            // print 0 (h deleted)
    printf("%d ", search(head, "hell"));         // print 1
    printf("%d\n", search(head, "helloworld"));  // print 1 + newline

    // deletion(&head, "helloworld");
    printf("%d ", search(head, "helloworld"));  // print 0
    printf("%d ", search(head, "hell"));        // print 1

    // deletion(&head, "hell");
    printf("%d\n", search(head, "hell"));  // print 0 + newline

    if (head == NULL) {
        printf("Trie empty!!\n");  // Trie is empty now
    }

    printf("%d ", search(head, "hell"));  // print 0

    deleteAllTrie(head);
    return 0;
}