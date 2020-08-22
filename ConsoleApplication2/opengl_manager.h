#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>

#include "camera.h"
#include "light.h"
#include "shader.h"
#include "material.h"

class OpenglManager
{
public:
	// Window Info
	GLFWwindow* window = nullptr;
	int height = 600, width = 800;
	char* title = (char*)default_title;

	float time = 0;

	// Cameras
	std::vector<Camera> cameraList;


	int init(const char* title, int width, int height);
	void exit(void);
	void log(std::string s);

	static void onWindowSizeChanged(GLFWwindow* window, int width, int height);
	static void onKeyboardCallback(GLFWwindow* window);
	static void onMouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void onScrollCallback(GLFWwindow* window, double xpos, double ypos);
	static OpenglManager* getCurrentManager(void);

private:
	const char* default_title = "No Title";
	static OpenglManager* currentManager;
	OpenglManager() {

	}
};

