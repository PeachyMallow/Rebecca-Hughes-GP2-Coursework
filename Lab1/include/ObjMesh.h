#pragma once

//#include <glm\glm.hpp>
#include <GL\glew.h>
//#include <vector>
//#include <string>
#include "obj_loader.h"

// used to store the mesh data in simplest form - speeding up the operation
// not using again in GP2, but keeping here in case we want to render out to quads, skyboxes(cube)
// was a class but changed to struct for lab 4 
//struct Vertex
//{
//	Vertex(const glm::vec3& pos, const glm::vec2& tCoord)
//	{
//		this->pos = pos;
//		this->textureCoord = tCoord;
//		this->normal = normal;
//	}
//
//	glm::vec3* GetPos() { return &pos; }
//	glm::vec2* GetTexCoord() { return &textureCoord; }
//	glm::vec3* GetNormal() { return &normal; }
//
//private:
//	glm::vec3 pos;
//	glm::vec2 textureCoord; //position on the texture that we will map to the vertex
//	glm::vec3 normal;
//};

class ObjMesh
{
	enum 
	{
		POSITION_VERTBUFF,
		TEXCOORD_VERTBUFF,
		NORMAL_VERTBUFF,
		INDEX_VERTBUFF,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount; // how much of the m_vertexArrayObject's do we want to draw
	
	float m_radius;

public: 
	
	//ObjMesh(Vertex* vertices, unsigned int numVertices);
	
	ObjMesh() : m_vertexArrayObject(0), m_vertexArrayBuffers{ NUM_BUFFERS }, m_drawCount(0), m_radius(15.0f) {};
	~ObjMesh();

	//void Init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void LoadModelFile(const std::string& fileName);
	void InitModel(const IndexedModel& model);
	void DrawModel();

	const float GetRadius() { return this->m_radius; };
	void SetRadius(float newRadius) { this->m_radius = newRadius; }; // maybe not needed

};