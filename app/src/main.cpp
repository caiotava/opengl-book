#include <core/Application.h>
#include "AppLayer.h"
#include <scene/LayerScene.h>

#include "scenes/02-chapter/SceneClearColor.h"
#include "scenes/02-chapter/SceneDrawingDot.h"
#include "scenes/02-chapter/SceneDrawingTriangle.h"
#include "scenes/02-chapter/SceneSimpleAnimation.h"
#include "scenes/02-chapter/SceneSimpleRotation.h"
#include "scenes/04-chapter/ScenePlainRedCube.h"
#include "scenes/04-chapter/SceneIntepolateCubeColor.h"
#include "scenes/04-chapter/SceneSwarmCube.h"
#include "scenes/04-chapter/SceneInstancedCube.h"
#include "scenes/04-chapter/SceneCubePyramid.h"
#include "scenes/04-chapter/SceneSimpleSolarSystem.h"
#include "scenes/05-chapter/ScenePyramidBrickTexture.h"
#include "scenes/06-chapter/SceneDrawingSphere.h"
#include "scenes/06-chapter/SceneDrawingTorus.h"
#include "scenes/06-chapter/SceneLoadModel.h"

int main() {
    core::ApplicationConfig appConfig;
    appConfig.name = "OpenGL book";
    appConfig.windowConfig.width = 600;
    appConfig.windowConfig.height = 600;
    appConfig.windowConfig.hasVSync = true;

    core::Application app(appConfig);
    // app.PushLayer<AppLayer>();
    app.PushLayer<core::LayerScene>(std::make_unique<SceneLoadModel>());
    app.Run();
}
