/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __putgame_putgame_h
#define __putgame_putgame_h

#include <time.h>

#define PUTGAME_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

#define PUTGAME_LEFT 0
#define PUTGAME_RIGHT 1
#define PUTGAME_UP 2
#define PUTGAME_DOWN 3
#define PUTGAME_START 4

struct putgame
{
    void (*on_destruct)(struct putgame *self);
    void (*on_start)(struct putgame *self);
    void (*on_stop)(struct putgame *self);
    void (*on_draw)(struct putgame *self);
    void (*on_resize)(struct putgame *self,
                      int width,
                      int height);
    void (*on_cursor)(struct putgame *self,
                      int xpos,
                      int ypos);
    void (*on_key)(struct putgame *self,
                   int keycode);
    void (*on_press)(struct putgame *self);
    void (*on_release)(struct putgame *self);
    void (*on_get_int)(struct putgame *self,
                       const char *key,
                       int def);
    void (*on_set_int)(struct putgame *self,
                       const char *key,
                       int value);

    time_t (*time)(struct putgame *self);
    void (*exit)(struct putgame *self);

    void *_game_instance;
};

PUTGAME_EXPORT void
putgame_construct(struct putgame *self);

PUTGAME_EXPORT void
putgame_destruct(struct putgame *self);

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
putgame_key(struct putgame *self,
            int direction);

PUTGAME_EXPORT void
putgame_press(struct putgame *self);

PUTGAME_EXPORT void 
putgame_release(struct putgame *self);

PUTGAME_EXPORT time_t
putgame_time(struct putgame *self);

PUTGAME_EXPORT void
putgame_exit(struct putgame *self);

PUTGAME_EXPORT int
putgame_get_int(struct putgame *self,
                const char *key,
                int def);

PUTGAME_EXPORT void
putgame_set_int(struct putgame *self,
                const char *key,
                int value);

#ifdef __cplusplus
}
#endif

#endif
