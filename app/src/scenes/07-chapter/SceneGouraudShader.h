#ifndef OPENGL_BOOK_SCENEGOURADSHADER_H
#define OPENGL_BOOK_SCENEGOURADSHADER_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Application.h"
#include "core/components/Light.h"
#include "core/components/Material.h"
#include "core/renderer/Shader.h"
#include "core/shapes/Torus.h"
#include "scene/Scene.h"
#include "core/renderer/System.h"

class SceneGouraudShader final : public core::Scene {
public:
    SceneGouraudShader() : Scene("7.1- Scene Gouraud Shading") {
        m_renderingProgram = core::createGraphicsShader(
            "assets/shaders/07-chapter/blinn-phong.vert",
            "assets/shaders/07-chapter/blinn-phong.frag"
            // "assets/shaders/07-chapter/phong.vert",
            // "assets/shaders/07-chapter/phong.frag"
            // "assets/shaders/07-chapter/gouraud.vert",
            // "assets/shaders/07-chapter/gouraud.frag"
        );

        m_camera = glm::vec3(0.0f, 0.0f, 1.0f);
        m_torusPosition = glm::vec3(0.0f, 0.0f, -1.0f);
        m_torus = core::Torus(0.5f, 0.2f, 48);

        const auto frameBuffer = core::Application::Get().GetFramebufferSize();
        const float aspectRatio = frameBuffer.x / frameBuffer.y;
        m_projectionMatrix = glm::perspective(1.0472f, aspectRatio, 0.1f, 1000.0f);

        m_globalLight = core::Light(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

        m_whiteLight = core::Light(
            core::Light::Point,
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec4(5.0f, 2.0f, 2.0f, 1.0f)
        );
        m_whiteLightInitPos = m_whiteLight.getPosition();
        m_material = core::Material::GOLD;

        setupVertices();
    }

    void OnRender() override {
        const float currentTime = core::Application::Get().GetTime() / 800.0f;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(m_renderingProgram);

        m_projectionMatrixLoc = glGetUniformLocation(m_renderingProgram, "projectionMatrix");
        m_modelMatrixLoc = glGetUniformLocation(m_renderingProgram, "modelMatrix");
        m_viewMatrixLoc = glGetUniformLocation(m_renderingProgram, "viewMatrix");
        m_normalMatrixLoc = glGetUniformLocation(m_renderingProgram, "normalMatrix");

        m_viewMatrix = glm::translate(glm::mat4(1.0f), -m_camera);
        m_modelMatrix = glm::translate(glm::mat4(1.0), m_torusPosition);
        m_modelMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        const auto lightRotation = glm::rotate(
            glm::mat4(1.0f),
            glm::radians(currentTime * 25.0f),
            glm::vec3(0.0f, 0.0f, 1.0)
        );
        m_whiteLight.setPosition(lightRotation * m_whiteLightInitPos);

        installLights();

        auto inverseModelMatrix = glm::transpose(glm::inverse(m_modelMatrix));

        glUniformMatrix4fv(m_projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
        glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(m_viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(inverseModelMatrix));

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[2]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[3]);
        glDrawElements(GL_TRIANGLES, m_torus.getNumberIndices(), GL_UNSIGNED_INT, 0);
    }

private:
    constexpr static int8_t NUM_VAOs = 1;
    constexpr static int8_t NUM_VBOs = 4;

    std::array<GLuint, NUM_VAOs> m_vaos;
    std::array<GLuint, NUM_VBOs> m_vbos;

    GLuint m_renderingProgram;
    GLint m_projectionMatrixLoc;
    GLint m_modelMatrixLoc;
    GLint m_viewMatrixLoc;
    GLint m_normalMatrixLoc;

    glm::vec3 m_camera;
    glm::vec3 m_torusPosition;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_modelMatrix;
    glm::mat4 m_modelViewMatrix;

    core::Torus m_torus;
    core::Material m_material;
    core::Light m_globalLight;
    core::Light m_whiteLight;
    glm::vec4 m_whiteLightInitPos;

    void setupVertices() {
        const auto indices = m_torus.getIndices();
        const auto vertices = m_torus.getVertices();
        const auto textureCoords = m_torus.getTexCoords();
        const auto normals = m_torus.getNormals();

        std::vector<float> verticesValues;
        std::vector<float> texturesValues;
        std::vector<float> normalsValues;

        for (int32_t i = 0; i < m_torus.getNumberVertices(); i++) {
            verticesValues.push_back(vertices[i].x);
            verticesValues.push_back(vertices[i].y);
            verticesValues.push_back(vertices[i].z);

            texturesValues.push_back(textureCoords[i].s);
            texturesValues.push_back(textureCoords[i].t);

            normalsValues.push_back(normals[i].x);
            normalsValues.push_back(normals[i].y);
            normalsValues.push_back(normals[i].z);
        }

        glGenVertexArrays(NUM_VAOs, &m_vaos[0]);
        glBindVertexArray(m_vaos[0]);

        glGenBuffers(NUM_VBOs, &m_vbos[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, verticesValues.size() * 4, verticesValues.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, texturesValues.size() * 4, texturesValues.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[2]);
        glBufferData(GL_ARRAY_BUFFER, normalsValues.size() * 4, normalsValues.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[3]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, indices.data(), GL_STATIC_DRAW);
    }

    void installLights() const {
        const GLint globalLoc = glGetUniformLocation(m_renderingProgram, "globalAmbient");
        const GLint ambientLoc = glGetUniformLocation(m_renderingProgram, "light.ambient");
        const GLint diffuseLoc = glGetUniformLocation(m_renderingProgram, "light.diffuse");
        const GLint specularLoc = glGetUniformLocation(m_renderingProgram, "light.specular");
        const GLint positionLoc = glGetUniformLocation(m_renderingProgram, "light.position");
        const GLint ambientMatLoc = glGetUniformLocation(m_renderingProgram, "material.ambient");
        const GLint diffuseMatLoc = glGetUniformLocation(m_renderingProgram, "material.diffuse");
        const GLint specularMatLoc = glGetUniformLocation(m_renderingProgram, "material.specular");
        const GLint shininessMatLoc = glGetUniformLocation(m_renderingProgram, "material.shininess");

        glUniform4fv(globalLoc, 1, glm::value_ptr(m_globalLight.getAmbient()));

        glUniform4fv(ambientLoc, 1, glm::value_ptr(m_whiteLight.getAmbient()));
        glUniform4fv(diffuseLoc, 1, glm::value_ptr(m_whiteLight.getDiffuse()));
        glUniform4fv(specularLoc, 1, glm::value_ptr(m_whiteLight.getSpecular()));
        glUniform4fv(positionLoc, 1, glm::value_ptr(m_whiteLight.getPosition()));

        glUniform4fv(ambientMatLoc, 1, glm::value_ptr(m_material.getAmbient()));
        glUniform4fv(diffuseMatLoc, 1, glm::value_ptr(m_material.getDiffuse()));
        glUniform4fv(specularMatLoc, 1, glm::value_ptr(m_material.getSpecular()));
        glUniform1f(shininessMatLoc, m_material.getShininess());
    }
};

#endif //OPENGL_BOOK_SCENEGOURADSHADER_H
