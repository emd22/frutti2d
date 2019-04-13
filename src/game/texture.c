#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>

GLuint vaid;
GLuint vbuf;

static const GLfloat buf_dat[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
};

void texture_init(int width, int height, unsigned char *pixels) {
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    

    // glGenFramebuffers(1, &fbo_id);
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_id);
    // glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glGenVertexArrays(1, &vaid);
    glBindVertexArray(vaid);
    
    glGenBuffers(1, &vbuf);
    glBindBuffer(GL_ARRAY_BUFFER, vbuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buf_dat), buf_dat, GL_STATIC_DRAW);
}

void texture_render(int width, int height) {
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_id);
    // glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbuf);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}