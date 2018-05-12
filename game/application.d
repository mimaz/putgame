/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

module game.game_instance;

import std.stdio;

import bindings.camera;

class Application
{
    this()
    {
        writeln("created Application");
    }

    ~this()
    {
        writeln("destroyed Application");
    }

    void start()
    {
        writeln("start");
    }

    void stop()
    {
        writeln("stop");
    }

    void draw()
    {
        writeln("draw");
    }
}
