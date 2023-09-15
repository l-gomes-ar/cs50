# TODO
from cs50 import get_string


def main():
    text = get_string("Text: ")

    words = count_words(text)
    letters = count_letters(text)
    sentences = count_sentences(text)

    coleman = calculate_coleman(words, letters, sentences)
    output(coleman)


def count_words(text):
    counter = 1

    for char in text:
        if char == " ":
            counter += 1

    return counter


def count_letters(text):
    counter = 0

    for char in text:
        if char.isalpha():
            counter += 1

    return counter


def count_sentences(text):
    # Any occurrence of ".", "!", or "?" indicates the end of a sentence.
    counter = 0

    for char in text:
        if char in [".", "!", "?"]:
            counter += 1

    return counter


def calculate_coleman(words, letters, sentences):
    # Average number of letters per 100 words in text
    average_letters = (letters * float(100)) / words

    # Average number of sentences per 100 words in text
    average_sentences = (sentences * float(100)) / words

    return int(round(0.0588 * average_letters - 0.296 * average_sentences - 15.8))


def output(coleman):
    x = coleman

    # Before Grade 1
    if x < 1:
        print("Before Grade 1")
        return

    # Grade 16+
    elif x > 16:
        print("Grade 16+")
    else:
        print(f"Grade {x}")


main()
