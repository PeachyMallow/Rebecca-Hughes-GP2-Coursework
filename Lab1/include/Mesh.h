#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>

#include <string>
#include "obj_loader.h"


// used to store the mesh data in simplest form - speeding up the operation
// not using again in GP2, but keeping here in case we want to render out to quads, skyboxes(cube)
// was a class but changed to struct for lab 4 
struct Vertex
{
	Vertex(const glm::vec3& pos, const glm::vec2& tCoord)
	{
		this->pos = pos;
		this->textureCoord = tCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &textureCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 textureCoord; //position on the texture that we will map to the vertex
	glm::vec3 normal;
};

class Mesh
{
	// using enum to make scalable
	enum 
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; // how much of the vertexArrayObject's do we want to draw
	

public: 
	
	//Mesh(Vertex* vertices, unsigned int numVertices);
	
	Mesh() : vertexArrayObject(0), drawCount(0) {};
	~Mesh();

	void Init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void LoadModel(const std::string& fileName);
	void InitModel(const IndexedModel& model);
	void Draw();

};

