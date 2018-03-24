/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "glass_pieces.hxx"

#include "glass_pane.hxx"
#include "context.hxx"
#include "draw_manager.hxx"

namespace world
{
    constexpr auto piece_size = 0.2f;

    glass_pieces::glass_pieces(const glass_pane *pane)
        : visible_object(pane->get_context())
        , color(pane->get_color())
    {
        auto area = pane->get_size();

        auto xcount = static_cast<int>(area.x / piece_size);
        auto ycount = static_cast<int>(area.y / piece_size);

        auto xgap = area.x / (xcount - 1);
        auto ygap = area.y / (ycount - 1);
        auto scale_vec = glm::vec3(xgap, ygap, 1.0f);

        auto base_matrix = pane->get_piece_matrix();

        for (int y = 0; y < ycount; y++)
            for (int x = 0; x < xcount; x++)
            {
                auto yoff = y * ygap - area.y / 2;
                auto xoff = x * xgap - area.x / 2;

                auto off_vec = glm::vec3(xoff, yoff, 0.0f);
                auto matrix = glm::translate(base_matrix, off_vec);

                matrix = glm::scale(matrix, scale_vec);

                matrices.push_back(matrix);
            }


        set_matrix(base_matrix);


        get_context()->get_part<draw_manager>()->add(this);
    }

    glass_pieces::~glass_pieces()
    {
        get_context()->get_part<draw_manager>()->remove(this);
    }

    int glass_pieces::get_count() const
    {
        return static_cast<int>(matrices.size());
    }

    const glm::mat4 *glass_pieces::get_matrices() const
    {
        return matrices.data();
    }
}
