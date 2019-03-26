#include <game/file/bmp.h>

#include <stdint.h>
#include <stdio.h>

typedef struct {
    int8_t header[2];
    uint32_t size;
    uint16_t resv0;
    uint16_t resv1;
    uint32_t offset;
} bmp_header_t;

void bmp_open(const char *fn) {
    FILE *bmp = fopen(fn, "rb");
    
    // get size of file
    fseek(bmp, 0, SEEK_END);
    unsigned long fsize = ftell(bmp);
    rewind(bmp);

    uint8_t *data = malloc(fsize);

    fread(data, sizeof(char), fsize, bmp);

    fclose(bmp);
}