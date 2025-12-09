#ifndef OPENGL_BOOK_LAYERSCENE_H
#define OPENGL_BOOK_LAYERSCENE_H

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <functional>
#include <ranges>

#include "Scene.h"
#include <core/Layer.h>

namespace core {
    const inline uint32_t EVENT_SCENE_CHANGE = SDL_RegisterEvents(1);

    class LayerScene : public Layer {
    public:
        LayerScene();
        virtual ~LayerScene();
        void OnUpdate(float ts) override;
        void OnRender() override;

        bool SetSceneByName(const std::string& name);
        const std::string& GetSceneName() const { return m_sceneName; }

        template <typename TScene> requires(std::is_base_of_v<Scene, TScene>)
        void RegisterScene(const std::string& name) {
            m_scenes[name] = []() {
                return std::make_unique<TScene>();
            };
        }

        std::vector<std::string> GetScenesNames() {
            std::vector<std::string> names;
            names.reserve(m_scenes.size());

            for (const auto& key : m_scenes | std::views::keys) {
                names.push_back(key);
            }

            std::ranges::sort(names);

            return names;
        }

    private:
        using SceneFactory = std::function<std::unique_ptr<Scene>()>;

        std::unordered_map<std::string, SceneFactory> m_scenes;
        std::unique_ptr<Scene> m_scene;
        std::string m_sceneName;
        uint32_t m_sceneChangeEvent{};
    };
}


#endif //OPENGL_BOOK_LAYERSCENE_H
