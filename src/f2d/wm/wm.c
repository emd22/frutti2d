#include <f2d/wm/wm.h>

#include <stdio.h>
#include <stdlib.h>

#ifdef IS_UNIX

#include <X11/Xlib.h>

Display *x11_display;

#endif

display_t *wm_start(void) {
#ifdef IS_UNIX
    x11_display = XOpenDisplay(NULL);
    if (x11_display == NULL) {
        printf("Cannot connect to X11 server\n");
        exit(1);
    }
    return x11_display;
#endif
    return NULL;
}

display_t *wm_get_display(void) {
#ifdef IS_UNIX
    return x11_display;
#endif
    return NULL;
}

void wm_exit(display_t *display) {
#ifdef IS_UNIX
    XCloseDisplay(display);
#endif
}