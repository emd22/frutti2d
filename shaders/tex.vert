#version 120

attribute vec2 position;

void main() {
    //                   x, y     z ,  w
    gl_Position = vec4(position, 0.0, 1.0);
}
