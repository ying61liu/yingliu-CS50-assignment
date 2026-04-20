#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool check_key(string text);
char replace_char(char c, string key);

int main(int argc, string argv[])
{
    // Limit commmand line arguments to two
    if (argc != 2 || check_key(argv[1]) == false)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Prompt user for a text input
    string plaintext = get_string("plaintext: ");

    // Replace the plaintext with info from the key
    printf("ciphertext: ");
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        printf("%c", replace_char(plaintext[i], argv[1]));
    }
    printf("\n");

    return 0;
}

bool check_key(string text)
{
    // Returns false if key doesn't have 26 chars or has non-alphabetic char, or has recurring
    // chars, otherwise, returns true
    int length = strlen(text);

    if (length != 26)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            if (isalpha(text[i]) == false)
            {
                return false;
            }
        }

        for (int i = 0; i < (length - 1); i++)
        {
            for (int j = (i + 1); j < length; j++)
            {
                if (text[i] == text[j])
                {
                    return false;
                }
            }
        }

        return true;
    }
}

char replace_char(char c, string key)
{
    if (isupper(c))
    {
        int index = (int) c - 65;
        char new_c = key[index];
        return (toupper(new_c));
    }
    else if (islower(c))
    {
        int index = (int) c - 97;
        char new_c = key[index];
        return (tolower(new_c));
    }

    return c;
}
