// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// Checks if password is valid
bool valid(string password)
{
    bool lower_case = false;
    bool upper_case = false;
    bool number = false;
    bool symbol = false;

    // Iterates through string to check for each bool expression
    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (islower(password[i]))
        {
            lower_case = true;
        }
        if (isupper(password[i]))
        {
            upper_case = true;
        }
        if (isdigit(password[i]))
        {
            number = true;
        }
        if (!isalnum(password[i]))
        {
            symbol = true;
        }
    }

    // Checks if all conditions are met
    if (lower_case == true && upper_case == true && number == true && symbol == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
