#ifndef FRUTTI2D_H
#define FRUTTI2D_H

#include <game/wm/wm.h>
#include <game/wm/window.h>
#include <game/wm/events.h>
#include <game/draw.h>
#include <game/texture.h>
#include <game/shader.h>

typedef struct {
    void (*wm_start_setup_func)(void);
    void (*wm_start_func)(void);
    void (*draw_func)(void);
    void (*on_event_func)(event_t);
} f2d_parameters_t;

void f2d_start(f2d_parameters_t _f2d_parameters);
void f2d_cleanup(void);

#endif
