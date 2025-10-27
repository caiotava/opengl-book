#include "AppLayer.h"

#include <core/renderer/Renderer.h>
#include <core/renderer/Shader.h>

#include "core/Application.h"

AppLayer::AppLayer() {
    m_shaderProgram = core::createGraphicsShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

    glCreateVertexArrays(1, &m_vertexArray);
    glCreateBuffers(1, &m_vertexBuffer);

    struct Vertex {
        glm::vec2 position;
        glm::vec2 texCoord;
    };

    Vertex vertices[] = {
        {{-1.0f, -1.0f}, {0.0f, 0.0f}},
        {{3.0f, -1.0f}, {2.0f, 0.0f}},
        {{-1.0f, 3.0f}, {0.0f, 2.0f}}
    };

    glNamedBufferData(m_vertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(m_vertexArray, 0, m_vertexBuffer, 0, sizeof(Vertex));

    glEnableVertexArrayAttrib(m_vertexArray, 0);
    glEnableVertexArrayAttrib(m_vertexArray, 1);

    glVertexArrayAttribFormat(m_vertexArray, 0, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, position)));
    glVertexArrayAttribFormat(m_vertexArray, 1, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, texCoord)));

    glVertexArrayAttribBinding(m_vertexArray, 0, 0);
    glVertexArrayAttribBinding(m_vertexArray, 1, 0);
}

AppLayer::~AppLayer() {
    glDeleteVertexArrays(1, &m_vertexArray);
    glDeleteBuffers(1, &m_vertexBuffer);

    glDeleteProgram(m_shaderProgram);
}

void AppLayer::OnUpdate(float ts) {
}

void AppLayer::OnRender() {
    glUseProgram(m_shaderProgram);

    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    glUniform1f(0, core::Application::GetTime()/60/60);
    glm::vec2 framebufferSize = core::Application::Get().GetFramebufferSize();

    glUniform2f(1, framebufferSize.x, framebufferSize.y);
    glUniform4f(2, mouseX, mouseY, 0.0f, 0.0f);
    glViewport(0, 0, framebufferSize.x, framebufferSize.y);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(m_vertexArray);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
