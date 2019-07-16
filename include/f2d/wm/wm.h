#ifndef WM_H
#define WM_H

#include <f2d/macros.h>

#include <X11/X.h>
#include <X11/Xlib.h>

#ifdef IS_UNIX
typedef Display display_t;
#endif

display_t *wm_start(void);
display_t *wm_get_display(void);
void wm_exit(display_t *display);

#endif