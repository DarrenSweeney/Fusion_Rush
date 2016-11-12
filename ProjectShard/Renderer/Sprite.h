#ifndef SPRITE_H
#define SPRITE_H

#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Render(Texture &texture, Shader &shader, Vector2 position, 
		Vector2 size = Vector2(10, 10), GLfloat rotate = 0.0f, 
		Vector3 color = Vector3(1.0f, 1.0f, 1.0f));

private:
	Shader *shader;
	GLuint quadVAO;
	
	void Init();
};

#endif