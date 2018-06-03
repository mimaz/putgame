/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __putgame_putgame_h
#define __putgame_putgame_h

#include <time.h>

#if defined PLATFORM_GNU_GLFW
#define PUTGAME_EXPORT __attribute__((visibility("default")))
#elif defined PLATFORM_ANDROID
#define PUTGAME_EXPORT
#else
#error invalid platform
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct putgame
{
    void (*on_destroy)(struct putgame *self);
    void (*on_start)(struct putgame *self);
    void (*on_stop)(struct putgame *self);
    void (*on_draw)(struct putgame *self);
    void (*on_resize)(struct putgame *self,
                      int width,
                      int height);
    void (*on_cursor)(struct putgame *self,
                      int xpos,
                      int ypos);
    void (*on_press)(struct putgame *self);
    void (*on_release)(struct putgame *self);
    void (*on_set)(struct putgame *self,
                   const char *key,
                   const char *value);

    time_t (*_time_ms)(struct putgame *self);
    void *_game_instance;
};

PUTGAME_EXPORT void
putgame_create(struct putgame *self,
               time_t (*time_ms)(struct putgame *self));

PUTGAME_EXPORT void
putgame_destroy(struct putgame *self);

PUTGAME_EXPORT void 
putgame_start(struct putgame *self);

PUTGAME_EXPORT void 
putgame_stop(struct putgame *self);

PUTGAME_EXPORT void
putgame_draw(struct putgame *self);

PUTGAME_EXPORT void 
putgame_resize(struct putgame *self,
               int width,
               int height);

PUTGAME_EXPORT void 
putgame_cursor(struct putgame *self,
               int width,
               int height);

PUTGAME_EXPORT void
putgame_press(struct putgame *self);

PUTGAME_EXPORT void 
putgame_release(struct putgame *self);

PUTGAME_EXPORT time_t
putgame_time(struct putgame *self);

PUTGAME_EXPORT void
putgame_set(struct putgame *self,
            const char *key,
            const char *value);

#ifdef __cplusplus
}
#endif

#endif
