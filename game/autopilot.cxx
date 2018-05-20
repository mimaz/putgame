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
    constexpr auto gradient_angle = math::pi / 250;
    constexpr auto gradient_factor = 0.05f;
    constexpr auto turning_rate = 0.15f;
    constexpr auto distance_offset = 2;

    autopilot::autopilot(player *pl)
        : object(pl)
        , xmom(0)
        , ymom(0)
    {}

    void autopilot::correct()
    {
        auto fgap = get<world::way_path>()->get_gap();
        auto foffset = static_cast<int>(distance_offset / fgap);

        auto tframe = get<world::way_path>()->get_camera_frame() + foffset;
        auto tmatrix = get<world::way_path>()->point(tframe).get_matrix();

        auto targetvec = math::coord3d(tmatrix)
            - get<world::camera>()->get_position();


        auto onaxis = [targetvec, this](glm::vec3 axis, 
                                        float &momentum) -> void {
            auto gr = get<world::camera>()
                ->gradient(gradient_angle, axis, targetvec);

            if (gr != gr)
                return;

            momentum = turning_rate * gradient_factor * gr 
                     + (1 - turning_rate) * momentum;

            get<world::camera>()->rotate(math::pi * momentum, axis);
        };


        onaxis(glm::vec3(1, 0, 0), xmom);
        onaxis(glm::vec3(0, 1, 0), ymom);
    }
}
