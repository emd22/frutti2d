#include <game/draw.h>

#include <string.h>
#include <stdio.h>

#include <game/macros.h>
#include <game/wm/window.h>

draw_event_t draw_events[64];
unsigned draw_event_index = 0;

void draw_push_event(draw_event_t *event) {
    draw_event_t *draw_event = &draw_events[draw_event_index++];
    memcpy(draw_event, event, sizeof(draw_event_t));
}

void draw_all(display_t *display, window_t *window, unsigned shader_id) {
    if (!draw_event_index)
        return;
    draw_event_t *event;
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_id);
    for (i = 0; i < draw_event_index; i++) {
        event = &draw_events[i];
        if (event->type == DRAW_EVENT_SINGLE_DRAW) {
            texture_render(&event->texture);
        }
    }

    // glViewport(0, 0, 600, 600);
    // draw_quad();

#ifdef IS_UNIX
    glXSwapBuffers(display, window->window);
#endif
    draw_event_index = 0;
}