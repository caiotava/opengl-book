#include "Texture.h"
#include <soil2/SOIL2.h>

namespace core {
    GLuint loadTexture(const std::filesystem::path& texturePath) {
        GLuint textureID = SOIL_load_OGL_texture(
            texturePath.string().c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
        );

        if (textureID == 0) {
            std::cerr << "failed to load texture: " << texturePath << std::endl;
            return 0;
        }

        return textureID;
    }
}
