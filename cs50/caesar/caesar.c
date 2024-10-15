#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    string str = argv[1];
    for (int i = 0, len = strlen(str); i < len; i++)
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(str);

    // Prompt user for plaintext
    string text = get_string("plaintext:  ");

    // For each character in the plaintext:
    // Rotate the character if it's a letter
    printf("ciphertext: ");
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        printf("%c", rotate(text[i], key));
    }

    printf("\n");

    return 0;
}

char rotate(char c, int n)
{
    if (isalpha(c))
    {
        int num = c + n;

        if (isupper(c) && num > 'Z')
        {
            return (((c + n) - 'A') % 26 + 'A');
        }
        else if (islower(c) && num > 'z')
        {
            return (((c + n) - 'a') % 26 + 'a');
        }
        else
        {
            return (c + n);
        }
    }

    return c;
}
