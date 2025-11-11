set(SOURCES
        src/core/Application.cpp
        src/core/Application.h
        src/core/Window.cpp
        src/core/renderer/Renderer.cpp
        src/core/renderer/Renderer.h
        src/core/renderer/Shader.cpp
        src/core/renderer/Shader.h
        src/core/renderer/Texture.cpp
        src/core/shapes/Sphere.cpp
        src/scene/LayerScene.cpp
)

add_library(Core STATIC)

# Allowing the math.h header to define values like: M_PI
add_compile_definitions(_USE_MATH_DEFINES=1)

set_target_properties(Core PROPERTIES CXX_SCAN_FOR_MODULES OFF)

target_sources(Core PRIVATE ${SOURCES})
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${Stb_INCLUDE_DIR})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(soil2 CONFIG REQUIRED)

target_link_libraries(Core PRIVATE
        glm::glm
        OpenGL::GL
        glad::glad
        SDL3::SDL3
        soil2
)