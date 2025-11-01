#version 300 es

layout(location=0) in vec3 position;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main(void) {
	 gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
