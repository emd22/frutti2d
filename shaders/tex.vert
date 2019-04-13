#version 330

layout(location = 0) in vec3 vert_pos_modelspace;

void main() {
    gl_Position.xyz = vert_pos_modelspace;
    gl_Position.w = 1.0;
}