#pragma once

#include "ObjMesh.h"
//#include "ShaderManager.h" // ??
#include "ObjTexture.h"
#include "ObjTransform.h"
//#include "Physics.h"


class GameObject
{
	//shader?
	ObjMesh m_mesh;
	ObjTexture m_texture;
	ObjTransform m_transform;
	static float m_counter;

public:

	GameObject() : m_mesh(), m_texture(), m_transform() {};
	~GameObject() {};

	// initialises GameObject with: model, texture, & transform
	void InitGameObj(const std::string& modelFileName, const std::string& texFileName, GLfloat posX, GLfloat posY, GLfloat posZ);

	//void SetTransforms(GLfloat posX, GLfloat posY);
	glm::mat4 GetObjTransform() { return this->m_transform.GetModMatrix(); };
	//void SetShader
	void DrawGOwithTexture();

	void MoveLeft();

	// all below needed?
	void Move(GameObject& obj);
	void MoveFrog();
	void MoveBee();
	void MovePumpkin();
	void IncrementCounter(GLfloat increaseAmount);
};

