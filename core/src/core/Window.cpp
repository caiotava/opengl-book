#include "Window.h"

#include <iostream>

#if defined(__EMSCRIPTEN__)
    #include <GLES3/gl3.h>
#else
    #include <glad/glad.h>
#endif

namespace core {
    Window::Window(const WindowConfig &cfg) :
        m_config(cfg) {
    }

    Window::~Window() { Destroy(); }

    void Window::Create() {
#if defined(__EMSCRIPTEN__)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

        m_sdlWindow = SDLWindowPtr(SDL_CreateWindow(
            m_config.title.c_str(),
            m_config.width,
            m_config.height,
            SDL_WINDOW_OPENGL
        ));

        if (!m_sdlWindow) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "creating sdl window: %s", SDL_GetError());
            assert(false);
        };

        m_openGLContex = SDL_GL_CreateContext(m_sdlWindow.get());
        SDL_GL_MakeCurrent(m_sdlWindow.get(), m_openGLContex);

        if (m_config.hasVSync) {
            SDL_GL_SetSwapInterval(1);
        }

#if !defined(__EMSCRIPTEN__)
        auto const gladVersion = gladLoadGL();
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "glad version %d", gladVersion);
        std::cout << "glad version " << gladVersion << std::endl;
#endif

    }

    void Window::Update() const { SDL_GL_SwapWindow(m_sdlWindow.get()); }

    void Window::Destroy() { SDL_GL_DestroyContext(m_openGLContex); }

    glm::ivec2 Window::GetFramebufferSize() const {
        int32_t width, height;
        SDL_GetWindowSize(m_sdlWindow.get(), &width, &height);

        return {width, height};
    }

    bool Window::ShouldClose() const { return m_sdlWindow.get() == nullptr; }
}; // namespace core
