#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int score(string w);

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int player1 = score(word1);
    int player2 = score(word2);

    if (player1 > player2)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1 == player2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int score(string w)
{
    int length = strlen(w);

    int sum = 0;

    for (int i = 0; i != length; i++)
    {
        char l = toupper(w[i]);

        if (l == 'A' || l == 'E' || l == 'I' || l == 'L' || l == 'N' || l == 'O' || l == 'R' ||
            l == 'S' || l == 'T' || l == 'U')
        {
            sum += 1;
        }
        else if (l == 'D' || l == 'G')
        {
            sum += 2;
        }
        else if (l == 'B' || l == 'C' || l == 'M' || l == 'P')
        {
            sum += 3;
        }
        else if (l == 'F' || l == 'H' || l == 'V' || l == 'W' || l == 'Y')
        {
            sum += 4;
        }
        else if (l == 'K')
        {
            sum += 5;
        }
        else if (l == 'J' || l == 'X')
        {
            sum += 8;
        }
        else if (l == 'Q' || l == 'Z')
        {
            sum += 10;
        }
    }
    return sum;
}
