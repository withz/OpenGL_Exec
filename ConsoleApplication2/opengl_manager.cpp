#include "opengl_manager.h"

OpenglManager* OpenglManager::currentManager = nullptr;

double x_last = 0, y_last = 0;

int OpenglManager::init(const char* title, int width, int height)
{
    if (width < 200) width = 200;
    if (width > 2000) width = 2000;
    if (height < 200) height = 200;
    if (height > 2000) height = 2000;
    if (title == nullptr) title = default_title;
    this->title = (char*)title;
    this->width = width;
    this->height = height;

    // Set Version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Set Window
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        log("Fail to create GLFW window!");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log("Fail to initialize GLAD!");
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, onWindowSizeChanged);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, onMouseCallback);
    glfwSetScrollCallback(window, onScrollCallback);

    // Get OpenGL Info
    int nrAttr;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttr);
    log("Max nr or vertex attr support:");

    // Default Setting
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    // Fill or Line
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Camera
    cameraList.push_back(Camera());

    return 0;
}

void OpenglManager::exit(void)
{
    log("Closing Program...");
    glfwTerminate();
}

void OpenglManager::log(std::string s)
{
    std::cout << s << std::endl;
}

void OpenglManager::onWindowSizeChanged(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    OpenglManager* manager = getCurrentManager();
    manager->width = width;
    manager->height = height;
}

void OpenglManager::onKeyboardCallback(GLFWwindow* window)
{
    OpenglManager* manager = getCurrentManager();
    Camera& camera = manager->cameraList.at(0);
    float delta_time = glfwGetTime() - manager->time;
    manager->time = glfwGetTime();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, delta_time);
    }
}

void OpenglManager::onMouseCallback(GLFWwindow* window, double x, double y)
{
    OpenglManager* manager = getCurrentManager();
    Camera& camera = manager->cameraList.at(0);
    camera.ProcessMouseMovement(x - x_last, y - y_last);
    x_last = x;
    y_last = y;
}

void OpenglManager::onScrollCallback(GLFWwindow* window, double x, double y)
{
    OpenglManager* manager = getCurrentManager();
    Camera& camera = manager->cameraList.at(0);
    camera.ProcessMouseScroll(y);
}

OpenglManager* OpenglManager::getCurrentManager(void)
{
    if (currentManager == nullptr) {
        currentManager = new OpenglManager();
    }
    return currentManager;
}
