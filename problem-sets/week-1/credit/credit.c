// Prompts user for credit card number and reports if it is a valid american express, mastercard, or visa card number.
#include <math.h>
#include <cs50.h>
#include <stdio.h>

bool checksum(long n);
bool check_amex(long n);
bool check_master(long n);
bool check_visa(long n);

int main(void)
{
    // Check if passes Luhn's Algorithm
    long number = get_long("Number: ");

    // Check if number has enough digits to be a credit card (between 13 and 16 digits)
    if (number >= pow(10, 12) && number < pow(10, 16))
    {
        // Check Luhn's algorithm
        if (checksum(number))
        {
            // Check if card is AMEX
            if (check_amex(number))
            {
                printf("AMEX\n");
            }
            // Check if card is MASTERCARD
            else if (check_master(number))
            {
                printf("MASTERCARD\n");
            }
            // Check if card is VISA
            else if (check_visa(number))
            {
                printf("VISA\n");
            }
            // Check if the checksum is right but still not a valid card number
            else
            {
                printf("INVALID\n");
            }
        }
        // If checksum fails, invalid
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        // Display INVALID if not enough digits to be credit card
        printf("INVALID\n");
    }

}

// Checks if number is a valid credit card number
bool checksum(long n)
{
    // Create two variables to use numbers in different loops
    long n_a = n;
    long n_b = n;

    // Multiply every other digit by 2, starting with second-to-last digit

    // This will be used to store the checksum of digits
    int sum = 0;

    // Create loop to execute the first part of checksum
    for (int i = 0; i < 8; i++)
    {
        // Divide by 10 to get second to last digit
        n_a /= 10;

        // Get second to last digit
        int digit = n_a % 10;

        // Multiply last digit by 2
        digit *= 2;

        // Check if this last digit is 2_digits long
        if (digit >= 10)
        {
            // If so, get each number
            int digit_a = (digit / 10) % 10;
            int digit_b = digit % 10;

            // Add these two numbers together
            digit = digit_a + digit_b;
        }

        // Add this number to the sum
        sum += digit;

        // Update the number by dividing for 10 to get to the next number
        n_a /= 10;
    }

    // Sum the digits that were not multiplied by 2 (starting from the end)
    for (int i = 0; i < 8; i++)
    {
        // Get last digit
        int digit = n_b % 10;

        // Add last digit to the sum
        sum += digit;

        // Update number to get the next digit (divide by 100)
        n_b /= 100;
    }

    // Check if checksum's last digit is 0
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Checks if it is an amex credit card number
bool check_amex(long n)
{
    // American express numbers are 15 digits
    if (n >= pow(10, 14) && n < pow(10, 15))
    {
        // All American Express numbers start with 34 or 37
        int first_two = n / pow(10, 13);

        if (first_two == 34 || first_two == 37)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Checks if it is a mastercard credit card number
bool check_master(long n)
{
    // Mastercard numbers are 16 digits
    if (n >= pow(10, 15) && n < pow(10, 16))
    {
        // MasterCard numbers start with 51, 52, 53, 54, or 55
        int first_two = n / pow(10, 14);

        if (first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 || first_two == 55)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Checks if it is a visa credit card number
bool check_visa(long n)
{
    // Visa numbers are either 13 digits
    if (n >= pow(10, 12) && n < pow(10, 13))
    {
        // Visa numbers start with 4
        int first_digit = n / pow(10, 12);

        if (first_digit == 4)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // Or 16 digits
    else if (n >= pow(10, 15) && n < pow(10, 16))
    {
        // Visa numbers start with 4
        int first_digit = n / pow(10, 15);

        if (first_digit == 4)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}