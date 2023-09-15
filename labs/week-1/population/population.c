#include <cs50.h>
#include <stdio.h>

int get_growth(int start);

int main(void)
{
    // Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // Calculate number of years until we reach threshold

    // Initialise variable for number of years
    int n = 1;

    // Get the number of populational growth for one year
    int growth = get_growth(start_size);

    while (growth < end_size)
    {
        // Add one more year of growth
        n++;
        growth = get_growth(growth);
    }

    // Check if the start size, and end size are the same, if so, set '0' as the year (there's no growth needed)
    if (start_size == end_size)
    {
        n = 0;
    }

    // Print number of years
    printf("Years: %i\n", n);
}

// Calculate anual growth
int get_growth(int n)
{
    // Each year, (n / 3) new llamas are born, and (n / 4) llamas pass away.
    int growth = n + (n / 3) - (n / 4);
    return growth;
}