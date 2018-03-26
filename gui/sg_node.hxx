/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_sg_node_hxx
#define __gui_sg_node_hxx

#include <putgame/common>

namespace gui
{
    class sg_node : public common::context::object
    {
    public:
        sg_node(common::context *ctx);
        sg_node(sg_node *parent);

        ~sg_node();

        void set_node_matrix(const glm::mat4 &matrix);
        void translate_node(glm::vec2 vec);

        const glm::mat4 &get_node_matrix() const
        { return matrix; }

        sg_node *get_parent() const 
        { return parent; }

    private:
        void set_parent_node(sg_node *parent);
        void add_child_node(sg_node *child);
        void remove_child_node(sg_node *child);

        std::set<sg_node *> childset;

        sg_node *parent;

        glm::mat4 matrix;
    };
}

#endif
