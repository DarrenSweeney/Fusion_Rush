#ifndef DEBUG_DRAW_MANAGER_H
#define DEBUG_DRAW_MANAGER_H

#include "..\Math\Vector3.h"
#include "..\Math\Matrix4x4.h"
#include "Shader.h"
#include "..\Game\Camera.h"
#include "..\Core\ResourceManager.h"

class DebugDrawManager
{
private:
	static const unsigned int MAX_LINES = 256;
	const float LINE_WIDTH = 1.5f;

	struct Line
	{
		Vector3 startPos;
		Vector3 color0;
		Vector3 endPos;
		Vector3 color1;
	};	
	Line lines[MAX_LINES];
	int lineCount = 0;
	Shader *lineShader;

public:
	void AddLine(const Vector3 &startPos,
				const Vector3 &endPos,
				Vector3 &color,
				float lineWidth = 1.0f,
				bool depthEnabled = true);

	// Represents a point in 3D space.
	void AddCross(const Vector3 &pos,
				Vector3 &color,
				float lineWidth = 1.0f,
				bool depthEnabled = true);

	// Submit the debug draw primtives for rendering.
	void Submit(Camera &camera);
};

extern DebugDrawManager g_debugDrawMgr;

#endif