#ifndef OPENGL_BOOK_SCENEPYRAMIDBRICKTEXTURE_H
#define OPENGL_BOOK_SCENEPYRAMIDBRICKTEXTURE_H

#include <array>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <scene/Scene.h>
#include <core/renderer/System.h>

#include <core/Application.h>
#include <core/renderer/Shader.h>
#include <core/renderer/Texture.h>

class ScenePyramidBrickTexture final : public core::Scene {
public:
    ScenePyramidBrickTexture() : Scene("5.1 Pyramid with Brick Texture") {
        m_renderingProgram = core::createGraphicsShader(
            "assets/shaders/05-chapter/texture.vert",
            "assets/shaders/05-chapter/texture.frag"
        );
        m_brickTexture = core::loadTexture("assets/shaders/05-chapter/brick1.jpg");
        const auto bufferSize = core::Application::Get().GetFramebufferSize();
        m_aspectRatio = bufferSize.x / bufferSize.y;

        m_perspectiveMatrix = glm::perspective(1.0472f, m_aspectRatio, 0.1f, 1000.0f);
        m_cameraPosition = glm::vec3(0.0f, 0.0f, 3.f);
        m_pyramidPosition = glm::vec3(0.0f, 0.0f, 0.0f);

        setupVertices();
    }

    void OnUpdate(float ts) override {
    }

    void OnRender() override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glUseProgram(m_renderingProgram);

        m_modelViewLocation = glGetUniformLocation(m_renderingProgram, "modelViewMatrix");
        m_perspectiveLocation = glGetUniformLocation(m_renderingProgram, "perspectiveMatrix");
		m_textureSamplerLocation = glGetUniformLocation(m_renderingProgram, "sampl");

        m_viewMatrix = glm::translate(glm::mat4(1.0f), -m_cameraPosition);
        m_modelMatrix = glm::translate(glm::mat4(1.0f), m_pyramidPosition);
        m_modelMatrix = glm::rotate(m_modelMatrix, -0.45f, glm::vec3(1.0f, 0.0f, 0.0f));
        m_modelMatrix = glm::rotate(m_modelMatrix, 0.61f, glm::vec3(0.0f, 1.0f, 0.0f));
        m_modelMatrix = glm::rotate(m_modelMatrix, 0.00f, glm::vec3(0.0f, 0.0f, 1.0f));
        m_modelViewMatrix = m_viewMatrix * m_modelMatrix;

        glUniformMatrix4fv(m_modelViewLocation, 1, GL_FALSE, glm::value_ptr(m_modelViewMatrix));
        glUniformMatrix4fv(m_perspectiveLocation, 1, GL_FALSE, glm::value_ptr(m_perspectiveMatrix));

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_brickTexture);
		glUniform1i(m_textureSamplerLocation, 0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glDrawArrays(GL_TRIANGLES, 0, 18);
    }

private:
    GLuint m_renderingProgram;
    GLuint m_brickTexture;

    static constexpr int NUM_VAOs = 1;
    std::array<GLuint, NUM_VAOs> m_vaos;
    std::array<GLuint, 2> m_vbos;

    glm::vec3 m_cameraPosition;
    glm::vec3 m_pyramidPosition;
    glm::mat4 m_perspectiveMatrix;
    glm::mat4 m_modelViewMatrix;
    glm::mat4 m_modelMatrix;
    glm::mat4 m_viewMatrix;

    float m_aspectRatio;

    GLint m_modelViewLocation;
    GLint m_perspectiveLocation;
	GLint m_textureSamplerLocation;

    void setupVertices() {
        float pyramidPositions[54] = {
            -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //front
            1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, //right
            1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, //back
            -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //left
            -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, //LF
            1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f //RR
        };

        float textureCoordinates[36] = {
            0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &m_vaos[0]);
        glBindVertexArray(m_vaos[0]);

        glGenBuffers(2, &m_vbos[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
    }
};

#endif //OPENGL_BOOK_SCENEPYRAMIDBRICKTEXTURE_H
