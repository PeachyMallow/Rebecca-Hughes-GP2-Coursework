#include "GameObject.h"


void GameObject::InitGameObj(const std::string& modelFileName, const std::string& texFileName)
{
// -Load Models-
	this->m_mesh.LoadModel(modelFileName);

// -Load Texture-
	this->m_texture.LoadTexture(texFileName);
	this->m_texture.Bind(0);
// -Init shaders-??

// -set transforms-

}

// 
// m_mesh[FROG].LoadModel("Frog");
//m_mesh[BEE].LoadModel("Bee");
//m_mesh[PUMPKIN].LoadModel("Pumpkin");
//// texture
//texture[FROG].LoadTexture("FrogTex");
//texture[BEE].LoadTexture("BeeTex");
//texture[PUMPKIN].LoadTexture("PumpkinTex");
//// shaders
//m_shader[FROG].InitShaders("toonShader");
//m_shader[BEE].InitShaders("basicShader");
//m_shader[PUMPKIN].InitShaders("RimLighting");

void GameObject::SetTransforms(GLfloat posX, GLfloat posY)
{
	// maybe move up, move down etc - could do that in physics class?
	this->m_transform.SetPos(glm::vec3(posX, posY, 3.0f));
	this->m_transform.SetRot(glm::vec3(0.0f, 1.0f, 0.0f));
	this->m_transform.SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
}

void GameObject::DrawGameObject()
{
	this->m_mesh.Draw();
}

void GameObject::Move()
{
	this->m_transform.SetPos(glm::vec3(3.0f - m_counter, 0.0f, -2.0f));
	this->m_transform.SetRot(glm::vec3(0.0f, 0.0f /*counter * 1.0f*/, 0.0f));
	this->m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void GameObject::IncrementCounter() // incrementing correctly
{
	m_counter = m_counter + 0.005f;
}