#ifndef OPENGL_BOOK_SDLDELETER_H
#define OPENGL_BOOK_SDLDELETER_H

#include <SDL3/SDL.h>
#include <memory>

namespace core {
    class SDLDeleter {
    public:
        void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
    };

    using SDLWindowPtr = std::unique_ptr<SDL_Window, SDLDeleter>;
}

#endif // OPENGL_BOOK_SDLDELETER_H
