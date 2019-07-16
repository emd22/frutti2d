#ifndef MATRIX4_H
#define MATRIX4_H

typedef struct {
    float data[16];
} mat4_t;

void mat4_print(float *mul);
void mat4_translate_x(mat4_t *mat1, float *vec);
void mat4_set(mat4_t *mat, int x, int y, float value);
void mat4_fill(mat4_t *mat, const float *data);
void mat4_identity(mat4_t *out);

#endif
