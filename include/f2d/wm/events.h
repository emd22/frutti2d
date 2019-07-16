#ifndef EVENTS_H
#define EVENTS_H

#include <f2d/macros.h>
#include <f2d/wm/wm.h>

#define MAX_KEYS_PRESSED 12

#ifdef IS_UNIX

#define EVENT_EXPOSE Expose
#define EVENT_KEYPRESS KeyPress
#define EVENT_KEYRELEASE KeyRelease
#define EVENT_BUTTONPRESS ButtonPress
#define EVENT_BUTTONRELEASE ButtonRelease
#define EVENT_CLIENTMESSAGE ClientMessage

#define SUBTYPE_WINDOW_RESIZE 1
#define SUBTYPE_WINDOW_MOVED  2
#endif

typedef struct {
#ifdef IS_UNIX
    XEvent event;
#endif
    int type;
    int subtype;
} event_t;

void wm_get_mouse_coords(event_t *event, int *coords);
void wm_events_init(display_t *_display);
char wm_get_key(event_t *event);
char *wm_get_pressed_keys(int *length);
void wm_events_loop(void (*on_event)(void *), void (*draw)(void *));
int wm_events_is_running(void);
void wm_events_kill(void);

#endif
