#include <f2d/wm/events.h>
#include <f2d/wm/wm.h>
#include <f2d/wm/window.h>
#include <f2d/macros.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef IS_UNIX
#include <X11/Xutil.h>
#include <X11/Xlib.h>

#include <unistd.h>
#include <sys/select.h>
#endif

char loop_finished = 0;
display_t *display;

char last_pressed[MAX_KEYS_PRESSED];
int last_pressed_index = 0;

void wm_get_mouse_coords(event_t *event, int *coords) {
#ifdef IS_UNIX
    coords[0] = event->event.xbutton.x;
    coords[1] = event->event.xbutton.y;
#endif
}

void wm_events_init(display_t *_display) {
    display = _display;
    memset(last_pressed, 0, MAX_KEYS_PRESSED);
}

void wm_events_kill(void) {
    loop_finished = 1;
}

int wm_events_is_running(void) {
    return !loop_finished;
}

char *wm_get_pressed_keys(int *length) {
    (*length) = MAX_KEYS_PRESSED;
    return last_pressed; 
}

char wm_get_key(event_t *event) {
#ifdef IS_UNIX
    return XLookupKeysym(&event->event.xkey, 0);
#endif
    return 0;
}

void wm_events_loop(void (*on_event)(void *), void (*draw)(void *)) {
    event_t event;
    event_t *new_event = malloc(sizeof(event_t));
    // int i;

    while (!loop_finished) {
        usleep(700);
        draw(NULL);
        while (XPending(display)) {
            memset(&event, 0, sizeof(event_t));
            XNextEvent(display, &(event.event));

            event.type = event.event.type;

            if (event.type == EVENT_EXPOSE) {
                window_t *root_window = get_root_window();

                if (root_window == NULL) {
                    printf("Warning: Could not find root window, setting root window to first window...\n");
                    root_window = get_window_at_index(0);
                    root_window->flags |= WINDOW_FLAG_ROOT;
                }

                int w_dim[2];
                int ret = window_get_info(root_window, WINDOW_SIZE, (void *)(&w_dim));
                if (ret != SUCCESS) {
                    printf("Error: Could not retrieve window data\n");
                }
                if (w_dim[0] != root_window->width ||
                    w_dim[1] != root_window->height)
                {
                    event.subtype = SUBTYPE_WINDOW_RESIZE;
                }
            }
            
            if (event.type == EVENT_KEYPRESS) {
                int i;
                for (i = 0; i < MAX_KEYS_PRESSED; i++) {
                    if (last_pressed[i] == 0) {
                        last_pressed[i] = wm_get_key(&event);
                        break;
                    }
                }
            }
            else if (event.type == EVENT_KEYRELEASE) {
                int i;
                char ch = wm_get_key(&event);
                for (i = 0; i < MAX_KEYS_PRESSED; i++) {
                    if (last_pressed[i] == ch) {
                        last_pressed[i] = 0;
                        break;
                    }
                }
            }
            memcpy(new_event, &event, sizeof(event_t));
            on_event(new_event);
        }
    }
    free(new_event);
}
