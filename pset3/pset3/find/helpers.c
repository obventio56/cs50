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
    while (n > 1)
    {
        if (n%2 == 0)
        {
            if (values[n/2] > value)
            {
                n = (n/2);
            }
            else if (values[n/2] < value)
            {
                n = (n/2);
                if (n%2 == 0)
                {
                    n = n + (n/2);
                }
                else
                {
                    n = n + ((n-1) /2) + 1;
                }
            }
            else
            {
                n = (n/2);
                break;
            }
        }
        else
        {
            int z = ((n-1) / 2);
            if (values[z] > value)
            {
                n = ((n-1) / 2);
            }
            else if (values[z] < value)
            {
                n = ((n-1) / 2);
                if (n%2 == 0)
                {
                    n = n + (n/2);
                }
                else
                {
                    n = n + ((n-1) / 2);
                }
            }
            else
            {
                n = (n/2);
                break;
            }
        }
    }
    if (value == values[n])
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
