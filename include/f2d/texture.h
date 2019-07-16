#ifndef TEXTURE_H
#define TEXTURE_H

#define TEX_TYPE_NULL      0
#define TEX_TYPE_BMP_BGRA  1

#define TEX_FLAGS_DUPE 0x01

typedef struct {
    float x;
    float y;
    int width;
    int height;
    int draw_scalex;
    int draw_scaley;

    int draw_width;
    int draw_height;

    int start_x;
    int start_y;
    
    int type;
    int flags;
    unsigned char *pixels;
    unsigned id;
    unsigned fbo_id;
    void *image;
} texture_t;

texture_t *texture_get_draw_stack(unsigned *index);
void texture_push_to_draw_stack(texture_t *texture);
void texture_spritesheet_next(texture_t *texture);
texture_t texture_load(const char *fn);
texture_t texture_dupe(texture_t *src);
void texture_render(texture_t *texture);
void texture_delete(texture_t *texture);

#endif
