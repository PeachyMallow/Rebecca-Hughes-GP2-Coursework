#pragma once

#include <GL\glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

#include <Camera.h>

class ShaderManager
{
	static const unsigned int NUM_SHADERS = 2;

	GLuint m_program;
	GLuint shaders[NUM_SHADERS];
	glm::mat4 mvp;
	std::unordered_map<std::string, GLint> u_locations;

public: 
	ShaderManager() : m_program(0), shaders{NUM_SHADERS} {};
	~ShaderManager();

	void InitShaders(const std::string& filename);
	GLuint CreateShader(const std::string& text, GLuint shaderType);
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(const GLuint shader, const GLuint flag, const bool isProgram, const std::string& errorMessage);

	const GLint GetUniformLocation(const std::string& name);

	void Bind();

	void UpdateUniforms(const glm::mat4& objTransform, const Camera& camera);

};