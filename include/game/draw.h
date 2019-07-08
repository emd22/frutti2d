#ifndef DRAW_H
#define DRAW_H

#include <game/texture.h>
#include <game/wm/window.h>
#include <game/wm/wm.h>

#define DRAW_EVENT_SINGLE_DRAW 0
#define DRAW_EVENT_CALLBACK 1

typedef struct {
    int type;
    int value;
    texture_t texture;
    void (*callback)(void);
} draw_event_t;

void draw_push_event(draw_event_t *event);
void draw_all(display_t *display, window_t *window, unsigned shader_id);

#endif
