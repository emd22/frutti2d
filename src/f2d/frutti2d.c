#include <f2d/frutti2d.h>

#include <stdio.h>
#include <string.h>

#include <f2d/wm/wm.h>
#include <f2d/wm/events.h>
#include <f2d/threads.h>

#include <GL/glew.h>

#define MAX_FUNCTIONS 8
#define FUNC(type, arg) functions[type](arg)

display_t *display;
thread_t event_thread;

void stub(void *arg) {
    (void)arg;
}

void (*functions[MAX_FUNCTIONS])(void *) = { stub, stub, stub, stub, stub, stub, stub, stub };

void *event_thread_f(void *arg) {
    display = wm_start();

    wm_events_init(display);
    int glew_return;

    functions[FUNC_WM_START_SETUP](NULL);

    glewExperimental = 1;
    if ((glew_return = glewInit()) != GLEW_OK) {
        printf("glewInit() failed with return code %d\n", glew_return);
        wm_events_kill();
        wm_exit(display);
        return NULL;
    }

    functions[FUNC_WM_START](NULL);
    wm_events_loop(functions[FUNC_ON_EVENT], functions[FUNC_DRAW]);

    functions[FUNC_CLEANUP](NULL);
    wm_exit(display);

    return NULL;
}

void f2d_add_function(unsigned function_index, void (*function)(void *arg)) {
    if (function_index > MAX_FUNCTIONS) {
        printf("f2d_add_function: function index(%u) too great or too small.\n", function_index);
        return;
    }
    
    functions[function_index] = function;
}

void f2d_start(void) {
#ifdef IS_UNIX
    XInitThreads();
#endif
    thread_create(&event_thread, &event_thread_f, NULL);
}

void f2d_cleanup(void) {
    thread_join(event_thread, NULL);
}
