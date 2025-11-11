#version 300 es

precision mediump float;

uniform sampler2D sampl;

in vec2 textureCoord;

out vec4 color;

void main() {
    color = texture(sampl, textureCoord);
}