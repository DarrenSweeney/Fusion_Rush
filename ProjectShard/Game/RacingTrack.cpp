#include "RacingTrack.h"

RacingTrack::RacingTrack()
	: blockAmount(40), startRacePosition()
{
	trackBlock = new TrackBlock[blockAmount];

	finishModel = g_resourceMgr.GetModel(SID("Finish_Model"));
	modelShader = g_resourceMgr.GetShader(SID("ModelShader"));
}

RacingTrack::~RacingTrack()
{
	delete[] trackBlock;
}

void RacingTrack::Init(int raceTrackSeed)
{
	// Seed the generator based on today's track seed
	srand(raceTrackSeed);
	
	int zIndent = 0;

	// Set up the track obstacles blocks
	for (int i = 0; i < blockAmount; i++)
	{
		bool oscillationBlock = ((rand() % 100) < 10) && (i + 8 < blockAmount);
		bool rotatingBlock = ((rand() % 100) < 40);

		// NOTE(Darren): Check the less chance ones first.
		if (oscillationBlock)
		{
			int firstIndex = i;
			int blockIndent = 0;

			for (; i < firstIndex + 8; i++)
			{
				trackBlock[i].blockType = TrackBlock::BlockType::oscillation;
				trackBlock[i].position = Vector3(50.0f - (blockIndent * 14.0f), 35.0f - (8.0f * blockIndent), -50.0f - (zIndent * 180));
				blockIndent++;
			}

			i--;		// NOTE(Darren): When going back to the top of the loop
						// decrement by 1 so a block index is not skipped

			zIndent++;

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
			trackBlock[i].position = Vector3(blockIndent, 7.0f, -50.0f + (zIndent * - 180));
			trackBlock[i].rotate.rotate(MathHelper::DegressToRadians(45.0f), Vector3(1.0f, 1.0f, 1.0f));

			zIndent++;

			continue;
		}
		else
		{
			float blockIndent = (rand() % 100);
			if (blockIndent > 50)
				blockIndent /= 2;
			else if (blockIndent <= 50)
				blockIndent = -blockIndent;

			trackBlock[i].blockType = TrackBlock::BlockType::stationary;
			trackBlock[i].position = Vector3(blockIndent, 4.0f, -50.0f + (zIndent * -180));

			zIndent++;

			continue;
		}
	}

	Matrix4 rotate = Matrix4();
	Vector3 scaleVec = Vector3(3.0f, 5.0f, 60.0f);

	finishRacePosition = Vector3(-0.4f, 0.0f, trackBlock[blockAmount - 1].position.z - 50.0f);
	//finishRacePosition = Vector3(-0.4f, 0.0f, -100.0f);	// For testing
}

void RacingTrack::Update(float deltaTime)
{
	for (unsigned int i = 0; i < blockAmount; i++)
	{
		trackBlock[i].Update(deltaTime);
	}
}

bool RacingTrack::ObstacleCollision(CollisionBox &playerBoundingBox)
{
	for (unsigned int i = 0; i < blockAmount; i++)
	{
		if (trackBlock[i].boundingBox.Intersects(playerBoundingBox))
		{
			return true;
			//return false;	Turn off collision for testing
		}
	}

	return false;
}

bool RacingTrack::BarrierCollision(CollisionBox &playerBoundingBox, Vector3 &playerPosition)
{
	if (playerBoundingBox.boundingBox.c.x <= -55.0f)
	{
		playerPosition.x = -55.0f;
		return true;
	}
	else if (playerBoundingBox.boundingBox.c.x >= 55.0f)
	{
		playerPosition.x = 55.0f;
		return true;
	}

	return false;
}

void RacingTrack::RenderTrack(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	trackSections.Render(camera, screenWidth, screenHeight);
}

void RacingTrack::RenderSceneObjects(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();

	modelShader->Use();
	Matrix4 modelMatrix = Matrix4();
	Matrix4 modelTranslate = Matrix4();
	Matrix4 modelScale = Matrix4();
	modelTranslate = modelTranslate.translate(finishRacePosition);
	modelScale = modelScale.scale(Vector3(3.2f, 5.0f, 5.0f));
	modelMatrix = modelScale * modelTranslate;
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "model"), 1, GL_FALSE, &modelMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	finishModel->Draw(*modelShader);
	
	buildings.Render(camera, screenWidth, screenHeight);
	barriers.Render(camera, screenWidth, screenHeight);

	for (unsigned int i = 0; i < blockAmount; i++)
		trackBlock[i].Render(camera, screenWidth, screenHeight);
}

void RacingTrack::RenderTrackReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view;
	view = camera.GetViewMatrix();

	buildings.RenderReflection(camera, screenWidth, screenHeight); 
	barriers.RenderReflection(camera, screenWidth, screenHeight);

	// TODO(Darren): Big problem here, only render what is in range from racer to fog.
	for (unsigned int i = 0; i < blockAmount; i++)
		trackBlock[i].RenderReflection(camera, screenWidth, screenHeight);
}