#include <core/Application.h>
#include "AppLayer.h"
#include <scene/LayerScene.h>

#include "scenes/02-chapter/SceneClearColor.h"

int main() {
    core::ApplicationConfig appConfig;
    appConfig.name = "OpenGL book";
    appConfig.windowConfig.width = 1920;
    appConfig.windowConfig.height = 1080;
    appConfig.windowConfig.hasVSync = true;

    core::Application app(appConfig);
    app.PushLayer<AppLayer>();
    // app.PushLayer<core::LayerScene>(std::make_unique<SceneClearColor>());
    app.Run();
}
