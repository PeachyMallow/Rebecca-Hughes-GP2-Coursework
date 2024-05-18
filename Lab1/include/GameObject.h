#pragma once

#include "Mesh.h"
#include "Shader.h" // ??
#include "Texture.h"
#include "Transform.h"
//#include "Physics.h"


class GameObject
{
	//shader?
	Mesh m_mesh;
	Texture m_texture;
	Transform m_transform; 
	static float m_counter;

public:

	GameObject() : m_mesh(), m_texture(), m_transform() {};
	~GameObject() {};
	void InitGameObj(const std::string& modelFileName, const std::string& texFileName, GLfloat posX, GLfloat posY, GLfloat posZ);

	//void SetTransforms(GLfloat posX, GLfloat posY);
	glm::mat4 GetObjTransform() { return this->m_transform.GetModMatrix(); };
	//void SetShader
	void DrawGOwithTexture();

	void MoveLeft();
	void Move(GameObject& obj);

	void MoveFrog();
	void MoveBee();
	void MovePumpkin();

	void IncrementCounter(GLfloat increaseAmount);
	//// shaders
	//m_shader[FROG].InitShaders("toonShader");
	//m_shader[BEE].InitShaders("basicShader");
	//m_shader[PUMPKIN].InitShaders("RimLighting");
	 
	 
	
	//void Update();
	//SetTransforms(i);
	//SetShader(i);
	//m_shader[i].Update(transform[i], m_Camera);
	//texture[i].Bind(0);
	//m_mesh[i].Draw();
};

