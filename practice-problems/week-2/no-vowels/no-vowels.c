// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string s);

int main(int argc, string argv[])
{
    // Print error message if more than one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    string output = replace(argv[1]);
    printf("%s\n", output);

}

// Replaces vowels for numbers
string replace(string s)
{
    // Use switch statement
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        switch (s[i])
        {
            case 'a':
                s[i] = '6';
                break;
            case 'e':
                s[i] = '3';
                break;
            case 'i':
                s[i] = '1';
                break;
            case 'o':
                s[i] = '0';
                break;
        }
    }
    return s;
}