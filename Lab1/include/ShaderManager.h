#pragma once

#include <GL\glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

#include <Camera.h>

//struct S_VertAndFrag
//{
//	//GLuint vertShader;
//	//GLuint fragShader;
//	GLuint _shaders[2];
//};
//
//namespace std
//{
//	template<>
//	struct hash<S_VertAndFrag>
//	{
//		size_t operator()(const S_VertAndFrag& key)
//		{
//			for (const GLuint& shader : key._shaders)
//			{
//				return hash<GLuint>()(shader);
//			}
//		}
//	};
//}

class ShaderManager
{
	static const unsigned int NUM_SHADERS = 2; // could be better as enum to make scalable 

	/*enum
	{
		U_TRANSFORM, 
		U_LIGHTING,
		NUM_UNIFORMS
	};*/

	GLuint m_program;
	GLuint shaders[NUM_SHADERS]; // array of shaders
	//GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables

	glm::mat4 mvp;
	std::unordered_map<std::string, GLint> u_locations;

	//std::unordered_map<std::string, S_VertAndFrag> m_shaders; // change s_VertandFrag to just gluint array? 
	//std::unordered_map<std::string, GLuint> m_programs;

	glm::vec4 lightPos = { 0.0f, 0.0f, 0.0f, 1.0f };

public: 
	ShaderManager() : m_program(0), shaders{NUM_SHADERS} {};

	//Shader(const std::string& filename) /*: program(0), shaders{NUM_SHADERS}*/;
	~ShaderManager();

	void InitShaders(const std::string& filename);
	GLuint CreateShader(const std::string& text, GLuint shaderType);
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(const GLuint shader, const GLuint flag, const bool isProgram, const std::string& errorMessage);

	const GLint GetUniformLocation(const std::string& name);

	void Bind();

	void SetLightPos(const Camera& camera);
	void UpdateLight(const glm::mat4& objTransform, const Camera& camera);
	void Update(const glm::mat4& objTransform, const Camera& camera);

};