#include <game/frutti2d.h>

#include <stdio.h>
#include <string.h>

#include <game/wm/wm.h>
#include <game/wm/events.h>
#include <game/threads.h>

#include <GL/glew.h>

display_t *display;
thread_t event_thread;
f2d_parameters_t f2d_parameters;

void *event_thread_f(void *arg) {
    display = wm_start();

    wm_events_init(display);
    int glew_return;

    f2d_parameters.wm_start_setup_func();

    glewExperimental = 1;
    if ((glew_return = glewInit()) != GLEW_OK) {
        printf("glewInit() failed with ret code %d\n", glew_return);
        wm_events_kill();
        wm_exit(display);
        return NULL;
    }

    f2d_parameters.wm_start_func();

    wm_events_loop(f2d_parameters.on_event_func, f2d_parameters.draw_func);
    wm_exit(display);

    return NULL;
}

void f2d_start(f2d_parameters_t _f2d_parameters) {
    memcpy(&f2d_parameters, &_f2d_parameters, sizeof(f2d_parameters_t));
#ifdef IS_UNIX
    XInitThreads();
#endif
    thread_create(&event_thread, &event_thread_f, NULL);
}

void f2d_cleanup(void) {
    thread_join(event_thread, NULL);
}