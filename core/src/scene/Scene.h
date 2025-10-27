#ifndef OPENGL_BOOK_SCENE_H
#define OPENGL_BOOK_SCENE_H

#include <string>

namespace core {
    class Scene {
    public:
        explicit Scene(const std::string& name = "Scene") : m_name(name) {
        }

        virtual ~Scene() = default;
        virtual void OnUpdate(float ts) {}
        virtual void OnRender() {}

        std::string GetName() const { return m_name; }

    protected:
        std::string m_name;
    };
}
#endif // OPENGL_BOOK_SCENE_H
