/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_hxx
#define __world_tunnel_hxx

#include "context_part.hxx"

namespace world
{
    class tunnel : public context_part
    {
    public:
        class frame;

        tunnel(context *ctx);

        void append(float distance, float angle, const glm::vec3 &axis);
        void append(const glm::mat4 &tranform);

        void draw();

    private:
        void update_camera_index();

        std::deque<frame> list;
        int camera_index;
    };

    class tunnel::frame
    {
    public:
        frame(int index, const glm::mat4 &model);

        frame(const frame &) = default;
        frame(frame &&) = default;

        int get_index() const { return index; }
        const glm::mat4 &get_model() const { return model; }
        float distance(const glm::vec3 &point) const;

    private:
        int index;
        glm::mat4 model;
    };
}

#endif
