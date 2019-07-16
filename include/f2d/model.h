#ifndef MODEL_H
#define MODEL_H

typedef struct {
    unsigned long buffer_size;
    unsigned vertex_amt;
    unsigned vbo;
} model_t;

model_t model_init(float *vertices, int vertex_amt);
void model_draw(model_t *model);

#endif
