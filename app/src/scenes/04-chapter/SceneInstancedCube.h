#ifndef OPENGL_BOOK_SCENEINSTANCEDCUBE_H
#define OPENGL_BOOK_SCENEINSTANCEDCUBE_H

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <core/Application.h>
#include <core/renderer/Shader.h>
#include <core/renderer/System.h>
#include <scene/Scene.h>

class SceneInstancedCube final : public core::Scene {
public:
    SceneInstancedCube() : Scene("4.6.1 Instanced Cube") {
        m_renderingProgram = core::createGraphicsShader(
            "assets/shaders/04-chapter/instanced-cube.vert",
            "assets/shaders/04-chapter/plain-red-cube.frag"
        );

        // m_cameraPosition = glm::vec3(0.0f, 0.0f, 32.0f);
        m_cameraPosition = glm::vec3(350.0f, -220.0f, 10.0f);
        setupVertices();
    }

    ~SceneInstancedCube() override {
        glDeleteBuffers(NUM_VBOs, &m_vbos[0]);
        glDeleteVertexArrays(NUM_VAOs, &m_vaos[0]);
        glDeleteProgram(m_renderingProgram);
    }

    void OnUpdate(float ts) override {}

    void OnRender() override {
        const auto currentTime = core::Application::GetTime() / 800.0f;
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_renderingProgram);

        m_matrixViewLocation = glGetUniformLocation(m_renderingProgram, "modelViewMatrix");
        m_projectionLocation = glGetUniformLocation(m_renderingProgram, "projectionMatrix");
        const auto timeFactorLocation = glGetUniformLocation(m_renderingProgram, "timeFactor");

        const auto bufferSize = core::Application::Get().GetFramebufferSize();
        m_aspectRatio = bufferSize.x / bufferSize.y;

        // 1.0472f radians == 60 degrees
        m_projectionMatrix = glm::perspective(1.0472f, m_aspectRatio, 0.1f, 1000.0f);
        glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

        m_viewMatrix = glm::translate(glm::mat4(1.0f), -m_cameraPosition);

        glUniformMatrix4fv(m_matrixViewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniform1f(timeFactorLocation, currentTime);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        m_instanceCount += currentTime * 0.45f;
        m_cameraPosition.x = std::sin(currentTime * 0.35f) * 200.0f;
        m_cameraPosition.y = std::cos(currentTime * 0.35f) * 200.0f;
        m_cameraPosition.z = std::clamp(std::sin(currentTime * 0.35f) * 400.f + 200.0f, -100.0f, 620.0f);

        m_instanceCount = std::clamp(m_instanceCount, 1.0f, 1'000'000.0f);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, static_cast<int>(m_instanceCount));
    }

private:
    static constexpr int NUM_VAOs = 1;
    static constexpr int NUM_VBOs = 2;

    glm::vec3 m_cameraPosition;

    GLuint m_renderingProgram;
    std::array<GLuint, NUM_VAOs> m_vaos;
    std::array<GLuint, NUM_VBOs> m_vbos;

    GLint m_matrixViewLocation;
    GLint m_projectionLocation;

    float m_instanceCount = 10.0f;

    int32_t m_screenWidth;
    int32_t m_screenHeight;
    float m_aspectRatio;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;

    void setupVertices(void) {
        constexpr float vertexPositions[108] = {
            // 1 - triangle
            -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
            // 2 - triangle
            1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
            // 3 - triangle
            1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
            // 4 - triangle
            1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
            // 5 - triangle
            1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            // 6 - triangle
            -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            // 7 - triangle
            -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
            // 8 - triangle
            -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
            // 9 - triangle
            -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
            // 10 - triangle
            1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
            // 11 - triangle
            -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
            // 12 - triangle
            1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
        };

        glGenVertexArrays(NUM_VAOs, &m_vaos[0]);
        glBindVertexArray(m_vaos[0]);

        glGenBuffers(NUM_VBOs, &m_vbos[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
    }
};

#endif //OPENGL_BOOK_SCENEINSTANCEDCUBE_H
