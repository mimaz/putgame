/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/world>
#include <putgame/math>

#include "autopilot.hxx"

#include "player.hxx"

namespace game
{
    constexpr auto sample_step = math::pi / 250;

    autopilot::autopilot(player *pl)
        : object(pl)
        , xmom(0)
        , ymom(0)
    {}

    void autopilot::correct()
    {
        auto tframe = get<world::way_path>()
            ->get_camera_frame() + 50;

        auto tmatrix = get<world::way_path>()
            ->point(tframe).get_matrix();

        auto target = math::coord3d(tmatrix)
            - get<world::camera>()->get_position();


        auto onaxis = [=](glm::vec3 axis, 
                          float &momentum) -> void {
            auto gr = get<world::camera>()
                ->gradient(sample_step, axis, target);

            if (gr != gr)
                return;

            momentum = 0.96f * momentum + 0.04f * gr;

            get<world::camera>()
                ->rotate(math::pi * momentum, axis);
        };


        onaxis(glm::vec3(1, 0, 0), xmom);
        onaxis(glm::vec3(0, 1, 0), ymom);
    }
}
