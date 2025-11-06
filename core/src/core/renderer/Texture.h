#ifndef OPENGL_BOOK_TEXTURE_H
#define OPENGL_BOOK_TEXTURE_H

#include <filesystem>
#include <core/renderer/System.h>

namespace core {
    GLuint loadTexture(const std::filesystem::path &texturePath);
}

#endif //OPENGL_BOOK_TEXTURE_H