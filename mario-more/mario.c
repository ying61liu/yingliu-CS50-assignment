#include <cs50.h>
#include <stdio.h>

void ascd_row(int spaces, int bricks);

int main(void)
{
    // get user input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // make a pyramid of rows
    for (int i = 0; i < n; i++)
    {
        ascd_row(n - i - 1, i + 1);
    }
}

void ascd_row(int spaces, int bricks)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }

    printf("\n");
}
