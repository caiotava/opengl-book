#ifndef OPENGL_BOOK_LAYER_H
#define OPENGL_BOOK_LAYER_H

#include <SDL3/SDL.h>

namespace core {
    class Layer {
    public:
        virtual ~Layer() = default;

        virtual void OnEvent(SDL_Event &e) {};

        virtual void OnUpdate(float ts) {};
        virtual void OnRender() {};
    };
};

#endif //OPENGL_BOOK_LAYER_H