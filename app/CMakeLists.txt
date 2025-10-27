
set(SOURCES src/main.cpp src/AppLayer.cpp)

if (EMSCRIPTEN)
    set(SOURCES src/main_web.cpp)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(LD_OPTIONS "${LD_OPTIONS}--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@/assets -sALLOW_MEMORY_GROWTH -lidbfs.js")
    set(LD_OPTIONS "${LD_OPTIONS} -s EXPORTED_RUNTIME_METHODS=['ccall'] -sUSE_WEBGL2=1")
    set(LD_OPTIONS "${LD_OPTIONS} --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/platforms/web/custom_shell.html")
endif ()

list(APPEND SOURCES
        src/scenes/02-chapter/SceneClearColor.h
        src/scenes/02-chapter/SceneDrawingDot.cpp
        src/scenes/02-chapter/SceneDrawingDot.h
)

add_executable(App)

set_target_properties(App PROPERTIES CXX_SCAN_FOR_MODULES OFF)

target_sources(App PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_link_libraries(App Core ${LD_OPTIONS})

target_include_directories(App PRIVATE Source)