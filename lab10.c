#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};

// Initializes a trie node
struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts the word into the trie
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *curr = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!curr->children[index]) {
            curr->children[index] = createTrieNode();
        }
        curr = curr->children[index];
    }
    curr->count++;
}

// Finds the number of occurrences of a word in the trie
int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *curr = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!curr->children[index]) {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// Deallocates the trie
void deallocateTrie(struct TrieNode *root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
}

// Reads the dictionary from file and returns the number of words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    int numWords;
    fscanf(file, "%d", &numWords);
    for (int i = 0; i < numWords; ++i) {
        pInWords[i] = (char *)malloc(100 * sizeof(char)); // Assuming max word length is 100
        fscanf(file, "%s", pInWords[i]);
    }
    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];
    // Read the dictionary
    int numWords = readDictionary("dictionary-1.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
    
    // Create trie and insert words
    struct TrieNode *root = createTrieNode();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }
    
    // Test the trie with some words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }
    
    // Deallocate trie
    deallocateTrie(root);
    
    return 0;
}
