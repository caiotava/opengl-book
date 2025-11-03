#version 300 es

layout (location = 0) in vec3 position;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform bool drawMode;

out vec4 varyingColor;

void main(void) {
    gl_PointSize = 3.0;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);

    if (drawMode) {
        varyingColor = vec4(1.0);
    } else {
        varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
    }
}
