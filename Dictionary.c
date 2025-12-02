#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// Number of buckets in hash table
const unsigned int N = 26;

// Represents a node in a trie
typedef struct node {
    bool is_word;
    struct node *children[N+1];
} node;

void free_node(node *n);
void create_string(node *n, char* word, long long unsigned int i);
void count_words(node *n);

unsigned int hash_index(int c);
void free_node(node *n);

unsigned int counter = 0;
node *root = NULL;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    long long unsigned int i = 0;
    int h;
    node *tmp = root;

    while (i < strlen(word)){
        h = hash_index(word[i]);

        if (tmp->children[h] == NULL){
            return false;
        }
        tmp = tmp->children[h];
        i++;
    }

    return true;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {

    FILE *file = fopen(dictionary, "r");

    if (file == NULL){
        printf("Cannot open file \n");
        return false;
    }

    char word[26];
    while (fscanf(file, "%s", word) != EOF){
        create_string(root, word, 0);
    }

    fclose(file);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    if (root == NULL) {
        return 0;
    }

    counter = 0;  // Reset counter before counting
    count_words(root);
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    if (root != NULL) {
        free_node(root);
        root = NULL;  // Ensure root is set to NULL after unloading
        return true;
    }

    return false;
}

void create_string(node *n, char* word, long long unsigned int i) {

    if (n == NULL){
        return;
    }


    while (i < strlen(word)){

        unsigned int h = hash_index(word[i]);

        if (n -> children[h] == NULL){

            node *m = malloc(sizeof(node));

            n->children[h] = m;

            n->children[h]->is_word = false;

            memset(n->children[h]->children, 0, sizeof(n->children[h]->children));
        }

        n = n->children[h];
        i++;
    }
    n->is_word = true;

}



void free_node(node *n) {
    if (n != NULL) {
        for (int i = 0; i <= N; i++) {
            free_node(n->children[i]);
        }
        free(n);
    }
}

void count_words(node *n){

    if (n -> is_word){

        counter++;
    }

    for (int i = 0; i < 27; i++){

        if (n -> children[i] != NULL){

            count_words(n->children[i]);
        }
    }
}

unsigned int hash_index(int c) {

    if (c == '\''){
        return 26;
    }
    return toupper(c) - 'A';
}