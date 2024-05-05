#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

//•	create a camera struct
//o	struct Camera

struct Camera
{
	//•	create a default constructor
	//o	Camera()

	Camera() {}/*: projection(0), pos(0), forward(0), up(0) {}*/; // need a destructor?

	//•	create a method to initialise the camera, this method takes in:
	// a vector 3 postion
	// a float for the field of view
	// a float for the aspect ratio
	// floats for the near and far clipping planes
	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	//•	inside the method set our private variables = to our arguments
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	//•	create a projection matrix, this will be explained in the lecture
	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	//•	create the following private variables
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;

};





