#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            float gray = (round(red) + round(green) + round(blue)) / 3;
            gray = round(gray);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sr = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            float sg = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            float sb = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);
            int r = round(sr);
            int g = round(sg);
            int b = round(sb);
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b > 255)
            {
                b = 255;
            }
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int tempr = 0;
        int tempg = 0;
        int tempb = 0;
        int middle = floor(width / 2);
        for (int j = 0; j < middle; j++)
        {
            tempr = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed;
            image[i][width - (j + 1)].rgbtRed = tempr;

            tempg = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][width - (j + 1)].rgbtGreen = tempg;

            tempb = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;
            image[i][width - (j + 1)].rgbtBlue = tempb;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image2[i][j].rgbtRed = image[i][j].rgbtRed;
            image2[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image2[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    float reds = 0;
    float greens = 0;
    float blues = 0;
    int cc;
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            if (i - 1 == -1)
            {
                if (j - 1 == -1)
                {
                    cc = 1;
                } 
                else if (j + 1 == width)
                {
                    cc = 3;
                } 
                else
                {
                    cc = 2;
                }
            } 
            else if (i + 1 == height)
            {
                if (j - 1 == -1)
                {
                    cc = 7;
                } 
                else if (j + 1 == width)
                {
                    cc = 9;
                } 
                else
                {
                    cc = 8;
                }
            } 
            else
            {
                if (j - 1 == -1)
                {
                    cc = 4;
                } 
                else if (j + 1 == width)
                {
                    cc = 6;
                } 
                else
                {
                    cc = 5;
                }
            }

            if (cc == 1)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i + 1][j].rgbtRed) + round(image2[i][j + 1].rgbtRed) +
                        round(image2[i + 1][j + 1].rgbtRed)) / 4;
                reds = round(reds);
                image[i][j].rgbtRed = reds;

                greens = (round(image2[i][j].rgbtGreen) + round(image2[i + 1][j].rgbtGreen) + round(image2[i][j + 1].rgbtGreen) +
                          round(image2[i + 1][j + 1].rgbtGreen)) / 4;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;

                blues = (round(image2[i][j].rgbtBlue) + round(image2[i + 1][j].rgbtBlue) + round(image2[i][j + 1].rgbtBlue) +
                         round(image2[i + 1][j + 1].rgbtBlue)) / 4;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }

            if (cc == 3)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i + 1][j].rgbtRed) + round(image2[i][j - 1].rgbtRed) +
                        round(image2[i + 1][j - 1].rgbtRed)) / 4;
                reds = round(reds);
                image[i][j].rgbtRed = reds;

                greens = (round(image2[i][j].rgbtGreen) + round(image2[i + 1][j].rgbtGreen) + round(image2[i][j - 1].rgbtGreen) +
                          round(image2[i + 1][j - 1].rgbtGreen)) / 4;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;

                blues = (round(image2[i][j].rgbtBlue) + round(image2[i + 1][j].rgbtBlue) + round(image2[i][j - 1].rgbtBlue) +
                         round(image2[i + 1][j - 1].rgbtBlue)) / 4;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }

            if (cc == 7)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i - 1][j].rgbtRed) + round(image2[i][j + 1].rgbtRed) +
                        round(image2[i - 1][j + 1].rgbtRed)) / 4;
                reds = round(reds);
                image[i][j].rgbtRed = reds;

                greens = (round(image2[i][j].rgbtGreen) + round(image2[i - 1][j].rgbtGreen) + round(image2[i][j + 1].rgbtGreen) +
                          round(image2[i - 1][j + 1].rgbtGreen)) / 4;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;

                blues = (round(image2[i][j].rgbtBlue) + round(image2[i - 1][j].rgbtBlue) + round(image2[i][j + 1].rgbtBlue) +
                         round(image2[i - 1][j + 1].rgbtBlue)) / 4;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }

            if (cc == 9)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i - 1][j].rgbtRed) + round(image2[i][j - 1].rgbtRed) +
                        round(image2[i - 1][j - 1].rgbtRed)) / 4;
                reds = round(reds);
                image[i][j].rgbtRed = reds;

                greens = (round(image2[i][j].rgbtGreen) + round(image2[i - 1][j].rgbtGreen) + round(image2[i][j - 1].rgbtGreen) +
                          round(image2[i - 1][j - 1].rgbtGreen)) / 4;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;

                blues = (round(image2[i][j].rgbtBlue) + round(image2[i - 1][j].rgbtBlue) + round(image2[i][j - 1].rgbtBlue) +
                         round(image2[i - 1][j - 1].rgbtBlue)) / 4;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }

            if (cc == 2)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i + 1][j].rgbtRed) + round(image2[i][j + 1].rgbtRed) +
                        round(image2[i + 1][j + 1].rgbtRed) + round(image2[i + 1][j - 1].rgbtRed) + round(image2[i][j - 1].rgbtRed)) / 6;
                reds = round(reds);
                image[i][j].rgbtRed = reds;

                greens = (round(image2[i][j].rgbtGreen) + round(image2[i + 1][j].rgbtGreen) + round(image2[i][j + 1].rgbtGreen) +
                          round(image2[i + 1][j + 1].rgbtGreen) + round(image2[i + 1][j - 1].rgbtGreen) + round(image2[i][j - 1].rgbtGreen)) / 6;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;

                blues = (round(image2[i][j].rgbtBlue) + round(image2[i + 1][j].rgbtBlue) + round(image2[i][j + 1].rgbtBlue) +
                         round(image2[i + 1][j + 1].rgbtBlue) + round(image2[i + 1][j - 1].rgbtBlue) + round(image2[i][j - 1].rgbtBlue)) / 6;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }
            
            if (cc == 4)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i + 1][j].rgbtRed) + round(image2[i][j + 1].rgbtRed) +
                        round(image2[i + 1][j + 1].rgbtRed) + round(image2[i - 1][j].rgbtRed) + round(image2[i - 1][j + 1].rgbtRed)) / 6;
                reds = round(reds);
                image[i][j].rgbtRed = reds;

                greens = (round(image2[i][j].rgbtGreen) + round(image2[i + 1][j].rgbtGreen) + round(image2[i][j + 1].rgbtGreen) +
                          round(image2[i + 1][j + 1].rgbtGreen) + round(image2[i - 1][j].rgbtGreen) + round(image2[i - 1][j + 1].rgbtGreen)) / 6;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;

                blues = (round(image2[i][j].rgbtBlue) + round(image2[i + 1][j].rgbtBlue) + round(image2[i][j + 1].rgbtBlue) +
                         round(image2[i + 1][j + 1].rgbtBlue) + round(image2[i - 1][j].rgbtBlue) + round(image2[i - 1][j + 1].rgbtBlue)) / 6;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }
            
            if (cc == 6)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i + 1][j].rgbtRed) + round(image2[i - 1][j].rgbtRed) +
                        round(image2[i][j - 1].rgbtRed) + round(image2[i + 1][j - 1].rgbtRed) + round(image2[i - 1][j - 1].rgbtRed)) / 6;
                reds = round(reds);
                image[i][j].rgbtRed = reds;

                greens = (round(image2[i][j].rgbtGreen) + round(image2[i + 1][j].rgbtGreen) + round(image2[i - 1][j].rgbtGreen) +
                          round(image2[i][j - 1].rgbtGreen) + round(image2[i + 1][j - 1].rgbtGreen) + round(image2[i - 1][j - 1].rgbtGreen)) / 6;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;

                blues = (round(image2[i][j].rgbtBlue) + round(image2[i + 1][j].rgbtBlue) + round(image2[i - 1][j].rgbtBlue) +
                         round(image2[i][j - 1].rgbtBlue) + round(image2[i + 1][j - 1].rgbtBlue) + round(image2[i - 1][j - 1].rgbtBlue)) / 6;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }
            
            if (cc == 8)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i][j - 1].rgbtRed) + round(image2[i][j + 1].rgbtRed) +
                        round(image2[i - 1][j].rgbtRed) + round(image2[i - 1][j - 1].rgbtRed) + round(image2[i - 1][j + 1].rgbtRed)) / 6;
                reds = round(reds);
                image[i][j].rgbtRed = reds;

                greens = (round(image2[i][j].rgbtGreen) + round(image2[i][j - 1].rgbtGreen) + round(image2[i][j + 1].rgbtGreen) +
                          round(image2[i - 1][j].rgbtGreen) + round(image2[i - 1][j - 1].rgbtGreen) + round(image2[i - 1][j + 1].rgbtGreen)) / 6;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;

                blues = (round(image2[i][j].rgbtBlue) + round(image2[i][j - 1].rgbtBlue) + round(image2[i][j + 1].rgbtBlue) +
                         round(image2[i - 1][j].rgbtBlue) + round(image2[i - 1][j - 1].rgbtBlue) + round(image2[i - 1][j + 1].rgbtBlue)) / 6;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }
            
            if (cc == 5)
            {
                reds = (round(image2[i][j].rgbtRed) + round(image2[i][j - 1].rgbtRed) + round(image2[i][j + 1].rgbtRed) +
                        round(image2[i - 1][j].rgbtRed) + round(image2[i - 1][j - 1].rgbtRed) + round(image2[i - 1][j + 1].rgbtRed) +
                        round(image2[i + 1][j].rgbtRed) + round(image2[i + 1][j - 1].rgbtRed) + round(image2[i + 1][j + 1].rgbtRed)) / 9;
                reds = round(reds);
                image[i][j].rgbtRed = reds;
                
                greens = (round(image2[i][j].rgbtGreen) + round(image2[i][j - 1].rgbtGreen) + round(image2[i][j + 1].rgbtGreen) +
                          round(image2[i - 1][j].rgbtGreen) + round(image2[i - 1][j - 1].rgbtGreen) + round(image2[i - 1][j + 1].rgbtGreen) +
                          round(image2[i + 1][j].rgbtGreen) + round(image2[i + 1][j - 1].rgbtGreen) + round(image2[i + 1][j + 1].rgbtGreen)) / 9;
                greens = round(greens);
                image[i][j].rgbtGreen = greens;
                
                blues = (round(image2[i][j].rgbtBlue) + round(image2[i][j - 1].rgbtBlue) + round(image2[i][j + 1].rgbtBlue) +
                         round(image2[i - 1][j].rgbtBlue) + round(image2[i - 1][j - 1].rgbtBlue) + round(image2[i - 1][j + 1].rgbtBlue) +
                         round(image2[i + 1][j].rgbtBlue) + round(image2[i + 1][j - 1].rgbtBlue) + round(image2[i + 1][j + 1].rgbtBlue)) / 9;
                blues = round(blues);
                image[i][j].rgbtBlue = blues;
            }
        }
    }
    return;
}
