#ifndef OPENGL_BOOK_SHADER_H
#define OPENGL_BOOK_SHADER_H

#include <filesystem>
#include "System.h"

namespace core {
    uint32_t createComputerShader(const std::filesystem::path& path);
    uint32_t reloadComputerShader(uint32_t shaderHandle, const std::filesystem::path& path);
    bool checkOpenGLError();
    void printProgramLog(int prog);
    void printShaderLog(GLuint shader);

    uint32_t createGraphicsShader(const std::filesystem::path& vertex, const std::filesystem::path& frag);
    uint32_t reloadGraphicsShader(
        uint32_t shaderHandle,
        const std::filesystem::path& vertex,
        std::filesystem::path& frag
    );
}

#endif //OPENGL_BOOK_SHADER_H
