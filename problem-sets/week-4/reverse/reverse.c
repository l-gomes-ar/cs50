#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not read file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, 1, sizeof(WAVHEADER), input);
    int end_header = ftell(input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 1)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");

    if (output == NULL)
    {
        printf("Could not open output file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, 1, sizeof(WAVHEADER), output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE block[block_size];

    // Set position to EOF
    fseek(input, -1 * block_size, SEEK_END); // EOF -> position indicator 352844

    // Iterate through file going backwards until position end_header, writing block by block
    while (ftell(input) > SEEK_SET)
    {
        if (ftell(input) >= end_header)
        {
            fread(&block, 1, block_size, input);
            fwrite(&block, 1, block_size, output);
        }

        // Move two block sizes back
        fseek(input, -2 * block_size, SEEK_CUR);
    }

    // Close files
    fclose(output);
    fclose(input);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'w' && header.format[1] == 'a' && header.format[2] == 'v' && header.format[3] == 'e')
    {
        return 1;
    }

    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    // Calculate the size of each block, n of channels * bytes per sample
    return header.numChannels * (header.bitsPerSample / 8);
}