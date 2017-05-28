/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <math.h>
#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
typedef struct node
{
    double dbl;
    char* ptr;
    struct node* next;
}
node;
typedef struct beg
{
    double dbl;
    struct node* next;
}
beg;
typedef struct npptr
{

    struct node **next;
}
npptr;
typedef struct pptr
{

    struct ptr* next;
}
pptr;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

int merge(beg* start, int size, double n);

int nmerge(node* start, int size, double n);
#endif // DICTIONARY_H
