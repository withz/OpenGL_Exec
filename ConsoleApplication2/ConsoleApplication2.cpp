// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#include "shader.h"


const char* window_title = "First Window";
const char* image_path_container = "container.jpg";
const char* image_path_wall = "wall.jpg";
const float border_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };

const float trangle_vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
};

const float small_box_vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

const float trangle_vertices_color[] = {
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};

float trangle_vertices_color_texture[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

const float texCoords[] = {
    0.0f, 0.0f, // 左下角
    1.0f, 0.0f, // 右下角
    0.5f, 1.0f // 上中
};

const float square_vertices[] = {
    // 第一个三角形
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, 0.5f, 0.0f,  // 左上角
    // 第二个三角形
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

const int square_indices[] = {
    0, 1, 2,
    0, 2, 3
};

const char* vertex_shader_code = 
"#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragment_shader_code = 
"#version 450 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


GLFWwindow* window = NULL;
unsigned int shader_program = 0;
int window_width = 800;
int window_height = 600;
float fov = 45.0f;

glm::vec3 camera_pos(0.0f, 0.0f, 3.0f);
glm::vec3 camera_front(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up(0.0f, 1.0f, 0.0f);


int argInit(void);
int compile_shader(void);
void window_resize_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
void log_out(std::string s);

int main()
{
    // Initialize
    std::cout << "OpenGL Initializing..." << std::endl;
    if (argInit() != 0) {
        std::cout << "OpenGL Initialize Error!" << std::endl;
        return -1;
    }

    // Get OpenGL Info
    int nrAttr;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttr);
    std::cout << "Max nr or vertex attr support:" << nrAttr << std::endl;

    // Compile Shader
    Shader shader("vertex-shader.glsl", "fragment-shader.glsl");
    //if (compile_shader() != 0) {
    //    std::cout << "Shader Compile Error!" << std::endl;
    //    return -1;
    //}

    std::cout << "Prepare Data..." << std::endl;
    // Prepare
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(small_box_vertices), small_box_vertices, GL_STATIC_DRAW);
    
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);
    
    // Point Attr
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Fill or Line
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Image
    int container_width, container_height, container_nrChannels;
    int wall_width, wall_height, wall_nrChannels;
    unsigned char* image_container = stbi_load(image_path_container, &container_width, &container_height, &container_nrChannels, 0);
    if (image_container == NULL) {
        std::cout << "Image Load Fail" << std::endl;
    }
    unsigned char* image_wall = stbi_load(image_path_wall, &wall_width, &wall_height, &wall_nrChannels, 0);
    if (image_wall == NULL) {
        std::cout << "Image Load Fail" << std::endl;
    }

    // Texture
    unsigned int texture_wall;
    glGenTextures(1, &texture_wall);
    glBindTexture(GL_TEXTURE_2D, texture_wall);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wall_width, wall_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_wall);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image_wall);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

    unsigned int texture_container;
    glGenTextures(1, &texture_container);
    glBindTexture(GL_TEXTURE_2D, texture_container);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, container_width, container_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_container);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image_container);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

    shader.use();
    shader.setInt("ourTexture_w", 0);
    shader.setInt("ourTexture_c", 1);
    
    // Transform
    glm::vec4 move(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans(1.0f);
    //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    //move = trans * move;
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    // Space
    glm::mat4 model(1.0f), view(1.0f), projection(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    
    
    
    // Main Loop
    log_out("Main Loop Start");
    float time = 0, last_time = 0;
    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Shader
        shader.use();
        //glUseProgram(shader_program);

        // Time Step
        last_time = time;
        time = glfwGetTime();
        //std::cout << 1 / (time - last_time) << std::endl;
        float red = (sin(time) / 1.1f) + 0.5f;
        float blue = (sin(time) / 1.7f) + 0.5f;
        float green = (sin(time) / 2.3f) + 0.5f;
        float alpha = (sin(time) / 2.7f) + 0.5f;
        
        shader.setFloat("xColor", red, green, blue, alpha);
        view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
        projection = glm::perspective(glm::radians(fov), (float)window_width / window_height, 0.1f, 100.0f);

        

        glm::mat4 trx = glm::rotate(trans, glm::radians(10.0f * time), glm::vec3(0.0f, 0.0f, 1.0f));
        unsigned int transform_uniform = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transform_uniform, 1, GL_FALSE, glm::value_ptr(trx));

        unsigned int model_uniform = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

        unsigned int view_uniform = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projection_uniform = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));
        
        
        //int vertexColor = glGetUniformLocation(shader_program, "xColor");
        //glUniform4f(vertexColor, 0.0f, green, 0.0f, 1.0f);

        // Draw
        //int point_count = sizeof(trangle_vertices_color_texture) / (8 * sizeof(float));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_container);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        for (int i = 0;i < 10;i++) {
            glm::mat4 md(1.0f);
            md = glm::translate(md, cubePositions[i]);
            float angle = 20.0f * i;
            md = glm::rotate(md, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            unsigned int md_uniform = glGetUniformLocation(shader.ID, "md");
            glUniformMatrix4fv(md_uniform, 1, GL_FALSE, glm::value_ptr(md));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Check & Swap Buffer
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Finish
    std::cout << "Closing Program..." << std::endl;
    glfwTerminate();
    return 0;
}

int argInit()
{
    // Set Version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Set Window
    window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
    if (window == NULL) {
        std::cout << "Fail to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Fail to initialize GLAD!" << std::endl;
        return -1;
    }

    // Set Viewport & Callback
    glfwSetFramebufferSizeCallback(window, window_resize_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Set Control

    return 0;
}

int compile_shader()
{
    const int log_len = 1024;
    int success;
    char info_log[log_len];

    // Vertex Shader
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, log_len, NULL, info_log);
        std::cout << "Error: Vertex Shader Compile Error" << std::endl;
        std::cout << info_log << std::endl;
        return -1;
    }

    // Fragment Shader
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, log_len, NULL, info_log);
        std::cout << "Error: Fragment Shader Compile Error" << std::endl;
        std::cout << info_log << std::endl;
        return -1;
    }

    // Shader Program
    unsigned int program;
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, log_len, NULL, info_log);
        std::cout << "Error: Link Error" << std::endl;
        std::cout << info_log << std::endl;
        return -1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    shader_program = program;

    return 0;
}

void window_resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

void processInput(GLFWwindow* window)
{
    float time = 0;
    float last_time = 0;
    float delta_time = 0;
    last_time = time;
    time = glfwGetTime();
    delta_time = time - last_time;

    float camera_speed = 0.0005f * delta_time;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera_pos += camera_speed * camera_front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera_pos -= camera_speed * camera_front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
    }
}

float last_x = 0, last_y = 0;
float x_offset = 0, y_offset = 0;
float sensitivity = 0.05f;
float yaw = 0, pitch = 0;

void mouse_callback(GLFWwindow* window, double x, double y)
{
    x_offset = x - last_x;
    y_offset = y - last_y;
    last_x = x;
    last_y = y;
    
    x_offset *= sensitivity;
    y_offset *= sensitivity;

    yaw += x_offset;
    pitch -= y_offset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 front(1.0f);
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    camera_front = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double x, double y)
{
    if (fov < 1.0f) {
        fov = 1.0f;
    }
    else if (fov > 45.0f) {
        fov = 45.0f;
    }
    else {
        fov -= y;
    }
}

void log_out(std::string s)
{
    std::cout << s << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
