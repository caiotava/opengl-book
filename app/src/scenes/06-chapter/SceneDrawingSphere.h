#ifndef OPENGL_BOOK_SCENEDRAWINGSPHERE_H
#define OPENGL_BOOK_SCENEDRAWINGSPHERE_H

#include <array>

#include <scene/Scene.h>
#include <core/Application.h>
#include <core/shapes/Sphere.h>
#include <core/renderer/Shader.h>
#include <core/renderer/Texture.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SceneDrawingSphere final : public core::Scene {
public:
    SceneDrawingSphere() : Scene("6.1 - Drawing Sphere") {
        m_sphere = core::Sphere(48);
        m_renderingProgram = core::createGraphicsShader(
            "assets/shaders/06-chapter/sphere.vert",
            "assets/shaders/06-chapter/sphere.frag"
        );

        m_camera = glm::vec3(0.0f, 0.0f, 2.0f);
        m_spherePosition = glm::vec3(0.0f, 0.0f, -1.0f);

        const auto bufferSize = core::Application::Get().GetFramebufferSize();
        const float aspectRatio = bufferSize.x / bufferSize.y;
        m_perspectiveMatrix = glm::perspective(1.0472f, aspectRatio, 0.1f, 1000.0f);

        m_earthTexture = core::loadTexture("assets/shaders/06-chapter/earth.jpg");
        setupVertices();
    }

    ~SceneDrawingSphere() override {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDeleteBuffers(NUM_VBOs, &m_vbos[0]);
        glDeleteVertexArrays(1, &m_vaos[0]);
        glDeleteProgram(m_renderingProgram);
    }

    void OnUpdate(float ts) override {
    }

    void OnRender() override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glUseProgram(m_renderingProgram);

        m_modelViewLocation = glGetUniformLocation(m_renderingProgram, "modelViewMatrix");
        m_perspectiveLocation = glGetUniformLocation(m_renderingProgram, "perspectiveMatrix");
        m_textureLocation = glGetUniformLocation(m_renderingProgram, "sampl");

        const auto viewMatrix = glm::translate(glm::mat4(1.0f), -m_camera);
        const auto modelMatrix = glm::translate(glm::mat4(1.0f), m_spherePosition);
        const auto modelViewMatrix = viewMatrix * modelMatrix;

        glUniformMatrix4fv(m_modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
        glUniformMatrix4fv(m_perspectiveLocation, 1, GL_FALSE, glm::value_ptr(m_perspectiveMatrix));

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_earthTexture);
        glUniform1i(m_textureLocation, 0);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, m_sphere.getIndices().size());
    }

private:
    constexpr static int NUM_VBOs = 3;

    core::Sphere m_sphere;
    std::array<GLuint, 1> m_vaos;
    std::array<GLuint, NUM_VBOs> m_vbos;
    GLuint m_renderingProgram;

    glm::vec3 m_camera;
    glm::vec3 m_spherePosition;
    glm::mat4 m_perspectiveMatrix;
    GLuint m_earthTexture;

    GLint m_modelViewLocation;
    GLint m_perspectiveLocation;
    GLint m_textureLocation;

    void setupVertices(void) {
        const auto indices = m_sphere.getIndices();
        const auto vertices = m_sphere.getVertices();
        const auto textures = m_sphere.getTexCoords();
        const auto normals = m_sphere.getNormals();

        std::vector<float> vertexPositions;
        std::vector<float> textureCoordinates;
        std::vector<float> normalsValues;

        for (const int idx : indices) {
            vertexPositions.push_back(vertices[idx].x);
            vertexPositions.push_back(vertices[idx].y);
            vertexPositions.push_back(vertices[idx].z);

            textureCoordinates.push_back(textures[idx].s);
            textureCoordinates.push_back(textures[idx].t);

            normalsValues.push_back(normals[idx].x);
            normalsValues.push_back(normals[idx].y);
            normalsValues.push_back(normals[idx].z);
        }

        glGenVertexArrays(1, &m_vaos[0]);
        glBindVertexArray(m_vaos[0]);

        glGenBuffers(NUM_VBOs, &m_vbos[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * 4, &vertexPositions[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * 4, &textureCoordinates[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[2]);
        glBufferData(GL_ARRAY_BUFFER, normalsValues.size() * 4, &normalsValues[0], GL_STATIC_DRAW);
    }
};

#endif //OPENGL_BOOK_SCENEDRAWINGSPHERE_H
