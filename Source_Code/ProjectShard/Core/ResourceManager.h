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
	void LoadCubeMap(const char* assetName, std::vector<const char *> faces);
	Texture* GetTexture(HashID hashID);

	void LoadSceneShaders();
	void LoadSceneModels();
	void LoadSceneTextures();
	
	void PrintShaderTable();

private:
	HashTable<Shader>	shaderResources;
	HashTable<Model>	modelResources;
	HashTable<Texture>  textureResources;
};

extern ResourceManager g_resourceMgr;

#endif