/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

module world.camera;

extern (C++, bindings)
{
    class Camera
    {
        @disable this();

        void set_view_angle(float angle);
        void set_view_ratio(float ratio);
        void set_view_range(float range);

        void move(float x, float y, float z);
        void move(const float* vec);
        void rotate(float angle, const float* axis);
    }
}
