#version 300 es

precision mediump float;

in vec3 varyingVertPos;
in vec3 varyingLightDir;
in vec3 varyingNormal;
in vec3 varyingHalfVector;

out vec4 fragColor;

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

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalsMatrix;

void main(void) {
    vec3 lightDir = normalize(varyingLightDir);
    vec3 normalDir = normalize(varyingNormal);
    vec3 vertDir = normalize(-viewMatrix[3].xyz - varyingVertPos);
    vec3 halfVector = normalize(varyingHalfVector);

    float cosTheta = dot(lightDir, normalDir);

    float cosPhi = dot(halfVector, normalDir);

    vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(cosTheta, 0.0);
    vec3 specular = light.specular.xyz * material.specular.xyz * pow(max(cosPhi, 0.0), material.shininess * 3.0);

    fragColor = vec4((ambient + diffuse + specular), 1.0);
}