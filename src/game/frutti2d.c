#include <game/wm/wm.h>
#include <game/threads.h>

#include <GL/glew.h>

display_t *display;

void *event_thread_f(void *arg) {
    display = wm_start();
    wm_events_init(display);
    // cast argument to void function pointer, then call
    ((void (*)(void))arg)();

    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        printf("glewInit() failed\n");
        wm_events_kill();
        wm_exit(display);
        return NULL;
    }
}

void f2d_start(void (*wm_start_function)(void)) {
#ifdef IS_UNIX
    XInitThreads();
#endif
    thread_t event_thread;
    thread_create(&event_thread, &event_thread_f, wm_start_function);
    
}