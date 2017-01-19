#include "GhostRacer.h"

GhostRacer::GhostRacer()
	:	lastTime(0.0f)
{
	ghostRacerModel = g_resourceMgr.GetModel(SID("PlayerShip"));
	ghostRacerShader = g_resourceMgr.GetShader(SID("ModelShader"));
}

GhostRacer::~GhostRacer()
{
	delete ghostRacerModel;
	delete ghostRacerShader;
}

void GhostRacer::RestGhostRacer()
{
	lastTime = 0.0f;
}

void GhostRacer::ReadRecordedPositions()
{
	std::ifstream ghostRacerFile;
	ghostRacerFile.open("Ghost_Racer.txt");

	Vector3 position;
	Quaternion orientation;

	std::string line;
	std::string word = "#";

	bool readPos = true;
	bool readOri = false;

	if (ghostRacerFile.is_open())
	{
		while (std::getline(ghostRacerFile, line))
		{
			std::size_t found = line.find(word);

			if (found != std::string::npos && readPos)
			{
				readOri = true;
				readPos = false;
				continue;
			}

			if (readPos)
			{
				std::stringstream stream(line);
				stream >> position.x >> position.y >> position.z;
				ghostRacerPositions.push_back(position);
			}
			else if (readOri)
			{
				std::stringstream stream(line);
				stream >> orientation.w >> orientation.x >> orientation.y >> orientation.z;
				ghostRacerOrientations.push_back(orientation);
			}
		}

		ghostRacerFile.close();
	}
	else
	{
		std::cout << "GhostRacer::Unable to open file" << std::endl;
	}
}

void GhostRacer::Update(float currentTrackTime)
{
	if ((int)lastTime < ghostRacerPositions.size() - 2 && ghostRacerPositions.size() > 0)
	{
		float interpolate = currentTrackTime - lastTime;
		if (interpolate >= 1.0f)
		{
			lastTime += 1.0;
			interpolate = 1.0f;
		}

		position = position.Lerp(ghostRacerPositions.at((int)lastTime), ghostRacerPositions.at((int)(lastTime + 1)), interpolate);
	}
}

void GhostRacer::Render(GLsizei screenWidth, GLsizei screenHeight, Camera &camera)
{
	ghostRacerShader->Use();
	Matrix4 modelMatrix = Matrix4();
	Matrix4 viewMatrix = camera.GetViewMatrix();
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 modelRotate = Matrix4();
	modelRotate = modelRotate.QuaternionToMatrix4(orientation);
	Matrix4 modelTranslate = Matrix4();
	modelTranslate = modelTranslate.translate(position);
	modelMatrix = modelRotate * modelTranslate;
	glUniformMatrix4fv(glGetUniformLocation(ghostRacerShader->Program, "model"), 1, GL_FALSE, &modelMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ghostRacerShader->Program, "view"), 1, GL_FALSE, &viewMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ghostRacerShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	ghostRacerModel->Draw(*ghostRacerShader);
}