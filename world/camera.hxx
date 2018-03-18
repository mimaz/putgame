/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_camera_hxx
#define __world_camera_hxx

#include "context_part.hxx"

namespace world
{
    class camera : public context_part
    {
    public:
        camera(context *ctx);

        ~camera();

        void set_view_angle(float angle);
        void set_view_ratio(float ratio);
        void set_view_range(float range);

        void move(const glm::vec3 &vec);
        void rotate(float angle, const glm::vec3 &axis);

        glm::mat4 get_proj() const;
        glm::mat4 get_view() const;
        glm::mat4 make_mvp(const glm::mat4 &model) const;

        glm::vec3 get_position() const;
        glm::vec3 get_direction() const;

        float get_view_angle() const { return view_angle; }
        float get_view_ratio() const { return view_ratio; }
        float get_view_range() const { return view_range; }

    private:
        mutable int flags;

        mutable glm::mat4 mvp_mat;
        mutable glm::mat4 proj_mat;

        glm::mat4 view_mat;

        float view_angle;
        float view_ratio;
        float view_range;
    };
}

#endif
