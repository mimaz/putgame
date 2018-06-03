/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/game>
#include <putgame/common>

#include "putgame.h"

namespace
{
    struct subinstance : game::instance
    {
        subinstance(putgame *pg) : pg(pg) {}

        time_t time_millis() final
        {
            return putgame_time(pg);
        }

        putgame *const pg;
    };

      template<typename _Func, typename ..._Args>
    void callback(_Func func, _Args ...args)
    {
        if (func != nullptr)
            func(args...);
    }
}

void putgame_create(putgame *self,
                    time_t (*time_ms)(putgame *))
{
    self->on_destroy = nullptr;
    self->on_start = nullptr;
    self->on_stop = nullptr;
    self->on_draw = nullptr;
    self->on_resize = nullptr;
    self->on_cursor = nullptr;
    self->on_press = nullptr;
    self->on_release = nullptr;

    self->_time_ms = time_ms;
    self->_game_instance = new subinstance(self);
}

void putgame_destroy(struct putgame *self)
{
    callback(self->on_destroy, self);

    delete static_cast<subinstance *>(self->_game_instance);
}

void putgame_start(struct putgame *self)
{
    callback(self->on_start, self);

    static_cast<subinstance *>(self->_game_instance)->start();
}

void putgame_stop(struct putgame *self)
{
    callback(self->on_stop, self);

    static_cast<subinstance *>(self->_game_instance)->stop();
}

void putgame_draw(struct putgame *self)
{
    callback(self->on_draw, self);

    static_cast<subinstance *>(self->_game_instance)->draw();
}

void putgame_resize(struct putgame *self,
                    int width,
                    int height)
{
    callback(self->on_resize, self, width, height);

    static_cast<subinstance *>(self->_game_instance)->resize(width, height);
}

void putgame_cursor(struct putgame *self,
                    int xpos,
                    int ypos)
{
    callback(self->on_cursor, self, xpos, ypos);

    static_cast<subinstance *>(self->_game_instance)->cursor(xpos, ypos);
}

void putgame_press(struct putgame *self)
{
    callback(self->on_press, self);

    static_cast<subinstance *>(self->_game_instance)->press();
}

void putgame_release(struct putgame *self)
{
    callback(self->on_release, self);

    static_cast<subinstance *>(self->_game_instance)->release();
}

time_t putgame_time(struct putgame *self)
{
    if (self->_time_ms != nullptr)
        return self->_time_ms(self);

    common::loge("_time_ms function was not set!");

    return 0;
}
