/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

module bindings.libgame;

import std.stdio;

extern (C)
{
    alias libgame = ulong;

    libgame libgame_create()
    {
        long self = 1234;

        writeln("created: ", self);

        return self;
    }

    void libgame_destroy(libgame self)
    {
        writeln("destroy: ", self);
    }

    void libgame_start(libgame self)
    {
        writeln("start: ", self);
    }

    void libgame_stop(libgame self)
    {
        writeln("stop: ", self);
    }

    void libgame_draw(libgame self)
    {
        writeln("draw: ", self);
    }
}
