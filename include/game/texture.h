#ifndef TEXTURE_H
#define TEXTURE_H

void texture_init(int width, int height, unsigned char *pixels);
void texture_render(int width, int height);
void texture_delete(void);

#endif