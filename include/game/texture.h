#ifndef TEXTURE_H
#define TEXTURE_H

unsigned texture_init(int width, int height, unsigned char *pixels);
void texture_render(unsigned texture, int width, int height);
void texture_delete(void);

#endif