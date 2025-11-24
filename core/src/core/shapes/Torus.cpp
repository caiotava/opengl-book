#include "Torus.h"

#include <cmath>
#include <iostream>
#include <glm/ext/matrix_transform.hpp>


namespace core {
    Torus::Torus() : m_precision(48), m_innerRadius(0.5f), m_outerRadius(0.2f) {
        init();
    }

    Torus::Torus(float i, float o, int32_t p) : m_precision(p), m_innerRadius(i), m_outerRadius(o) {
        init();
    }

    void Torus::init() {
        auto numberVertices = (m_precision + 1) * (m_precision + 1);
        auto numberIndices = m_precision * m_precision * 6;

        m_vertices.resize(numberVertices);
        m_textureCoords.resize(numberVertices);
        m_normals.resize(numberVertices);
        m_tangents.resize(numberVertices);
        m_tangentsBI.resize(numberVertices);
        m_indices.resize(numberIndices);

        const float ringStep = 360.0f / m_precision;

        // Build only the first ring, this ring will be used to clone other rings.
        for (int32_t i = 0; i < m_precision + 1; i++) {
            float amt = glm::radians(i * ringStep);

            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::vec3 initPosition{rotationMatrix * glm::vec4(0.0f, m_outerRadius, 0.0f, 1.0f)};
            m_vertices[i] = glm::vec3(initPosition + glm::vec3(m_innerRadius, 0.0f, 0.0f));

            m_textureCoords[i] = glm::vec2(0.0f, static_cast<float>(i) / m_precision);

            rotationMatrix = glm::rotate(
                glm::mat4(1.0f),
                amt + static_cast<float>(M_PI_2),
                glm::vec3(0.0f, 0.0f, 1.0f)
            );
            m_tangents[i] = glm::vec3(rotationMatrix * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
            m_tangentsBI[i] = glm::vec3(glm::vec3(0.0f, 0.0f, -1.0f));
            m_normals[i] = glm::cross(m_tangents[i], m_tangentsBI[i]);
        }

        for (int32_t ring = 1; ring < m_precision + 1; ring++) {
            for (int32_t i = 0; i < m_precision + 1; i++) {
                const float amt = glm::radians(ring * ringStep);
                const int32_t index = ring * (m_precision + 1) + i;

                glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
                m_vertices[index] = glm::vec3(rotationMatrix * glm::vec4(m_vertices[i], 1.0f));

                m_textureCoords[index] = glm::vec2(
                    ring * 2.0f / m_precision, m_textureCoords[i].t);

                m_tangents[index] = glm::vec3(rotationMatrix * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
                m_tangentsBI[index] = glm::vec3(rotationMatrix * glm::vec4(m_tangentsBI[i], 1.0f));
                m_normals[index] = glm::vec3(rotationMatrix * glm::vec4(m_normals[i], 1.0f));
            }
        }

        for (int32_t ring = 0; ring < m_precision; ring++) {
            for (int32_t i = 0; i < m_precision; i++) {
                const int32_t index = (ring * m_precision + i) * 6;

                m_indices[index + 0] = ring * (m_precision + 1) + i;
                m_indices[index + 1] = (ring + 1) * (m_precision + 1) + i;
                m_indices[index + 2] = ring * (m_precision + 1) + i + 1;
                m_indices[index + 3] = ring * (m_precision + 1) + i + 1;
                m_indices[index + 4] = (ring + 1) * (m_precision + 1) + i;
                m_indices[index + 5] = (ring + 1) * (m_precision + 1) + i + 1;
            }
        }
    }

    int32_t Torus::getNumberVertices() {
        return m_vertices.size();
    }

    int32_t Torus::getNumberIndices() {
        return m_indices.size();
    }

    std::vector<glm::vec3> Torus::getVertices() {
        return m_vertices;
    }

    std::vector<int32_t> Torus::getIndices() {
        return m_indices;
    }

    std::vector<glm::vec2> Torus::getTexCoords() {
        return m_textureCoords;
    }

    std::vector<glm::vec3> Torus::getNormals() {
        return m_normals;
    }

    std::vector<glm::vec3> Torus::getTangents() {
        return m_tangents;
    }

    std::vector<glm::vec3> Torus::getTangentsBI() {
        return m_tangentsBI;
    }
}
