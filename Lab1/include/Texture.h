#pragma once

#include <string>
#include <GL\glew.h>

class Texture
{
	GLuint textureHandler;

public: 
	Texture() : textureHandler { 0 } {};
	//Texture(const std::string& fileName);
	~Texture();

	void LoadTexture(const std::string& fileName);

	void Bind(unsigned int unit); //bind upto 32 textures


};

