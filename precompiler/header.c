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

static FILE *input;

static char headerbuf[16386];
static char *buffptr;

static void findpatt(const char *patt)
{
    int c, idx;

    idx = 0;

    do {
        c = fgetc(input);

        if (c < 0)
            break;

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
    char symbol[64], datatype[64];

    findpatt("data_type");
    fscanf(input, "%s", datatype);


    findpatt("data_type");
    fscanf(input, "%s", symbol);
    symbol[strlen(symbol) - 2] = 0;

    buffptr += sprintf(buffptr, "extern const %s %s[];\n\n", datatype, symbol);
}

static void update(const char *outname)
{
    static char lastbuf[16386];

    FILE *last, *output;
    int lastsiz, bufsiz;


    bufsiz = buffptr - headerbuf;


    last = fopen(outname, "r");

    if (last != NULL)
    {
        lastsiz = fread(lastbuf, 1, sizeof(lastbuf), last);

        fclose(last);
    }
    else
    {
        lastsiz = -1;
    }



    if (lastsiz != bufsiz || memcmp(lastbuf, headerbuf, bufsiz) != 0)
    {
        output = fopen(outname, "w");

        if (output == NULL)
        {
            fprintf(stderr, "failed to open file %s to write: %s\n",
                    outname, strerror(errno));
            exit(1);
        }

        fwrite(headerbuf, 1, bufsiz, output);

        fclose(output);
    }
}

static void closefiles(void)
{
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




    atexit(closefiles);


    strcpy(unitname, argv[2]);

    for (i = 0; i < strlen(unitname); i++)
    {
        if (strchr("/.-", unitname[i]) != NULL)
            unitname[i] = '_';
    }

    buffptr = headerbuf;

    buffptr += sprintf(buffptr, "%s\n", author_message);
    buffptr += sprintf(buffptr, "#ifndef __%s\n", unitname);
    buffptr += sprintf(buffptr, "#define __%s\n\n", unitname);

    
    for (i = 3; i < argc; i++)
    {
        src = argv[i];

        if (input != NULL)
            fclose(input);

        input = fopen(src, "r");

        if (input != NULL)
        {
            handlefile();

            fclose(input);
            input = NULL;
        }
    }

    buffptr += sprintf(buffptr, "#endif\n");


    update(argv[2]);
}
