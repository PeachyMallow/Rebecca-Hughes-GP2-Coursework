#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> //all transformation functions
//#include "camera.h"

struct Transform
{
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos; this->rot = rot; this->scale = scale;
	}

	//inline glm::mat4 GetModelMatrix() const //runs at compile time
	//{
	//	glm::mat4 posMat = glm::translate(pos); 
	//	glm::mat4 scaleMat = glm::scale(scale);
	//	glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	//	glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	//	glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0f, 0.0f, 1.0f)); 
	//	glm::mat4 rotMat = rotX * rotY * rotZ;
	//	return posMat * rotMat * scaleMat; // this order matters
	//}

	// getters
	inline glm::vec3* GetPos() { return &pos; } 
	inline glm::vec3* GetRot() { return &rot; }
	inline glm::vec3* GetScale() { return &scale; }
	
	// setters
	inline void SetPos(glm::vec3& pos) { this->pos = pos; } 
	inline void SetRot(glm::vec3& rot) { this->rot = rot; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; } 

	inline glm::mat4 GetModMatrix() const // copied from lab 4 solution - look to implement myself or maybe this is the best way? Might not need as many local vars
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

private:
	// can lead to gimbal lock, using quaternions is suggested instead
	glm::vec3 pos; 
	glm::vec3 rot; 
	glm::vec3 scale;
};
