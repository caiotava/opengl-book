#ifndef OPENGL_BOOK_LIGHT_H
#define OPENGL_BOOK_LIGHT_H

#include <glm/glm.hpp>

namespace core {
    class Light {
    public:
        enum Type {
            Ambient,
            Point,
            Directional,
            Spotlight,
        };

        Light() = default;

        explicit Light(glm::vec4 ambient) : m_type(Type::Ambient), m_ambient(ambient) {}

        Light(Type type, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec4 position) :
            m_type(type),
            m_ambient(ambient),
            m_diffuse(diffuse),
            m_specular(specular),
            m_position(position) {}

        void setPosition(const glm::vec4 &position) {
            m_position = position;
        }

        glm::vec4 getAmbient() const { return m_ambient; }
        glm::vec4 getDiffuse() const { return m_diffuse; }
        glm::vec4 getSpecular() const { return m_specular; }
        glm::vec4 getPosition() const { return m_position; }
        Type getType() const { return m_type; }

    private:
        Type m_type = Type::Point;
        glm::vec4 m_ambient = {};
        glm::vec4 m_diffuse = {};
        glm::vec4 m_specular = {};
        glm::vec4 m_position = {};
    };
} // core

#endif //OPENGL_BOOK_LIGHT_H
