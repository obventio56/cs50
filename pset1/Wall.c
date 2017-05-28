#include <stdio.h>
#include <cs50.h>

int main()
{
    int h, x = 0, s = 0, n = 0;
    do
    {
        printf("Enter a value ");
        h = GetInt();
    }
    while (h >= 23);
    while (x <= h)
    {
        s = 0;
        n = 0;
        while (s <= h + (-x-0))
        {
            printf(" ");
            s = s+1;
        }
        while (n <= x + 1)
        {
            printf("#");
            n = n + 1;
        }
        s = 0;
        n = 0;
        while (s <= 4)
        {
            printf(" ");
            s = s+1;
        }
        while (n <= x + 2)
        {
            printf("#");
            n = n + 1;
        }
        x = x + 1;
        printf("\n");
    }
}

            
        
