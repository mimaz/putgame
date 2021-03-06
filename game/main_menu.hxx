/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_main_menu_hxx
#define __game_main_menu_hxx

#include <putgame/gui>

namespace game
{
    class main_menu : public gui::rect_item
    {
    public:
        main_menu(common::context *ctx);

        void process() override;
        void enable();
        void disable();

        void on_surface_resize(int w, int h) override;

        bool is_enabled() const;
        bool is_animating() const;

    private:
        void bottomoff_prop_set(const property_value &value);
        void layout();
        void layout(int w, int h);
        void exit_clicked();
        void start_clicked();
        void animate();

        gui::color_rectangle bottom_spacer;
        gui::color_button start_btn;
        gui::color_button exit_btn;

        float yoff;
        float yspd;
        bool animating;
        bool enabled;
        int bottomoff;
    };
}

#endif
