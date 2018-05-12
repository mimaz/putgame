/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __bindings_libgame_h
#define __bindings_libgame_h

#ifdef __cplusplus
extern "C" {
#endif

typedef void *libgame;

libgame     libgame_create      ();

void        libgame_destroy     (libgame self);

void        libgame_start       (libgame self);

void        libgame_stop        (libgame self);

void        libgame_draw        (libgame self);

#ifdef __cplusplus
}
#endif

#endif
