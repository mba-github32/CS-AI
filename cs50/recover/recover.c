#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Card cannot be opened for reading!");
        return 1;
    }
    // Create a buffer for a block of data
    uint8_t buffer[512];

    int count = 0;
    FILE *img = NULL;
    char filename[8];
    bool found = false;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (count > 0)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(img);
                fclose(card);
                return 1;
            }
            fwrite(buffer, 1, 512, img);
            count++;
            found = true;
        }
        else
        {
            if (found == true)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }
    fclose(card);
    fclose(img);
}
