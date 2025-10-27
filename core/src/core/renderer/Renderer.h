#ifndef OPENGL_BOOK_RENDERER_H
#define OPENGL_BOOK_RENDERER_H

#include <cstdint>

#if defined(__EMSCRIPTEN__)
    #include <GLES3/gl3.h>
#else
    #include <glad/glad.h>
#endif

#include <filesystem>
#include <glm/glm.hpp>

namespace core {
    class Texture {
    public:
        Texture(uint32_t width, uint32_t height);
        Texture(const std::filesystem::path& path);

        bool Load();

        glm::u32vec2 GetSize() const;

    private:
        GLuint m_handle;
        std::filesystem::path m_path;
        uint32_t m_width;
        uint32_t m_height;
    };

    class Framebuffer {
    public:
        explicit Framebuffer(const Texture& texture);

        bool AttachTexture(const Texture& texture);
        void BlitToSwapChain();

    private:
        GLuint m_handle = 0;
        Texture m_colorAttachment;
    };
}


#endif //OPENGL_BOOK_RENDERER_H
