/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_application_hxx
#define __game_application_hxx

#include <putgame/common>

namespace game
{
    class application : public common::context
    {
    public:
        class window;

        application();

        void run();

        void rotate(float angle, glm::vec3 axis);
        void move(glm::vec3 vec);
        void resize(int width, int height);
        void cursor(int x, int y);
        void press();
        void release();
        void exit();

    protected:
        using shared_window = std::shared_ptr<window>;

        virtual shared_window make_window() = 0;

    private:
        shared_window window;
        int flags, xpos, ypos;
        time_t start_time;
    };

    class application::window
    {
    public:
        virtual void swap_buffers() = 0;
    };
}

#endif
