#include <cs50.h>
#include <math.h>
#include <stdio.h>

int luhn(long num);
void company(long num);

int main(void)
{
    // Prompt user for input
    long num = get_long("Number: ");

    // Run through the Luhn's algorithm
    int sum = luhn(num);

    // If pass Luhn's algorithm, then check if match any credit card company and print company name
    if (sum % 10 == 0)
    {
        company(num);
    }

    else
    {
        printf("sum is: %i\n", sum);
        printf("INVALID\n");
    }
}

int luhn(long num)
{
    int sum1 = 0;
    int sum2 = 0;

    // Loop through the odd-digit number backwards, multiply each by 2, and add the products
    for (int i = 0; num != 0; i++)
    {
        // Get each single digit
        int d = num % 10;

        // Multiply each odd digit by 2 and sum the products all together
        if (i % 2 != 0 && i != 0)
        {
            int double_d = d * 2;

            // Add up each digit of a product if it is a two-digit product
            if (double_d > 9)
            {
                sum1 = sum1 + (double_d % 10) + (double_d / 10);
            }

            else
            {
                sum1 = sum1 + double_d;
            }
        }

        // Add up the rest of digits altogether
        else
        {
            sum2 = sum2 + d;
        }

        num = num / 10;
    }

    return (sum1 + sum2);
}

void company(long num)
{
    int i = 0;
    int two_d;
    int one_d;

    while (num != 0)
    {
        int d = num % 10;
        if (num > 10 && num < 100)
        {
            two_d = num;
        }
        if (num > 0 && num < 10)
        {
            one_d = num;
        }
        num = num / 10;
        i += 1;
    }

    if (i == 15 && (two_d == 34 || two_d == 37))
    {
        printf("AMEX\n");
    }

    else if (i == 16 && (two_d == 51 || two_d == 52 || two_d == 53 || two_d == 54 || two_d == 55))
    {
        printf("MASTERCARD\n");
    }

    else if ((i == 13 || i == 16) && (one_d == 4))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}
