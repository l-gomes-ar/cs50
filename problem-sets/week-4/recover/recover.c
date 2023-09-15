#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check if there is one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card
    FILE *raw_file = fopen(argv[1], "r");

    // If it returns NULL, print error message
    if (raw_file == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    // String for filename
    char *filename = malloc(sizeof(char) * 8);

    // Counter for filename
    int counter = 0;

    // Repeat until end of card
    BYTE *buffer = malloc(sizeof(BYTE) * BLOCK_SIZE);

    // Create pointer for image
    FILE *img;

    // Initialise variable for keeping track of the first JPEG
    int is_first = 1;

    // Read 512 bytes into a buffer
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Check if start of buffer equals new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (is_first)
            {
                // Print to filename's location the name of file
                sprintf(filename, "%03i.jpg", counter);

                // Open filename
                img = fopen(filename, "w");

                // Write image to new_file and update condition for is_first
                fwrite(buffer, 1, BLOCK_SIZE, img);

                is_first = 0;
            }
            // Else
            else
            {
                // Close old file and update counter if this is a new JPEG
                // Repeat the same process
                fclose(img);
                counter++;
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
        // If not, keep writing
        else if (!is_first)
        {
            // Keep writing to current JPEG
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    free(filename);
    free(buffer);
    fclose(raw_file);
    fclose(img);
}