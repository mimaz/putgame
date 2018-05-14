/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_context_hxx
#define __game_context_hxx

#include <putgame/common>

namespace game
{
    class play_activity;

    class context : public common::context
    {
    public:
        context();
        ~context();

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
        int mouse_x;
        int mouse_y;
        int mouse_pressed;

        std::shared_ptr<play_activity> play;
    };
}

#endif
