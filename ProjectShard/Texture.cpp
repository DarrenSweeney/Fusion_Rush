#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

Texture::Texture()
	: textureID(0) { }

GLuint Texture::LoadTexture(const char* path)
{
	int width, height, numComponents;
	unsigned char* image = stbi_load(path, &width, &height, &numComponents, STBI_rgb);

	if (image == NULL)
	{
		std::cout << "ERROR::TEXTURE::TEXTURE_NOT_FOUND: " << path << std::endl;
		// Texture if not found so fill the image buffer with a pink color to visual
		// show a texture was not created succesfully.
		unsigned char s[] = { 0xFF,0xAE,0xC9,0XFF };
		// TODO(Darren): Fill image with pink texture if one if not loaded.
	}
	else
		std::cout << "TEXTURE_LOADED: " << path << std::endl;

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	float aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	// Assign the memeber textureID to the currently binded texture so
	// it can be used outside LoadTexture for binding and unbinding.
	textureID = texture;

	return texture;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::DeleteTexture()
{
	glDeleteTextures(1, &textureID);
}
