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
    
    int k[strlen(argv) = (atoi(argv[1]));
    
    // Prompt user for imput.
    printf("Enter your text: ");
    string p = GetString();
    
    //Encypher Text.
    
    
    // Initilize Loop
    for (int i = 0, len = strlen(p); i <= len; i++)
    {
        // Check is letter
        if (isalpha(p[i]))
        {
            // Check is uppercase
            if (isupper(p[i]))
            {
                p[i] = (p[i] - 65 + k) % 26 + 65;
                printf("%c", p[i]);
            }
            // If lowercase
            else
            {
                p[i] = (int) (p[i] - 97 + k) % 26 + 97;
                printf("%c", p[i]);
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
