/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_game_instance_hxx
#define __game_game_instance_hxx

#include <putgame/common>

namespace game
{
    class game_instance : public common::context
    {
    public:
        game_instance();
        ~game_instance();

        virtual void start();
        virtual void stop();
        virtual void draw();

        virtual void resize(int width, int height);
        virtual void cursor(int x, int y);
        virtual void press();
        virtual void release();

        virtual void swap_buffers() = 0;

        int get_width() const { return width; }
        int get_height() const { return height; }

    private:
        int width;
        int height;
    };
}

#endif
