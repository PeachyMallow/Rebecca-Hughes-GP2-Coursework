#version 330 core
// called a passthrough shader

//attribute
layout (location = 0) vec3 positions;
layout (location = 2) vec3 normals;

out vec3 normal;
uniform mat4 transform;

void main()
{
	normal = normals;
	gl_Position = transform * vec4(position, 1.0);
}