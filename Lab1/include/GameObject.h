#pragma once

#include "Mesh.h"
#include "Shader.h" // ??
#include "Texture.h"
#include "Transform.h"



class GameObject
{
	//shader?
	Mesh m_mesh;
	Texture m_texture;
	Transform m_transform; 
	float m_counter;

public:

	GameObject() : m_mesh(), m_texture(), m_transform(), m_counter(0) {};
	~GameObject() {};
	void InitGameObj(const std::string& modelFileName, const std::string& texFileName);

	void SetTransforms(GLfloat posX, GLfloat posY);
	glm::mat4 GetObjTransform() { return this->m_transform.GetModMatrix(); };
	//void SetShader
	void DrawGameObject();
	void Move();
	void IncrementCounter();
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

