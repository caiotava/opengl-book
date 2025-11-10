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

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        enableAnisotropy();

        return textureID;
    }
}
