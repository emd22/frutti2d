#include <f2d/model.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GL/gl.h>

model_t model_init(float *vertices, int vertex_amt) {
    model_t model;
    unsigned vbo;
    unsigned long buffer_size;

    memset(&model, 0, sizeof(model_t));
    // generate buffer for vertex buffer object
    glGenBuffers(1, &vbo);
    // bind array buffer to vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // find the size for vbo (vertex_amt(x, y, and z)*sizeof float)
    buffer_size = (vertex_amt*3)*sizeof(float);
    // copy vertices to vbo
    glBufferData(GL_ARRAY_BUFFER, buffer_size, vertices, GL_STATIC_DRAW);
    
    // fill data in for model_t structure
    model.vbo = vbo;
    model.buffer_size = buffer_size;
    model.vertex_amt = vertex_amt;
    
    return model;
}

void model_draw(model_t *model) {
    // use vertex positions from shader 0 (TODO: more shaders)
    //glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
    glVertexAttribPointer(0, model->vertex_amt, GL_FLOAT, GL_FALSE, 0, (void *)0);
    // finally draw the buffer
    glDrawArrays(GL_TRIANGLES, 0, model->vertex_amt);
    //glDisableVertexAttribArray(0);
}
// model_t *model_init(float *vertices, int vertex_amt) {
//     model_t *model = malloc(sizeof(model_t));
//     model->vertex_amt = vertex_amt;
//     
//     glGenBuffers(1, &model->vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex_amt, vertices, GL_STATIC_DRAW);
//     return model;
// }

// void model_draw(model_t *model) {
//     glEnableVertexAttribArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
//     glVertexAttribPointer(0, model->vertex_amt, GL_FLOAT, GL_FALSE, 0, NULL);
//     glDrawArrays(GL_TRIANGLES, 0, model->vertex_amt);
//     glDisableVertexAttribArray(0);
// }

// void model_destroy(model_t *model) {
//     free(model);
// }
