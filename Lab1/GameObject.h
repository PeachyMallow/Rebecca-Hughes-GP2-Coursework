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

public:

	GameObject() : m_mesh(), m_texture(), m_transform() {};
	~GameObject() {};
	//void Initialise();
	//void Update();
	//SetTransforms(i);
	//SetShader(i);
	//m_shader[i].Update(transform[i], m_Camera);
	//texture[i].Bind(0);
	//m_mesh[i].Draw();
};

