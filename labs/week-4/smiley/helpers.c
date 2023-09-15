#include "helpers.h"

// Colorizes black pixels to purple
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Checks if pixel is black
            if (image[j][i].rgbtBlue == 0x00 && image[j][i].rgbtGreen == 0x00 && image[j][i].rgbtRed == 0x00)
            {
                // Change pixels to purple
                image[j][i].rgbtBlue = 0x4b;
                image[j][i].rgbtGreen = 0x00;
                image[j][i].rgbtRed = 0x82;
            }
        }
    }
}
