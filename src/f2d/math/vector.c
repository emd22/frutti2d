#include <f2d/math/vector.h>

#include <math.h>

#define POW(num) (num*num)

vec3_t vec3_cross(vec3_t *v1, vec3_t *v2) {
    vec3_t new;
    new.x = v1->y * v2->z - v1->z * v2->y;
    new.y = v1->z * v2->x - v1->x * v2->z;
    new.z = v1->x * v2->y - v1->y * v2->x;
    return new;
}

float vec3_length(vec3_t *vec) {
    float total = sqrt(POW(vec->x) + POW(vec->y) + POW(vec->z));
    return total;
}

vec3_t vec3_multiply_vec3(vec3_t *v1, vec3_t *v2) {
    vec3_t res;
    res.x = v1->x*v2->x;
    res.y = v1->y*v2->y;
    res.z = v1->z*v2->z;
    return res;
}

vec3_t vec3_multiply_val(vec3_t *vec, float value) {
    vec3_t res;
    res.x = vec->x*value;
    res.y = vec->y*value;
    res.z = vec->z*value;
    return res;
}

vec3_t vec3_normalize(vec3_t *vec) {
    float len = vec3_length(vec);
    if (POW(len) == 0 || POW(len) == 1)
        return *vec;
    vec3_t new;
    new = vec3_multiply_val(vec, 1.0f/len);
    return new;
}
