#include "SceneDrawingDot.h"

#include <string>

SceneDrawingDot::SceneDrawingDot() : Scene("2.2 Shaders, Drawing a POINT") {
    m_renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, m_vao);
    glBindVertexArray(m_vao[0]);
}

void SceneDrawingDot::OnUpdate(float ts) {
}

void SceneDrawingDot::OnRender() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_renderingProgram);
    glDrawArrays(GL_POINTS, 0, 1);
}

GLuint SceneDrawingDot::createShaderProgram() {
    const std::string vShaderSource =
        "#version 300 es	\n"
        "precision mediump float; \n"
        "void main(void) {	\n"
        "	gl_Position = vec4(0.0, 0.0, 0.0, 1.0); \n "
        "	gl_PointSize = 30.0; \n "
        "} \n ";

    const std::string fShaderSource =
        "#version 300 es  \n"
        "precision mediump float; \n"
        "out vec4 color;	\n"
        "void main(void) { 	\n"
        "   if (gl_FragCoord.x < 295.0)\n"
        "		color = vec4(1.0, 0.0, 0.0, 1.0); \n"
        "	else \n"
        "		color = vec4(0.0, 1.0, 1.0, 1.0); \n"
        "}";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    const auto* vertexSource = vShaderSource.c_str();
    const auto* fragSource = fShaderSource.c_str();

    glShaderSource(vShader, 1, &vertexSource, nullptr);
    glShaderSource(fShader, 1, &fragSource, nullptr);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}
