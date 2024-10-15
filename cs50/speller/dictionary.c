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

unsigned int words_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);

    node *tmp = table[index];
    // printf("tmp->word: %s\n", tmp->word);

    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            // printf("Found word: %s\n", word);
            return true;
        }

        tmp = tmp->next;
    }

    free(tmp);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';

    unsigned int sum = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        sum += toupper(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    // Read each word in the file
    // Add each word to the hash table
    char word[LENGTH + 1];
    unsigned int index;

    while (fscanf(source, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
            return false;

        strcpy(new_node->word, word);
        new_node->next = NULL;

        index = hash(word);

        // printf("word: %s, index: %i\n", word, index);

        if (table[index] == NULL) // first
        {
            table[index] = new_node;
        }
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }

        // printf("word: %s, index: %i\n", table[index]->word, index);
        words_count++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];

        while (ptr != NULL)
        {
            node *tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }

        free(ptr);
    }
    return true;
}
