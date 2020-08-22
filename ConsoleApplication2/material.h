#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>



class Material
{
public:
    

    glm::vec3 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
    unsigned char* image_diffuse;
    unsigned char* image_specular;

    int image_width, image_height, nrChannels;

    unsigned int TextureID;
    

    Material(glm::vec3 color)
    {
        this->color = color;
    }

    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    }

    Material(std::string texturePath);
    Material(std::string diffusePath, std::string specularPath);

    void use(unsigned int area)
    {
        glActiveTexture(GL_TEXTURE0 + area);
        glBindTexture(GL_TEXTURE_2D, TextureID);
    }

private:
	Material() {
        //// Image
        //int container_width, container_height, container_nrChannels;
        //int wall_width, wall_height, wall_nrChannels;
        //const char* image_path_container = "container.jpg";
        //const char* image_path_wall = "wall.jpg";

        //unsigned char* image_container = stbi_load(image_path_container, &container_width, &container_height, &container_nrChannels, 0);
        //if (image_container == NULL) {
        //    std::cout << "Image Load Fail" << std::endl;
        //}
        //unsigned char* image_wall = stbi_load(image_path_wall, &wall_width, &wall_height, &wall_nrChannels, 0);
        //if (image_wall == NULL) {
        //    std::cout << "Image Load Fail" << std::endl;
        //}

        //// Texture
        //unsigned int texture_wall;
        //glGenTextures(1, &texture_wall);
        //glBindTexture(GL_TEXTURE_2D, texture_wall);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wall_width, wall_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_wall);
        //glGenerateMipmap(GL_TEXTURE_2D);
        //stbi_image_free(image_wall);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Linear
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

        //unsigned int texture_container;
        //glGenTextures(1, &texture_container);
        //glBindTexture(GL_TEXTURE_2D, texture_container);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, container_width, container_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_container);
        //glGenerateMipmap(GL_TEXTURE_2D);
        //stbi_image_free(image_container);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Linear
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
	}
};

