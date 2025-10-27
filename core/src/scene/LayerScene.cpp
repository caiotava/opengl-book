#include "LayerScene.h"

namespace core {
    LayerScene::LayerScene(std::unique_ptr<Scene> scene) : m_scene(std::move(scene)) {
    }

    LayerScene::~LayerScene() = default;

    void LayerScene::OnUpdate(float ts) {
        m_scene->OnUpdate(ts);
    }

    void LayerScene::OnRender() {
        m_scene->OnRender();
    }

    void LayerScene::SetScene(std::unique_ptr<Scene> scene) {
        m_scene = std::move(scene);
    }
}
