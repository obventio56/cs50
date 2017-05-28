/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"
int* tester;
node* nst;
beg* st;
int r = 0;
int hash = 0;
bool loaded = NULL;
long word = 0;
int rem = 0;
int nrem = 0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int alt = hash + r;
    int aspot = 0;
    int spot = 0;
    int len = strlen(word);
    double test;
    int a = 0;
    char temp;
    char wtemp[len+1];
    for (int i = 0; i < len; i++)
    {
        temp = word[i];
        if (isupper(word[i]))
        {
            temp = word[i] + 32;
        }
        wtemp[i] = temp;
    }
    wtemp[len+1] = 0x00;
    for (int y = 0; y < len; y++)
        {
            a = a + word[y];
        }
    test = a/len;
    spot = merge(st, hash, test);
    if (spot != hash - 1)
    {
        aspot = nmerge(nst[spot * hash], hash, test);
    }
    else 
    {
        aspot = nmerge(nst[spot * hash], alt, test);
    }
    node* ntempp = malloc(sizeof(node));
    ntempp = &*nst[asopt];
    int lencmp = strlen(ntempp->ptr);
    if (lencmp != len)
    {
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        if (word[i] != ntempp->ptr[i])
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dict = fopen(dictionary, "r");
    int index = 0;
    char* words[200000];
    int wordlen[200000];
    // spell-check each word in text
    words[0] = malloc(46);
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            words[word][index] = c;
            index++;

        }
        else
        {
            words[word][index] = 0x00;
            wordlen[word] = index;
            word++;
            words[word] = malloc(46);
            index = 0;

        }
    }
    tester = &wordlen[0];
    double x = sqrt(word);
    hash = (int) x;
    int m = x*x;
    r = word - m;
    node* w[word];
    beg* start[hash];
    for (int i = 0; i < hash; i++)
    {
        int a;
        int place = i * hash;

        start[i] = malloc(sizeof(beg));
        for (int y = 0; y < wordlen[place]; y++)
        {
            a = a + words[place][y];
        }
        start[i]->dbl = a/wordlen[place];
        
    }
    for (int i = 0; i < word; i++)
    {
        w[i] = malloc(sizeof(node));
        w[i]->ptr = words[i];
    }
    
    nst = malloc(sizeof(node*));
    st = malloc(sizeof(beg*));
    st = start[0];
    nst = w[0];
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (loaded)
    {
        return word;
    }
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{

    for (int i = 0; i < word; i++)
    {
        node* ntemp = &nst->next[i];
        free(ntemp);
    }
    for (int i = 0; i < hash; i++)
    {
        beg* btemp = &st->next[i];      
        free(btemp);
    }
    return true;

}

int merge(beg* start, int size, double n)
{
    
    int ttemp = 0;
    int temp = 0;
    int hsize = 0;
    if (size % 2 == 0)
    {
        hsize = size/2;
    }
    else
    {
        hsize = (size + 1)/ 2;
    }
    if (n > start[hsize + rem]->dbl)
    {
        if (hsize % 2 == 0)
        {
            rem = hsize;
            temp = hsize/2;
        }
        else
        {
            rem = hsize;
            temp = (hsize + 1) / 2;
        }
    }
    else if ( n <start[rem + hsize]->dbl)
    {
        if (hsize % 2 == 0)
        {
            rem = hsize;
            temp = -1*(hsize/2);
        }
        else
        {
            rem = hsize;
            temp = -1*((hsize + 1) / 2);
        }
    }
    ttemp = temp;
    if (ttemp != 1 && ttemp != -1 && ttemp != 0)
    {
        ttemp = merge(&start[0], temp, n);
    }
    else
    {
        return ttemp;
    }
    return -1;
}  

int nmerge(node* start, int size, double n)
{
    
    int ttemp = 0;
    int temp = 0;
    int hsize = 0;
    if (size % 2 == 0)
    {
        hsize = size/2;
    }
    else
    {
        hsize = (size + 1)/ 2;
    }
    if (n > start[hsize + nrem]->dbl)
    {
        if (hsize % 2 == 0)
        {
            nrem = hsize;
            temp = hsize/2;
        }
        else
        {
            nrem = hsize;
            temp = (hsize + 1) / 2;
        }
    }
    else if ( n <start[nrem + hsize]->dbl)
    {
        if (hsize % 2 == 0)
        {
            nrem = hsize;
            temp = -1*(hsize/2);
        }
        else
        {
            nrem = hsize;
            temp = -1*((hsize + 1) / 2);
        }
    }
    ttemp = temp;
    if (ttemp != 1 && ttemp != -1 && ttemp != 0)
    {
        ttemp = nmerge(&start[0], temp, n);
    }
    else
    {
        return ttemp;
    }
    return -1;
}  
