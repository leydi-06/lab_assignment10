#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
  struct Trie *Children[26];
  int Word;
  int number;
};

struct Trie *createTrie() {
    struct Trie *New_Trie = (struct Trie *)malloc(sizeof(struct Trie));
    memset(New_Trie, 0, sizeof(struct Trie));
    return New_Trie;

}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
  struct Trie *current_nd = pTrie;
  int word_length = strlen(word);
  for (int i = 0; i < word_length; i++) {
      int index = word[i] - 'a';
      if (current_nd->Children[index] == NULL) {
          current_nd->Children[index] = (struct Trie *)malloc(sizeof(struct Trie));
          memset(current_nd->Children[index], 0, sizeof(struct Trie));
      }
        current_nd= current_nd->Children[index];
  }
  current_nd->Word = 1;
  current_nd->number++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  struct Trie *current_nd
  = pTrie;
  for (int i = 0; i < strlen(word); i++) {
      int index = word[i] - 'a';
      if (current_nd->Children[index] == NULL) {
          return 0;
      }
      current_nd = current_nd->Children[index];
  }
  return current_nd->number;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
  if (pTrie == NULL) {
    return NULL;
  }
  for (int i = 0; i < 26; i++) {
    if (pTrie->Children[i] != NULL) {
        deallocateTrie(pTrie->Children[i]);
    }
  }
  free(pTrie);
  return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE *file = fopen("dictionary-1.txt", "r");
  if (file == NULL) {
      printf("Error opening file\n");
      exit(1);
  }
  int number = 0;
  while (!feof(file)) {
      char word[256];
      fscanf(file, "%s", word);
      pInWords[number] = (char *)malloc((strlen(word) + 1) * sizeof(char));
      strcpy(pInWords[number], word);
      number++;
  }
  fclose(file);
  return number;
}

int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i=0;i<numWords;++i)
  {
    printf("%s\n",inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i=0;i<numWords;i++)
  {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++)
  {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}