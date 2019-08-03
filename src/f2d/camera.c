#include <f2d/camera.h>

#include <stdio.h>
#include <f2d/math/mat4.h>

#include <GL/glew.h>
#include <GL/gl.h>

void camera_lookat(unsigned shader) {
     const float data[] = {
         100,  100,    0,  0,
           0,  100,  100,  0,
           0,    0,    1,  0,
         100,  100,    0,  1
    };
    float vec4[] = {100, 10, 10, 1};
    mat4_t matrix;
    // printf("new matrix\n");
    // mat4_print(matrix.data);
    // mat4_t matrix;
    // memset(&matrix, 0, sizeof(mat4_t));
    // mat4_identity(&matrix);
    int view = glGetUniformLocation(shader, "view");
    mat4_fill(&matrix, data);
    // printf("old matrix:\n");
    // mat4_print(matrix.data);
    mat4_translate_x(&matrix, vec4);
    glUniformMatrix4fv(view, 1, GL_FALSE, matrix.data);
    
}
