/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "game_instance.hxx"

namespace game
{
    game_instance::game_instance()
    {

    }

    game_instance::~game_instance()
    {

    }

    void game_instance::start()
    {

    }

    void game_instance::stop()
    {

    }

    void game_instance::draw()
    {

    }

    void game_instance::resize(int wid, int hei)
    {
        width = wid;
        height = hei;

        glViewport(0, 0, width, height);
    }

    void game_instance::cursor(int x, int y)
    {

    }

    void game_instance::press()
    {

    }

    void game_instance::release()
    {

    }
}
