#ifndef OPENGL_BOOK_TORUS_H
#define OPENGL_BOOK_TORUS_H

#include <vector>
#include <glm/glm.hpp>

namespace core {
class Torus {
public:
	Torus();
	Torus(float innerRadius, float outerRadius, int32_t precisionInner);

	void init();

	int32_t getNumberVertices();
	int32_t getNumberIndices();
	std::vector<int32_t> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getTexCoords();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getTangents();
	std::vector<glm::vec3> getTangentsBI();
private:
	int32_t m_precision;
	float m_innerRadius;
	float m_outerRadius;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_textureCoords;
	std::vector<glm::vec3> m_normals;
	std::vector<int32_t> m_indices;
	std::vector<glm::vec3> m_tangents;
	std::vector<glm::vec3> m_tangentsBI;
};
}


#endif //OPENGL_BOOK_TORUS_H
