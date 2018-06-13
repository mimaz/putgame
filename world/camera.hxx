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
        PUTGAME_OBJECT

        camera(common::context *ctx);

        void set_view_angle(float angle);
        void set_view_ratio(float ratio);
        void set_view_range(float range);

        void move(const glm::vec3 &vec);
        void absolute_move(const glm::vec3 &vec);
        void rotate(float angle, const glm::vec3 &axis);
        void apply(const glm::mat4 &matrix);
        float gradient(float angle, 
                       glm::vec3 axis, 
                       glm::vec3 targetvec);

        const glm::mat4 &get_proj();
        const glm::mat4 &get_view();
        const glm::mat4 &get_view_proj();
        glm::mat4 make_mvp(const glm::mat4 &model);

        glm::vec3 get_position();
        glm::vec3 get_direction();
        glm::vec3 get_top();

        float get_view_angle() const { return view_angle; }
        float get_view_ratio() const { return view_ratio; }
        float get_view_range() const { return view_range; }

        glm::vec3 get_light_position() override;
        glm::vec3 get_light_color() override;
        float get_light_range() override;

        int get_frame_id();

    private:
        glm::mat4 inversed_view();
        void update_frame_id();

        glm::mat4 proj_mat;
        glm::mat4 view_proj_mat;
        glm::mat4 view_mat;
        glm::mat4 view_inverse_mat;

        int flags;

        float view_angle;
        float view_ratio;
        float view_range;

        int frame_id;
    };
}

#endif
