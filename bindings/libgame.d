/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

module bindings.libgame;

import std.conv;
import core.stdc.stdlib;

import game.application;

extern (C)
{
    alias libgame = Application;

    libgame libgame_create()
    {
        auto object_size = __traits(classInstanceSize, libgame);
        auto memory = malloc(object_size)[0..object_size];

        return emplace!(libgame)(memory);
    }

    void libgame_destroy(libgame self)
    {
        destroy(self);

        free(cast(void *) self);
    }

    void libgame_start(libgame self)
    {
        self.start();
    }

    void libgame_stop(libgame self)
    {
        self.stop();
    }

    void libgame_draw(libgame self)
    {
        self.draw();
    }
}
