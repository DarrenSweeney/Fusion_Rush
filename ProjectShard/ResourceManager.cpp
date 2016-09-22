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

void ResourceManager::LoadSceneShaders()
{
	// Model Shader
	LoadShader("ModelShader", "Shaders/model.vert", "Shaders/model.frag");
	// Debug drawing line shader
	LoadShader("DebugLine","Shaders/DebugDrawMgr/DebugLine.vert", "Shaders/DebugDrawMgr/DebugLine.frag", "Shaders/DebugDrawMgr/DebugLine.gs");
	// General basic scene objects
	LoadShader("Darren", "Shaders/EnviromentObject.vert", "Shaders/EnviromentObject.frag");
	// Rendering text to screen
	LoadShader("Text", "Shaders/text.vert", "Shaders/text.frag");
}

void ResourceManager::LoadSceneModels()
{
	LoadModel("Nanosuit", "Resources/nanosuit/nanosuit.obj");
}

void ResourceManager::PrintShaderTable()
{
	// TODO(Darren): May override the << operator for ouputting the name of the T type, 
	// ie, shaders, models, textures.
	//shaderResources.PrintTable();
}