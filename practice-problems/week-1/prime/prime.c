#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // Checks if number is either 1 or 2 (exceptions)
    if (number == 1)
    {
        return false;
    }
    else if (number == 2)
    {
        return true;
    }

    // Check if number can be divided by any other number
    int quotient = 0;

    for (int i = 2; i < (number - 1); i++)
    {
        // If it can, because the remainder is 0, return false
        quotient = number % i;
        if (quotient == 0)
        {
            return false;
            break;
        }
    }

    // Any other case, return true
    return true;
}