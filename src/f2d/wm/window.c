#include <f2d/wm/window.h>
#include <f2d/wm/wm.h>
#include <f2d/macros.h>

#include <X11/Xatom.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Document more

Window root;
GLXContext glx_context;

display_t *display;
window_t windows[MAX_WINDOWS];

int window_index = 0;

window_t window_new(const char *title, int flags) {
    // attributes to use for our GLX instance
    // RGB+A colouring; 24 bits of colour. No double buffer(also a TODO)
    const int glx_attrs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    window_t window;
    memset(&window, 0, sizeof(window_t));
    
    // get information from our x11 instance
    display = wm_get_display();

    unsigned char screen = DefaultScreen(display);

    if (flags & WINDOW_FLAG_ROOT) {
        root = RootWindow(display, screen);
        window.flags |= WINDOW_FLAG_ROOT;
    }

    XVisualInfo *visual_inf;

    visual_inf = glXChooseVisual(display, 0, (int *)glx_attrs);
    if (visual_inf == NULL) {
        printf("Error: No appropriate visual found\n");
        exit(1);
    }
    Colormap colourmap = XCreateColormap(display, root, visual_inf->visual, 0);

    XSetWindowAttributes window_attrs;
    window_attrs.colormap = colourmap;
    window_attrs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;

    window.window = XCreateWindow(
        display, root, 
        0, 0, 600, 600, 0, 
        visual_inf->depth, 
        InputOutput, 
        visual_inf->visual, 
        CWColormap | CWEventMask, 
        (&window_attrs)
    );

    XSelectInput(display, window.window, (/* ExposureMask |  */KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask));
    XStoreName(display, window.window, title);
    XMapWindow(display, window.window);
    XFlush(display);

    window.delete_window = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(display, window.window, &window.delete_window, 1);

    glx_context = glXCreateContext(display, visual_inf, NULL, GL_TRUE);
    glXMakeCurrent(display, window.window, glx_context);

    // (*context) = glx_context;

    glEnable(GL_DEPTH_TEST);
    
    int win_dimensions[2];
    window_get_info(&(window), WINDOW_SIZE, win_dimensions);

    window.width = win_dimensions[0];
    window.height = win_dimensions[1];

    if (window_index == 0) {
        memset(windows, 0, sizeof(window_t)*MAX_WINDOWS);
    }
    memcpy(&windows[window_index++], &window, sizeof(window_t));

    return window;
}

window_t *find_window(intern_window_t window) {
    int i;
    for (i = 0; i < window_index; i++) {
        if (memcmp(&(windows[i].window), &window, sizeof(intern_window_t))) {
            return &(windows[i]);
        }
    }
    return NULL;
}

window_t *get_window_at_index(int index) {
    if (index > window_index || index < 0)
        return NULL;
    return &(windows[index]);
}

window_t *get_root_window(void) {
    int i;
    window_t *window;
    for (i = 0; i < window_index; i++) {
        window = &windows[i];
        if (window->flags & WINDOW_FLAG_ROOT)
            return window;
    }
    return NULL;
}

int window_get_info(window_t *window, int option, void *value) {
#ifdef IS_UNIX
    XWindowAttributes attrs;
#endif
    switch (option) {
        case WINDOW_SIZE:
        #ifdef IS_UNIX
            XGetWindowAttributes(display, window->window, &attrs);
            ((int *)value)[0] = attrs.width;
            ((int *)value)[1] = attrs.height;
        #endif
            return SUCCESS;
        default:
            return GETINF_UNKNOWN_OPTION;
    }
    return FAILURE;
}

void window_exit(window_t *window) {
#ifdef IS_UNIX
    XDestroyWindow(display, window->window);
#endif
}
