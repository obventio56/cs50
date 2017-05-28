#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    string s[5];
    for (int i = 0; i < 5; i++)
    {
        printf("Please enter a name %d: ", i + 1);
        s[i] = GetString();
    }
    srand(time(NULL));
    int name = rand() % 5;
    printf("%s\n", s[name]);
}

