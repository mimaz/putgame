/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

extern const char *author_message;

static FILE *input, *output;

static void findpatt(const char *patt)
{
    int c, idx;

    idx = 0;

    do {
        c = fgetc(input);

        if (c < 0)
        {
            fprintf(stderr, "missing \"size\" comment\n");
            exit(1);
        }

        if (c == patt[idx])
        {
            idx++;

            if (idx == strlen(patt))
                return;
        }
        else
        {
            idx = 0;
        }

    } while (1);

    fprintf(stderr, "cannot find pattern %s\n", patt);

    exit(1);
}

static void handlefile(void)
{
    char symbol[64];
    int size;

    findpatt("const char");
    fscanf(input, "%s", symbol);
    symbol[strlen(symbol) - 2] = 0;



    findpatt("size");
    fscanf(input, "%d", &size);



    fprintf(output, "extern const char %s[];\n", symbol);
    fprintf(output, "#define %s_size %d\n\n", symbol, size);
}

static void closefiles(void)
{
    if (output != NULL)
        fclose(output);

    if (input != NULL)
        fclose(input);
}

void header(int argc, char **argv)
{
    char unitname[64];
    int i;
    const char *src;


    if (argc < 4)
    {
        fprintf(stderr, "missing arguments\n");
        exit(1);
    }


    output = fopen(argv[2], "w");

    if (output == NULL)
    {
        fprintf(stderr, "failed to open file %s to write: %s\n",
                argv[2], strerror(errno));
        exit(1);
    }


    atexit(closefiles);


    strcpy(unitname, argv[2]);

    for (i = 0; i < strlen(unitname); i++)
    {
        if (strchr("/.-", unitname[i]) != NULL)
            unitname[i] = '_';
    }

    fprintf(output, "%s\n", author_message);
    fprintf(output, "#ifndef __%s\n", unitname);
    fprintf(output, "#define __%s\n\n", unitname);

    
    for (i = 3; i < argc; i++)
    {
        src = argv[i];

        if (input != NULL)
            fclose(input);

        input = fopen(src, "r");

        handlefile();
    }

    fprintf(output, "#endif\n");
}
