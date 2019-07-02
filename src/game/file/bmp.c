#include <game/file/bmp.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int8_t header[2];
    uint32_t size;
    uint16_t resv0;
    uint16_t resv1;
    uint32_t offset;
} __attribute__((packed)) bmp_header_t;

typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t data_size;
    int32_t horiz_resolution;
    int32_t vert_resolution;
    uint32_t num_colours_colour_palette;
    uint32_t num_important_colours;
} __attribute__((packed)) bmp_dib_t;

bmp_file_t bmp_open(const char *fn) {
    FILE *bmp = fopen(fn, "rb");

    if (bmp == NULL) {
        printf("Error: Could not load BMP file\n");
        exit(1);
    }
    
    // get size of file
    fseek(bmp, 0, SEEK_END);
    unsigned long fsize = ftell(bmp);
    rewind(bmp);

    unsigned char *data = malloc(fsize);
    fread(data, 1, fsize, bmp);

    bmp_header_t *head = (bmp_header_t *)data;
    bmp_dib_t *dib = (bmp_dib_t *)(data+sizeof(bmp_header_t));
    bmp_file_t bmp_file;
    bmp_file.data = malloc(head->size);

    unsigned long i;
    for (i = 0; i < fsize-head->offset; i++) {
        bmp_file.data[i] = data[head->offset+i];
    }

    bmp_file.data_start = head->offset;
    bmp_file.size = fsize;

    bmp_file.width = dib->width;
    bmp_file.height = dib->height;
    // if (file->header->header[0] != 'B' || file->header->header[1] != 'M') {
        // printf("fsize: %lu\n", fsize);
        // printf("Error: Invalid BMP header\n");
        // goto end;
    // }

// end:
    free(data);
    fclose(bmp);

    return bmp_file;
}

void bmp_close(bmp_file_t *bmp_image) {
    free(bmp_image->data);
}
