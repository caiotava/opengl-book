#include "Sphere.h"
#include <cmath>

constexpr static int32_t defaultPrecision = 48;

namespace core {
    Sphere::Sphere() {
        init(defaultPrecision);
    }

    Sphere::Sphere(const int32_t precision) {
        init(precision);
    }

    float Sphere::toRadians(const float degrees) {
        return degrees * static_cast<float>(M_PI) / 180.0f;
    }

    void Sphere::init(const int32_t precision) {
        m_numberVertices = (precision + 1) * (precision + 1);
        m_numberIndices = precision * precision * 6;

        m_vertices.resize(m_numberVertices);
        m_texCoords.resize(m_numberVertices);
        m_normals.resize(m_numberVertices);
        m_indices.resize(m_numberIndices);

        for (int32_t i = 0; i <= precision; i++) {
            for (int32_t j = 0; j <= precision; j++) {
                float y = std::cos(toRadians(180.0f - i * 180.0f / static_cast<float>(precision)));
                float x = (
                    -std::cos(toRadians(j * 360.0f / static_cast<float>(precision))) *
                    std::abs(std::cos(std::asin(y)))
                );
                float z = (
                    std::sin(toRadians(j * 360.0f / static_cast<float>(precision))) *
                    std::abs(std::cos(std::asin(y)))
                );

                m_vertices[i * (precision + 1) + j] = glm::vec3(x, y, z);
                m_texCoords[i * (precision + 1) + j] = glm::vec2(static_cast<float>(j) / precision, static_cast<float>(i) / precision);
                m_normals[i * (precision + 1) + j] = glm::vec3(x, y, z);
            }
        }

        for (int32_t i = 0; i < precision; i++) {
            for (int32_t j = 0; j < precision; j++) {
                m_indices[6 * (i * precision + j) + 0] = i * (precision + 1) + j;
                m_indices[6 * (i * precision + j) + 1] = i * (precision + 1) + j + 1;
                m_indices[6 * (i * precision + j) + 2] = (i + 1) * (precision + 1) + j;
                m_indices[6 * (i * precision + j) + 3] = i * (precision + 1) + j + 1;
                m_indices[6 * (i * precision + j) + 4] = (i + 1) * (precision + 1) + j + 1;
                m_indices[6 * (i * precision + j) + 5] = (i + 1) * (precision + 1) + j;
            }
        }
    }
}
