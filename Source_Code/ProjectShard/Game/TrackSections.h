#ifndef TRACK_SECTIONS_H
#define TRACK_SECTIONS_H

#include "..\Renderer\InstancingEntity.h"
#include "..\Renderer\Model.h"
#include "Camera.h"

class TrackSections : public InstancingEntity
{
public:
	TrackSections();
	~TrackSections();
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);

private:
	Model *trackModel;
	Matrix4 *modelMatrices;
	Matrix4 scaleMatrix;
};

#endif