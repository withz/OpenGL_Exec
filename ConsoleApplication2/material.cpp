#include "material.h"

#include <stb_image.h>



#include <iostream>

Material::Material(std::string texturePath)
{
    float border_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };

    image_diffuse = stbi_load(texturePath.c_str(), &image_width, &image_height, &nrChannels, 0);
    if (image_diffuse == NULL) {
        std::cout << "Image Load Fail" << std::endl;
    }
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_diffuse);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image_diffuse);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

}

Material::Material(std::string diffusePath, std::string specularPath)
{
}
