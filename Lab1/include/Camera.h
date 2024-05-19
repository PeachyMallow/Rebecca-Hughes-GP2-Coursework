#pragma once

#include <glm/gtx/transform.hpp>

struct Camera
{
	Camera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
		: m_pos(pos), m_forward(0.0f, 0.0f, 1.0f), m_up(0.0f, 1.0f, 0.0f), 
		m_projection(glm::perspective(fov, aspect, nearClip, farClip)) {};

	const inline glm::mat4 GetMVPMatrix() const
	{
		return m_projection * glm::lookAt(m_pos, m_pos + m_forward, m_up);
	}

	const inline glm::vec3 GetCameraPos() const
	{
		return m_pos;
	}

private:
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::mat4 m_projection;

};