/*
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
    int  x = 0;
    for (int i = 0; i <= n; i++)
    {
        while (x <= n)
        {
            if (values[x] < values[x+1])
            {
                values[x] = values[x];
            }
            else
            {
                int y = values[x];
                values[x] = values[x+1];
                values[x+1] = y;
            }
            x = x + 1;
        } 
    }
    return;
    for (int f = 0; n > f; f++)
    {
        printf("%d", values[f]);
    }
        printf("/n");
}
