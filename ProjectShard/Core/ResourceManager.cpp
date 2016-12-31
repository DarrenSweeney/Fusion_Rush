#include "ResourceManager.h"

ResourceManager g_resourceMgr;

void ResourceManager::LoadShader(const char *assetName, const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
	Shader shader;
	shader.LoadShader(vertexPath, fragmentPath, geometryPath);
	shaderResources.Insert(SID(assetName), shader);
}

Shader* ResourceManager::GetShader(HashID hashID)
{
	return shaderResources.Find(hashID);
}

void ResourceManager::LoadModel(const char *assetName, std::string path)
{
	Model model;
	model.LoadModel(path);
	modelResources.Insert(SID(assetName), model);
}

Model* ResourceManager::GetModel(HashID hashID)
{
	return modelResources.Find(hashID);
}

void ResourceManager::LoadTexture(const char *assetName, const char *path)
{
	Texture texture;
	texture.LoadTexture(path);
	textureResources.Insert(SID(assetName), texture);
}

void ResourceManager::LoadCubeMap(const char* assetName, std::vector<const char *> faces)
{
	Texture texture;
	texture.LoadCubeMap(faces);
	textureResources.Insert(SID(assetName), texture);
}

Texture* ResourceManager::GetTexture(HashID hashID)
{
	return textureResources.Find(hashID);
}

void ResourceManager::LoadSceneShaders()
{
	LoadShader("ModelShader", "Shaders/model.vert", "Shaders/model.frag");
	LoadShader("DebugLine","Shaders/DebugDrawMgr/DebugLine.vert", "Shaders/DebugDrawMgr/DebugLine.frag", "Shaders/DebugDrawMgr/DebugLine.gs");
	LoadShader("EnviromentObject", "Shaders/EnviromentObject.vert", "Shaders/EnviromentObject.frag");
	LoadShader("Text", "Shaders/text.vert", "Shaders/text.frag");
	LoadShader("Instancing", "Shaders/instancing.vert", "Shaders/EnviromentObject.frag");
	LoadShader("SkyboxShader", "Shaders/Skybox.vert", "Shaders/Skybox.frag");
	LoadShader("PlayerShader", "Shaders/Player.vert", "Shaders/Player.frag");// , "Shaders/ExplodeGeometry.gs");
	LoadShader("BlurShader", "Shaders/SceneBlur.vert", "Shaders/SceneBlur.frag");
	LoadShader("UI_Shader", "Shaders/UI.vert", "Shaders/UI.frag");
}

void ResourceManager::LoadSceneModels()
{
	LoadModel("PlayerShip", "Resources/Ship/Shard_Ship.obj");
	LoadModel("RaceTrack", "Resources/Track_new/Race_Track.obj");
	LoadModel("Barrier", "Resources/Barrier/Barrier.obj");
	LoadModel("BarrierReflection", "Resources/Barrier/Barrier.obj");
	LoadModel("Building", "Resources/Buildings/Building/Building.obj");
	LoadModel("BuildingReflection", "Resources/Buildings/Building/Building.obj");
	LoadModel("Building_2", "Resources/Buildings/Building_2/Building_2.obj");
	LoadModel("BuildingReflection_2", "Resources/Buildings/Building_2/Building_2.obj");
	LoadModel("Block", "Resources/Obstacle/Obstacle.obj");
	LoadModel("Finish_Model", "Resources/Finish_Model/Race_Finish.obj");
}

// Loads independent textures, that excludes models textures.
void ResourceManager::LoadSceneTextures()
{
	std::vector<const GLchar*> faces;
	faces.push_back("Resources/skybox/galaxy+X.png");
	faces.push_back("Resources/skybox/galaxy-X.png");
	faces.push_back("Resources/skybox/galaxy+Y.png");
	faces.push_back("Resources/skybox/galaxy-Y.png");
	faces.push_back("Resources/skybox/galaxy+Z.png");
	faces.push_back("Resources/skybox/galaxy-Z.png");
	LoadCubeMap("GameSkybox", faces);

	LoadTexture("Bottom_UI", "Resources/UI/Bottom_UI.png");
	LoadTexture("Menu_UI", "Resources/UI/Menu_UI.png");
	LoadTexture("Enter_UI", "Resources/UI/EnterPanel.png");
	LoadTexture("TypeElement", "Resources/UI/TypeElement.png");
	LoadTexture("Race_Bar_UI", "Resources/UI/Race_Line_UI.png");
	LoadTexture("Arrow_UI", "Resources/UI/Arrow_UI.png");
	LoadTexture("Best_Time_UI", "Resources/UI/Best_Time_UI.png");
	LoadTexture("Current_Time_UI", "Resources/UI/Current_Time_UI.png");
	LoadTexture("Gauge_Speed_UI", "Resources/UI/Gauge_Vel.png");
	LoadTexture("Gauge_Arrow_UI", "Resources/UI/Speed_Pointer.png");
	LoadTexture("Engine_Logo", "Resources/Engine_Logo/Engine_Logo.png");
	LoadTexture("Speed_Box_UI", "Resources/UI/Speed_Box_UI.png");
}

void ResourceManager::PrintShaderTable()
{
	// TODO(Darren): May override the << operator for ouputting the name of the T type, 
	// ie, shaders, models, textures.
	//shaderResources.PrintTable();
}