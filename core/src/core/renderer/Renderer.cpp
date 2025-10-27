#include "Renderer.h"

#include <iostream>

#include "stb_image.h"

namespace core {
    Texture::Texture(uint32_t width, uint32_t height) :
        m_width(width), m_height(height), m_handle(0) {
        // glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
        // glTextureStorage2D(m_handle, 1, GL_RGBA32F, m_width, m_height);
        //
        // glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //
        // glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    Texture::Texture(const std::filesystem::path& path): m_handle(0) {
        int32_t width, height, channels;
        auto const filePath = path.string();
        unsigned char* imgData = stbi_load(
            filePath.c_str(),
            &width,
            &height,
            &channels,
            STBI_default
        );

        if (!imgData) {
            std::cerr << "failed to load texture: " << filePath << std::endl;
            return;
        }

        GLenum format;
        switch (channels) {
        case 4:
            format = GL_RGBA;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 1:
            format = GL_RED;
            break;
        default:
            format = 0;
        }

        m_width = width;
        m_height = height;

        // glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
        //
        // glTextureStorage2D(m_handle, 1, (format == GL_RGBA ? GL_RGBA8 : GL_RGB8), m_width, m_height);
        // glTextureSubImage2D(m_handle, 0,0,0, m_width, m_height, format, GL_UNSIGNED_BYTE, imgData);
        //
        // glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //
        // glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glGenerateMipmap(m_handle);
        stbi_image_free(imgData);
    }

    glm::u32vec2 Texture::GetSize() const {
        return {m_width, m_height};
    }

    Framebuffer::Framebuffer(const Texture& texture): m_colorAttachment(texture) {
        // glCreateFramebuffers(1, &m_handle);

        if (!AttachTexture(texture)) {
            glDeleteFramebuffers(1, &m_handle);
        }
    }

    bool Framebuffer::AttachTexture(const Texture& texture) {
        // glNamedFramebufferTexture(m_handle, GL_COLOR_ATTACHMENT0, m_handle, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "framebuffer is not complete!" << std::endl;
            return false;
        }

        m_colorAttachment= texture;
        return true;
    }

    void Framebuffer::BlitToSwapChain() {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_handle);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        auto texSize = m_colorAttachment.GetSize();

        glBlitFramebuffer(0,0, texSize.x, texSize.y, 0, 0, texSize.x, texSize.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }


}
