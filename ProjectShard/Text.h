#ifndef TEXT_H
#define TEXT_H

#include <GL\gl3w.h>
#include "Math\Vector2.h"
#include "Math\Vector3.h"
#include <map>
#include "Shader.h"

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

	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;

public:
	void Init();
	void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, Vector3 color);
};

#endif