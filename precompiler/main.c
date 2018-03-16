/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>

#include <sys/stat.h>

#define AUTHOR_MESSAGE \
    "/*\n" \
    " * File auto-generated by putgame GLSL resource precompiler\n" \
    " * Mieszko Mazurek <mimaz@gmx.com>\n" \
    " * 2018\n" \
    " */\n"

#define MAX_FILENAME_LENGTH 64
#define MAX_FILE_COUNT 64
#define MAX_FILE_SIZE 16384

static const char *extensions[] = {
    ".vert", ".frag"
};


static char summary[MAX_FILE_COUNT][MAX_FILENAME_LENGTH];
static int filecount;


static const char *findext(const char *filename)
{
    static char shortname[MAX_FILENAME_LENGTH];

    int namelen, i, extcnt, extlen, cmp, shortlen;
    const char *ext, *suff;
    
    namelen = strlen(filename);
    extcnt = sizeof(extensions) / sizeof(extensions[0]);

    for (i = 0; i < extcnt; i++)
    {
        ext = extensions[i];
        extlen = strlen(ext);

        suff = filename + namelen - extlen;

        if (suff <= filename)
            continue;

        cmp = strcmp(ext, suff);

        if (cmp == 0)
        {
            shortlen = namelen - extlen;

            memcpy(shortname, filename, shortlen);
            shortname[shortlen] = 0;

            return shortname;
        }
    }

    return NULL;
}

static void process(const char *srcdir, 
                    const char *dstdir,
                    const char *filename)
{
    static char filebuff[MAX_FILE_SIZE];

    const char *shortname; 
    char outname[MAX_FILENAME_LENGTH];
    FILE *input, *output;
    int readno, i, buflen;

    
    shortname = findext(filename);

    if (shortname == NULL)
        return;

    strcpy(outname, shortname);
    strcat(outname, ".c");


    chdir(srcdir);
    input = fopen(filename, "r");

    if (input == NULL)
    {
        fprintf(stderr, "cannot open file %s: %s\n", 
                filename, strerror(errno));

        return;
    }


    buflen = 0;
    readno = fread(filebuff + buflen, sizeof(char), 64, input);

    while (readno > 0)
    {
        buflen += readno;

        readno = fread(filebuff + buflen, sizeof(char), 64, input);
    }

    fclose(input);



    chdir(dstdir);
    output = fopen(outname, "w");

    if (outname == NULL)
    {
        fprintf(stderr, "cannot open file %s: %s\n", 
                outname, strerror(errno));

        return;
    }


    fprintf(output, "%s\n", AUTHOR_MESSAGE);
    fprintf(output, "const char %s[] = {", shortname);

    for (i = 0; i < buflen; i++)
    {
        if (i % 8 == 0)
            fprintf(output, "\n    ");

        fprintf(output, "0x%02x, ", filebuff[i]);
    }

    fprintf(output, "\n};\n");

    fclose(output);


    strcpy(summary[filecount++], shortname);
}

static void genheader(const char *dstdir, const char *filename)
{
    FILE *output;
    int i;


    chdir(dstdir);
    output = fopen(filename, "w");


    if (output == NULL)
    {
        fprintf(stderr, "cannot open file %s: %s\n", 
                filename, strerror(errno));
        return;
    }


    fprintf(output, "%s\n", AUTHOR_MESSAGE);
    fprintf(output, "#ifdef __cplusplus\n"
                    "extern \"C\" {\n"
                    "#endif\n\n");

    for (i = 0; i < filecount; i++)
    {
        fprintf(output, "extern const char *%s;\n\n", summary[i]);
    }

    fprintf(output, "#ifdef __cplusplus\n"
                    "}\n"
                    "#endif\n");

    fclose(output);
}

int main(int argc, char **argv)
{
    const char *dirname;
    const char *outdirname;

    DIR *dir;
    struct dirent *entr;
    struct stat st;


    if (argc < 3)
    {
        fprintf(stderr, "no source and/or destination directory\n");
        return 1;
    }

    dirname = argv[1];
    outdirname = argv[2];


    dir = opendir(dirname);

    if (dir == NULL)
    {
        fprintf(stderr, "cannot open directory %s: %s\n",
                dirname, strerror(errno));
        return 1;
    }


    entr = readdir(dir);

    while (entr != NULL)
    {
        lstat(entr->d_name, &st);

        process(dirname, outdirname, entr->d_name);


        entr = readdir(dir);
    }



    closedir(dir);


    genheader(outdirname, "glsl.h");

    return 0;
}
