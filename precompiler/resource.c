/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

extern const char *author_message;

static const char *comname(const char *filename)
{
    static char comn[64];

    const char *bg;
    char *ptr;

    bg = strrchr(filename, '/') + 1;


    if (bg == NULL)
        bg = filename;


    strcpy(comn, bg);

    ptr = comn;

    while (*ptr)
    {
        if (strchr(".-/\\", *ptr))
            *ptr = '_';

        ptr++;
    }


    return comn;
}

void resource(int argc, char **argv)
{
    char buff[64];
    const char *infile, *outfile, *common;
    FILE *input, *output;
    int readno, byteno, i;


    if (argc < 4)
    {
        fprintf(stderr, "missing file name\n");
        exit(1);
    }


    infile = argv[2];
    outfile = argv[3];


    common = comname(infile);


    input = fopen(infile, "r");

    if (input == NULL)
    {
        fprintf(stderr, "cannot open file %s to read: %s\n", 
                infile, strerror(errno));

        exit(1);
    }

    output = fopen(outfile, "w");

    if (output == NULL)
    {
        fprintf(stderr, "cannot open file %s to write: %s\n", 
                outfile, strerror(errno));

        fclose(input);
        exit(1);
    }


    fprintf(output, "%s\n", author_message);
    fprintf(output, "const char %s[] = {\n", common);


    readno = fread(buff, 1, sizeof(buff), input);


    byteno = 0;

    while (readno > 0)
    {
        for (i = 0; i < readno; i++)
        {
            fprintf(output, "0x%02x, ", buff[i]);

            if (byteno++ % 8 == 0)
                fprintf(output, "\n\t");
        }

        readno = fread(buff, 1, sizeof(buff), input);
    }

    fprintf(output, "0x%02x\n};\n\n// size %d\n", 0, byteno);


    fclose(output);
    fclose(input);
}
