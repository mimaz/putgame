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

        void exit() final
        {
            putgame_exit(pg);
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

void putgame_construct(putgame *self)
{
    self->on_destruct = nullptr;
    self->on_start = nullptr;
    self->on_stop = nullptr;
    self->on_draw = nullptr;
    self->on_resize = nullptr;
    self->on_cursor = nullptr;
    self->on_press = nullptr;
    self->on_release = nullptr;
    self->on_set = nullptr;

    self->time = nullptr;
    self->exit = nullptr;

    self->_game_instance = new subinstance(self);
}

void putgame_destruct(putgame *self)
{
    callback(self->on_destruct, self);

    delete static_cast<subinstance *>(self->_game_instance);

    self->_game_instance = nullptr;
}

void putgame_start(putgame *self)
{
    callback(self->on_start, self);

    static_cast<subinstance *>(self->_game_instance)->start();
}

void putgame_stop(putgame *self)
{
    callback(self->on_stop, self);

    static_cast<subinstance *>(self->_game_instance)->stop();
}

void putgame_draw(putgame *self)
{
    callback(self->on_draw, self);

    static_cast<subinstance *>(self->_game_instance)->process();
    static_cast<subinstance *>(self->_game_instance)->draw();
}

void putgame_resize(putgame *self,
                    int width,
                    int height)
{
    callback(self->on_resize, self, width, height);

    static_cast<subinstance *>(self->_game_instance)->resize(width, height);
}

void putgame_cursor(putgame *self,
                    int xpos,
                    int ypos)
{
    callback(self->on_cursor, self, xpos, ypos);

    static_cast<subinstance *>(self->_game_instance)->cursor(xpos, ypos);
}

void putgame_press(putgame *self)
{
    callback(self->on_press, self);

    static_cast<subinstance *>(self->_game_instance)->press();
}

void putgame_release(putgame *self)
{
    callback(self->on_release, self);

    static_cast<subinstance *>(self->_game_instance)->release();
}

time_t putgame_time(putgame *self)
{
    if (self->time != nullptr)
        return self->time(self);

    common::loge("time function was not set!");

    return 0;
}

void putgame_exit(putgame *self)
{
    if (self->exit != nullptr)
        self->exit(self);
    else
        common::loge("exit function was not set!");
}

void putgame_set(putgame *self,
                 const char *key,
                 const char *value)
{
    callback(self->on_set, self, key, value);

    static_cast<subinstance *>(self->_game_instance)->set_property(key, value);
}
