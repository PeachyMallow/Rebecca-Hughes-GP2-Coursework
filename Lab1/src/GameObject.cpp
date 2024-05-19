#include "GameObject.h"

void GameObject::InitGameObj(const std::string& modelFileName, const std::string& texFileName, 
	GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ,
	GLfloat radius)
{
	this->m_mesh.LoadObjFile(modelFileName);
	this->m_texture.LoadTexture(texFileName);

	this->m_transform.SetPos(glm::vec3(posX, posY, posZ));
	this->m_transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	this->m_transform.SetScale(glm::vec3(scaleX, scaleY, scaleZ));

	this->m_mesh.SetRadius(radius);
}

void GameObject::DrawGOwithTexture()
{
	this->m_texture.BindTexture(0);
	this->m_mesh.DrawMesh();
}

void GameObject::MoveUp()
{
	glm::vec3 objPos = *m_transform.GetPos();
	
	m_transform.SetPos(glm::vec3(objPos.x, objPos.y + m_moveSpeed, objPos.z));
}

void GameObject::MoveDown()
{
	glm::vec3 objPos = *m_transform.GetPos();

	m_transform.SetPos(glm::vec3(objPos.x, objPos.y - m_moveSpeed, objPos.z));
}

void GameObject::MoveLeft()
{
	glm::vec3 objPos = *m_transform.GetPos();

	m_transform.SetPos(glm::vec3(objPos.x + m_moveSpeed, objPos.y, objPos.z));
}

void GameObject::MoveRight()
{
	glm::vec3 objPos = *m_transform.GetPos();

	m_transform.SetPos(glm::vec3(objPos.x - m_moveSpeed, objPos.y, objPos.z));
}

// bounces currently controlled obj away from obj it collided with
void GameObject::CollisionMove(GameObject& collidedObj)
{
	glm::vec3 objPos = *m_transform.GetPos();

	glm::vec3 offset = glm::normalize(objPos - collidedObj.GetObjPos()) * 2.0f;
	glm::vec3 newPos = glm::vec3(objPos.x + offset.x, objPos.y + offset.y, objPos.z + offset.z );

	m_transform.SetPos(newPos);
}