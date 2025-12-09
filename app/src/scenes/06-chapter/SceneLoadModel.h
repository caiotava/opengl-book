#ifndef OPENGL_BOOK_SCENELOADMODEL_H
#define OPENGL_BOOK_SCENELOADMODEL_H

#include <array>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <core/Application.h>
#include <core/renderer/Shader.h>
#include <core/renderer/System.h>
#include <core/renderer/Texture.h>
#include <core/shapes/ModelImported.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <scene/Scene.h>

class SceneLoadModel final : public core::Scene {
public:
    SceneLoadModel() : Scene("6.3 - Loading obj models") {
        m_programRendering = core::createGraphicsShader(
            "assets/shaders/06-chapter/sphere.vert",
            "assets/shaders/06-chapter/sphere.frag"
        );

        m_camera = glm::vec3(0.0f, 0.0f, 1.5f);
        m_shuttlePosition = glm::vec3(0.0f, 0.0f, 0.0f);

        const auto bufferSize = core::Application::Get().GetFramebufferSize();
        const float aspectRatio = bufferSize.x / bufferSize.y;

        m_projectionMatrix = glm::perspective(1.0472f, aspectRatio, 0.1f, 1000.0f);
        m_shuttle = core::ModelImported("assets/shaders/06-chapter/shuttle.obj");

        setupVertices();

        m_texture = core::loadTexture("assets/shaders/06-chapter/shuttle.jpg");
    }

    ~SceneLoadModel() override {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDeleteBuffers(NUM_VBOs, &m_vbos[0]);
        glDeleteVertexArrays(NUM_VAOs, &m_vaos[0]);
        glDeleteProgram(m_programRendering);
    }

    void OnUpdate(float ts) override {
    }

    void OnRender() override {
        auto currentTime = core::Application::GetTime() / 700.0f / glm::pi<float>();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glUseProgram(m_programRendering);

        m_projectionLocation = glGetUniformLocation(m_programRendering, "perspectiveMatrix");
        m_modelViewLocation = glGetUniformLocation(m_programRendering, "modelViewMatrix");
        m_textureLocation = glGetUniformLocation(m_programRendering, "sampl");

        m_viewMatrix = glm::translate(glm::mat4(1.0f), -m_camera);
        m_modelMatrix = glm::translate(glm::mat4(1.0f), m_shuttlePosition);

        m_modelMatrix = glm::rotate(m_modelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_modelMatrix = glm::rotate(m_modelMatrix, std::cos(currentTime), glm::vec3(0.0f, 0.0f, 1.0f));

        m_modelViewMatrix = m_viewMatrix * m_modelMatrix;

        glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
        glUniformMatrix4fv(m_modelViewLocation, 1, GL_FALSE, glm::value_ptr(m_modelViewMatrix));

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glUniform1i(m_textureLocation, 0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, m_shuttle.getNumberVertices());
    }

private:
    static constexpr int NUM_VAOs = 1;
    static constexpr int NUM_VBOs = 3;

    std::array<GLuint, NUM_VAOs> m_vaos;
    std::array<GLuint, NUM_VBOs> m_vbos;
    GLuint m_programRendering;
    GLuint m_texture;
    GLint m_textureLocation;
    GLint m_modelViewLocation;
    GLint m_projectionLocation;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_modelViewMatrix;
    glm::mat4 m_modelMatrix;
    glm::mat4 m_viewMatrix;
    glm::vec3 m_camera;
    glm::vec3 m_shuttlePosition;

    core::ModelImported m_shuttle;
    // ImportedModel m_shuttle;

    void setupVertices() {
        const auto vertices = m_shuttle.getVertices();
        const auto textureCoords = m_shuttle.getTextureCoords();
        const auto normals = m_shuttle.getNormals();

        std::vector<float> pValues;
        std::vector<float> tValues;
        std::vector<float> nValues;

        for (int32_t i = 0; i < m_shuttle.getNumberVertices(); i++) {
            pValues.push_back(vertices[i].x);
            pValues.push_back(vertices[i].y);
            pValues.push_back(vertices[i].z);

            tValues.push_back(textureCoords[i].s);
            tValues.push_back(textureCoords[i].t);

            nValues.push_back(normals[i].x);
            nValues.push_back(normals[i].y);
            nValues.push_back(normals[i].z);
        }

        glGenVertexArrays(NUM_VAOs, &m_vaos[0]);
        glBindVertexArray(m_vaos[0]);

        glGenBuffers(NUM_VBOs, &m_vbos[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, pValues.size() * 4, pValues.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, tValues.size() * 4, tValues.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[2]);
        glBufferData(GL_ARRAY_BUFFER, nValues.size() * 4, nValues.data(), GL_STATIC_DRAW);
    }
};

#endif //OPENGL_BOOK_SCENELOADMODEL_H
