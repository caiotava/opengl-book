#ifndef OPENGL_BOOK_SCENESIMPLEROTATION_H
#define OPENGL_BOOK_SCENESIMPLEROTATION_H

#include <cmath>

#include <scene/Scene.h>
#include <core/renderer/System.h>
#include <core/renderer/Shader.h>

class SceneSimpleRotation final : public core::Scene {
public:
    SceneSimpleRotation() : Scene("3.1 Simple Roration Exercise"), m_trianglePosX(0.0f), m_movingOffset(0.1f) {
        m_programHandle = core::createGraphicsShader(
            "assets/shaders/02-chapter/animation-rotation.vert",
            "assets/shaders/02-chapter/animation.frag"
        );

        glGenVertexArrays(NUM_VAOs, m_vao);
        glBindVertexArray(m_vao[0]);
    }

    void OnUpdate(float ts) override {
        m_trianglePosX += m_movingOffset * ts;
        if (std::abs(m_trianglePosX) > 1.0f) {
            m_movingOffset *= -1;
        }

        const GLint offsetLoc = glGetUniformLocation(m_programHandle, "offset");
        glUseProgram(m_programHandle);
        glUniform1f(offsetLoc, m_trianglePosX);
    }

    void OnRender() override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(m_programHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    GLuint m_programHandle;
    static constexpr int32_t NUM_VAOs = 1;
    GLuint m_vao[NUM_VAOs];
    float m_trianglePosX;
    float m_movingOffset;
};

#endif //OPENGL_BOOK_SCENESIMPLEROTATION_H
