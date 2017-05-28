#include <stdio.h>
#include <cs50.h>

int main(int argc, char* argv)
{
    if (argc != 3) 
    {
        printf("Enter two arg's. Int file and out file.");
        return 1;
    }
    FILE* nf = fopen(&argv[2], "w");
    if (nf == NULL)
    {
        return 2;
    }
    FILE* of = fopen(&argv[1], "r");
    if (of == NULL)
    {
        return 3;
    }
    int x = strlen(of);
    while (x - y >= 0)
    {
        char* buffer;
        fread(buffer, 1, 1, FILE of);
        fwrite(buffer, 1 , 1, nf);
    }
    fclose(nf);
    fclose(of);
}
    
    
