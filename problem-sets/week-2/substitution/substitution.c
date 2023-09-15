// Implements substitution cipher, and displays it
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check if there is one single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the command-line argument has 26 letters
    string k = argv[1];

    // Store the length of the key in a variable
    int n = strlen(k);
    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if all characters are alphabetic
    for (int i = 0; i < n; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("All characters must be alphabetic characters.\n");
            return 1;
        }
    }

    // Turn the key case insensitive by turning it lowercase
    for (int i = 0; i < n; i++)
    {
        k[i] = tolower(k[i]);
    }

    // Check if all characters are different
    for (int i = 0; i < n; i++)
    {
        // Set counter to 0 each iteration
        int counter = 0;
        for (int j = 0; j < n; j++)
        {
            // Add to counter everytime the letter is the same
            if (k[i] == k[j])
            {
                counter++;
            }
        }

        // If at any moment the counter is more than 1, print error
        if (counter > 1)
        {
            printf("Key must contain each letter exactly once.\n");
            return 1;
        }
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    int length_text = strlen(plaintext);
    int ciphertext[length_text];

    // Preserve case
    for (int i = 0; i < length_text; i++)
    {
        if (isupper(plaintext[i]))
        {
            // Substitute
            ciphertext[i] = k[plaintext[i] - 'A'];

            // Turn uppercase toupper()
            ciphertext[i] = toupper(ciphertext[i]);
        }
        else if (islower(plaintext[i]))
        {
            // Substitute
            ciphertext[i] = k[plaintext[i] - 'a'];
        }
        else
        {
            // Add char to cipher as it is
            ciphertext[i] = plaintext[i];
        }
    }

    // Output encripted text
    printf("ciphertext: ");
    for (int i = 0; i < length_text; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");

    return 0;
}