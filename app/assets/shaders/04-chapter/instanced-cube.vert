#version 300 es

layout (location = 0) in vec3 position;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform float timeFactor;

out vec4 varyingColor;

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void) {
    float x = float(gl_InstanceID) + timeFactor;
    float a = sin(203.0 * x / 8000.0) * 403.0;
    float b = cos(301.0 * x / 4001.0) * 401.0;
    float c = sin(400.0 * x / 6003.0) * 405.0;

//    float a = sin(0.35 * x) * 8.0;
//    float b = cos(0.52 * x) * 8.0;
//    float c = sin(0.70 * x) * 8.0;

    mat4 localRotX = buildRotateX(1.75 * x);
    mat4 localRotY = buildRotateY(1.75 * x);
    mat4 localRotZ = buildRotateZ(1.75 * x);
    mat4 localTrans = buildTranslate(a, b, c);

    mat4 newModelViewMatrix = localTrans * localRotX * localRotY * localRotZ;
    newModelViewMatrix = modelViewMatrix * newModelViewMatrix;

    gl_Position = projectionMatrix * newModelViewMatrix * vec4(position, 1.0);

    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}

mat4 buildTranslate(float x, float y, float z) {
    return mat4(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    x, y, z, 1.0
    );
}

//  rotation around the X axis
mat4 buildRotateX(float rad) {
    mat4 xrot = mat4(
    1.0, 0.0, 0.0, 0.0,
    0.0, cos(rad), -sin(rad), 0.0,
    0.0, sin(rad), cos(rad), 0.0,
    0.0, 0.0, 0.0, 1.0
    );
    return xrot;
}

//  rotation around the Y axis
mat4 buildRotateY(float rad)
{
    mat4 yrot = mat4(
    cos(rad), 0.0, sin(rad), 0.0,
    0.0, 1.0, 0.0, 0.0,
    -sin(rad), 0.0, cos(rad), 0.0,
    0.0, 0.0, 0.0, 1.0
    );
    return yrot;
}

//  rotation around the Z axis
mat4 buildRotateZ(float rad)
{
    mat4 zrot = mat4(
    cos(rad), sin(rad), 0.0, 0.0,
    -sin(rad), cos(rad), 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
    );
    return zrot;
}
