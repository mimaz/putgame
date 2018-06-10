/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_instance_hxx
#define __game_instance_hxx

#include <putgame/common>

namespace game
{
    class activity;
    class main_menu;

    class instance : public common::context
    {
    public:
        instance();
        ~instance();

        virtual void start();
        virtual void stop();
        virtual void draw();
        virtual void process();

        virtual void resize(int width, int height);
        virtual void cursor(int x, int y);
        virtual void press();
        virtual void release();

        int get_width() override;
        int get_height() override;

    private:
        int width;
        int height;
        int mouse_x;
        int mouse_y;
        bool mouse_pressed;
        bool shifting;
    };
}

#endif
