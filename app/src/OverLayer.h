#ifndef OPENGL_BOOK_OVERLAYER_H
#define OPENGL_BOOK_OVERLAYER_H

#include <string>

#include <core/Layer.h>

class OverLayer final : public core::Layer {
public:
    OverLayer();
    ~OverLayer();

    void OnEvent(SDL_Event& e) override;
    void OnUpdate(float dt) override;
    void OnRender() override;

private:
    int32_t m_selectedSceneIndex = {0};
    std::string m_currentScene;
};


#endif //OPENGL_BOOK_OVERLAYER_H