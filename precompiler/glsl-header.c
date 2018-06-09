/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BEGIN_STR "/* begin */"
#define END_STR "/* end */"

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

static int compare(int len1, const char *str1,
                   int len2, const char *str2)
{
    if (len1 < 0 || len2 < 0)
        return 1;

    str1 = strstr(str1, BEGIN_STR);
    str2 = strstr(str2, BEGIN_STR);

    if (str1 == NULL || str2 == NULL)
        return 1;

    const char *str1end = strstr(str1, END_STR);
    const char *str2end = strstr(str2, END_STR);

    if (str1end == NULL || str2end == NULL)
        return 1;

    len1 = str1end - str1;
    len2 = str2end - str2;

    if (len1 != len2)
        return 1;

    return memcmp(str1, str2, len1);
}

static void update(const char *outname)
{
    static char lastbuf[16386];

    FILE *last, *output;
    int lastsiz, headersiz;


    headersiz = buffptr - headerbuf;


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


    if (compare(lastsiz, lastbuf, headersiz, headerbuf) != 0)
    {
        output = fopen(outname, "w");

        if (output == NULL)
        {
            fprintf(stderr, "failed to open file %s to write: %s\n",
                    outname, strerror(errno));
            exit(1);
        }

        fwrite(headerbuf, 1, headersiz, output);

        fclose(output);
    }
}

static void closefiles(void)
{
    if (input != NULL)
        fclose(input);
}

void glsl_header(int argc, char **argv)
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
    buffptr += sprintf(buffptr, "%s\n\n", BEGIN_STR);

    
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

    buffptr += sprintf(buffptr, "%s\n\n", END_STR);
    buffptr += sprintf(buffptr, "#endif\n");


    update(argv[2]);
}
