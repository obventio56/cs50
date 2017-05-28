#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Make sure there are two argu.
    if (argc != 2)
    {
        return 1;
    }
    // Assign argu to k.
    
    string k = (argv[1]);
    
    // Prompt user for imput.
    printf("Enter your text: ");
    string p = GetString();
    
    //Encypher Text.
    
    
    // Initilize Loop
    int x = 0;
    for (int i = 0, len = strlen(p), y = x % strlen(k); i <= len; i++)
    {
        // Check is letter
        if (isalpha(p[i]))
        {
            // Check is uppercase
            if (isupper(p[i]))
            {
                p[i] = (p[i] - 65 + (int) k[y]) % 26 + 65;
                printf("%c", p[i]);
                x = x + 1;
            }
            // If lowercase
            else
            {
                p[i] = (int) (p[i] - 97 + (int) k[y]) % 26 + 97;
                printf("%c", p[i]);
                x = x + 1;
            }
        // If not letter
        }
        else
        {
            p[i] = (int) p[i];
            printf("%c", p[i]);
        }
    }
    printf("\n");
}
