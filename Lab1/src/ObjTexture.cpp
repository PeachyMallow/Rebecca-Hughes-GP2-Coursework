#include "ObjTexture.h"

ObjTexture::~ObjTexture()
{
	glDeleteTextures(1, &m_textureHandler);
}

void ObjTexture::LoadTexture(const std::string& fileName)
{
	int width, height, numComponents;

	unsigned char* imageData = stbi_load(("..\\res\\textures\\" + fileName + ".png").c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture load failed for: " << fileName << stbi_failure_reason() << std::endl;
	}

	glGenTextures(1, &m_textureHandler);
	glBindTexture(GL_TEXTURE_2D, m_textureHandler);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // mipmap to prevent texture shimmering artifacts when textured model is far from the camera
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);
}

void ObjTexture::BindTexture(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_textureHandler);
}