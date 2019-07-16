#include <f2d/math/mat4.h>

#include <stdio.h>
#include <string.h>

void mat4_print(float *mul) {
    int i;
    printf("{\n");
    // for (i = 0; i < 16; i++) {
    //     printf("%d ", mat[i]);
    //     if (i == 3 || i == 7 || i == 11)
    //         printf("\n");
    // }
    for (i = 0; i < 4; i++) {
        printf("%.2f\n", mul[i]);
    }
    printf("}\n");
}

void mat4_translate_x(mat4_t *mat1, float *vec) {
    int i, j = 0;

    for (i = 0; i < 16; i++) {
        //multiply matrix by vector
        mat1->data[i] *= vec[j++];

        //when hit end of vector, set to zero for next row.
        if (j == 4)
            j = 0;
    }

    int temp;
    for (i = 0; i < 4; i++) {
        temp = 0;
        for (j = 0; j < 4; j++) {
            //add all the columns together to make final answer
            temp += mat1->data[j+(i*4)];
        }
        //push, go to next
        vec[i] = temp;
    }
}


void mat4_set(mat4_t *mat, int x, int y, float value) {
    mat->data[x+(y*4)] = value;
}

void mat4_fill(mat4_t *mat, const float *data) {
    memcpy(mat->data, data, 16);
}

void mat4_identity(mat4_t *out) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            out->data[j+(i*4)] = !(j-i);
        }
    }
}

