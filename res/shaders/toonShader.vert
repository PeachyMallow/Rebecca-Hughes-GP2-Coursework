#version 330 core

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in vec2 vertexTexCoord;
layout (location = 2) in vec3 vertexNormals;

out vec3 normal;
out vec2 v_texCoord;
//out vec3 lightPos;

uniform mat4 u_transform;
//uniform vec3 u_lighting;

void main()
{
	v_texCoord = vertexTexCoord;
	normal = vertexNormals;
	//lightPos = u_lighting;
	gl_Position = u_transform * vertexPos;
}