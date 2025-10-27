#include <core/Application.h>
#include <core/Layer.h>
#include "AppLayer.h"

int main() {
    core::ApplicationConfig appConfig;
    appConfig.name = "OpenGL book";
    appConfig.windowConfig.width = 1920;
    appConfig.windowConfig.height = 1080;
    appConfig.windowConfig.hasVSync = true;

    core::Application app(appConfig);
    app.PushLayer<AppLayer>();
    app.Run();
}
