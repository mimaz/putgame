/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "light_box_view.hxx"

#include "constants.hxx"

constexpr float F = world::light_box_size;
constexpr float N = 0.6f * F;

const float world::light_box_view::mesh[] = {
    -N, -N, F, 0, 0, 1,
    -N, N, F, 0, 0, 1,
    N, N, F, 0, 0, 1,

    -N, -N, F, 0, 0, 1,
    N, N, F, 0, 0, 1,
    N, -N, F, 0, 0, 1,


    -F, -N, -N, -1, 0, 0, 
    -F, N, -N, -1, 0, 0,
    -F, N, N, -1, 0, 0,

    -F, -N, -N, -1, 0, 0,
    -F, N, N, -1, 0, 0,
    -F, -N, N, -1, 0, 0,


    N, -N, -F, 0, 0, -1,
    N, N, -F, 0, 0, -1,
    -N, N, -F, 0, 0, -1,

    N, -N, -F, 0, 0, -1,
    -N, N, -F, 0, 0, -1,
    -N, -N, -F, 0, 0, -1,


    F, -N, N, 1, 0, 0,
    F, N, N, 1, 0, 0,
    F, N, -N, 1, 0, 0,

    F, -N, N, 1, 0, 0, 
    F, N, -N, 1, 0, 0, 
    F, -N, -N, 1, 0, 0,


    -N, F, N, 0, 1, 0,
    -N, F, -N, 0, 1, 0,
    N, F, -N, 0, 1, 0,

    -N, F, N, 0, 1, 0,
    N, F, -N, 0, 1, 0,
    N, F, N, 0, 1, 0,


    -N, -F, -N, 0, -1, 0,
    -N, -F, N, 0, -1, 0,
    N, -F, N, 0, -1, 0,

    -N, -F, -N, 0, -1, 0,
    N, -F, N, 0, -1, 0,
    N, -F, -N, 0, -1, 0,




    -N, -N, F, -1, -1, 1,
    -N, -F, N, -1, -1, 1,
    -F, -N, N, -1, -1, 1,

    -N, N, F, -1, 1, 1,
    -F, N, N, -1, 1, 1,
    -N, F, N, -1, 1, 1,

    N, N, F, 1, 1, 1, 
    N, F, N, 1, 1, 1,
    F, N, N, 1, 1, 1,

    N, -N, F, 1, -1, 1,
    F, -N, N, 1, -1, 1,
    N, -F, N, 1, -1, 1,


    N, -N, -F, 1, -1, -1,
    N, -F, -N, 1, -1, -1,
    F, -N, -N, 1, -1, -1,

    N, N, -F, 1, 1, -1,
    F, N, -N, 1, 1, -1,
    N, F, -N, 1, 1, -1,

    -N, N, -F, -1, 1, -1,
    -N, F, -N, -1, 1, -1,
    -F, N, -N, -1, 1, -1,

    -N, -N, -F, -1, -1, -1,
    -F, -N, -N, -1, -1, -1,
    -N, -F, -N, -1, -1, -1,



    -N, -N, F, -1, 0, 1,
    -F, -N, N, -1, 0, 1,
    -F, N, N, -1, 0, 1,

    -N, -N, F, -1, 0, 1,
    -F, N, N, -1, 0, 1,
    -N, N, F, -1, 0, 1,


    -N, N, F, 0, 1, 1,
    -N, F, N, 0, 1, 1,
    N, F, N, 0, 1, 1,

    -N, N, F, 0, 1, 1,
    N, F, N, 0, 1, 1, 
    N, N, F, 0, 1, 1,


    N, N, F, 1, 0, 1,
    F, N, N, 1, 0, 1,
    F, -N, N, 1, 0, 1,
     
    N, N, F, 1, 0, 1,
    F, -N, N, 1, 0, 1,
    N, -N, F, 1, 0, 1,


    N, -N, F, 0, -1, 1,
    N, -F, N, 0, -1, 1,
    -N, -F, N, 0, -1, 1,

    N, -N, F, 0, -1, 1,
    -N, -F, N, 0, -1, 1,
    -N, -N, F, 0, -1, 1,



    N, -N, -F, 1, 0, -1,
    F, -N, -N, 1, 0, -1,
    F, N, -N, 1, 0, -1,

    N, -N, -F, 1, 0, -1,
    F, N, -N, 1, 0, -1,
    N, N, -F, 1, 0, -1,


    N, N, -F, 0, 1, -1,
    N, F, -N, 0, 1, -1,
    -N, F, -N, 0, 1, -1,

    N, N, -F, 0, 1, -1,
    -N, F, -N, 0, 1, -1,
    -N, N, -F, 0, 1, -1,


    -N, N, -F, -1, 0, -1,
    -F, N, -N, -1, 0, -1,
    -F, -N, -N, -1, 0, -1,

    -N, N, -F, -1, 0, -1,
    -F, -N, -N, -1, 0, -1,
    -N, -N, -F, -1, 0, -1,


    -N, -N, -F, 0, -1, -1,
    -N, -F, -N, 0, -1, -1,
    N, -F, -N, 0, -1, -1,

    -N, -N, -F, 0, -1, -1,
    N, -F, -N, 0, -1, -1,
    N, -N, -F, 0, -1, -1,



    -F, N, N, -1, 1, 0,
    -F, N, -N, -1, 1, 0,
    -N, F, -N, -1, 1, 0,

    -F, N, N, -1, 1, 0,
    -N, F, -N, -1, 1, 0,
    -N, F, N, -1, 1, 0,


    N, F, N, 1, 1, 0,
    N, F, -N, 1, 1, 0,
    F, N, -N, 1, 1, 0,

    N, F, N, 1, 1, 0,
    F, N, -N, 1, 1, 0,
    F, N, N, 1, 1, 0,


    F, -N, N, 1, -1, 0,
    F, -N, -N, 1, -1, 0,
    N, -F, -N, 1, -1, 0,

    F, -N, N, 1, -1, 0,
    N, -F, -N, 1, -1, 0,
    N, -F, N, 1, -1, 0,


    -F, -N, N, -1, -1, 0,
    -N, -F, N, -1, -1, 0,
    -N, -F, -N, -1, -1, 0,

    -F, -N, N, -1, -1, 0,
    -N, -F, -N, -1, -1, 0,
    -F, -N, -N, -1, -1, 0,
};

const size_t world::light_box_view::size_of_mesh = sizeof(mesh);
