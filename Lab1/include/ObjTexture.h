#pragma once

#include <GL\glew.h>

#include <cassert>
#include <iostream>
#include <string>

#include "stb_image.h"

class ObjTexture
{
	GLuint m_textureHandler;

public: 
	ObjTexture() : m_textureHandler { 0 } {};
	//Texture(const std::string& fileName);
	~ObjTexture();

	void LoadTexture(const std::string& fileName);
	void BindTexture(unsigned int unit);

	//GLint GetTextureLocation(const int texName);
};