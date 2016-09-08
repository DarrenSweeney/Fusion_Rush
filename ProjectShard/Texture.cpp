#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

Texture::Texture(const char* path)
{
	int width, height, numComponents;
	unsigned char* image = stbi_load(path, &width, &height, &numComponents, 4);

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

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	float aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	// TODO(Darren): Test mipmap

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}