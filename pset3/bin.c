#include <stdbool.h>
bool binary_search(int value, int values[], int n)
{
    int big = 0;
     int end = n -1;
    while  (end - big > 0)
    {
        if (values[n/2] > value)
        {
        n = n/2;
        }
        else if (values [n/2] < value)
        {
        n = (n/2) + (n/4); 
        }
    }
    return false;
}
 
