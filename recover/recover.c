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
        printf("Error opening file.\n");
        return 1;
    }

 // Create a buffer for a block of data
    uint8_t buffer[512];
    FILE *image = NULL;
    int count = 0;

 // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Close previous jpeg file, if any.
        if (image != NULL)
        {
            fclose(image);
        }

        // Create a new jpeg file.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            char filename[14];
            sprintf(filename, "%03i.jpg", count);
            image = fopen(filename, "w");
            if (image == NULL)
            {
                printf("Error: could not create file %s.\n", filename);
                fclose(card);
                return 1;
            }

            count +=1;
        }

        // Continue write to currently open jpeg file, if any.
        if (image != NULL)
        {
            fwrite(buffer, 1, 512, image);
        }
    }
    
    // Close any remaining open files.
    if (image != NULL)
    {
        fclose(image);
    }
    fclose(card);
}
