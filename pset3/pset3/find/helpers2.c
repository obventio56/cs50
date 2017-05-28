/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    int y = 0;
    while (n > 1)
    {
        if (values[y] != value)
        {
            y = y + 1;
            n = n - 1;
        }
        else
        {
            break;
        }
    }
    if (value == values[y])
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    return;
}
