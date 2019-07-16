#ifndef FRUTTI2D_H
#define FRUTTI2D_H

#include <f2d/wm/wm.h>
#include <f2d/wm/window.h>
#include <f2d/wm/events.h>
#include <f2d/draw.h>
#include <f2d/texture.h>
#include <f2d/shader.h>
#include <f2d/error.h>
#include <f2d/model.h>
#include <f2d/camera.h>

#define FUNC_WM_START_SETUP 0
#define FUNC_WM_START       1
#define FUNC_DRAW           2
#define FUNC_ON_EVENT       3
#define FUNC_CLEANUP        4

void f2d_start(void);
void f2d_add_function(unsigned function_index, void (*function)(void *arg));
void f2d_cleanup(void);

#endif
