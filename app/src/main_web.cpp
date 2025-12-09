#include <emscripten.h>

#include <core/Application.h>
#include <scene/LayerScene.h>
#include "OverLayer.h"
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
#include "scenes/07-chapter/SceneGouraudShader.h"

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
            .width = 600,
            .height = 600,
            .hasVSync = true
        }
    };

    core::Application app(appConfig);
    app.SetRunning(true);

    app.PushLayer<core::LayerScene>();

    const auto layerScene = app.GetLayer<core::LayerScene>();
    layerScene->RegisterScene<SceneClearColor>("02.1 - Scene Clear Color");
    layerScene->RegisterScene<SceneDrawingDot>("02.2 - Scene Drawing");
    layerScene->RegisterScene<SceneDrawingTriangle>("02.3 - Scene Drawing Triangle");
    layerScene->RegisterScene<SceneSimpleAnimation>("02.4 - Scene Simple Animation");
    layerScene->RegisterScene<SceneSimpleRotation>("02.5 - Scene Simple Rotation");
    layerScene->RegisterScene<ScenePlainRedCube>("04.1 - Scene Plain Red Cube");
    layerScene->RegisterScene<SceneIntepolateCubeColor>("04.2 - Scene Interpolate Cube Color");
    layerScene->RegisterScene<SceneSwarmCube>("04.3 - Scene Swarm Cube Color");
    layerScene->RegisterScene<SceneInstancedCube>("04.4 - Scene Instanced Cube (1 Million)");
    layerScene->RegisterScene<SceneCubePyramid>("04.5 - Scene Pyramid");
    layerScene->RegisterScene<SceneSimpleSolarSystem>("04.6 - Scene Simple Solar System");
    layerScene->RegisterScene<ScenePyramidBrickTexture>("05.1 - Scene Pyramid Brick Texture");
    layerScene->RegisterScene<SceneDrawingSphere>("06.1 - Scene Drawing Sphere");
    layerScene->RegisterScene<SceneDrawingTorus>("06.2 - Scene Drawing Torus");
    layerScene->RegisterScene<SceneLoadModel>("06.3 - Scene Load OBJ Model");
    layerScene->RegisterScene<SceneGouraudShader>("07.1 - Scene Lighting Mode Shader");

    layerScene->SetSceneByName("07.1 - Scene Lighting Mode Shader");

    app.PushLayer<OverLayer>();
    emscripten_set_main_loop(RunGameLoop, 0, 1);

    return 0;
}
