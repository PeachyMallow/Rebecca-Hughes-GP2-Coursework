#include "GameObject.h"


void GameObject::InitGameObj(const std::string& modelFileName, const std::string& texFileName, GLfloat posX, GLfloat posY, GLfloat posZ)
{
// -Load Models-
	this->m_mesh.LoadModel(modelFileName);

// -Load Texture-
	this->m_texture.LoadTexture(texFileName);
	//this->m_texture.Bind(0);
// -Init shaders-??

// -set transforms-
	this->m_transform.SetPos(glm::vec3(posX, posY, posZ));
	this->m_transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	this->m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
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

//void GameObject::SetTransforms(GLfloat posX, GLfloat posY)
//{
//	// maybe move up, move down etc - could do that in physics class?
//	this->m_transform.SetPos(glm::vec3(posX, posY, 3.0f));
//	this->m_transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
//	this->m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
//}

void GameObject::DrawGOwithTexture()
{
	this->m_texture.Bind(0);
	this->m_mesh.Draw();
}

void GameObject::Move(GameObject& obj)
{
	glm::vec3 objPos = *m_transform.GetPos();
	glm::vec3 objRot = *m_transform.GetRot();

	obj.m_transform.SetPos(glm::vec3(objPos.x, objPos.y, objPos.z));
	//obj.m_transform.SetRot(glm::vec3(objRot.x, objRot.y + m_counter, objRot.z));
	//obj.m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void GameObject::MoveLeft()
{
	glm::vec3 objPos = *m_transform.GetPos();
	glm::vec3 objRot = *m_transform.GetRot();

	m_transform.SetPos(glm::vec3(objPos.x + 0.005f, objPos.y, objPos.z));
	//obj.m_transform.SetRot(glm::vec3(objRot.x, objRot.y + m_counter, objRot.z));
	//obj.m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
}



void GameObject::MoveFrog()
{
	this->m_transform.SetPos(glm::vec3(sinf(m_counter) * 1.5f, 0.0f, 0.0f));
	this->m_transform.SetRot(glm::vec3(0.0f, 0.0f /*counter * 1.0f*/, 0.0f));
	this->m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void GameObject::MoveBee()
{
	this->m_transform.SetPos(glm::vec3(1.0f, sinf(m_counter) * 1.5f, 10.0f));
	this->m_transform.SetRot(glm::vec3(0.0f, 0.0f /*counter * 1.0f*/, 0.0f));
	this->m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void GameObject::MovePumpkin()
{
	this->m_transform.SetPos(glm::vec3(0.0f, 0.0f, sinf(m_counter) * 6.0f + 3.0f));
	this->m_transform.SetRot(glm::vec3(0.0f, 0.0f /*counter * 1.0f*/, 0.0f));
	this->m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void GameObject::IncrementCounter(GLfloat increaseAmount) // incrementing correctly
{
	m_counter = m_counter + increaseAmount;
}