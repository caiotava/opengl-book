#version 300 es

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 modelViewMatrix;
uniform mat4 perspectiveMatrix;
uniform sampler2D sampl;

out vec2 textureCoord;

void main() {
    gl_Position = perspectiveMatrix * modelViewMatrix * vec4(position, 1.0);

    textureCoord = texCoord;
}