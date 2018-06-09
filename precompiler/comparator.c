/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <string.h>

#include "comparator.h"

int compare(int len1, const char *str1,
            int len2, const char *str2)
{
    if (len1 < 0 || len2 < 0)
        return 1;

    str1 = strstr(str1, BEGIN_TAG);
    str2 = strstr(str2, BEGIN_TAG);

    if (str1 == NULL || str2 == NULL)
        return 1;

    const char *str1end = strstr(str1, END_TAG);
    const char *str2end = strstr(str2, END_TAG);

    if (str1end == NULL || str2end == NULL)
        return 1;

    len1 = str1end - str1;
    len2 = str2end - str2;

    if (len1 != len2)
        return 1;

    return memcmp(str1, str2, len1);
}

