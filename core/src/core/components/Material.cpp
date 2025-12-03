#include "Material.h"

namespace core {
    const Material Material::GOLD = Material(
        glm::vec4(0.2473f, 0.1995f, 0.0745f, 1),
        glm::vec4(0.7516f, 0.6065f, 0.2265f, 1),
        glm::vec4(0.6283f, 0.5559f, 0.3661f, 1),
        81.2f
    );

    const Material Material::SILVER = Material(
        glm::vec4(0.1923f, 0.1923f, 0.1923f, 1),
        glm::vec4(0.5075f, 0.5075f, 0.5075f, 1),
        glm::vec4(0.5083f, 0.5083f, 0.5083f, 1),
        51.2
    );

    const Material Material::BRONZE = Material(
        glm::vec4(0.2125f, 0.1275f, 0.0540f, 1),
        glm::vec4(0.7140f, 0.4284f, 0.1814f, 1),
        glm::vec4(0.3936f, 0.2719f, 0.1667f, 1),
        25.6f
    );
}
