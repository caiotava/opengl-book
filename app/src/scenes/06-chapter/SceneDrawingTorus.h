#ifndef OPENGL_BOOK_SCENEDRAWINGTORUS_H
#define OPENGL_BOOK_SCENEDRAWINGTORUS_H

#include <glm/glm.hpp>

#include <scene/Scene.h>
#include <core/renderer/System.h>
#include <core/shapes/Torus.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "core/Application.h"
#include "core/renderer/Shader.h"
#include "core/renderer/Texture.h"

class SceneDrawingTorus final : public core::Scene {
public:
    SceneDrawingTorus() : Scene("6.2 - SceneDrawingTorus") {
        m_renderingProgram = core::createGraphicsShader(
            "assets/shaders/06-chapter/sphere.vert",
            "assets/shaders/06-chapter/sphere.frag"
        );

        m_cameraPosition = glm::vec3(0.0f, 0.0f, 2.0f);
        m_torusPosition = glm::vec3(0.0f, 0.0f, 0.5f);

        m_torus = {0.5f, 0.2f, 48};
        m_rotationAmount = glm::radians(30.0f);

        auto frameBuffer = core::Application::Get().GetFramebufferSize();
        float aspectRatio = frameBuffer.x / frameBuffer.y;

        m_projectionMatrix = glm::perspective(1.0472f, aspectRatio, 0.1f, 1000.0f);

        setupVertices();

        m_brickTextures = core::loadTexture("assets/shaders/06-chapter/brick1.jpg");
        glBindTexture(GL_TEXTURE_2D, m_brickTextures);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    }

    void OnUpdate(float ts) override {
    }

    void OnRender() override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glUseProgram(m_renderingProgram);

        m_modelViewLocation = glGetUniformLocation(m_renderingProgram, "modelViewMatrix");
        m_projectionLocation = glGetUniformLocation(m_renderingProgram, "perspectiveMatrix");
        m_textureLocation = glGetUniformLocation(m_renderingProgram, "sampl");

        m_viewMatrix = glm::translate(glm::mat4(1.0f), -m_cameraPosition);
        m_modelMatrix = glm::translate(glm::mat4(1.0f), m_torusPosition);
        m_modelMatrix = glm::rotate(m_modelMatrix, m_rotationAmount, glm::vec3(1.0f, 0.0f, 0.0f));

        m_modelViewMatrix = m_viewMatrix * m_modelMatrix;

        glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
        glUniformMatrix4fv(m_modelViewLocation, 1, GL_FALSE, glm::value_ptr(m_modelViewMatrix));

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_brickTextures);
        glUniform1i(m_textureLocation, 0);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[3]);
        glDrawElements(GL_TRIANGLES, m_torus.getIndices().size(), GL_UNSIGNED_INT, nullptr);
    }

private:
    static constexpr int NUM_VAOs = 1;
    static constexpr int NUM_VBOs = 4;

    glm::vec3 m_cameraPosition;
    glm::vec3 m_torusPosition;

    GLuint m_renderingProgram;
    GLuint m_vaos[NUM_VAOs];
    GLuint m_vbos[NUM_VBOs];
    GLuint m_brickTextures;

    float m_rotationAmount = 0.0f;
    GLint m_modelViewLocation;
    GLint m_projectionLocation;
    GLint m_textureLocation;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_modelMatrix;
    glm::mat4 m_modelViewMatrix;

    core::Torus m_torus;

    void setupVertices() {
        const auto indices = m_torus.getIndices();
        const auto vertices = m_torus.getVertices();
        const auto textures = m_torus.getTexCoords();
        const auto normals = m_torus.getNormals();

        std::vector<float> pValues;
        std::vector<float> tValues;
        std::vector<float> nValues;

        for (int32_t i = 0; i < vertices.size(); i++) {
            pValues.push_back(vertices[i].x);
            pValues.push_back(vertices[i].y);
            pValues.push_back(vertices[i].z);

            tValues.push_back(textures[i].s);
            tValues.push_back(textures[i].t);

            nValues.push_back(normals[i].x);
            nValues.push_back(normals[i].y);
            nValues.push_back(normals[i].z);
        }

        glGenVertexArrays(NUM_VAOs, &m_vaos[0]);
        glBindVertexArray(m_vaos[0]);

        glGenBuffers(NUM_VBOs, &m_vbos[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, pValues.size() * 4, &pValues[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, tValues.size() * 4, &tValues[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[2]);
        glBufferData(GL_ARRAY_BUFFER, nValues.size() * 4, &nValues[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[3]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, &indices[0], GL_STATIC_DRAW);
    }
};

#endif //OPENGL_BOOK_SCENEDRAWINGTORUS_H
