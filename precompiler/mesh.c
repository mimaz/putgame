/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

extern const char *symname(const char *);
extern const char *author_message;

void mesh(int argc, char **argv)
{
    const char *infile, *outfile, *symbol;
    float val;
    int readno, byteno;
    FILE *input, *output;

    if (argc < 4)
    {
        fprintf(stderr, "missing file name\n");
        exit(1);
    }


    infile = argv[2];
    outfile = argv[3];


    symbol = symname(infile);


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
    fprintf(output, "#define data_type float\n\n");
    fprintf(output, "const data_type %s[] = {", symbol);

    readno = fscanf(input, "%f", &val);
    byteno = 0;

    while (readno > 0)
    {
        if (byteno % 4 == 0)
            fprintf(output, "\n\t");

        fprintf(output, "%f, ", val);
        
        readno = fscanf(input, "%f", &val);
        byteno++;
    }

    fprintf(output, "\n};\n\n// size %d\n", byteno);


    fclose(output);
    fclose(input);
}
