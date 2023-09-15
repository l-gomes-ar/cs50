// Encrypts messages using Caesar’s cipher and displays it
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check if user provided one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if every character in argv[i] is a digit
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert argv[1] to an int store it in key (k)
    int k = atoi(argv[1]);

    // If key is bigger than the letters in alphabet (26), wrap it back to 1-26
    while (k > 26)
    {
        k -= 26;
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Create array for ciphertext of type int (to store 4 bytes each element)
    int n = strlen(plaintext);
    int ciphertext[n];

    // For each char in plaintext
    for (int i = 0; i < n; i++)
    {
        // Rotate the char if it is a letter
        if (isalpha(plaintext[i]))
        {
            // Check if uppercase
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = plaintext[i] + k;

                // If letter is now not alpha, rotate it back to A-Z
                while (ciphertext[i] > 'Z')
                {
                    ciphertext[i] -= 26;
                }
            }
            // Check if lowercase
            else if (islower(plaintext[i]))
            {
                ciphertext[i] = plaintext[i] + k;

                // If letter is now not alpha, rotate it back to a-z
                while (ciphertext[i] > 'z')
                {
                    ciphertext[i] -= 26;
                }
            }
        }
        // In case it is not a letter, assign it to ciphertext as it is
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // Output ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    return 0;
}