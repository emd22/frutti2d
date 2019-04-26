#ifndef FILE_BMP_H
#define FILE_BMP_H

#include <stdint.h>

typedef struct {
    unsigned size;
    unsigned data_start;
    int width;
    int height;
    unsigned char *data;
} bmp_file_t;

bmp_file_t bmp_open(const char *fn);
void bmp_close(bmp_file_t *bmp_image);

#endif