#ifndef OPENGL_BOOK_SCENEDRAWINGTRIANGLE_H
#define OPENGL_BOOK_SCENEDRAWINGTRIANGLE_H

#include <core/renderer/Shader.h>
#include <core/renderer/System.h>
#include <scene/Scene.h>

class SceneDrawingTriangle final : public core::Scene {
public:
    SceneDrawingTriangle() : Scene("2.5 Drawing a triangle") {
        m_programHandle = core::createGraphicsShader(
            "assets/shaders/02-chapter/triangle-vert.glsl",
            "assets/shaders/02-chapter/triangle-frag.glsl"
        );

        glGenVertexArrays(NUM_VAOs, m_vao);
        glBindVertexArray(m_vao[0]);
    }

    ~SceneDrawingTriangle() override {
        glDeleteVertexArrays(NUM_VAOs, m_vao);
        glDeleteProgram(m_programHandle);
    }

    void OnUpdate(float ts) override {}

    void OnRender() override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(m_programHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    GLint m_programHandle = 0;
    static constexpr int32_t NUM_VAOs = 1;
    GLuint m_vao[NUM_VAOs];
};

#endif //OPENGL_BOOK_SCENEDRAWINGTRIANGLE_H
