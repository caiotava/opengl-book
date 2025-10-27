#ifndef OPENGL_BOOK_APPLAYER_H
#define OPENGL_BOOK_APPLAYER_H

#include <cstdint>
#include <core/Layer.h>

class AppLayer : public core::Layer {
public:
    AppLayer();
    virtual ~AppLayer();

    virtual void OnUpdate(float ts) override;
    virtual void OnRender() override;

private:
    uint32_t m_shaderProgram = 0;
    uint32_t m_vertexArray = 0;
    uint32_t m_vertexBuffer = 0;
};

#endif //OPENGL_BOOK_APPLAYER_H
