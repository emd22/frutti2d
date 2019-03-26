#include <game/wm/window.h>
#include <game/wm/events.h>
#include <game/macros.h>
#include <game/wm/wm.h>

#include <game/threads.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

display_t *display = NULL;
GLXContext glx_context;
window_t window;

void draw_quad(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1., 1., -1., 1., 1., 20.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0); glVertex3f(-.75, -.75, 0.);
    glColor3f(0, 1, 0); glVertex3f( .75, -.75, 0.);
    glColor3f(0, 0, 1); glVertex3f( .75,  .75, 0.);
    glColor3f(1, 1, 0); glVertex3f(-.75,  .75, 0.);
    glEnd();
}

void draw(void) {
    glViewport(0, 0, 600, 600);
    draw_quad();
    glXSwapBuffers(display, window.window);
}

void on_event(event_t event) {
    switch (event.type) {
        case EVENT_CLIENTMESSAGE:
        case EVENT_KEYPRESS:
            wm_events_kill();
            break;
        case EVENT_EXPOSE:
            switch (event.subtype) {
                case SUBTYPE_WINDOW_RESIZE:
                    break;
                default:
                    break;
            }
            draw();
            break;
    }
}

void *window_thread(void *arg) {
#ifdef IS_UNIX
    XInitThreads();
#endif
    display = wm_start();
    wm_events_init(display);
    window = window_new("fut", WINDOW_FLAG_ROOT, &glx_context);
    wm_events_loop(&on_event);
    wm_exit(display);
    return NULL;
}

int main() {
    thread_t event_thread;
    thread_create(&event_thread, &window_thread, NULL);

    while (wm_events_is_running()) {
        
    }

    return 0;
}