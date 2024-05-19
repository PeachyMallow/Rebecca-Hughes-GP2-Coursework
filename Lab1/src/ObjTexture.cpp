#include "ObjTexture.h"

//Texture::Texture(const std::string& fileName)
//{
//	int width, height, numComponents; // values set in stbi_load()
//
//	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4); //loads image from file, and memory addresses where the program data can be saved
//
//	if (imageData == NULL)
//	{
//		std::cerr << "Texture load failed for: " << fileName << std::endl;
//	}
//
//	glGenTextures(1, &textureHandler); //texture amount & addresses
//	glBindTexture(GL_TEXTURE_2D, textureHandler); //(define type, texture we're working with)
//
//	//setting wrapping behaviour for textures that fall outwidth 
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //width
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //height
//
//	//linear (interpolation) filtering for
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minification (texture takes up fewer pixels than set resolution)
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnification (texture takes up more pixels than set resolution)
//
//	//(tell GPU how to interpret texture data, 
//	// mipmapping level (use higher res when image closer to camera & lower res when image further), 
//	// pixel format (how OpenGL stores individual pixels on GPU), 
//	// width, height, border size, 
//	// input format (format of the data being sent to GPU), 
//	// texture data type, our image data)
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
//
//	stbi_image_free(imageData); //delete data from CPU
//}

ObjTexture::~ObjTexture()
{
	glDeleteTextures(1, &m_textureHandler);
}

void ObjTexture::LoadTexture(const std::string& fileName)
{
	int width, height, numComponents;

	unsigned char* imageData = stbi_load(("..\\res\\textures\\" + fileName + ".png").c_str(), &width, &height, &numComponents, 4); //loads image from file, and memory addresses where the program data can be saved

	if (imageData == NULL)
	{
		std::cerr << "Texture load failed for: " << fileName << stbi_failure_reason() << std::endl;
	}

	glGenTextures(1, &m_textureHandler); //texture amount & addresses
	glBindTexture(GL_TEXTURE_2D, m_textureHandler); //(define type, texture we're working with)

	//setting wrapping behaviour for textures that fall outwidth 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //height

	//linear (interpolation) filtering for
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // mipmap to prevent texture shimmering artifacts when textured model is far from the camera
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnification (texture takes up more pixels than set resolution)

	//(tell GPU how to interpret texture data, 
	// mipmapping level (use higher res when image closer to camera & lower res when image further), 
	// pixel format (how OpenGL stores individual pixels on GPU), 
	// width, height, border size, 
	// input format (format of the data being sent to GPU), 
	// texture data type, our image data)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData); //delete data from CPU
}

void ObjTexture::BindTexture(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); //check unit value is within range

	glActiveTexture(GL_TEXTURE0 + unit); //which texture OpenGL is working with
	glBindTexture(GL_TEXTURE_2D, m_textureHandler); //(texture type, texture to bind to unit)
}