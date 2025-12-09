#ifndef OPENGL_BOOK_WINDOW_H
#define OPENGL_BOOK_WINDOW_H

#include <string>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "platform/SDLDeleter.h"

namespace core {
    struct WindowConfig {
        std::string title;
        std::uint32_t width;
        std::uint32_t height;
        bool isResizable;
        bool hasVSync;
    };

    class Window {
    public:
        explicit Window(const WindowConfig &cfg = {});
        ~Window();

        void Create();
        void Destroy();

        void Update() const;

        glm::ivec2 GetFramebufferSize() const;

        bool ShouldClose() const;

        SDL_Window* GetHandler() const { return m_sdlWindow.get(); }
        SDL_GLContext GetGLContext() const { return m_openGLContex; }

    private:
        WindowConfig m_config;
        SDLWindowPtr m_sdlWindow;
        SDL_GLContext m_openGLContex;
    };
}; // namespace core


#endif // OPENGL_BOOK_WINDOW_H
