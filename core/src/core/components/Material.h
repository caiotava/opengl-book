#ifndef OPENGL_BOOK_MATERIAL_H
#define OPENGL_BOOK_MATERIAL_H

#include <glm/glm.hpp>

namespace core {
    class Material {
    public:
        static const Material GOLD;
        static const Material SILVER;
        static const Material BRONZE;

        Material() = default;

        Material(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, const float shiness) :
            m_ambient(ambient),
            m_diffuse(diffuse),
            m_specular(specular),
            m_shininess(shiness) {}

        glm::vec4 getAmbient() const { return m_ambient; }
        glm::vec4 getDiffuse() const { return m_diffuse; }
        glm::vec4 getSpecular() const { return m_specular; }
        float getShininess() const { return m_shininess; }

    private:
        glm::vec4 m_ambient;
        glm::vec4 m_diffuse;
        glm::vec4 m_specular;
        float m_shininess;
    };
} // core

#endif //OPENGL_BOOK_MATERIAL_H
