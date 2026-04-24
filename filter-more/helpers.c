#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdio.h>

int Cap(int n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel and take the RGB values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int R = image[i][j].rgbtRed;
            int G = image[i][j].rgbtGreen;
            int B = image[i][j].rgbtBlue;

            // Calculate the average of the RGB values for a shade of gray
            int average = round((R + G + B) / 3.0);

            // Update the RGB values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over the pixels of first half of each row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap each pixel with its corresponding pixel in the second half
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
    // Iterate over each pixel and make a copy of the file for later use
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Calculate the average surrounding RGB values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int *p = &count;
            int sum_R = 0, sum_G = 0, sum_B = 0;
            int *p_sumR = &sum_R, *p_sumG = &sum_G, *p_sumB = &sum_B;

            // Top edge
            if ((i == 0) && (j > 0) && (j < width - 1))
            {
                *p = 6;
                for (int ni = 0; ni <= 1; ni++)
                {
                    for (int nj = -1; nj <= 1; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }
            // Bottom edge
            else if ((i == height - 1) && (j > 0) && (j < width - 1))
            {
                *p = 6;
                for (int ni = -1; ni <= 0; ni++)
                {
                    for (int nj = -1; nj <= 1; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }
            // Left edge
            else if ((j == 0) && (i > 0) && (i < height - 1))
            {
                *p = 6;
                for (int ni = -1; ni <= 1; ni++)
                {
                    for (int nj = 0; nj <= 1; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }
            // Right edge
            else if ((j == width - 1) && (i > 0) && (i < height - 1))
            {
                *p = 6;
                for (int ni = -1; ni <= 1; ni++)
                {
                    for (int nj = -1; nj <= 0; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }
            // Top left corner
            else if ((i == 0) && (j == 0))
            {
                *p = 4;
                for (int ni = 0; ni <= 1; ni++)
                {
                    for (int nj = 0; nj <= 1; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }
            // Bottom right corner
            else if ((i == height - 1) && (j == width - 1))
            {
                *p = 4;
                for (int ni = -1; ni <= 0; ni++)
                {
                    for (int nj = -1; nj <= 0; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }
            // Top right corner
            else if ((i == 0) && (j == width - 1))
            {
                *p = 4;
                for (int ni = 0; ni <= 1; ni++)
                {
                    for (int nj = -1; nj <= 0; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }
            // Bottom left corner
            else if ((i == height - 1) && (j == 0))
            {
                *p = 4;
                for (int ni = -1; ni <= 0; ni++)
                {
                    for (int nj = 0; nj <= 1; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }
            // Center pixels that form 3x3 grid
            else if ((i > 0) && (i < height - 1) && (j > 0) && (j < width - 1))
            {
                *p = 9;
                for (int ni = -1; ni <= 1; ni++)
                {
                    for (int nj = -1; nj <= 1; nj++)
                    {
                        int pi = i + ni, pj = j + nj;
                        sum_R += copy[pi][pj].rgbtRed;
                        sum_G += copy[pi][pj].rgbtGreen;
                        sum_B += copy[pi][pj].rgbtBlue;
                    }
                }
                *p_sumR = sum_R, *p_sumG = sum_G, *p_sumB = sum_B;
            }

            // Update the image
            int new_R = round(sum_R / (float) count);
            int new_G = round(sum_G / (float) count);
            int new_B = round(sum_B / (float) count);

            image[i][j].rgbtRed = new_R;
            image[i][j].rgbtGreen = new_G;
            image[i][j].rgbtBlue = new_B;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over every pixel of image and create a copy for later use
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int Gx_R, Gx_G, Gx_B, Gy_R, Gy_G, Gy_B;

    int Sobel_gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Sobel_gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Gx_R = 0, Gx_G = 0, Gx_B = 0;
            Gy_R = 0, Gy_G = 0, Gy_B = 0;

            for (int ni = -1; ni <= 1; ni++)
            {
                for (int nj = -1; nj <= 1; nj++)
                {
                    int pi = i + ni, pj = j + nj;

                    if ((pi < 0) || (pi >= height) || (pj < 0) || (pj >= width))
                    {
                        continue;
                    }

                    Gx_R += copy[pi][pj].rgbtRed * Sobel_gx[ni + 1][nj + 1];
                    Gx_G += copy[pi][pj].rgbtGreen * Sobel_gx[ni + 1][nj + 1];
                    Gx_B += copy[pi][pj].rgbtBlue * Sobel_gx[ni + 1][nj + 1];
                    Gy_R += copy[pi][pj].rgbtRed * Sobel_gy[ni + 1][nj + 1];
                    Gy_G += copy[pi][pj].rgbtGreen * Sobel_gy[ni + 1][nj + 1];
                    Gy_B += copy[pi][pj].rgbtBlue * Sobel_gy[ni + 1][nj + 1];
                }
            }

            int new_Red = Cap((int) round(sqrt(Gx_R * Gx_R + Gy_R * Gy_R)));
            int new_Green = Cap((int) round(sqrt(Gx_G * Gx_G + Gy_G * Gy_G)));
            int new_Blue = Cap((int) round(sqrt(Gx_B * Gx_B + Gy_B * Gy_B)));

            image[i][j].rgbtRed = new_Red;
            image[i][j].rgbtGreen = new_Green;
            image[i][j].rgbtBlue = new_Blue;
        }
    }
    return;
}

int Cap(int n)
{
    int m = 255;
    if (n > m)
    {
        return m;
    }
    else
    {
        return n;
    }
}
