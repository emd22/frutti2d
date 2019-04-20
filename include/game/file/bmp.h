#ifndef FILE_BMP_H
#define FILE_BMP_H

#include <stdint.h>

typedef struct {
    int8_t header[2];
    uint32_t size;
    uint16_t resv0;
    uint16_t resv1;
    uint32_t offset;
} bmp_header_t;

typedef struct {
    bmp_header_t *header;
    unsigned char *data;
} bmp_file_t;

bmp_file_t bmp_open(const char *fn);

#endif