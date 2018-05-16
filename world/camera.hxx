/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_camera_hxx
#define __world_camera_hxx

#include <putgame/common>

#include "light_source.hxx"

namespace world
{
    class camera : public common::context::object, public light_source
    {
    public:
        camera(common::context *ctx);

        void set_view_angle(float angle);
        void set_view_ratio(float ratio);
        void set_view_range(float range);

        void move(float x, float y, float z);
        void move(const glm::vec3 &vec);
        void rotate(float angle, const glm::vec3 &axis);

        const glm::mat4 &get_proj() const;
        const glm::mat4 &get_view() const;
        const glm::mat4 &get_view_proj() const;
        glm::mat4 make_mvp(const glm::mat4 &model) const;

        glm::vec3 get_position() const;
        glm::vec3 get_direction() const;
        glm::vec3 get_top() const;

        float get_view_angle() const { return view_angle; }
        float get_view_ratio() const { return view_ratio; }
        float get_view_range() const { return view_range; }

        glm::vec3 get_light_position() override;
        glm::vec3 get_light_color() override;
        float get_light_range() override;

    private:
        glm::mat4 inversed_view() const;

        mutable int flags;

        mutable glm::mat4 proj_mat;
        mutable glm::mat4 view_proj_mat;

        glm::mat4 view_mat;

        float view_angle;
        float view_ratio;
        float view_range;
    };
}

#endif
