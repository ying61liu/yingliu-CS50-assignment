#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float L = (letters / (float) words) * 100;
    float S = (sentences / (float) words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Print the grade level
    int grade = (int) round(index);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    // Returns the number of letters in text
    int letters = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }

    return letters;
}

int count_words(string text)
{
    // Returns the number of words in text
    int length = strlen(text);
    int words = 1;

    for (int i = 0; i < length; i++)
    {
        if (isblank(text[i]))
        {
            words += 1;
        }
    }

    return words;
}

int count_sentences(string text)
{
    int length = strlen(text);

    int sentences = 0;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }

    return sentences;
}
