#ifndef WINDOW_H
#define WINDOW_H

#include <f2d/macros.h>
#include <f2d/wm/wm.h>

#ifdef IS_UNIX
#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/glew.h>
#include <GL/glx.h>

typedef Window intern_window_t;
#endif

#define MAX_WINDOWS 8

#define WINDOW_FLAG_ROOT 0x01

#define WINDOW_EXPOSE 0x01
#define WINDOW_SIZE   0x02

#define GETINF_UNKNOWN_OPTION 1

typedef struct {
    int flags;
    unsigned width;
    unsigned height;
    intern_window_t window;
#ifdef IS_UNIX
    Atom delete_window;
#endif
} window_t;

window_t window_new(const char *title, int flags);
int window_get_info(window_t *window, int option, void *value);
window_t *find_window(intern_window_t window);
window_t *get_window_at_index(int index);
window_t *get_root_window(void);
void window_exit(window_t *window);

#endif