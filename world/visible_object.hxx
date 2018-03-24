/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_visible_object_hxx
#define __world_visible_object_hxx

#include "context.hxx"

namespace world
{
    class context;

    class visible_object : public context::object
    {
    public:
        visible_object(context *ctx);

        visible_object(const visible_object &) = delete;
        visible_object(visible_object &&) = delete;

        void set_matrix(const glm::mat4 &mat);

        void translate(float x, float y, float z);
        void scale(float scalar);

        virtual void translate(const glm::vec3 &vec);
        virtual void rotate(float angle, const glm::vec3 &axis);
        virtual void scale(const glm::vec3 &vec);

        const glm::mat4 &get_model() const;

        glm::vec3 get_position() const;

    private:
        glm::mat4 model;
    };
}

#endif
