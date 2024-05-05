#pragma once

#include <string>
#include <GL\glew.h>

class Texture
{
	GLuint textureHandler;

public: 
	Texture() {};
	//Texture(const std::string& fileName);
	~Texture();

	void LoadTexture(const std::string& fileName);

	void Bind(unsigned int unit); //bind upto 32 textures


};

