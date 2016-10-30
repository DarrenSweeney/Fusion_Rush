#include "RacingTrack.h"

RacingTrack::RacingTrack()
	: blockAmount(50), skyColour(0.5f, 0.5f, 0.5f)
{
	trackBlock = new TrackBlock[blockAmount];
}

RacingTrack::~RacingTrack()
{
	delete[] trackBlock;
}

void RacingTrack::Init()
{
	srand(time(NULL));

	// Set up the track obstacles blocks
	for (int i = 0; i < blockAmount; i++)
	{
		bool oscillationBlock = ((rand() % 100) < 20) && (i + 5 < blockAmount);
		bool rotatingBlock = ((rand() % 100) < 40);

		// NOTE(Darren): Check the less chance ones first.
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
		else
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

	Matrix4 rotate = Matrix4();
	Vector3 scaleVec = Vector3(3.0f, 5.0f, 60.0f);
	debug_block.position = Vector3(-60.0f, 0.0f, 0.0f);
	debug_block.rotate = rotate;
	debug_block.scaleVec = scaleVec;
	debug_BoundingBox.UpdateBoundingBox(Vector3(-60.0f, 0.0f, 0.0f), rotate, scaleVec);
}

void RacingTrack::Update(float deltaTime)
{
	for (unsigned int i = 0; i < blockAmount; i++)
	{
		trackBlock[i].Update(deltaTime);
	}
}

bool RacingTrack::TrackCollision(CollisionBox &playerBoundingBox)
{
	for (unsigned int i = 0; i < blockAmount; i++)
	{
		if (trackBlock[i].boundingBox.Intersects(playerBoundingBox))
		{
			return true;
		}
	}

	if (debug_BoundingBox.Intersects(playerBoundingBox))
	{
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
	
	buildings.Render(camera, screenWidth, screenHeight);
	barriers.Render(camera, screenWidth, screenHeight);

	debug_block.Render(camera, screenWidth, screenHeight);

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

	for (unsigned int i = 0; i < blockAmount; i++)
		trackBlock[i].RenderReflection(camera, screenWidth, screenHeight);
}