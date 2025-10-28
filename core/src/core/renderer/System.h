#ifndef OPENGL_BOOK_SYSTEM_H
#define OPENGL_BOOK_SYSTEM_H

#include <SDL3/SDL.h>
#include <iostream>

#if defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>
#else
#include <glad/glad.h>
#endif

namespace core {
    inline void SetRendererAttributes() {
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
    }

    inline void RegisterGLFunction() {
#if !defined(__EMSCRIPTEN__)
        auto const gladVersion = gladLoadGL();
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "glad version %d", gladVersion);
        std::cout << "glad version " << gladVersion << std::endl;

        glEnable(GL_PROGRAM_POINT_SIZE);
#endif
    }
}

#endif //OPENGL_BOOK_SYSTEM_H
