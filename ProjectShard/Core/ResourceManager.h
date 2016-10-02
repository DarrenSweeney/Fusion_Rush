#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "HashTable.h"
#include "..\Renderer\Shader.h"
#include "..\Renderer\Model.h"

class ResourceManager
{
public:
	void LoadShader(const char *assetName, const char *vertexPath, const char *fragmentPath, const char *geometryPath = NULL);
	Shader* GetShader(HashID hashID);

	void LoadModel(const char *assetName, std::string path);
	Model* GetModel(HashID hashID);

	void LoadTexture(const char *assetName, const char *path);
	Texture* GetTexture(HashID hashID);

	// TODO(Darren): Will need to change this to a batch system.
	void LoadSceneShaders();
	void LoadSceneModels();
	void LoadSceneTextures();
	
	// TODO(Darren): Need to add this in or take it out.
	void PrintShaderTable();

private:
	HashTable<Shader>	shaderResources;
	HashTable<Model>	modelResources;
	HashTable<Texture>  textureResources;
};

extern ResourceManager g_resourceMgr;

#endif