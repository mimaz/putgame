/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

module game.game_instance;

import std.stdio;

class GameInstance
{
    this()
    {
        writeln("created GameInstance");
    }

    ~this()
    {
        writeln("destroyed GameInstance");
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
