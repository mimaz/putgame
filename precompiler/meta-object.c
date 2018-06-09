/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "comparator.h"

#define META_TAG "PUTGAME_OBJECT"

extern const char *author_message;

static const char *srcdir;
static const char *outfile;

static char outbuf[16384];
static char *outptr = outbuf;

static char lastbuf[16384];
static char *lastptr = lastbuf;

static char token[64];
static int toklen;

static char classname[8][64];
static int depth;
static int declarator;

static int idcount = 1;

static int tokchar1shot(char c)
{
    return strchr(":{};", c) != NULL;
}

static int tokchar(char c)
{
    return isalpha(c) || strchr("_", c) != NULL;
}

static int isclassdecl(void)
{
    return strcmp(token, "class") == 0 
        || strcmp(token, "struct") == 0 
        || strcmp(token, "namespace") == 0;
}

static void handle(const char *filename)
{
    outptr += sprintf(outptr, "#include \"%s%s\"\n", srcdir, filename);
    outptr += sprintf(outptr, "const int ");

    for (int i = 0; i < depth; i++)
        outptr += sprintf(outptr, "%s::", classname[i]);

    outptr += sprintf(outptr, "id = %d;\n\n", idcount);
}

static void processtok(const char *filename)
{
    token[toklen] = 0;

    if (declarator == 1)
    {
        strcpy(classname[depth], token);
        declarator = 0;
    }
    else if (strcmp(token, "{") == 0)
    {
        depth++;
    }
    else if (strcmp(token, "}") == 0)
    {
        depth--;

        classname[depth][0] = 0;
    }
    else if (isclassdecl())
    {
        declarator = 1;
    } 
    else if (strcmp(token, META_TAG) == 0)
    {
        if (depth > 0 && classname[depth - 1][0] != 0)
            handle(filename);
    }

    toklen = 0;
}

static void parse(int len, const char *src, const char *filename)
{
    while (len--)
    {
        if (tokchar1shot(*src))
        {
            if (toklen > 0)
                processtok(filename);

            token[toklen++] = *src;

            processtok(filename);
        }
        else if (tokchar(*src))
        {
            token[toklen++] = *src;
        }
        else if (toklen > 0)
        {
            processtok(filename);
        }

        src++;
    }
}

static void parsefile(const char *name)
{
    FILE *file;
    char buff[64];
    size_t len;
        
    file = fopen(name, "r");

    if (file == NULL)
    {
        fprintf(stderr, "cannot open file %s: %s\n", 
                name, strerror(errno));
        exit(1);
    }


    depth = 0;


    len = fread(buff, 1, sizeof(buff), file);

    while (len != 0)
    {
        parse(len, buff, name);

        len = fread(buff, 1, sizeof(buff), file);
    }

    parse(0, NULL, name);
}

static void readlast(void)
{
    FILE *file;
    size_t len;

    file = fopen(outfile, "r");

    if (file != NULL)
    {
        len = fread(lastbuf, 1, sizeof(lastbuf), file);

        lastptr = lastbuf + len;

        fclose(file);
    }
    else
    {
        lastptr = lastbuf;
    }
}

static void writenew(void)
{
    FILE *file;

    file = fopen(outfile, "w");

    if (file != NULL)
    {
        fwrite(outbuf, 1, (outptr - outbuf), file);

        fclose(file);
    }
    else
    {
        fprintf(stderr, "writing to file %s failed: %s\n", 
                outfile, strerror(errno));
        exit(1);
    }
}

void meta_object(int argc, char **argv)
{
    int i, lastlen, outlen;

    srcdir = argv[2];
    outfile = argv[3];

    readlast();

    outptr += sprintf(outptr, "%s\n", author_message);
    outptr += sprintf(outptr, "%s\n", BEGIN_TAG);

    for (i = 4; i < argc; i++)
        parsefile(argv[i]);

    outptr += sprintf(outptr, "%s\n", END_TAG);

    lastlen = lastptr - lastbuf;
    outlen = outptr - outbuf;

    if (compare(lastlen, lastbuf, outlen, outbuf))
        writenew();
}
