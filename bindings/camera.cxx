/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <iostream>

namespace bindings
{
    class Camera
    {
    public:
        void set_view_angle(float angle);
        void set_view_ratio(float angle);
        void set_view_range(float angle);

        void move(float x, float y, float z);
        void move(const float *vec);
        void rotate(float angle, const float *axis);
    };

    void Camera::set_view_angle(float angle)
    {
    }

    void Camera::set_view_ratio(float angle)
    {
    }

    void Camera::set_view_range(float angle)
    {
    }

    void Camera::move(float x, float y, float z)
    {

    }

    void Camera::move(const float *vec)
    {

    }

    void Camera::rotate(float angle, const float *axis)
    {

    }
}

