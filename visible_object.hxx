/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __visible_object_hxx
#define __visible_object_hxx

namespace world
{
    class context;

    class visible_object
    {
    public:
        visible_object(context *ctx);

        visible_object(const visible_object &) = delete;
        visible_object(visible_object &&) = delete;

        virtual ~visible_object();

        void set_matrix(const glm::mat4 &mat);

        void move(const glm::vec3 &vec);
        void rotate(float angle, const glm::vec3 &axis);

        virtual void draw();

        context *get_context() const { return ctx; }
        const glm::mat4 &get_model() const { return model; }

    private:
        context *const ctx;

        glm::mat4 model;
    };
}

#endif
