#ifndef MESH_H
#define MESH_H

#include <string>	
#include <vector>

#include <assimp\Importer.hpp>

#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Shader.h"

using namespace std;

struct Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TexCoords;
	Vector3 Tangents;
};

struct ModelTexures
{
	GLuint id;
	string type;
	aiString path;
};

class Mesh
{
public:
	// Render Data
	GLuint VAO;
	bool loadTangents;

	// Mesh Data
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<ModelTexures> textures;

	// Functions
	Mesh(vector<Vertex> &verticies, vector<GLuint> &indices, vector<ModelTexures> &textures, bool loadTangent = false);
	~Mesh();
	void Draw(Shader &shader);

private:
	// Render Data
	GLuint VBO, EBO;
	// Functions
	void setupMesh();
};
#endif