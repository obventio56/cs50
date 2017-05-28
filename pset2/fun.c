#include <stdio.h>
#include <cs50.h>

void greet(void);

int main(void)
{
    greet();

}
void greet(void)
{
    printf("Enter you name: \n");
    string name = GetString();
    printf("Hello, %s!\n", name);
}
