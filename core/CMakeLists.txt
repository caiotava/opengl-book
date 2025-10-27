set(SOURCES
        src/core/Application.cpp
        src/core/Application.h        src/core/Window.cpp
        src/core/renderer/Renderer.cpp
        src/core/renderer/Renderer.h
        src/core/renderer/Shader.cpp
        src/core/renderer/Shader.h
)

add_library(Core STATIC)

set_target_properties(Core PROPERTIES CXX_SCAN_FOR_MODULES OFF)

target_sources(Core PRIVATE ${SOURCES})
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${Stb_INCLUDE_DIR})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(Stb REQUIRED)

target_link_libraries(Core PRIVATE
        glm::glm
        OpenGL::GL
        glad::glad
        SDL3::SDL3
)