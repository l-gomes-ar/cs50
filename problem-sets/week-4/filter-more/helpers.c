#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average rbgt value and add it to each value rgbt.Red, Green, and Blue
            int average = round(((int)image[i][j].rgbtRed + (int)image[i][j].rgbtGreen + (int)image[i][j].rgbtBlue) / 3.0);

            if (average < 0)
            {
                average = 0;
            }
            else if (average > 255)
            {
                average = 255;
            }

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
    // Initialie variable for swapping
    RGBTRIPLE tmp;

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        // Iterate through only half of width minus 1 (as it is 0 indexed)
        for (int j = 0; j <= (width - 1) / 2; j++)
        {
            // Swap pixels horizontally
            tmp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create new array for image
    RGBTRIPLE new_image[height][width];

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create variable for average
            RGBTRIPLE average;

            // Left edge case
            if (j == 0)
            {
                // Top left corner case
                if (i == 0)
                {
                    // Create variables for pixels in the grid and average
                    RGBTRIPLE centre = image[i][j];
                    RGBTRIPLE right = image[i][j + 1];
                    RGBTRIPLE bottom = image[i + 1][j];
                    RGBTRIPLE bottom_right = image[i + 1][j + 1];

                    int average_rgbtRed = round((centre.rgbtRed + right.rgbtRed + bottom.rgbtRed + bottom_right.rgbtRed) / 4.0);
                    int average_rgbtGreen = round((centre.rgbtGreen + right.rgbtGreen + bottom.rgbtGreen + bottom_right.rgbtGreen) / 4.0);
                    int average_rgbtBlue = round((centre.rgbtBlue + right.rgbtBlue + bottom.rgbtBlue + bottom_right.rgbtBlue) / 4.0);

                    average.rgbtRed = average_rgbtRed;
                    average.rgbtGreen = average_rgbtGreen;
                    average.rgbtBlue = average_rgbtBlue;

                    new_image[i][j] = average;
                }
                // Bottom left corner case
                else if (i == height - 1)
                {
                    // Create variables for pixels in the grid and average
                    RGBTRIPLE top = image[i - 1][j];
                    RGBTRIPLE top_right = image[i - 1][j + 1];
                    RGBTRIPLE centre = image[i][j];
                    RGBTRIPLE right = image[i][j + 1];

                    int average_rgbtRed = round((top.rgbtRed + top_right.rgbtRed + centre.rgbtRed + right.rgbtRed) / 4.0);
                    int average_rgbtGreen = round((top.rgbtGreen + top_right.rgbtGreen + centre.rgbtGreen + right.rgbtGreen) / 4.0);
                    int average_rgbtBlue = round((top.rgbtBlue + top_right.rgbtBlue + centre.rgbtBlue + right.rgbtBlue) / 4.0);

                    average.rgbtRed = average_rgbtRed;
                    average.rgbtGreen = average_rgbtGreen;
                    average.rgbtBlue = average_rgbtBlue;

                    new_image[i][j] = average;
                }
                // Normal left edge
                else
                {
                    // Create variables for pixels in the grid and average
                    RGBTRIPLE top = image[i - 1][j];
                    RGBTRIPLE top_right = image[i - 1][j + 1];
                    RGBTRIPLE centre = image[i][j];
                    RGBTRIPLE right = image[i][j + 1];
                    RGBTRIPLE bottom = image[i + 1][j];
                    RGBTRIPLE bottom_right = image[i + 1][j + 1];

                    int average_rgbtRed = round((top.rgbtRed + top_right.rgbtRed + centre.rgbtRed + right.rgbtRed + bottom.rgbtRed +
                                                 bottom_right.rgbtRed) / 6.0);
                    int average_rgbtGreen = round((top.rgbtGreen + top_right.rgbtGreen + centre.rgbtGreen + right.rgbtGreen + bottom.rgbtGreen +
                                                   bottom_right.rgbtGreen) / 6.0);
                    int average_rgbtBlue = round((top.rgbtBlue + top_right.rgbtBlue + centre.rgbtBlue + right.rgbtBlue + bottom.rgbtBlue +
                                                  bottom_right.rgbtBlue) / 6.0);

                    average.rgbtRed = average_rgbtRed;
                    average.rgbtGreen = average_rgbtGreen;
                    average.rgbtBlue = average_rgbtBlue;

                    new_image[i][j] = average;
                }
            }
            // Right edge case
            else if (j == width - 1)
            {
                // Top right corner case
                if (i == 0)
                {
                    // Create variables for pixels in the grid
                    RGBTRIPLE left = image[i][j - 1];
                    RGBTRIPLE centre = image[i][j];
                    RGBTRIPLE bottom_left = image[i + 1][j - 1];
                    RGBTRIPLE bottom = image[i + 1][j];

                    int average_rgbtRed = round((left.rgbtRed + centre.rgbtRed + bottom_left.rgbtRed + bottom.rgbtRed) / 4.0);
                    int average_rgbtGreen = round((left.rgbtGreen + centre.rgbtGreen + bottom_left.rgbtGreen + bottom.rgbtGreen) / 4.0);
                    int average_rgbtBlue = round((left.rgbtBlue + centre.rgbtBlue + bottom_left.rgbtBlue + bottom.rgbtBlue) / 4.0);

                    average.rgbtRed = average_rgbtRed;
                    average.rgbtGreen = average_rgbtGreen;
                    average.rgbtBlue = average_rgbtBlue;

                    new_image[i][j] = average;
                }
                // Bottom right corner case
                else if (i == height - 1)
                {
                    // Create variables for pixels in the grid
                    RGBTRIPLE top_left = image[i - 1][j - 1];
                    RGBTRIPLE top = image[i - 1][j];
                    RGBTRIPLE left = image[i][j - 1];
                    RGBTRIPLE centre = image[i][j];

                    int average_rgbtRed = round((top_left.rgbtRed + top.rgbtRed + left.rgbtRed + centre.rgbtRed) / 4.0);
                    int average_rgbtGreen = round((top_left.rgbtGreen + top.rgbtGreen + left.rgbtGreen + centre.rgbtGreen) / 4.0);
                    int average_rgbtBlue = round((top_left.rgbtBlue + top.rgbtBlue + left.rgbtBlue + centre.rgbtBlue) / 4.0);

                    average.rgbtRed = average_rgbtRed;
                    average.rgbtGreen = average_rgbtGreen;
                    average.rgbtBlue = average_rgbtBlue;

                    new_image[i][j] = average;
                }
                // Normal right edge
                else
                {
                    // Create variables for pixels in the grid
                    RGBTRIPLE top_left = image[i - 1][j - 1];
                    RGBTRIPLE top = image[i - 1][j];
                    RGBTRIPLE left = image[i][j - 1];
                    RGBTRIPLE centre = image[i][j];
                    RGBTRIPLE bottom_left = image[i + 1][j - 1];
                    RGBTRIPLE bottom = image[i + 1][j];

                    int average_rgbtRed = round((top_left.rgbtRed + top.rgbtRed + left.rgbtRed + centre.rgbtRed + bottom_left.rgbtRed +
                                                 bottom.rgbtRed) / 6.0);
                    int average_rgbtGreen = round((top_left.rgbtGreen + top.rgbtGreen + left.rgbtGreen + centre.rgbtGreen + bottom_left.rgbtGreen +
                                                   bottom.rgbtGreen) / 6.0);
                    int average_rgbtBlue = round((top_left.rgbtBlue + top.rgbtBlue + left.rgbtBlue + centre.rgbtBlue + bottom_left.rgbtBlue +
                                                  bottom.rgbtBlue) / 6.0);

                    average.rgbtRed = average_rgbtRed;
                    average.rgbtGreen = average_rgbtGreen;
                    average.rgbtBlue = average_rgbtBlue;

                    new_image[i][j] = average;
                }
            }
            // Normal Top edge
            else if (i == 0 && j != 0 && j != width - 1)
            {
                // Create variables for pixels in the grid
                RGBTRIPLE left = image[i][j - 1];
                RGBTRIPLE centre = image[i][j];
                RGBTRIPLE right = image[i][j + 1];
                RGBTRIPLE bottom_left = image[i + 1][j - 1];
                RGBTRIPLE bottom = image[i + 1][j];
                RGBTRIPLE bottom_right = image[i + 1][j + 1];

                int average_rgbtRed = round((left.rgbtRed + centre.rgbtRed + right.rgbtRed + bottom_left.rgbtRed + bottom.rgbtRed +
                                             bottom_right.rgbtRed) / 6.0);
                int average_rgbtGreen = round((left.rgbtGreen + centre.rgbtGreen + right.rgbtGreen + bottom_left.rgbtGreen + bottom.rgbtGreen +
                                               bottom_right.rgbtGreen) / 6.0);
                int average_rgbtBlue = round((left.rgbtBlue + centre.rgbtBlue + right.rgbtBlue + bottom_left.rgbtBlue + bottom.rgbtBlue +
                                              bottom_right.rgbtBlue) / 6.0);

                average.rgbtRed = average_rgbtRed;
                average.rgbtGreen = average_rgbtGreen;
                average.rgbtBlue = average_rgbtBlue;

                new_image[i][j] = average;
            }
            // Normal bottom edge
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                // Create variables for pixels in the grid
                RGBTRIPLE left = image[i][j - 1];
                RGBTRIPLE centre = image[i][j];
                RGBTRIPLE right = image[i][j + 1];
                RGBTRIPLE top_left = image[i - 1][j - 1];
                RGBTRIPLE top = image[i - 1][j];
                RGBTRIPLE top_right = image[i - 1][j + 1];

                int average_rgbtRed = round((top_left.rgbtRed + top.rgbtRed + top_right.rgbtRed + left.rgbtRed + centre.rgbtRed + right.rgbtRed) /
                                            6.0);
                int average_rgbtGreen = round((top_left.rgbtGreen + top.rgbtGreen + top_right.rgbtGreen + left.rgbtGreen + centre.rgbtGreen +
                                               right.rgbtGreen) / 6.0);
                int average_rgbtBlue = round((top_left.rgbtBlue + top.rgbtBlue + top_right.rgbtBlue + left.rgbtBlue + centre.rgbtBlue +
                                              right.rgbtBlue) / 6.0);

                average.rgbtRed = average_rgbtRed;
                average.rgbtGreen = average_rgbtGreen;
                average.rgbtBlue = average_rgbtBlue;

                new_image[i][j] = average;
            }
            // All other values
            else
            {
                // Create variables for pixels in the grid
                RGBTRIPLE top_left = image[i - 1][j - 1];
                RGBTRIPLE top = image[i - 1][j];
                RGBTRIPLE top_right = image[i - 1][j + 1];
                RGBTRIPLE left = image[i][j - 1];
                RGBTRIPLE centre = image[i][j];
                RGBTRIPLE right = image[i][j + 1];
                RGBTRIPLE bottom_left = image[i + 1][j - 1];
                RGBTRIPLE bottom = image[i + 1][j];
                RGBTRIPLE bottom_right = image[i + 1][j + 1];

                // Calculate the average amount of red, green, and blue of all the ORIGINAL pixels colours around the centre pixel, including itself
                int average_rgbtRed = round((top_left.rgbtRed + top.rgbtRed + top_right.rgbtRed + left.rgbtRed +
                                             centre.rgbtRed + right.rgbtRed + bottom_left.rgbtRed + bottom.rgbtRed + bottom_right.rgbtRed) / 9.0);
                int average_rgbtGreen = round((top_left.rgbtGreen + top.rgbtGreen + top_right.rgbtGreen + left.rgbtGreen +
                                               centre.rgbtGreen + right.rgbtGreen + bottom_left.rgbtGreen + bottom.rgbtGreen + bottom_right.rgbtGreen) / 9.0);
                int average_rgbtBlue = round((top_left.rgbtBlue + top.rgbtBlue + top_right.rgbtBlue + left.rgbtBlue +
                                              centre.rgbtBlue + right.rgbtBlue + bottom_left.rgbtBlue + bottom.rgbtBlue + bottom_right.rgbtBlue) / 9.0);

                average.rgbtRed = average_rgbtRed;
                average.rgbtGreen = average_rgbtGreen;
                average.rgbtBlue = average_rgbtBlue;

                new_image[i][j] = average;
            }
        }
    }

    // Update image with values from new_image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create new array for image
    RGBTRIPLE new_image[height][width];

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Set all pixel values for 0
            RGBTRIPLE top_left;
            top_left.rgbtRed = 0;
            top_left.rgbtGreen = 0;
            top_left.rgbtBlue = 0;

            RGBTRIPLE top;
            top.rgbtRed = 0;
            top.rgbtGreen = 0;
            top.rgbtBlue = 0;

            RGBTRIPLE top_right;
            top_right.rgbtRed = 0;
            top_right.rgbtGreen = 0;
            top_right.rgbtBlue = 0;

            RGBTRIPLE left;
            left.rgbtRed = 0;
            left.rgbtGreen = 0;
            left.rgbtBlue = 0;

            RGBTRIPLE centre;
            centre.rgbtRed = 0;
            centre.rgbtGreen = 0;
            centre.rgbtBlue = 0;

            RGBTRIPLE right;
            right.rgbtRed = 0;
            right.rgbtGreen = 0;
            right.rgbtBlue = 0;

            RGBTRIPLE bottom_left;
            bottom_left.rgbtRed = 0;
            bottom_left.rgbtGreen = 0;
            bottom_left.rgbtBlue = 0;

            RGBTRIPLE bottom;
            bottom.rgbtRed = 0;
            bottom.rgbtGreen = 0;
            bottom.rgbtBlue = 0;

            RGBTRIPLE bottom_right;
            bottom_right.rgbtRed = 0;
            bottom_right.rgbtGreen = 0;
            bottom_right.rgbtBlue = 0;

            // Left edge case
            if (j == 0)
            {
                // Top left corner case
                if (i == 0)
                {
                    // Create variables for pixels in the grid and average
                    centre = image[i][j];
                    right = image[i][j + 1];
                    bottom = image[i + 1][j];
                    bottom_right = image[i + 1][j + 1];
                }
                // Bottom left corner case
                else if (i == height - 1)
                {
                    // Create variables for pixels in the grid and average
                    top = image[i - 1][j];
                    top_right = image[i - 1][j + 1];
                    centre = image[i][j];
                    right = image[i][j + 1];
                }
                // Normal left edge
                else
                {
                    // Create variables for pixels in the grid and average
                    top = image[i - 1][j];
                    top_right = image[i - 1][j + 1];
                    centre = image[i][j];
                    right = image[i][j + 1];
                    bottom = image[i + 1][j];
                    bottom_right = image[i + 1][j + 1];
                }
            }
            // Right edge case
            else if (j == width - 1)
            {
                // Top right corner case
                if (i == 0)
                {
                    // Create variables for pixels in the grid
                    left = image[i][j - 1];
                    centre = image[i][j];
                    bottom_left = image[i + 1][j - 1];
                    bottom = image[i + 1][j];
                }
                // Bottom right corner case
                else if (i == height - 1)
                {
                    // Create variables for pixels in the grid
                    top_left = image[i - 1][j - 1];
                    top = image[i - 1][j];
                    left = image[i][j - 1];
                    centre = image[i][j];
                }
                // Normal right edge
                else
                {
                    // Create variables for pixels in the grid
                    top_left = image[i - 1][j - 1];
                    top = image[i - 1][j];
                    left = image[i][j - 1];
                    centre = image[i][j];
                    bottom_left = image[i + 1][j - 1];
                    bottom = image[i + 1][j];
                }
            }
            // Normal Top edge
            else if (i == 0 && j != 0 && j != width - 1)
            {
                // Create variables for pixels in the grid
                left = image[i][j - 1];
                centre = image[i][j];
                right = image[i][j + 1];
                bottom_left = image[i + 1][j - 1];
                bottom = image[i + 1][j];
                bottom_right = image[i + 1][j + 1];
            }
            // Normal bottom edge
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                // Create variables for pixels in the grid
                left = image[i][j - 1];
                centre = image[i][j];
                right = image[i][j + 1];
                top_left = image[i - 1][j - 1];
                top = image[i - 1][j];
                top_right = image[i - 1][j + 1];
            }
            // All other values
            else
            {
                // Create variables for pixels in the grid
                top_left = image[i - 1][j - 1];
                top = image[i - 1][j];
                top_right = image[i - 1][j + 1];
                left = image[i][j - 1];
                centre = image[i][j];
                right = image[i][j + 1];
                bottom_left = image[i + 1][j - 1];
                bottom = image[i + 1][j];
                bottom_right = image[i + 1][j + 1];
            }

            // Create variables for sobel_final algorithm
            RGBTRIPLE sobel_final;

            // Calculate gx
            int gx_rgbtRed = ((int)top_left.rgbtRed * -1) + ((int)top.rgbtRed * 0) + ((int)top_right.rgbtRed * 1) +
                             ((int)left.rgbtRed * -2) + ((int)centre.rgbtRed * 0) + ((int)right.rgbtRed * 2) +
                             ((int)bottom_left.rgbtRed * -1) + ((int)bottom.rgbtRed * 0) +
                             ((int)bottom_right.rgbtRed * 1);
            int gx_rgbtGreen = ((int)top_left.rgbtGreen * -1) + ((int)top.rgbtGreen * 0) + ((int)top_right.rgbtGreen * 1) +
                               ((int)left.rgbtGreen * -2) + ((int)centre.rgbtGreen * 0) + ((int)right.rgbtGreen * 2) +
                               ((int)bottom_left.rgbtGreen * -1) + ((int)bottom.rgbtGreen * 0) +
                               ((int)bottom_right.rgbtGreen * 1);
            int gx_rgbtBlue = ((int)top_left.rgbtBlue * -1) + ((int)top.rgbtBlue * 0) + ((int)top_right.rgbtBlue * 1) +
                              ((int)left.rgbtBlue * -2) + ((int)centre.rgbtBlue * 0) + ((int)right.rgbtBlue * 2) +
                              ((int)bottom_left.rgbtBlue * -1) + ((int)bottom.rgbtBlue * 0) +
                              ((int)bottom_right.rgbtBlue * 1);

            // Calculate gy
            int gy_rgbtRed = ((int)top_left.rgbtRed * -1) + ((int)top.rgbtRed * -2) + ((int)top_right.rgbtRed * -1) +
                             ((int)left.rgbtRed * 0) + ((int)centre.rgbtRed * 0) + ((int)right.rgbtRed * 0) +
                             ((int)bottom_left.rgbtRed * 1) + ((int)bottom.rgbtRed * 2) + ((int)bottom_right.rgbtRed * 1);
            int gy_rgbtGreen = ((int)top_left.rgbtGreen * -1) + ((int)top.rgbtGreen * -2) + ((int)top_right.rgbtGreen * -1) +
                               ((int)left.rgbtGreen * 0) + ((int)centre.rgbtGreen * 0) + ((int)right.rgbtGreen * 0) +
                               ((int)bottom_left.rgbtGreen * 1) + ((int)bottom.rgbtGreen * 2) + ((int)bottom_right.rgbtGreen * 1);
            int gy_rgbtBlue = ((int)top_left.rgbtBlue * -1) + ((int)top.rgbtBlue * -2) + ((int)top_right.rgbtBlue * -1) +
                              ((int)left.rgbtBlue * 0) + ((int)centre.rgbtBlue * 0) + ((int)right.rgbtBlue * 0) +
                              ((int)bottom_left.rgbtBlue * 1) + ((int)bottom.rgbtBlue * 2) + ((int)bottom_right.rgbtBlue * 1);

            // Compute each new channel value as the square root of Gx^2 + Gy^2 based of the original image
            int sobel_final_rgbtRed = round(sqrt(pow((double)gx_rgbtRed, (double)2) + (pow((double)gy_rgbtRed, (double)2))));
            int sobel_final_rgbtGreen = round(sqrt(pow((double)gx_rgbtGreen, (double)2) + (pow((double)gy_rgbtGreen, (double)2))));
            int sobel_final_rgbtBlue = round(sqrt(pow((double)gx_rgbtBlue, (double)2) + (pow((double)gy_rgbtBlue, (double) 2))));

            // Cap values between 0 and 255
            if (sobel_final_rgbtRed < 0)
            {
                sobel_final_rgbtRed = 0;
            }
            if (sobel_final_rgbtGreen < 0)
            {
                sobel_final_rgbtGreen = 0;
            }
            if (sobel_final_rgbtBlue < 0)
            {
                sobel_final_rgbtBlue = 0;
            }
            if (sobel_final_rgbtRed > 255)
            {
                sobel_final_rgbtRed = 255;
            }
            if (sobel_final_rgbtGreen > 255)
            {
                sobel_final_rgbtGreen = 255;
            }
            if (sobel_final_rgbtBlue > 255)
            {
                sobel_final_rgbtBlue = 255;
            }

            // Update the RGBTRIPLE sobel_final
            sobel_final.rgbtBlue = sobel_final_rgbtBlue;
            sobel_final.rgbtGreen = sobel_final_rgbtGreen;
            sobel_final.rgbtRed = sobel_final_rgbtRed;

            // Update the new image with new values
            new_image[i][j] = sobel_final;
        }
    }

    // Update image with values from new_image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }

    return;
}
