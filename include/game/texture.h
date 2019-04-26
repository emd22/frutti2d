#ifndef TEXTURE_H
#define TEXTURE_H

#define TEX_TYPE_NULL 0
#define TEX_TYPE_BMP  1

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int draw_width;
    int draw_height;
    
    int type;
    unsigned char *pixels;
    unsigned id;
    unsigned fbo_id;
    void *image;
} texture_t;

texture_t texture_load(const char *fn);
texture_t texture_dupe(texture_t *src);
void texture_render(texture_t *texture);
void texture_delete(texture_t *texture);

#endif