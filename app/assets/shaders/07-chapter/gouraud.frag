#version 300 es

precision mediump float;

in vec4 varyingColor;
out vec4 fragColor;

//  interpolate lighted color
// (interpolation of gl_Position is automatic)

void main(void) {
    fragColor = varyingColor;
}