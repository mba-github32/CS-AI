from cs50 import get_string


def main():
    # Prompt the user for some text
    text = get_string("Text: ")

    # Count the number of letters, words, and sentences in the text
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Compute the Coleman-Liau index
    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    result = round(index)

    # Print the grade level
    if result >= 16:
        print("Grade 16+")
    elif result < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {result}")


def count_letters(text):
    # Return the number of letters in text
    length = len(text)
    counter = 0
    for i in range(length):
        if (text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z'):
            counter += 1

    return counter


def count_words(text):
    # Return the number of words in text
    length = len(text)
    counter = 1
    for i in range(length):
        if text[i] == ' ':
            counter += 1

    return counter


def count_sentences(text):
    # Return the number of sentences in text
    length = len(text)
    counter = 0
    for i in range(length):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            counter += 1

    return counter


main()
