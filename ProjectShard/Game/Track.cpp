#include "Track.h"

Track::Track()
	: trackAmount(100), barrierAmount(200), buildingAmount(100), blockAmount(20)
{
	raceTrack = g_resourceMgr.GetModel(SID("RaceTrack"));
	trackBarrier = g_resourceMgr.GetModel(SID("Barrier"));
	// TODO(Darren): I have to fix this, have to load a second model for the VAO to be different.
	//				 Instancing won't work if it's the same model assigned to different pointers.
	reflecTrackBarrier = g_resourceMgr.GetModel(SID("BarrierReflection"));
	building = g_resourceMgr.GetModel(SID("Building"));
	reflecBuilding = g_resourceMgr.GetModel(SID("BuildingReflection"));
	instancingShader = g_resourceMgr.GetShader(SID("Instancing"));

	trackModelMatrices = new Matrix4[trackAmount];
	barrierModelMatrices = new Matrix4[barrierAmount];
	barrierRefleMatrices = new Matrix4[barrierAmount];
	buildingModelMatrices = new Matrix4[buildingAmount];
	buildingRefleMatrices = new Matrix4[buildingAmount];

	trackBlock = new TrackBlock[blockAmount];
}

Track::~Track()
{
	delete raceTrack;
	delete trackBarrier;
	delete reflecTrackBarrier;
	delete building;
	delete[] trackModelMatrices;
	delete[] barrierModelMatrices;
	delete[] buildingModelMatrices;
	delete[] barrierRefleMatrices;
	delete[] trackBlock;
}

void Track::Init()
{
	srand(time(NULL));

	// Set up the track blocks
	for (int i = 0; i < blockAmount; i++)
	{
		bool oscillationBlock = ((rand() % 100) < 20) && (i + 5 < blockAmount);
		bool rotatingBlock = ((rand() % 100) < 40);
		//bool stationaryBlock = ((rand() % 100) < 70);

		// NOTE(Darren): Need to check the less chance ones first.
		if (oscillationBlock)
		{
			int firstIndex = i;
			int blockIndent = 0;

			for (; i < firstIndex + 5; i++)
			{
				trackBlock[i].blockType = TrackBlock::BlockType::oscillation;
				trackBlock[i].position = Vector3(40.0f - (blockIndent * 14.0f), 35.0f - (8.0f * blockIndent), -firstIndex * 80);
				blockIndent++;
			}

			i--;		// NOTE(Darren): When going back to the top of the loop
						// decrement by 1 so a block index is not skipped

			continue;	// Go back to the top of the loop
		}
		else if (rotatingBlock)
		{
			float blockIndent = (rand() % 100);
			if (blockIndent > 50)
			{
				blockIndent /= 2;
				trackBlock[i].moveToTarget = false;
			}
			else if (blockIndent <= 50)
			{
				blockIndent = -blockIndent;
				trackBlock[i].moveToTarget = true;
			}

			trackBlock[i].blockType = TrackBlock::BlockType::rotating;
			trackBlock[i].position = Vector3(blockIndent, 7.0f, (i * -80));
			trackBlock[i].rotate.rotate(MathHelper::DegressToRadians(45.0f), Vector3(1.0f, 1.0f, 1.0f));

			continue;
		}
		else// if (stationaryBlock)
		{
			float blockIndent = (rand() % 100);
			if (blockIndent > 50)
				blockIndent /= 2;
			else if (blockIndent <= 50)
				blockIndent = -blockIndent;

			trackBlock[i].blockType = TrackBlock::BlockType::stationary;
			trackBlock[i].position = Vector3(blockIndent, 4.0f, (i * -80));

			continue;
		}
	}

	// Set the model matrices for the track
	Matrix4 scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(3.0f, 0.0f, 3.0f));
	for (GLuint i = 0; i < trackAmount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		 
		transMatrix = transMatrix.translate(Vector3(0.0f, -4.0f, (-120.0f * i)));
		trackModelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < raceTrack->meshes.size(); i++)
		SetUpBuffers(raceTrack->meshes[i].VAO, trackModelMatrices, trackAmount);

	// Set the model matrices for the barrier
	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(3.0f, 5.0f, 3.0f));
	for (GLuint i = 0; i < barrierAmount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();
		
		int rotateDeg = i % 2 == 0 ? 90.0f : -90.0f;
		rotate = rotate.rotateY(MathHelper::DegressToRadians(rotateDeg));

		int barrierZPos = i;
		if (barrierZPos % 2 == 0)
			barrierZPos = -60.0f * i;
		else if (barrierZPos % 2 == 1)
			barrierZPos = -60.0f * (i - 1);

		int barrierXPos = i % 2 == 0 ? 60.0f : -60.0f;
		transMatrix = transMatrix.translate(Vector3(barrierXPos, -9.0f, barrierZPos));
		barrierModelMatrices[i] = scaleMatrix * rotate * transMatrix;
	}

	for (GLuint i = 0; i < trackBarrier->meshes.size(); i++)
		SetUpBuffers(trackBarrier[0].meshes[i].VAO, barrierModelMatrices, barrierAmount);

	// Set the model matrices for the buildings
	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(19.9f, 19.9f, 19.9f));
	for (GLuint i = 0; i < buildingAmount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 90.0f : -90.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -100.0f, -80.0f * i));
		buildingModelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < building->meshes.size(); i++)
		SetUpBuffers(building->meshes[i].VAO, buildingModelMatrices, buildingAmount);

	/*
		Track Scene objects
	*/
	// - Render barriers
	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(3.0f, 5.0f, 3.0f));
	for (GLuint i = 0; i < barrierAmount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int rotateDeg = i % 2 == 0 ? 90.0f : -90.0f;
		rotate = rotate.rotateY(MathHelper::DegressToRadians(rotateDeg));

		int barrierZPos = i;
		if (barrierZPos % 2 == 0)
			barrierZPos = -60.0f * i;
		else if (barrierZPos % 2 == 1)
			barrierZPos = -60.0f * (i - 1);

		int barrierXPos = i % 2 == 0 ? 60.0f : -60.0f;
		transMatrix = transMatrix.translate(Vector3(barrierXPos, 1.0f, barrierZPos));
		barrierRefleMatrices[i] = scaleMatrix * rotate * transMatrix;
	}

	for (GLuint i = 0; i < reflecTrackBarrier->meshes.size(); i++)
		SetUpBuffers(reflecTrackBarrier[0].meshes[i].VAO, barrierRefleMatrices, barrierAmount);

	// - Render buildings
	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(20.0f, 20.0f, 20.0f));
	for (GLuint i = 0; i < buildingAmount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 90.0f : -90.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -25.0f, -80.0f * i));
		buildingRefleMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < reflecBuilding->meshes.size(); i++)
		SetUpBuffers(reflecBuilding->meshes[i].VAO, buildingRefleMatrices, buildingAmount);
}

void Track::Update(float deltaTime)
{
	for (unsigned int i = 0; i < blockAmount; i++)
	{
		trackBlock[i].Update(deltaTime);
	}
}

bool Track::TrackBlockCollision(CollisionBox &playerBoundingBox)
{
	for (unsigned int i = 0; i < blockAmount; i++)
	{
		if (trackBlock[i].boundingBox.Intersects(playerBoundingBox))
		{
			return true;
		}
	}

	return false;
}

void Track::SetUpBuffers(GLuint &vao, Matrix4 *matrices, GLuint amount)
{
	GLuint buffer;
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(Matrix4), &matrices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Vertex Attributes
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (GLvoid*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (GLvoid*)(sizeof(Vector4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (GLvoid*)(2 * sizeof(Vector4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (GLvoid*)(3 * sizeof(Vector4)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	// Clean up
	glBindVertexArray(0);
	glDeleteBuffers(1, &buffer);
}

void Track::RenderSceneObjects(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view;
	view = camera.GetViewMatrix();

	instancingShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(instancingShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(instancingShader->Program, "view"), 1, GL_FALSE, &view.data[0]);

	// Render the barriers for the tracks
	RenderInstance(reflecTrackBarrier, barrierAmount);
	// Render the building along the track
	RenderInstance(reflecBuilding, buildingAmount);

	for (unsigned int i = 0; i < blockAmount; i++)
		trackBlock[i].Render(camera, screenWidth, screenHeight);
}

void Track::RenderTrack(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view;
	view = camera.GetViewMatrix();

	instancingShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(instancingShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(instancingShader->Program, "view"), 1, GL_FALSE, &view.data[0]);

	// Render the layer of tracks
	RenderInstance(raceTrack, trackAmount);
}

void Track::RenderTrackReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view;
	view = camera.GetViewMatrix();

	instancingShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(instancingShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(instancingShader->Program, "view"), 1, GL_FALSE, &view.data[0]);

	// Render the barriers for the tracks
	RenderInstance(trackBarrier, barrierAmount);
	// Render the building along the track
	RenderInstance(building, buildingAmount);

	for (unsigned int i = 0; i < blockAmount; i++)
		trackBlock[i].RenderReflection(camera, screenWidth, screenHeight);
}

void Track::RenderInstance(Model *model, GLuint amount)
{
	glBindTexture(GL_TEXTURE_2D, model->texturesLoaded[0].id);
	for (GLuint i = 0; i < model->meshes.size(); i++)
	{
		glBindVertexArray(model->meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, model->meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}