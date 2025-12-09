#include "LayerScene.h"

#include <core/Application.h>

namespace core {
    LayerScene::LayerScene() {}

    LayerScene::~LayerScene() = default;

    void LayerScene::OnUpdate(float ts) {
        m_scene->OnUpdate(ts);
    }

    void LayerScene::OnRender() {
        m_scene->OnRender();
    }

    bool LayerScene::SetSceneByName(const std::string& name) {
        if (!m_scenes.contains(name)) {
            return false;
        }

        const auto& newScene = m_scenes[name];
        m_scene = nullptr;
        m_scene = newScene();
        m_sceneName = name;

        return true;
    }
}
