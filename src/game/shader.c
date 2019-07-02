#include <game/shader.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include <stdio.h>
#include <stdlib.h>

#define VERT_SHADER 0
#define FRAG_SHADER 1

char *get_shader_data(FILE *fp) {
    // get file size
    unsigned long size;
    // seek to end of file
    fseek(fp, 0, SEEK_END);
    // get counter location
    size = ftell(fp);
    // reset counter
    rewind(fp);

    // allocate memory size of file
    char *data = malloc(size);
    // read data in from file to buffer
    fread(data, 1, size, fp);

    return data;
}

int compile_shader(const char *data, int type, unsigned *_shader) {
    unsigned shader = glCreateShader((type == VERT_SHADER) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &data, NULL);
    // printf("compiling shader...\n");
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        const char *str_type[] = {"vertex", "fragment"};
        printf("Error: compilation of %s shader failed.\n", str_type[type]);
       
        int info_log_length;
        char *info_log = malloc(info_log_length);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        printf("INFO LOG: %s\n", info_log);
        free(info_log);
        exit(1);
    }

    (*_shader) = shader;
    return 0;
}

unsigned shader_load(const char *vert_path, const char *frag_path) {
    FILE *vert = fopen(vert_path, "rb");
    FILE *frag = fopen(frag_path, "rb");

    if (vert == NULL) {
        printf("could not find vertex shader\n");
        return 0;
    }
    if (frag == NULL) {
        printf("could not find fragment shader\n");
        return 0;
    }


    char *vdata = get_shader_data(vert);
    char *fdata = get_shader_data(frag);
    fclose(vert);
    fclose(frag);

    unsigned vertex, fragment;
    if (compile_shader(vdata, VERT_SHADER, &vertex)) {
        return 0;
    }
    if (compile_shader(fdata, FRAG_SHADER, &fragment)) {
        return 0;
    }
    return 0;

    unsigned shader_id = glCreateProgram();
    glAttachShader(shader_id, vertex);
    glAttachShader(shader_id, fragment);
    printf("linking shader...\n");
    glLinkProgram(shader_id);
    int info_log_length;
    glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        printf("Error: could not link shader\n");
        // char *info_log = malloc(info_log_length);
        // glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        // glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        // printf("INFO LOG: %s\n", info_log);
        return 0;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vdata);
    free(fdata);

    printf("shader id: %u\n", shader_id);
    return shader_id;
}

void shader_delete(unsigned shader_id) {
    glDeleteProgram(shader_id);
}