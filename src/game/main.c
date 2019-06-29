#include <game/wm/window.h>
#include <game/wm/events.h>
#include <game/macros.h>
#include <game/wm/wm.h>

#include <game/threads.h>
#include <game/texture.h>
#include <game/shader.h>
#include <game/draw.h>
#include <game/file/bmp.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

#define PLR_SPEED 0.1

display_t *display = NULL;
char started = 0;
window_t window;
unsigned shader_id;
texture_t texture;
texture_t texture2;

// int key_pressed = 0;
char *keys;
int key_index = 0;
int tick = 0;

void check_keys(void) {
    int i;
    char ch;

    for (i = 0; i < key_index; i++) {
        ch = keys[i];
        if (ch == 'w')
            texture.y += PLR_SPEED;
        else if (ch == 'a')
            texture.x -= PLR_SPEED;
        else if (ch == 's')
            texture.y -= PLR_SPEED;
        else if (ch == 'd')
            texture.x += PLR_SPEED;
    }
}

void draw(void) {
    check_keys();
    draw_all(display, &window, shader_id);
}

void on_event(event_t event) {
    draw_event_t draw_event;
    switch (event.type) {
        case EVENT_CLIENTMESSAGE:
            wm_events_kill();
            break;
        case EVENT_KEYRELEASE:
            break;
        case EVENT_KEYPRESS:
            keys = wm_get_pressed_keys(&key_index);

            break;
        case EVENT_BUTTONPRESS:
            break;
        case EVENT_BUTTONRELEASE:
            break;
        // case EVENT_EXPOSE:
        //     switch (event.subtype) {
        //         case SUBTYPE_WINDOW_RESIZE:
        //             break;
        //         default:
        //             break;
        //     }
        //     break;
    }
}

void *window_thread(void) {
    window = window_new("Interesting Title", WINDOW_FLAG_ROOT);

    shader_id = shader_load("../shaders/tex.vert", "../shaders/tex.frag");
    glClearColor(0.4, 0.0, 0.6, 1.0);
    texture = texture_load("../test.bmp");
    texture.draw_width = 100;
    texture.draw_height = 100;

    // texture2 = texture_load("../frick.bmp");
    texture2 = texture_dupe(&texture);
    texture2.draw_width = 100;
    texture2.draw_height = 100;

    draw_event_t draw_event;
    draw_event.type = DRAW_EVENT_SINGLE_DRAW;
    draw_event.value = 0;
    draw_event.texture = texture;
    // memcpy(&draw_event.texture, &texture, sizeof(texture_t));
    draw_push_event(&draw_event);
    draw_event.texture = texture2;
    texture2.y = 200;
    draw_push_event(&draw_event);
    started = 1;
    
    wm_events_loop(&on_event, &draw);
    
    // texture_delete(&texture);
    // texture_delete(&texture2);
    // shader_delete(shader_id);

    wm_exit(display);
    return NULL;
}

int main() {
    draw_event_t draw_event;    
    while (!started);
    
    keys = wm_get_pressed_keys(&key_index);
    // key_pressed = 0;

    //main thread
    while (wm_events_is_running()) {
        check_keys();

        draw_event.type = 0;
        draw_event.value = 0;

        draw_event.texture = texture;
        draw_push_event(&draw_event);
        draw_event.texture = texture2;
        draw_push_event(&draw_event);
        usleep(700);
    }

    
    // unsigned char img[] = {
    //     0, 0, 0,     1, 1, 1,
    //     0, 0, 0,     1, 1, 1
    // };
    // while (wm_events_is_running());
    thread_join(event_thread, NULL);

    return 0;
}