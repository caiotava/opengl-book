#include "OverLayer.h"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include <core/Application.h>
#include <scene/LayerScene.h>

OverLayer::OverLayer() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    const auto& window = core::Application::Get().GetWindow();
    ImGui_ImplSDL3_InitForOpenGL(window.GetHandler(), window.GetGLContext());
    ImGui_ImplOpenGL3_Init("#version 300 es");
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    const auto layerScene = core::Application::Get().GetLayer<core::LayerScene>();
    m_currentScene = layerScene->GetSceneName();
}

void OverLayer::OnEvent(SDL_Event& e) {
    ImGui_ImplSDL3_ProcessEvent(&e);
}

void OverLayer::OnUpdate(float dt) {}

void OverLayer::OnRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Choose the Scene you want to see!");

    ImGui::SeparatorText("Scenes");
    if (ImGui::BeginCombo(" ", m_currentScene.c_str())) {
        const auto layerScene = core::Application::Get().GetLayer<core::LayerScene>();
        const auto sceneNames = layerScene->GetScenesNames();

        for (const auto& name : layerScene->GetScenesNames()) {
            const bool is_selected = (m_currentScene == name);
            if (ImGui::Selectable(name.c_str(), is_selected)) {
                m_currentScene = name;
                layerScene->SetSceneByName(name);
            }

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::Separator();
    ImGui::SeparatorText("Render Options");
    // const auto layerScene = core::Application::Get().GetLayer<core::LayerScene>();
    // for (const auto& name : layerScene->GetScenesNames()) {
    //     ImGui::Checkbox(k.c_str(), &v);
    //     ImGui::SameLine();
    // }
    ImGui::End();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

OverLayer::~OverLayer() {
    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}