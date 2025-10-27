#include <emscripten.h>

#include <core/Application.h>
#include <scene/LayerScene.h>
#include "scenes/02-chapter/SceneClearColor.h"
#include "AppLayer.h"

void RunGameLoop() {
    core::Application::Get().RunLoop();
}

int main() {
    EM_ASM(
            {
                FS.mkdir('/libsdl');
                FS.mount(IDBFS, {}, '/libsdl');
            }
    );

    core::ApplicationConfig appConfig = {
        .name = "OpenGL book",
        .windowConfig = {
            .title = "OpenGL book",
            .width = 1920,
            .height = 1080,
            .hasVSync = true
        }
    };

    core::Application app(appConfig);
    app.SetRunning(true);
    app.PushLayer<core::LayerScene>(std::make_unique<SceneClearColor>());
    emscripten_set_main_loop(RunGameLoop, 0, 1);

    return 0;
}
