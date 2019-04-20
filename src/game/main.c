#include <game/wm/window.h>
#include <game/wm/events.h>
#include <game/macros.h>
#include <game/wm/wm.h>

#include <game/threads.h>
#include <game/texture.h>
#include <game/shader.h>
#include <game/file/bmp.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

display_t *display = NULL;
char started = 0;
GLXContext glx_context;
window_t window;
unsigned shader_id;
unsigned texture;

// struct {
//   unsigned int 	 width;
//   unsigned int 	 height;
//   unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
//   unsigned int	 pixels[10 * 10 * 3 + 1];
// } img = {
//   10, 10, 3,
//   0xD5, 0x8E, 0x31, 0xD5, 0x8E, 0x31, 0xD5, 0x8E, 0x31, 0x00, 0xA8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA8, 0xFF, 0xD5, 0x8E, 0x31, 0xD5, 0x8E, 0x31, 0xD5, 0x8E, 0x31, 0x00, 0x00, 0xD5, 0x8E, 0x31, 0x00, 0xA8, 0xFF, 0x00, 0xA8, 0xFF, 0x09, 0x09, 0xFF, 0x09, 0x09, 0xFF, 0x09, 0x09, 0xFF, 0x09, 0x09, 0xFF, 0x00, 0xA8, 0xFF, 0x00, 0xA8, 0xFF, 0xD5, 0x8E, 0x31, 0x00, 0x00, 0xD5, 0x8E, 0x31, 0x00, 0xA8, 0xFF, 0x09, 0x09, 0xFF, 0x09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 00, A8, FF, D5, 8E, 31, 00, 00, 00, A8, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 00, A8, FF, 00, 00, 00, 00, 00, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 00, 00, 00, 00, 00, 00, 00, 00, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 00, 00, 00, 00, 00, 00, A8, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 00, A8, FF, 00, 00, D5, 8E, 31, 00, A8, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 00, A8, FF, D5, 8E, 31, 00, 00, D5, 8E, 31, 00, A8, FF, 00, A8, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 09, 09, FF, 00, A8, FF, 00, A8, FF, D5, 8E, 31, 00, 00, D5, 8E, 31, D5, 8E, 31, D5, 8E, 31, 00, A8, FF, 00, 00, 00, 00, 00, 00, 00, A8, FF, D5, 8E, 31, D5, 8E, 31, D5, 8E, 31, 00, 00
// };

void draw_quad(void) {
    // glClearColor(1.0, 1.0, 1.0, 1.0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(-1., 1., -1., 1., 1., 20.);

    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    
    // gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // glBegin(GL_QUADS);
    // glColor3f(1, 0, 0); glVertex3f(-0.75, -0.75, 0.0);
    // glColor3f(0, 1, 0); glVertex3f( 0.75, -0.75, 0.0);
    // glColor3f(0, 0, 1); glVertex3f( 0.75,  0.75, 0.0);
    // glColor3f(1, 1, 0); glVertex3f(-0.75,  0.75, 0.0);
    // glEnd();
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glViewport(0, 0, 600, 600);
    printf("shd id: %u\n", shader_id);
    // draw_quad();

    glUseProgram(shader_id);
    texture_render(texture, 50, 50);

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
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        printf("glew failed\n");
        wm_events_kill();
        wm_exit(display);
        return NULL;
    }
    started = 1;


    unsigned char image[] = {
        0, 255, 0,     255, 255, 255,
        0, 255, 0,     255, 255, 255
    };
    shader_id = shader_load("../shaders/tex.vert", "../shaders/tex.frag");
    glClearColor(0.4, 0.0, 0.6, 1.0);
    bmp_file_t bmp = bmp_open("../test.bmp");
    texture = texture_init(10, 10, bmp.data);
    wm_events_loop(&on_event);
    texture_delete();
    glDeleteProgram(shader_id);
    printf("done\n");
    wm_exit(display);
    return NULL;
}

int main() {
    thread_t event_thread;
    thread_create(&event_thread, &window_thread, NULL);
    
    while (!started);
    // unsigned char img[] = {
    //     0, 0, 0,     1, 1, 1,
    //     0, 0, 0,     1, 1, 1
    // };
    // while (wm_events_is_running());
    thread_join(event_thread, NULL);

    return 0;
}