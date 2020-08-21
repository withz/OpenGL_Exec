#include "shader.h"

Shader::Shader(const char* verPath, const char* fragPath)
{
	std::string verCode, fragCode;
	std::ifstream vFile, fFile;
	std::stringstream vStream, fStream;

	vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vFile.open(verPath);
		vStream << vFile.rdbuf();
		vFile.close();

		fFile.open(fragPath);
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
		std::cout << "Error: Vertex Shader Compile Error!" << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, log_len, NULL, log);
		std::cout << "Error: Fragment Shader Compile Error!" << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, log_len, NULL, log);
		std::cout << "Error: Shader Link Error!" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setFloat(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setFloat(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
