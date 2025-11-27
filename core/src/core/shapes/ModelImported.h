#ifndef OPENGL_BOOK_MODELIMPORTED_H
#define OPENGL_BOOK_MODELIMPORTED_H

#include <filesystem>

#include <glm/glm.hpp>

namespace core {
    class ModelImported {
    public:
        ModelImported() = default;
        explicit ModelImported(const std::filesystem::path& filePath);

        int32_t getNumberVertices() const;
        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec2> getTextureCoords();
        std::vector<glm::vec3> getNormals();

    private:
        int32_t m_numberVertices;
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec2> m_textureCoords;
        std::vector<glm::vec3> m_normals;
    };

    class ModelImporter {
    public:
        ModelImporter() = default;
        void parseOBJ(const std::filesystem::path& filePath);

        int getNumVertices();
        std::vector<float> getVertices();
        std::vector<float> getTextureCoords();
        std::vector<float> getNormals();

    private:
        std::vector<float> m_vertices;
        std::vector<float> m_triangleVertices;
        std::vector<float> m_textureCoords;
        std::vector<float> m_stVals;
        std::vector<float> m_normals;
        std::vector<float> m_normalsVals;
    };
}


#endif //OPENGL_BOOK_MODELIMPORTED_H
