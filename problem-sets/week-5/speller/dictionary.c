// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 456976;

// Hash table
node *table[N];

// Initiate global variable for tracking size
unsigned int n = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word to obtain hash value (idx)
    unsigned int idx = hash(word);

    // Access linked list at that index in the hash table
    node *trav = table[idx];

    // Traverse the linked list, looking for word with strcasecmp()
    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }

        trav = trav->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int len = strlen(word);

    int i = 0;

    if (len > 3)
    {
        i = ((toupper(word[0]) - 'A') * 17576) + (toupper(word[1]) - 'A') * 676 + (toupper(word[2]) - 'A') * 26 + (toupper(word[3]) - 'A');
        if (i > N)
        {
            i = i % N;
        }

        return i;
    }
    if (len > 2)
    {
        i = ((toupper(word[0]) - 'A') * 17576) + (toupper(word[1]) - 'A') * 676 + (toupper(word[2]) - 'A') * 26;
        if (i > N)
        {
            i = i % N;
        }

        return i;
    }
    else if (len > 1)
    {
        i = ((toupper(word[0]) - 'A') * 17576) + (toupper(word[1]) - 'A') * 676;
        if (i > N)
        {
            i = i % N;
        }

        return i;
    }
    else
    {
        i = (toupper(word[0]) - 'A') * 17576;
        if (i > N)
        {
            i = i % N;
        }

        return i;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary for reading
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Create array for storing words
    char word[LENGTH + 1];

    // Read one word at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create variable for indexing words from dictionary
        unsigned int idx = hash(word);

        // Create new node and ensure we have enough memory
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }

        strcpy(new->word, word);
        new->next = NULL;

        // Check if bucket is not empty
        if (table[idx] != NULL)
        {
            // Append node to it
            new->next = table[idx];
            table[idx] = new;
        }
        else
        {
            table[idx] = new;
        }

        size();
    }

    // Close file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return n++;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate through each bucket of hash table
    for (int i = 0; i < N; i++)
    {
        // If bucket not empty, free bucket
        if (table[i] != NULL)
        {
            // If bucket is not empty, iterate through linked list freeing one node at a time
            node *trav = table[i]->next;
            while (trav != NULL)
            {
                free(table[i]);
                table[i] = trav;
                trav = trav->next;
            }

            free(table[i]);
        }
    }

    return true;
}
