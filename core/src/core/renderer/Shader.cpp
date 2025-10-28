#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace core {
    static std::string readTextFile(const std::filesystem::path& path) {
        std::ifstream file(path);

        if (!file.is_open()) {
            std::cerr << "failed to open file: " << path.string() << std::endl;
            return {};
        }

        std::ostringstream contentStream;
        contentStream << file.rdbuf();

        return contentStream.str();
    }

    uint32_t createComputerShader(const std::filesystem::path& path) {
        const auto shaderSource = readTextFile(path);

        const GLuint shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

        const auto* source = shaderSource.c_str();
        glShaderSource(shaderHandle, 1, &source, nullptr);

        glCompileShader(shaderHandle);

        GLint isCompiled = 0;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE) {
            printShaderLog(shaderHandle);
            glDeleteShader(shaderHandle);
            return -1;
        }

        GLuint program = glCreateProgram();
        glAttachShader(program, shaderHandle);
        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE) {
            printProgramLog(program);
            glDeleteProgram(program);
            glDeleteShader(shaderHandle);
            return -1;
        }

        glDetachShader(program, shaderHandle);
        return program;
    }

    bool checkOpenGLError() {
        bool foundError = false;
        int32_t glErr = glGetError();

        while (glErr != GL_NO_ERROR) {
            std::cerr << "gl_error: " << glErr << std::endl;
            glErr = glGetError();
            foundError = true;
        }

        return foundError;
    }

    void printProgramLog(int programID) {
        GLint logLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            std::vector<GLchar> infoLog(logLength);
            glGetProgramInfoLog(programID, logLength, &logLength, &infoLog[0]);
            std::cerr << "program log: " << infoLog.data() << std::endl;
        }
    }

    void printShaderLog(GLuint shaderID) {
        GLint logLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            std::vector<GLchar> infoLog(logLength);
            glGetShaderInfoLog(shaderID, logLength, &logLength, &infoLog[0]);
            std::cerr << "shader info log: " << infoLog.data() << std::endl;
        }
    }

    uint32_t reloadComputerShader(uint32_t shaderHandle, const std::filesystem::path& path) {
        uint32_t newShaderHandle = createComputerShader(path);

        if (newShaderHandle == -1) {
            return shaderHandle;
        }

        glDeleteShader(shaderHandle);
        return newShaderHandle;
    }

    uint32_t createGraphicsShader(const std::filesystem::path& vertex, const std::filesystem::path& frag) {
        const auto vertexSource = readTextFile(vertex);
        const auto fragSource = readTextFile(frag);

        GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
        const auto* source = vertexSource.c_str();

        glShaderSource(vertexShaderHandle, 1, &source, nullptr);
        glCompileShader(vertexShaderHandle);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            printShaderLog(vertexShaderHandle);
            glDeleteShader(vertexShaderHandle);
            return -1;
        }

        GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragSource.c_str();
        glShaderSource(fragmentShaderHandle, 1, &source, nullptr);
        glCompileShader(fragmentShaderHandle);

        isCompiled = 0;
        glGetShaderiv(fragmentShaderHandle, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            printShaderLog(fragmentShaderHandle);
            glDeleteShader(fragmentShaderHandle);
            return -1;
        }

        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShaderHandle);
        glAttachShader(program, fragmentShaderHandle);
        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            printProgramLog(program);
            glDeleteProgram(program);
            glDeleteShader(vertexShaderHandle);
            glDeleteShader(fragmentShaderHandle);

            return -1;
        }

        glDetachShader(program, vertexShaderHandle);
        glDetachShader(program, fragmentShaderHandle);

        return program;
    }

    uint32_t reloadGraphicsShader(uint32_t handle, const std::filesystem::path& vertex, std::filesystem::path& frag) {
        uint32_t newShaderHandle = createGraphicsShader(vertex, frag);

        if (newShaderHandle == -1) {
            return handle;
        }

        glDeleteShader(handle);
        return newShaderHandle;
    }
}
