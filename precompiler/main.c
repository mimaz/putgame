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

extern void glsl_source(int argc, char **argv);
extern void glsl_header(int argc, char **argv);
extern void meta_object(int argc, char **argv);

struct option
{
    void (*fun)(int, char **);
    const char *name;
};

static struct option optionlst[] = {
    { glsl_source, "glsl-source" },
    { glsl_header, "glsl-header" },
    { meta_object, "meta-object" }
};

#define funcnt (sizeof(optionlst) / sizeof(struct option))

const char *author_message =
    "/*\n" 
    " * File auto-generated by putgame resource precompiler\n" 
    " *\n"
    " * Mieszko Mazurek <mimaz@gmx.com>\n"
    " * 2018\n"
    " */\n";

int main(int argc, char **argv)
{
    const char *opt;
    int i;

    if (argc < 2)
    {
        fprintf(stderr, "invalid usage\n");
        return 1;
    }

    opt = argv[1];


    for (i = 0; i < funcnt; i++)
    {
        if (strcmp(optionlst[i].name, opt) == 0)
        {
            optionlst[i].fun(argc, argv);

            return 0;
        }
    }

    fprintf(stderr, "invalid opt: %s\n", opt);

    return 1;
}
