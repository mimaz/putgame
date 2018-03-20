/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_path_hxx
#define __world_tunnel_path_hxx

namespace world
{
    class pathway;

    class tunnel_path
    {
    public:
        class frame;

        tunnel_path(pathway *way, float gap);

        void gen_frame();

        const std::deque<frame> &get_frames() const 
        { return frames; }

        const frame &get_last_frame() const
        { return frames.back(); }

    private:
        std::deque<frame> frames;

        pathway *way;
        float gap;

        int way_point_id;
    };

    class tunnel_path::frame
    {
    public:
        frame(const glm::mat4 &matrix, int index);

        frame(const frame &) = default;
        frame(frame &&) = default;

        const glm::mat4 &get_matrix() const { return matrix; }
        int get_index() const { return index; }
        int get_hash() const { return hash; }

        float distance(const glm::vec3 &point) const;

    private:
        glm::mat4 matrix;
        int index;
        int hash;
    };
}

#endif
