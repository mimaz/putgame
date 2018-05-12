/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <stdio.h>

#include "../bindings/libgame.h"

int main(void)
{
    libgame lg = libgame_create();

    libgame_start(lg);

    for (int i = 0; i < 10; i++)
        libgame_draw(lg);

    libgame_stop(lg);

    libgame_destroy(lg);

    return 0;
}
