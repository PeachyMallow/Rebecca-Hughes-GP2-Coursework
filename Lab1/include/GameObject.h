#pragma once

#include <iostream>

#include "ObjMesh.h"
#include "ObjTexture.h"
#include "ObjTransform.h"

class GameObject
{
	ObjMesh m_mesh;
	ObjTexture m_texture;
	ObjTransform m_transform;
	GLfloat m_moveSpeed = 0.06f;

public:

	~GameObject() {};

	// initialises GameObject with: model, texture, transform, & radius
	void InitGameObj(const std::string& modelFileName, const std::string& texFileName, 
		GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, 
		GLfloat radius);

	// draws GO with texture it was assigned
	void DrawGOwithTexture();

	// movement methods
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void CollisionMove(GameObject& collidedObj);
	
	//getters
	const glm::mat4 GetObjTransform() { return this->m_transform.GetModMatrix(); };
	const glm::vec3 GetObjPos() { return *m_transform.GetPos(); }
	const GLfloat GetObjRadius() { return m_mesh.GetRadius(); }
};