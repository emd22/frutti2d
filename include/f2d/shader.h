#ifndef SHADER_H
#define SHADER_H

unsigned shader_load(const char *vert_path, const char *frag_path);
void shader_delete(unsigned shader_id);

#endif