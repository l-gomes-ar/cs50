// Prints a message encoded in binary
#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // Get text from user
    string text = get_string("Text: ");

    // Turn each letter into 8 bits of 0s and 1s
    int n = strlen(text);
    int bits[n][BITS_IN_BYTE];

    // Iterate through each char
    for (int i = 0; i < n; i++)
    {
        int decimal = text[i];

        // Create second loop to iterate 8 times (bits) for each char
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            // Check if number will be greater than 0 if divided by 2
            if (decimal / (float) 2 >= 0)
            {
                switch (decimal % 2)
                {
                    // Adds to array "bits" where [i] is char and [j] is each of the 8 bits
                    case 0:
                        bits[i][j] = 0;
                        break;
                    case 1:
                        bits[i][j] = 1;
                        break;
                }
            }
            decimal /= 2;
        }
    }

    // Print binary in the right direction
    for (int i = 0; i < n; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            print_bulb(bits[i][j]);
        }
        printf("\n");
    }
}

// Prints bulbs emojis
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}