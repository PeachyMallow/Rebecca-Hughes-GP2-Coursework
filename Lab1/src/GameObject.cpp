#include "GameObject.h"

void GameObject::InitGameObj(const std::string& modelFileName, const std::string& texFileName, GLfloat posX, GLfloat posY, GLfloat posZ)
{
	this->m_mesh.LoadModelFile(modelFileName);

	this->m_texture.LoadTexture(texFileName);

	this->m_transform.SetPos(glm::vec3(posX, posY, posZ));
	this->m_transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	this->m_transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void GameObject::DrawGOwithTexture()
{
	this->m_texture.BindTexture(0);
	this->m_mesh.DrawModel();
}

void GameObject::Move(GameObject& obj)
{
	glm::vec3 objPos = *m_transform.GetPos();
	glm::vec3 objRot = *m_transform.GetRot();

	obj.m_transform.SetPos(glm::vec3(objPos.x, objPos.y, objPos.z));
	obj.m_transform.SetRot(glm::vec3(objRot.x, objRot.y + m_counter, objRot.z));
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