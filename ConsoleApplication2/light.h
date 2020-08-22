#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "data.h"


class Light : Model
{
public:
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 State = glm::mat4(1.0f);
    glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);

    unsigned int VAO;
    unsigned int VBO;

	Light() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, small_box_vertices_normal_size, small_box_vertices_normal, GL_STATIC_DRAW);

        // Point Attr
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
	}

    void SetPosition(glm::vec3 pos)
    {
        State = glm::translate(glm::mat4(1.0f), pos);
    }

    void SetMove(glm::vec3 pos)
    {
        State = glm::translate(State, Position);
    }
};

