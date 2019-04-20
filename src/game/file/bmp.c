#include <game/file/bmp.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bmp_file_t bmp_open(const char *fn) {
    FILE *bmp = fopen(fn, "rb");

    if (bmp == NULL) {
        printf("could not find file\n");
    }
    
    // get size of file
    fseek(bmp, 0, SEEK_END);
    unsigned long fsize = ftell(bmp);
    rewind(bmp);


    unsigned char *data = malloc(fsize);

    fread(data, 1, fsize, bmp);

    bmp_header_t *head = (bmp_header_t *)data;

    bmp_file_t bmp_file;
    bmp_file.header = head;
    bmp_file.data = malloc(bmp_file.header->size);
    printf("bmp fsize = %d\n", bmp_file.header->size);
    printf("fsize = %lu\n", fsize);
    // if (file->header->header[0] != 'B' || file->header->header[1] != 'M') {
        // printf("fsize: %lu\n", fsize);
        // printf("Error: Invalid BMP header\n");
        // goto end;
    // }

end:
    // free(data);
    fclose(bmp);

    return bmp_file;
}