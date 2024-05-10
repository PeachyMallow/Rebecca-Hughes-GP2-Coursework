#version 330 core
// called a passthrough shader

layout (location = 0) in vec3 v_pos;
layout (location = 2) in vec3 v_normals;

out vec3 normal;
uniform mat4 transform;

void main()
{
	normal = v_normals;
	gl_Position = transform * vec4(v_pos, 1.0);
}