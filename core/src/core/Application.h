#ifndef OPENGL_BOOK_APPLICATION_H
#define OPENGL_BOOK_APPLICATION_H

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Layer.h"
#include "Window.h"

namespace core {
    struct ApplicationConfig {
        std::string name;
        WindowConfig windowConfig;
    };

    class Application {
    public:
        explicit Application(const ApplicationConfig& cfg);
        ~Application();

        void Run();
        void RunLoop();
        void Stop();
        void SetRunning(bool running) { m_isRunning = running; }

        template <typename TLayer, typename... Args>
            requires(std::is_base_of_v<Layer, TLayer>)
        void PushLayer(Args&&... args) {
            m_layerStack.push_back(std::make_unique<TLayer>(std::forward<Args>(args)...));
        }

        glm::vec2 GetFramebufferSize() const;

        static Application& Get();
        static float GetTime();

    private:
        ApplicationConfig m_config;
        std::shared_ptr<Window> m_window;
        std::vector<std::unique_ptr<Layer>> m_layerStack;
        float m_lastFrameTime = 0;

        bool m_isRunning = false;
    };
} // namespace core

#endif // OPENGL_BOOK_APPLICATION_H
