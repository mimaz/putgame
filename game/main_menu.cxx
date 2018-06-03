/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "main_menu.hxx"

namespace game
{
    main_menu::main_menu(common::context *ctx)
        : rect_item(ctx)
        , space_btn(ctx, std::bind([](){}))
        , start_btn(ctx, std::bind(&main_menu::clicked, 
                    this, std::placeholders::_1))
        , exit_btn(ctx, std::bind(&main_menu::clicked,
                   this, std::placeholders::_1))
        , yoff(1)
        , yspd(0)
        , animating(false)
        , enabled(false)
        , bottomoff(100)
    {
        auto primary = glm::vec4(0.15f, 0.15f, 0.15f, 0.75f);

        space_btn.set_text("");
        space_btn.set_primary_color(primary);
        space_btn.set_secondary_color(glm::vec4(0, 1, 0, 0.5f));

        start_btn.set_text("start!");
        start_btn.set_primary_color(primary);
        start_btn.set_secondary_color(glm::vec4(1, 0, 0, 0.5f));

        exit_btn.set_text("exit");
        exit_btn.set_primary_color(primary);
        exit_btn.set_secondary_color(glm::vec4(0, 0, 1, 0.5f));

        auto handler = std::bind(&main_menu::bottomoff_prop_set, this, 
                                 std::placeholders::_1);

        register_handler("bottom_offset", handler);

        layout();
        enable();
    }

    void main_menu::process()
    {
        if (animating)
            animate();
    }

    void main_menu::enable()
    {
        if (not is_enabled())
        {
            yoff = 1;
            yspd = 0;
            animating = true;
            enabled = true;
        }
    }

    void main_menu::disable()
    {
        if (is_enabled())
        {
            yoff = 0;
            yspd = 0;
            animating = true;
            enabled = false;
        }
    }

    void main_menu::on_surface_resize(int w, int h)
    {
        gui::rect_item::on_surface_resize(w, h);

        layout(w, h);
    }

    void main_menu::bottomoff_prop_set(const std::string &value)
    {
        std::istringstream(value) >> bottomoff;
    }

    void main_menu::layout()
    {
        layout(get_context()->get_width(), get_context()->get_height());
    }

    void main_menu::layout(int w, int h)
    {
        resize(w, w / 6);

        auto btnwidth = get_width() / 2;
        auto btnheight = get_height();

        auto btnoff = static_cast<int>(yoff * h);
        auto btny = -h / 2 + btnoff;


        space_btn.resize(w, bottomoff);
        space_btn.set_position(0, btny + bottomoff / 2);

        btny += bottomoff;


        start_btn.resize(btnwidth, btnheight);
        start_btn.set_position((btnwidth - w) / 2, btny + btnheight / 2);

        exit_btn.resize(btnwidth, btnheight);
        exit_btn.set_position((w - btnwidth) / 2, btny + btnheight / 2);
    }

    void main_menu::clicked(gui::color_button *btn)
    {
        common::logd("clicked");
    }

    void main_menu::animate()
    {
        constexpr auto acceleration = 0.0075f;
        constexpr auto resistance = 0.95f;
        constexpr auto speed_eps = 0.025f;

        if (enabled)
        {
            yspd -= acceleration;
            yoff += yspd;
            yspd *= resistance;

            if (yoff < 0)
            {
                yoff = 0;
                yspd *= -1;

                if (yspd < speed_eps)
                    animating = false;
            }
        }
        else
        {
            yspd -= acceleration;
            yoff += yspd;

            if (yoff < -1)
                animating = false;
        }


        layout();
    }
}
