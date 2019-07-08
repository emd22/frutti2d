#include <game/draw.h>

#include <string.h>
#include <stdio.h>

#include <game/macros.h>
#include <game/texture.h>
#include <game/wm/window.h>
#include <game/wm/wm.h>

#define DRAW_EVENTS_MAX 256

draw_event_t draw_events[DRAW_EVENTS_MAX];
unsigned draw_event_index = 0;

void draw_push_event(draw_event_t *event) {
    if (draw_event_index == DRAW_EVENTS_MAX) {
        //printf("WARNING: draw event buffer full, please run draw_all to clear buffer or increase DRAW_EVENTS_MAX.\n");
        return;
    }
    draw_event_t *draw_event = &draw_events[draw_event_index++];
    memcpy(draw_event, event, sizeof(draw_event_t));
}

void draw_all(display_t *display, window_t *window, unsigned shader_id) {
    if (!draw_event_index)
        return;
    if (display == NULL) {
        display = wm_get_display();
    }

    draw_event_t *event;
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_id);
    for (i = 0; i < draw_event_index; i++) {
        event = &draw_events[i];
        if (event->type == DRAW_EVENT_SINGLE_DRAW) {
            texture_render(&event->texture);
        }
        else if (event->type == DRAW_EVENT_CALLBACK) {
            event->callback();
        }
    }

#ifdef IS_UNIX
    glXSwapBuffers(display, window->window);
#endif
    printf("didx: %d\n", draw_event_index);
    draw_event_index = 0;
}
