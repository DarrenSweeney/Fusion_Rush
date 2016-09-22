#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "HashTable.h"
#include "Shader.h"

class ResourceManager
{
public:
	void LoadShader(const char* assetName, const char *vertexPath, const char *fragmentPath, const char *geometryPath = NULL);
	Shader* GetShader(HashID hashID);
	// TODO(Darren): Will need to change this to a batch system.
	void LoadSceneShaders();
	void PrintShaderTable();

private:
	HashTable<Shader> shaderResources;
};

extern ResourceManager g_resourceMgr;

#endif