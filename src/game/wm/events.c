#include <game/wm/events.h>
#include <game/wm/wm.h>
#include <game/wm/window.h>
#include <game/macros.h>

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

void wm_events_loop(void (*on_event)(event_t), void (*draw)(void)) {
    event_t event;
    // int i;

    while (!loop_finished) {
        usleep(700);
        draw();
        while (XPending(display)) {
            memset(&event, 0, sizeof(event_t));
            XNextEvent(display, &(event.event));

            event.type = event.event.type;

#ifdef IS_UNIX
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
#endif      
            if (event.type == EVENT_KEYPRESS) {
                last_pressed[last_pressed_index++] = wm_get_key(&event);
                if (last_pressed_index > MAX_KEYS_PRESSED)
                    last_pressed_index = 0; 
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

            on_event(event);
        }
        
// #ifdef IS_UNIX
//         FD_ZERO(&in_fds);
//         FD_SET(x11_fd, &in_fds);

//         // check to see if fd updated
//         select(x11_fd+1, &in_fds, NULL, NULL, NULL);

//         // go through all events in buffer and call on_event accordingly
//         do {
//             XNextEvent(display, &(event.event));
//             event.type = event.event.type;
//             on_event(event);
//         } while (XPending(display));
// #endif
    }
}