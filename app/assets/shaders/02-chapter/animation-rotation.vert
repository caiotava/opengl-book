#version 300 es

uniform float offset;

mat4 buildRotateZ(float rad) {
    return mat4(
        cos(rad), -sin(rad), 0.0, 0.0,
        sin(rad), cos(rad), 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

void main(void) {
    if (gl_VertexID == 0) {
        gl_Position = vec4(0.25, -0.25, 0.0, 1.0);
    } else if (gl_VertexID == 1) {
        gl_Position = vec4(-0.25, -0.25, 0.0, 1.0);
    } else {
        gl_Position = vec4(0.25, 0.25, 0.0, 1.0);
    }

    gl_Position = buildRotateZ(offset * 3.0) * gl_Position;
}
