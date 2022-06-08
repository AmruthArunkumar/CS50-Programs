// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

FILE *file;
FILE *testfile;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    
    int i = hash(word); 
    node *currlist = table[i];
    for (node *tmp = currlist; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0) 
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //hashes the word
    if ((int) word[0] < 90)
    {
        return ((int) word[0]) - 65;
    }
    if ((int) word[0] > 90)
    {
        return ((int) word[0]) - 97;
    }
    return 0;
    
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //opening dictionary
    file = fopen(dictionary, "r");
    testfile = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }
    if (!testfile)
    {
        return false;
    }
    
    //finding word
    
    char test[LENGTH + 1];
    char currword[LENGTH + 1];
    
    while (fscanf(testfile, "%s", test) != EOF) 
    {
        fscanf(file, "%s", currword);
        count++;
        
        int i = hash(currword); 
        node *currlist = table[i];
        
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        strcpy(n->word, currword);
        n->next = NULL;
        
        if (table[i] == NULL) 
        {
            table[i] = n;
        }
        else 
        {
            for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
            {
                currlist = tmp;
            }
            currlist->next = n;
        }
        
    }
    //closing file
    
    fclose(testfile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //unloading dictionary
    int fc = fclose(file);
    if (fc == 0)
    {
        for (int i = 0; i < N; i++) 
        {
            while (table[i] != NULL)
            {
                node *tmp = table[i]->next;
                free(table[i]);
                table[i] = tmp;
            }
        }
        return true;
    } 
    else 
    {
        return false;
    }
    
}
