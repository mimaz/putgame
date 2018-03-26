/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "sg_node.hxx"

namespace gui
{
    sg_node::sg_node(common::context *ctx)
        : object(ctx)
        , parent(nullptr)
    {
    }

    sg_node::sg_node(sg_node *parent)
        : sg_node(parent->get_context())
    {
        set_parent_node(parent);
    }

    sg_node::~sg_node()
    {
        if (get_parent() != nullptr)
            get_parent()->remove_child_node(this);

        for (auto child : childset)
            child->set_parent_node(get_parent());
    }

    void sg_node::set_node_matrix(const glm::mat4 &mat)
    {
        matrix = mat;
    }

    void sg_node::translate_node(glm::vec2 vec)
    {
        matrix = glm::translate(matrix, glm::vec3(vec, 0.0f));
    }

    void sg_node::set_parent_node(sg_node *par)
    {
        if (par != get_parent())
        {
            if (get_parent() != nullptr)
                get_parent()->remove_child_node(this);

            parent = par;

            if (get_parent() != nullptr)
                get_parent()->add_child_node(this);
        }
    }

    void sg_node::add_child_node(sg_node *child)
    {
        if (childset.find(child) != childset.end())
        {
            childset.insert(child);
            child->set_parent_node(this);
        }
    }

    void sg_node::remove_child_node(sg_node *child)
    {
        if (childset.find(child) == childset.end())
        {
            childset.erase(child);
            child->set_parent_node(get_parent());
        }
    }
}
