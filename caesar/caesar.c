#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string text);
char rotate(char p, int k);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2 || only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (argc == 2 && only_digits(argv[1]))
    {
        int num = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");

        int length = strlen(plaintext);

        printf("ciphertext: ");
        for (int i = 0; i < length; i++)
        {
            char c_i = rotate(plaintext[i], num);
            printf("%c", (char) c_i);
        }
        printf("\n");
    }
}

bool only_digits(string text)
{
    // Returns true if every char is a digit
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isdigit(text[i]) == false)
        {
            return false;
        }
    }

    return true;
}

char rotate(char p, int k)
{
    // Returns a char with an increased value of k
    if (isalpha(p))
    {
        if (isupper(p))
        {
            int c_i = ((int) p - 65 + k) % 26;
            c_i += 65;
            return (char) c_i;
        }
        else
        {
            int c_i = ((int) p - 97 + k) % 26;
            c_i += 97;
            return (char) c_i;
        }
    }
    else
    {
        return p;
    }
}
