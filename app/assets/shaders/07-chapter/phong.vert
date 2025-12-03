#version 300 es

precision mediump float;

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNormal;

out vec3 varyingNormal;
out vec3 varyingLightDir;
out vec3 varyingVertPos;

struct PositionalLight {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
};

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

void main(void) {
    varyingVertPos = (modelMatrix * vec4(vertPos, 1.0)).xyz;
    varyingLightDir = light.position.xyz - varyingVertPos;
    varyingNormal = (normalMatrix * vec4(vertNormal, 1.0)).xyz;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertPos, 1.0);
}