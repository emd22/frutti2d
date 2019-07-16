#include <f2d/camera.h>

#include <stdio.h>
#include <f2d/math/mat4.h>

void camera_lookat() {
    // const float data[] = {
    //     1,  0,  0,  0,
    //     0,  1,  0,  0,
    //     0,  0,  1,  0,
    //     0,  0,  0,  1
    // };
    // float vec4[] = {10, 10, 10, 1};
    // mat4_t matrix;
    // mat4_fill(&matrix, data);
    // printf("old matrix:\n");
    // mat4_print(matrix.data);
    // mat4_translate_x(&matrix, vec4);
    // printf("new matrix\n");
    // mat4_print(matrix.data);
    mat4_t matrix;
    memset(&matrix, 0, sizeof(mat4_t));
    mat4_identity(&matrix);
    
}
