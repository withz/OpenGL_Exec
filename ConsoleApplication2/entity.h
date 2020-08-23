#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "data.h"

class Entity 
{
public:
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 State = glm::mat4(1.0f);
    glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

	Entity() 
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, box_vertices_norm_tex_size, box_vertices_norm_tex, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, square_vertices_size, square_indices, GL_STATIC_DRAW);

        // Point Attr
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
	}

    void SetPosition(glm::vec3 pos) 
    {
        State = glm::translate(glm::mat4(1.0f), pos);
    }

    void SetMove(glm::vec3 pos)
    {
        State = glm::translate(State, pos);
    }

    void SetRotate(float angle, glm::vec3 shaft) 
    {
        State = glm::rotate(State, glm::radians(angle), glm::normalize(shaft));
    }

    void SetScale(glm::vec3 scale)
    {
        State = glm::scale(State, scale);
    }
};
