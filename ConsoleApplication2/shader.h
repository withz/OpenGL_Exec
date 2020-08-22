#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath)
	{
		std::string verCode, fragCode;
		std::ifstream vFile, fFile;
		std::stringstream vStream, fStream;

		vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vFile.open(vertexPath);
			vStream << vFile.rdbuf();
			vFile.close();

			fFile.open(fragmentPath);
			fStream << fFile.rdbuf();
			fFile.close();

			verCode = vStream.str();
			fragCode = fStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "Error: Shader file read fail" << std::endl;
		}

		const char* vCode = verCode.c_str();
		const char* fCode = fragCode.c_str();
		const int log_len = 1024;

		unsigned int vertex, fragment;
		int success;
		char log[log_len];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, log_len, NULL, log);
			std::cout << "Error: Vertex Shader Compile Error! File Name: " << vertexPath << std::endl;
			std::cout << log << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, log_len, NULL, log);
			std::cout << "Error: Fragment Shader Compile Error! File Name: " << fragmentPath << std::endl;
			std::cout << log << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, log_len, NULL, log);
			std::cout << "Error: Shader Link Error!" << std::endl;
			std::cout << log << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use()
	{
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	void setFloat(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void setFloat(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	void setFloat(const std::string& name, glm::vec2 m) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), m.x, m.y);
	}

	void setFloat(const std::string& name, glm::vec3 m) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), m.x, m.y, m.z);
	}

	void setFloat(const std::string& name, glm::vec4 m) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), m.x, m.y, m.z, m.w);
	}

	void setMatrixFloat4(const std::string& name, glm::mat4 m) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
	}
};

