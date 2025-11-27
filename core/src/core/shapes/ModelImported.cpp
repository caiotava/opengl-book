#include "ModelImported.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace core {
    ModelImported::ModelImported(const std::filesystem::path& filePath) {
        auto importer = ModelImporter{};
        importer.parseOBJ(filePath);

         m_numberVertices = importer.getNumVertices();
        auto vertices = importer.getVertices();
        auto textureCoords = importer.getTextureCoords();
        auto normals = importer.getNormals();

        for (int32_t i = 0; i < m_numberVertices; i++) {
            m_vertices.emplace_back(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
            m_textureCoords.emplace_back(textureCoords[i * 2], textureCoords[i * 2 + 1]);
            m_normals.emplace_back(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
        }
    }

    int32_t ModelImported::getNumberVertices() const {
        return m_numberVertices;
    }

    std::vector<glm::vec3> ModelImported::getVertices() {
        return m_vertices;
    }

    std::vector<glm::vec2> ModelImported::getTextureCoords() {
        return m_textureCoords;
    }

    std::vector<glm::vec3> ModelImported::getNormals() {
        return m_normals;
    }


    void ModelImporter::parseOBJ(const std::filesystem::path& filePath) {
        std::ifstream fileStream(filePath, std::ios::in);

        if (!fileStream.is_open()) {
            std::cerr << "failed to open file: " << filePath.string() << std::endl;
            return;
        }

        float x, y, z;
        std::string type;
        std::string line;
        while (!fileStream.eof()) {
            std::getline(fileStream, line);

            if (line.empty()) {
                continue;
            }


            if (line.starts_with("v ")) {
                std::stringstream ss(line);

                ss >> type >> x >> y >> z;
                m_vertices.push_back(x);
                m_vertices.push_back(y);
                m_vertices.push_back(z);
            }

            if (line.starts_with("vt")) {
                std::stringstream ss(line);

                ss >> type >> x >> y;
                m_stVals.push_back(x);
                m_stVals.push_back(y);
            }

            if (line.starts_with("vn")) {
                std::stringstream ss(line);
                ss >> type >> x >> y >> z;

                m_normalsVals.push_back(x);
                m_normalsVals.push_back(y);
                m_normalsVals.push_back(z);
            }

            if (line.starts_with("f ")) {
                std::string oneCorner, v, t, n;
                std::stringstream ss(line.erase(0, 2));

                for (int i = 0; i < 3; i++) {
                    std::getline(ss, oneCorner, ' ');
                    std::stringstream oneCornerSS(oneCorner);

                    std::getline(oneCornerSS, v, '/');
                    std::getline(oneCornerSS, t, '/');
                    std::getline(oneCornerSS, n, '/');

                    int vertexIndex = (std::stoi(v) - 1) * 3;
                    int textureCoordIndex = (std::stoi(t) - 1) * 2;
                    int normalIndex = (std::stoi(n) - 1) * 3;

                    m_triangleVertices.push_back(m_vertices[vertexIndex]);
                    m_triangleVertices.push_back(m_vertices[vertexIndex + 1]);
                    m_triangleVertices.push_back(m_vertices[vertexIndex + 2]);

                    m_textureCoords.push_back(m_stVals[textureCoordIndex]);
                    m_textureCoords.push_back(m_stVals[textureCoordIndex + 1]);

                    m_normals.push_back(m_normalsVals[normalIndex]);
                    m_normals.push_back(m_normalsVals[normalIndex + 1]);
                    m_normals.push_back(m_normalsVals[normalIndex + 2]);
                }
            }
        }
    }

    int ModelImporter::getNumVertices() {
        return m_vertices.size() / 3;
    }

    std::vector<float> ModelImporter::getVertices() {
        return m_triangleVertices;
    }

    std::vector<float> ModelImporter::getTextureCoords() {
        return m_textureCoords;
    }

    std::vector<float> ModelImporter::getNormals() {
        return m_normalsVals;
    }
}
