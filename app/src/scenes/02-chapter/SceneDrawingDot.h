#ifndef OPENGL_BOOK_SCENEDRAWINGDOT_H
#define OPENGL_BOOK_SCENEDRAWINGDOT_H

#include <scene/Scene.h>
#include <core/renderer/System.h>

class SceneDrawingDot final : public core::Scene {
public:
    SceneDrawingDot();
    ~SceneDrawingDot() override;

    void OnUpdate(float ts) override;

    void OnRender() override;

private:
    static constexpr int32_t numVAOs = 1;
    GLuint m_renderingProgram;
    GLuint m_vao[numVAOs]{};

    GLuint createShaderProgram();
};

#endif //OPENGL_BOOK_SCENEDRAWINGDOT_H
