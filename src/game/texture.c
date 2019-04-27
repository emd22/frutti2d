#include <game/texture.h>
#include <game/file/bmp.h>
#include <game/wm/window.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// GLuint vaid;
// GLuint vbuf;

// static const GLfloat buf_dat[] = {
//     -1.0f, -1.0f, 0.0f,
//      1.0f, -1.0f, 0.0f,
//      0.0f,  1.0f, 0.0f,
// };

void texture_init(texture_t *texture) {
    unsigned texture_id;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, texture->width, texture->height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);    
    
    glGenFramebuffers(1, &texture->fbo_id);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, texture->fbo_id);
    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    texture->id = texture_id;
}

int get_extension(char *fn) {
    int index = strlen(fn);
    int i = 0;
    int j = 0;
    fn += index;
    char extension[16];

    while ((*fn) != '.') fn--, i++;
    while (j < i) {
        extension[j++] = tolower((*fn));
        fn++;
    }
    extension[j++] = 0;

    if (!strcmp(extension, ".bmp"))
        return TEX_TYPE_BMP;
    return TEX_TYPE_NULL;
}

texture_t texture_load(const char *fn) {
    int ext = get_extension((char *)fn);
    texture_t texture;
    memset(&texture, 0, sizeof(texture_t));
    if (ext == TEX_TYPE_BMP) {
        bmp_file_t bmp = bmp_open(fn);
        texture.width = bmp.width;
        texture.height = bmp.height;
        texture.pixels = bmp.data;
        texture.type = TEX_TYPE_BMP;
        texture_init(&texture);
    }
    return texture;
}

texture_t texture_dupe(texture_t *src) {
    texture_t dest;
    memcpy(&dest, src, sizeof(texture_t));
    return dest;
}

void texture_render(texture_t *texture) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, texture->fbo_id);
    glBlitFramebuffer(0, 0, texture->width, texture->height, texture->x, texture->y, texture->x+texture->draw_width, texture->y+texture->draw_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    // glEnableVertexAttribArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, vbuf);
    // glVertexAttribPointer(
    //     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    //     3,                  // size
    //     GL_FLOAT,           // type
    //     GL_FALSE,           // normalized?
    //     0,                  // stride
    //     (void*)0            // array buffer offset
    // );
    // // Draw the triangle !
    // glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    // glDisableVertexAttribArray(0);
}

void texture_delete(texture_t *texture) {
    free(texture->pixels);
    // glDeleteBuffers(1, &vbuf);
    glDeleteFramebuffers(1, &texture->fbo_id);
    // glDeleteVertexArrays(1, &vaid);
}