#pragma once

#include <string>
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>

#include <iostream> // needed?
#include <fstream> // needed?
#include <unordered_map>

#include <Camera.h>
#include "Transform.h"

struct S_VertAndFrag
{
	//GLuint vertShader;
	//GLuint fragShader;
	GLuint _shaders[2];
};

namespace std
{
	template<>
	struct hash<S_VertAndFrag>
	{
		size_t operator()(const S_VertAndFrag& key)
		{
			for (const GLuint& shader : key._shaders)
			{
				return hash<GLuint>()(shader);
			}
		}
	};
}

class Shader
{
	static const unsigned int NUM_SHADERS = 2; // could be better as enum to make scalable 
	/*Shader(const Shader& other) {};
	void operator=(const Shader& other) {};*/

	enum
	{
		U_TRANSFORM, 
		test,
		U_LIGHTING,
		NUM_UNIFORMS
	};

	GLuint program; // track the shader program
	//GLuint shaders[NUM_SHADERS]; // array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables


	std::unordered_map<std::string, GLint> u_locations;

	std::unordered_map<std::string, S_VertAndFrag> m_shaders;


public: 
	Shader() : /*shaders{ NUM_SHADERS },*/ uniforms{ NUM_UNIFORMS }
	{ /*program = glCreateProgram();*/ };

	//Shader(const std::string& filename) /*: program(0), shaders{NUM_SHADERS}*/;
	~Shader();

	//void Init();
	void Initialise(const std::string& filename);
	void Bind(); // set GPU to use our shaders
	void Update(const Transform& transform, const Camera& camera);

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLuint shaderType);
	//void SetUniform()

	GLint GetShader(const std::string& shaderName);

	GLint GetUniformLocation(const std::string& name);
};

