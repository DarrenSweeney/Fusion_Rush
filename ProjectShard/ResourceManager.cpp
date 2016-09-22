#include "ResourceManager.h"

ResourceManager g_resourceMgr;

Shader* ResourceManager::GetShader(HashID hashID)
{
	return shaderResources.Find(hashID);
}

void ResourceManager::LoadShader(const char* assetName, const char *vertexPath, const char *fragmentPath, const char *geometryPath)
 {
	Shader shader;
	shader.LoadShader(vertexPath, fragmentPath, geometryPath);
	shaderResources.Insert(SID(assetName), shader);
}

void ResourceManager::LoadSceneShaders()
{
	// Model Shader
	LoadShader("Shader_ModelShader", "Shaders/model.vert", "Shaders/model.frag");
	// Debug drawing line shader
	LoadShader("Shader_DebugLine","Shaders/DebugDrawMgr/DebugLine.vert", "Shaders/DebugDrawMgr/DebugLine.frag", "Shaders/DebugDrawMgr/DebugLine.gs");
	// General basic scene objects
	LoadShader("Shader_EnviromentObject", "Shaders/EnviromentObject.vert", "Shaders/EnviromentObject.frag");
	// Rendering text to screen
	LoadShader("Shader_Text", "Shaders/text.vert", "Shaders/text.frag");
}

void ResourceManager::PrintShaderTable()
{
	// TODO(Darren): May override the << operator for ouputting the name of the T type, 
	// ie, shaders, models, textures.
	//shaderResources.PrintTable();
}