#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Change owed: ");
    }
    while (n < 0);

    int coin = 0;

    while (n > 0)
    {
        if (n - 25 >= 0)
        {
            n -= 25;
        }

        else if (n - 10 >= 0)
        {
            n -= 10;
        }

        else if (n - 5 >= 0)
        {
            n -= 5;
        }

        else
        {
            n -= 1;
        }

        coin++;
    }

    printf("%i\n", coin);
}
