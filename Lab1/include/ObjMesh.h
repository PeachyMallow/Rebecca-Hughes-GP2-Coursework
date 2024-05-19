#pragma once

#include <GL\glew.h>
#include "obj_loader.h"

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
	unsigned int m_drawCount;
	
	float m_radius;

public: 
	
	ObjMesh() : m_vertexArrayObject(0), m_vertexArrayBuffers{ NUM_BUFFERS }, m_drawCount(0), m_radius(15.0f) {};
	~ObjMesh();

	void LoadObjFile(const std::string& fileName);
	void InitMesh(const IndexedModel& model);
	void DrawMesh();

	const float GetRadius() { return this->m_radius; };
	void SetRadius(float newRadius) { this->m_radius = newRadius; };

};