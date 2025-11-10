#version 300 es

precision mediump float;

uniform sampler2D sampl;

in vec2 textureCoord;
//noperspective in vec2 textureCoord;
out vec4 color;

void main(void) {
    color = texture(sampl, textureCoord);
//    color = vec4(1.0, 1.0, 0.0, 1.0);
}
