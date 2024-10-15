#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    float average;
    for (int i = 0; i < height; i++)
    {
        average = 0.0;
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            // Update pixel values
            image[i][j].rgbtRed = (int) round(average);
            image[i][j].rgbtGreen = (int) round(average);
            image[i][j].rgbtBlue = (int) round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    int originalRed, originalGreen, originalBlue;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            // Update pixel with sepia values
            if (sepiaRed > 255)
                image[i][j].rgbtRed = 255;
            else
                image[i][j].rgbtRed = (int) round(sepiaRed);

            if (sepiaGreen > 255)
                image[i][j].rgbtGreen = 255;
            else
                image[i][j].rgbtGreen = (int) round(sepiaGreen);

            if (sepiaBlue > 255)
                image[i][j].rgbtBlue = 255;
            else
                image[i][j].rgbtBlue = (int) round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
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

    int sumRed, sumGreen, sumBlue;
    int count;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumRed = 0;
            sumGreen = 0;
            sumBlue = 0;
            count = 0;
            for (int r = i - 1; r <= i + 1; r++)
            {
                for (int c = j - 1; c <= j + 1; c++)
                {
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        sumRed += copy[r][c].rgbtRed;
                        sumGreen += copy[r][c].rgbtGreen;
                        sumBlue += copy[r][c].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = (int) round((float) sumRed / count);
            image[i][j].rgbtGreen = (int) round((float) sumGreen / count);
            image[i][j].rgbtBlue = (int) round((float) sumBlue / count);
        }
    }
    return;
}
