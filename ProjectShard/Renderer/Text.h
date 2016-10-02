#ifndef TEXT_H
#define TEXT_H

#include <GL\gl3w.h>
#include "..\Math\Vector2.h"
#include "..\Math\Vector3.h"
#include "..\Math\Matrix4x4.h"
#include <map>
#include "Shader.h"
#include "..\Core\ResourceManager.h"

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

class Text
{
private:
	// Holds all state information relevant to a character as loaded using FreeType
	struct Character
	{
		GLuint textureID;		// ID handle of the glyph texture
		Vector2 size;			// Size of glphy
		Vector2 bearing;		// Offset from baseline to left/top glyph
		GLuint advance;			// Horizontal offset to advance to next glyph
	};
	// Holds the list of pre-compiled characters
	std::map<GLchar, Character> Characters;

	Shader *textShader;
	GLuint textVAO, textVBO;

public:
	Text(GLsizei screenWidth, GLsizei screenHeight);
	~Text();
	void Load(const char* fontPath);
	void RenderText(std::string text, Vector2 &pos, GLfloat scale, Vector3 &color, GLsizei screenWidth, GLsizei screenHeight);
};

#endif