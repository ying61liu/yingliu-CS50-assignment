// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 101;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obatin its hash value
    int idx = hash(word);

    // Search the hash table at the location specified by the word's hash value
    node *trv = table[idx];

    while (trv != NULL)
    {
        if (strcasecmp(trv->word, word) == 0)
        {
            return true;
        }
        trv = trv->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //return toupper(word[0]) - 'A';
    int length = strlen(word);
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += toupper(word[i]);
    }
    return sum % 101;
}

// Make a global variable word_count to count the number of words in the dictionary
unsigned int word_count = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file and check if the file is opened successfully
    FILE *fptr = fopen(dictionary, "r");
    if (fptr == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char current_w[LENGTH + 1];
    while (fscanf(fptr, "%s", current_w) != EOF)
    {
        // Create a new node for each word
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            fclose(fptr);
            return false;
        }

        strcpy(new_word->word, current_w);
        new_word->word[LENGTH] = '\0';

        // Hash word to obtain a hash value
        int idx = hash(current_w);

        // Insert node into hash table at that location
        new_word->next = table[idx];
        table[idx] = new_word;

        // Update word count
        word_count++;
    }

    // Close the dictionary file
    fclose(fptr);

    // Return true if done
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Returns total word count of the dictionary when called
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *trv = table[i];

        while (trv != NULL)
        {
            node *tmp = trv;
            trv = trv->next;
            free(tmp);
        }
    }

    return true;
}
