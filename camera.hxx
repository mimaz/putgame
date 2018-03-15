/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_camera_hxx
#define __world_camera_hxx

namespace world
{
    class camera
    {
    public:
        camera();

        ~camera();

        glm::mat4 get_proj() const;
        glm::mat4 get_view() const;
        glm::mat4 get_mvp(const glm::mat4 &model) const;

    private:
        glm::mat4 proj_mat;
        glm::mat4 view_mat;
    };
}

#endif
