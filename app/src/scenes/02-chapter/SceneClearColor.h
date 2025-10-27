#ifndef OPENGL_BOOK_SCENECLEARCOLOR_H
#define OPENGL_BOOK_SCENECLEARCOLOR_H

#include <scene/Scene.h>
#include <core/renderer/System.h>

class SceneClearColor final : public core::Scene {
public:
    SceneClearColor() : Scene("SceneClearColor") {
    }

    void OnUpdate(float ts) override {
    }

    void OnRender() override {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};


#endif //OPENGL_BOOK_SCENECLEARCOLOR_H
