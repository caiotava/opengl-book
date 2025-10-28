#include "Application.h"

namespace core {
    static Application* s_app;

    Application::Application(const ApplicationConfig& cfg) : m_config(cfg) {
        s_app = this;

        SDL_Init(SDL_INIT_VIDEO);

        if (m_config.windowConfig.title.empty()) {
            m_config.windowConfig.title = m_config.name;
        }

        m_window = std::make_shared<Window>(m_config.windowConfig);
        m_window->Create();;
    }

    Application::~Application() {
        m_window->Destroy();
        SDL_Quit();
        s_app = nullptr;
    }

    void Application::Run() {
        SetRunning(true);

        while (m_isRunning) {
            RunLoop();
        }
    }

    void Application::RunLoop() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                Stop();
                break;
            }
        }

        float currentTime = GetTime();
        float timeStep = glm::clamp(currentTime - m_lastFrameTime, 0.001f, 0.1f);
        m_lastFrameTime = currentTime;

        for (const auto& layer : m_layerStack) {
            layer->OnUpdate(timeStep);
        }

        for (const auto& layer : m_layerStack) {
            layer->OnRender();
        }

        m_window->Update();
    }


    void Application::Stop() {
        m_isRunning = false;
    }

    glm::vec2 Application::GetFramebufferSize() const {
        return m_window->GetFramebufferSize();
    }

    Application& Application::Get() {
        assert(s_app);
        return *s_app;
    }

    float Application::GetTime() {
        return static_cast<float>(SDL_GetTicks());
    }
}
