// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>




#include "opengl_manager.h"
#include "shader.h"
#include "camera.h"
#include "light.h"
#include "entity.h"
#include "material.h"
#include "data.h"


const char* window_title = "First Window";
const char* image_path_container = "container.jpg";
const char* image_path_wall = "wall.jpg";
const float border_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };


void log_out(std::string s);

int main()
{
    log_out("Initialize...");
    OpenglManager* manager = OpenglManager::getCurrentManager();
    manager->init("Chapter 2", 800, 600);
    GLFWwindow* window = manager->window;
    Camera& camera = manager->cameraList.at(0);

    log_out("Compile Shader...");
    Shader shader("entity-vs.glsl", "entity-fs.glsl");
    Shader light_shader("light-vs.glsl", "light-fs.glsl");

    log_out("Prepare Data...");
    Entity entity;
    entity.SetPosition(glm::vec3(0.0f, 0.0f, -13.0f));
    entity.SetRotate(15, glm::vec3(0.0f, 0.0f, 1.0f));
    entity.SetScale(glm::vec3(5.0f, 5.0f, 5.0f));

    Light light;
    light.SetPosition(glm::vec3(0.0f, 0.0f, -4.0f));

    Material material("container2.jpg");
    Material material_sp("container2_specular.jpg");

    material.use(0);
    material_sp.use(1);

    shader.use();
    shader.setInt("diffuseTexture", 0);
    shader.setInt("specularTexture", 1);

    // Main Loop
    log_out("Main Loop Start");
    while (!glfwWindowShouldClose(window)) {
        // Input
        OpenglManager::onKeyboardCallback(window);

        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // View
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)manager->width / manager->height, 0.1f, 100.0f);
        

        // Shader Color
        shader.use();
        shader.setFloat("material.ambient", 1.0f, 0.5f, 0.31f);
        shader.setFloat("material.diffuse", 1.0f, 1.0f, 1.0f);
        shader.setFloat("material.specular", 10.0f, 10.0f, 10.0f);
        shader.setFloat("material.shininess", 32.0f);
        shader.setFloat("LightColor", light.Color);
        shader.setFloat("LightPosition", light.Position);
        shader.setFloat("ViewPosition", camera.Position);

        // Shader Transform
        shader.use();
        shader.setMatrixFloat4("transform", glm::mat4(1.0f));
        shader.setMatrixFloat4("model", entity.State);
        shader.setMatrixFloat4("view", view);
        shader.setMatrixFloat4("projection", projection);

        glBindVertexArray(entity.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        light_shader.use();
        light_shader.setMatrixFloat4("transform", glm::mat4(1.0f));
        light_shader.setMatrixFloat4("model", light.State);
        light_shader.setMatrixFloat4("view", view);
        light_shader.setMatrixFloat4("projection", projection);
        light_shader.setFloat("Color", light.Color);

        glBindVertexArray(light.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //for (int i = 0;i < 10;i++) {
        //    glm::mat4 md(1.0f);
        //    md = glm::translate(md, cubePositions[i]);
        //    float angle = 20.0f * i;
        //    md = glm::rotate(md, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //    shader.setMatrixFloat4("md", md);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}
        //
        //light_shader.use();
        //light_shader.setMatrixFloat4("md", light_model);
        //glBindVertexArray(VAO_LIGHT);
        //glDrawArrays(GL_TRIANGLES, 0, 36);



        // Check & Swap Buffer
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Finish
    manager->exit();
    return 0;
}

void log_out(std::string s)
{
    std::cout << s << std::endl;
}
