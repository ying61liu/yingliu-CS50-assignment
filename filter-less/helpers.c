#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdio.h>

int cap(int num);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int average = round((red + green + blue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Compute sepia values
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            // Update pixel with sepia values
            image[i][j].rgbtRed = cap(sepiaRed);
            image[i][j].rgbtGreen = cap(sepiaGreen);
            image[i][j].rgbtBlue = cap(sepiaBlue);
        }
    }
    return;
}

int cap(int num)
{
    int CAP = 255;
    if (num < CAP)
    {
        return num;
    }
    else
    {
        return CAP;
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over necessary pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Blur surrounding pixels of each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Count how many grids are valid and add up their RGB values
            float count = 0.0;
            int sumRed = 0, sumGreen = 0, sumBlue = 0;

            // Add the ij pixel itself to the count and its value to the sum
            count += 1.0;
            sumRed += copy[i][j].rgbtRed;
            sumGreen += copy[i][j].rgbtGreen;
            sumBlue += copy[i][j].rgbtBlue;

            if (i >= 1 && j >= 1)
            {
                count += 1.0;
                sumRed += copy[i - 1][j - 1].rgbtRed;
                sumGreen += copy[i - 1][j - 1].rgbtGreen;
                sumBlue += copy[i - 1][j - 1].rgbtBlue;
            }

            if (i >= 1 && j >= 0)
            {
                count += 1.0;
                sumRed += copy[i - 1][j].rgbtRed;
                sumGreen += copy[i - 1][j].rgbtGreen;
                sumBlue += copy[i - 1][j].rgbtBlue;
            }

            if (i >= 1 && (j + 1 < width))
            {
                count += 1.0;
                sumRed += copy[i - 1][j + 1].rgbtRed;
                sumGreen += copy[i - 1][j + 1].rgbtGreen;
                sumBlue += copy[i - 1][j + 1].rgbtBlue;
            }

            if (i >= 0 && j >= 1)
            {
                count += 1.0;
                sumRed += copy[i][j - 1].rgbtRed;
                sumGreen += copy[i][j - 1].rgbtGreen;
                sumBlue += copy[i][j - 1].rgbtBlue;
            }

            if (i >= 0 && (j + 1 < width))
            {
                count += 1.0;
                sumRed += copy[i][j + 1].rgbtRed;
                sumGreen += copy[i][j + 1].rgbtGreen;
                sumBlue += copy[i][j + 1].rgbtBlue;
            }

            if ((i + 1 < height) && j >= 1)
            {
                count += 1.0;
                sumRed += copy[i + 1][j - 1].rgbtRed;
                sumGreen += copy[i + 1][j - 1].rgbtGreen;
                sumBlue += copy[i + 1][j - 1].rgbtBlue;
            }

            if ((i + 1 < height) && j >= 0)
            {
                count += 1.0;
                sumRed += copy[i + 1][j].rgbtRed;
                sumGreen += copy[i + 1][j].rgbtGreen;
                sumBlue += copy[i + 1][j].rgbtBlue;
            }

            if ((i + 1 < height) && (j + 1 < width))
            {
                count += 1.0;
                sumRed += copy[i + 1][j + 1].rgbtRed;
                sumGreen += copy[i + 1][j + 1].rgbtGreen;
                sumBlue += copy[i + 1][j + 1].rgbtBlue;
            }

            int blurRed = round((float) sumRed / count);
            int blurGreen = round((float) sumGreen / count);
            int blurBlue = round((float) sumBlue / count);

            // Blur the pixel/update the image BMP with the average RGB values
            image[i][j].rgbtRed = blurRed;
            image[i][j].rgbtGreen = blurGreen;
            image[i][j].rgbtBlue = blurBlue;
        }
    }
    return;
}
