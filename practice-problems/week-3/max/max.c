// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// Return the max value
int max(int array[], int n)
{
    // Get min number first
    // Initialise variable for keeping min number
    int min = 999999999;

    for (int i = 0; i < n; i++)
    {
        // If current element < max
        if (array[i] < min)
        {
            // Assign element to max
            min = array[i];
        }
    }

    // Initialise variable for keeping max number
    int max = min;

    for (int i = 0; i < n; i++)
    {
        // If current element > max
        if (array[i] > max)
        {
            // Assign element to max
            max = array[i];
        }
    }

    return max;
}
