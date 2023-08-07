#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 26

// Trie node structure
struct TrieNode {

  struct TrieNode* child[size];
  int count;

};

// Trie structure
struct Trie {

  struct TrieNode* root;

};

// Create a new Trie node
struct TrieNode* createTrieNode() {
  
  struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
  for (int i = 0; i < size; i++)
  {
    newNode->child[i] = NULL;
  }
  newNode->count = 0;
  return newNode;
  
}

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word) {
  
  struct TrieNode* hold = pTrie->root;
  for (int i = 0; word[i] != '\0'; i++)
  {
    int index = word[i] - 'a';
    if (hold->child[index] == NULL)
    {
      hold->child[index] = createTrieNode();
    }
    hold = hold->child[index];
  }
  hold->count++;
  
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie* pTrie, char* word) {
  
  struct TrieNode* hold = pTrie->root;
  for (int i = 0; word[i] != '\0'; i++)
  {
    int index = word[i] - 'a';
    if (hold->child[index] == NULL)
    {
      return 0;
    }
    hold = hold->child[index];
  }
  return hold->count;
  
}

// Deallocate the trie node
struct TrieNode* deallocateTrieNode(struct TrieNode* pNode) {
  
  if (pNode == NULL)
  {
    return NULL;
  }
  for (int i = 0; i < size; i++)
  {
    pNode->child[i] = deallocateTrieNode(pNode->child[i]);
  }
  free(pNode);
  return NULL;
  
}

// Deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie) {
  
  pTrie->root = deallocateTrieNode(pTrie->root);
  free(pTrie);
  return NULL;
  
}

// Initializes a trie structure
struct Trie* createTrie() {
  
  struct Trie* pTrie = (struct Trie*)malloc(sizeof(struct Trie));
  pTrie->root = createTrieNode();
  
  return pTrie;
}

// This function will read the dictionary file, count the number of words,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords) {
  
  FILE* fp;
  int numWords = 0;
  char word[256];

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    perror("Error opening file");
    exit(1);
  }

  fscanf(fp, "%d", &numWords); // Read the number of words from the file

  for (int i = 0; i < numWords; ++i)
  {
    fscanf(fp, "%s", word);
    pInWords[i] = strdup(word);
  }

  fclose(fp);
  return numWords;
  
}

int main(void) {
  
  char* inWords[256];
  int numWords = readDictionary("dictionary.txt", inWords);

  // Read the dictionary words
  printf("%d\n", numWords);
  for (int i = 0; i < numWords; ++i)
  {
    printf("%s\n", inWords[i]);
  }
  struct Trie* pTrie = createTrie();

  // Insert dictionary words into the trie
  for (int i = 0; i < numWords; i++)
  {
    insert(pTrie, inWords[i]);
  }
  
  // Test the occurrences of some words
  char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
  for (int i = 0; i < 5; i++)
  {
    printf("\t%s %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i])); 
  }

  pTrie = deallocateTrie(pTrie);

  if (pTrie != NULL)
  {
    printf("There is an error in this program\n");
  }
  
  // Deallocate the memory for the dictionary words
  for (int i = 0; i < numWords; ++i)
  {
    free(inWords[i]);
  }
  
  return 0;
  
}
