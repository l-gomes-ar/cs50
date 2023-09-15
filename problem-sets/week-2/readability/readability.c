// Computes and displays the Coleman_liau index of text
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_index(int letters, int words, int sentences);

int main(void)
{
    // Prompt user for a string
    string text = get_string("Text: ");

    // Count number of letters, words, and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calculate Coleman-Liau Index
    int index = calculate_index(letters, words, sentences);

    // Print grade (Exceptions: If more than 16 should print "16+". If less than 1, "Before Grade 1")
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Counts letters
int count_letters(string text)
{
    // Iterate through text, and count number of letters
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

// Counts words
int count_words(string text)
{
    // Iterate through text, and count number of spaces (for words)
    int words = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }

    return words;
}

// Counts sentences
int count_sentences(string text)
{
    // Iterate through text, and count number of spaces (for words)
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}

// Calculates the Coleman-Liau index
int calculate_index(int letters, int words, int sentences)
{
    // Calculate average number of letters per 100 words in text
    float average_letters = letters * (float) 100 / words;

    // Calculate average number of sentences per 100 words in text
    float average_sentences = sentences * (float) 100 / words;

    // Calculate
    float index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;
    
    return (int) round(index);
}