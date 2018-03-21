/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "wall_obstacle_view.hxx"

const float world::wall_obstacle_view::mesh[] = {
    /*
     * data layout
     *
     * xyzghitsm
     *
     * xyz - coordinates
     * ghi - normal
     * ts  - texture
     * m   - mode
     *
     * 9 bytes per vertex
     */

    /*
     * front face
     */
    -0.5f, -0.5f, 0.5f, 0, 0, 1, 0, 0, 1,
    -0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 1, 1,
    0.5f, 0.5f, 0.5f, 0, 0, 1, 1, 1, 1,

    -0.5f, -0.5f, 0.5f, 0, 0, 1, 0, 0, 1,
    0.5f, 0.5f, 0.5f, 0, 0, 1, 1, 1, 1,
    0.5f, -0.5f, 0.5f, 0, 0, 1, 1, 0, 1,

    /*
     * back face
     */
    0.5f, -0.5f, -0.5f, 0, 0, -1, 0, 0, 1,
    0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 1, 1,
    -0.5f, 0.5f, -0.5f, 0, 0, -1, 1, 1, 1,

    0.5f, -0.5f, -0.5f, 0, 0, -1, 0, 0, 1,
    -0.5f, 0.5f, -0.5f, 0, 0, -1, 1, 1, 1,
    -0.5f, -0.5f, -0.5f, 0, 0, -1, 1, 0, 1,

    /*
     * left
     */
    -0.5f, -0.5f, 0.5f, -1, 0, 0, 0, 0, 1,
    -0.5f, -0.5f, -0.5f, -1, 0, 0, 0, 0, 1,
    -0.5f, 0.5f, -0.5f, -1, 0, 0, 0, 0, 1,

    -0.5f, -0.5f, 0.5f, -1, 0, 0, 0, 0, 1,
    -0.5f, 0.5f, -0.5f, -1, 0, 0, 0, 0, 1,
    -0.5f, 0.5f, 0.5f, -1, 0, 0, 0, 0, 1,

    /*
     * top
     */
    -0.5f, 0.5f, 0.5f, 0, 1, 0, 0, 0, 1,
    -0.5f, 0.5f, -0.5f, 0, 1, 0, 0, 0, 1,
    0.5f, 0.5f, -0.5f, 0, 1, 0, 0, 0, 1,

    -0.5f, 0.5f, 0.5f, 0, 1, 0, 0, 0, 1,
    0.5f, 0.5f, -0.5f, 0, 1, 0, 0, 0, 1,
    0.5f, 0.5f, 0.5f, 0, 1, 0, 0, 0, 1,

    /*
     * right
     */
    0.5f, -0.5f, 0.5f, 1, 0, 0, 0, 0, 1,
    0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 0, 1,
    0.5f, 0.5f, -0.5f, 1, 0, 0, 0, 0, 1,

    0.5f, -0.5f, 0.5f, 1, 0, 0, 0, 0, 1,
    0.5f, 0.5f, -0.5f, 1, 0, 0, 0, 0, 1,
    0.5f, -0.5f, -0.5f, 1, 0, 0, 0, 0, 1,

    /*
     * bottom
     */
    -0.5f, -0.5f, 0.5f, 0, -1, 0, 0, 0, 1,
    0.5f, -0.5f, 0.5f, 0, -1, 0, 0, 0, 1,
    0.5f, -0.5f, -0.5f, 0, -1, 0, 0, 0, 1,

    -0.5f, -0.5f, 0.5f, 0, -1, 0, 0, 0, 1,
    0.5f, -0.5f, -0.5f, 0, -1, 0, 0, 0, 1,
    -0.5f, -0.5f, -0.5f, 0, -1, 0, 0, 0, 1,
};

const size_t world::wall_obstacle_view::size_of_mesh =
    sizeof(mesh);