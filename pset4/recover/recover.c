#include <stdio.h>
#include <stdint.h>
#include <cs50.h>
#include <stdlib.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512
#define FILE_NAME_SIZE 8

bool is_start(BYTE buffer[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("File not found\n");
        return 1;
    }
    
    BYTE buffer[BLOCK_SIZE];
    int file_index = 0;
    bool ff = false;
    FILE *outfile;
    while (fread(buffer, BLOCK_SIZE, 1, infile))
    {
        if (is_start(buffer))
        {
            if (!ff)
            {
                ff = true;
            }
            else
            {
                fclose(outfile);
            }
            char filename[FILE_NAME_SIZE];
            sprintf(filename, "%03i.jpg", file_index++);
            outfile = fopen(filename, "w");
            if (outfile == NULL)
            {
                return 1;
            }
            fwrite(buffer, BLOCK_SIZE, 1, outfile);
        }
        else if (ff)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outfile);
        }

    }
    fclose(outfile);
    fclose(infile);
}

bool is_start(BYTE buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}