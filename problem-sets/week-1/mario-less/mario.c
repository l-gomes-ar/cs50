// Asks user for height of pyramid, then displays it
#include <cs50.h>
#include <stdio.h>

void build_pyramid(int n);

int main(void)
{
    // Prompt user for positive integer between 1 and 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Build pyramid
    build_pyramid(height);
}

// Build pyramid
void build_pyramid(int n)
{
    // This loop prints the space for each row
    for (int i = 1; i <= n; i++)
    {
        // Print the opposite number of dots for each row (to reach 8 blocks per row)
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");
        }
        // This loop prints the blocks in each row
        for (int k = i - i; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}