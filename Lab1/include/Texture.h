#pragma once

#include <string>
#include <GL\glew.h>
#include <unordered_map>

// textures enum for hash table
enum
{
	FROG_TEX,
	BEE_TEX,
	PUMPKIN_TEX
};

class Texture
{
	GLuint textureHandler;
	std::unordered_map<std::string, GLint> m_textures;

public: 
	Texture() : textureHandler { 0 } {};
	//Texture(const std::string& fileName);
	~Texture();

	void LoadTexture(const std::string& fileName);

	void Bind(unsigned int unit); //bind upto 32 textures

	GLint GetTextureLocation(const int texName);


};

