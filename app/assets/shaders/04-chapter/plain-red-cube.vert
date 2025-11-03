#version 300 es

layout (location = 0) in vec3 position;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

out vec4 varyingColor;

void main(void) {
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}
