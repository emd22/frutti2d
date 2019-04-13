#include <game/file/bmp.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void bmp_open(const char *fn) {
    FILE *bmp = fopen(fn, "rb");
    
    // get size of file
    fseek(bmp, 0, SEEK_END);
    unsigned long fsize = ftell(bmp);
    rewind(bmp);

    uint8_t *data = malloc(fsize);

    fread(data, sizeof(char), fsize, bmp);

    bmp_header_t *header = (bmp_header_t *)data;
    if (header->header[0] != 'B' || header->header[1] != 'M') {
        printf("Error: Invalid BMP header\n");
        goto end;
    }



end:
    free(data);
    fclose(bmp);
}