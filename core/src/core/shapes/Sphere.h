#ifndef OPENGL_BOOK_SPHERE_H
#define OPENGL_BOOK_SPHERE_H

#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

namespace core {
    class Sphere {
    public:
        Sphere();
        explicit Sphere(int32_t precision);

        static float toRadians(float degrees);
        void init(int32_t precision);
        int32_t getNumberVertices() const { return m_numberVertices; }
        int32_t getNumberIndices() const { return m_numberIndices; }
        std::vector<glm::vec3> getVertices() { return m_vertices; }
        std::vector<glm::vec2> getTexCoords() { return m_texCoords; }
        std::vector<glm::vec3> getNormals() { return m_normals; }
        std::vector<int32_t> getIndices() { return m_indices; }

    private:
        int32_t m_numberVertices;
        int32_t m_numberIndices;

        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec2> m_texCoords;
        std::vector<glm::vec3> m_normals;
        std::vector<int32_t> m_indices;
    };
}


#endif //OPENGL_BOOK_SPHERE_H
