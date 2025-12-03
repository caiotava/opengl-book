#version 300 es

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNormal;
out vec4 varyingColor;

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
    vec4 color;
    vec4 vertexPos = modelMatrix * vec4(vertPos, 1.0);
    vec3 normalPos = normalize((normalMatrix * vec4(vertNormal, 1.0)).xyz);
    vec3 lightVec = normalize(light.position.xyz - vertexPos.xyz);
    vec3 cameraVec = normalize(-viewMatrix[3].xyz - vertexPos.xyz);
    vec3 reflection = reflect(-lightVec, normalPos);

    vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(normalPos.xyz, lightVec.xyz), 0.0);
    vec3 specular = pow(max(dot(reflection.xyz, cameraVec.xyz), 0.0f), material.shininess) * material.specular.xyz * light.specular.xyz;

    varyingColor = vec4(ambient + diffuse + specular, 1.0);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertPos, 1.0);
}