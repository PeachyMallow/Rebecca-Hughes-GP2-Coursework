#version 400

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 vertexTexCoord;
layout (location = 2) in vec3 vertexNormals;

uniform mat4 u_transform;
uniform vec3 u_lighting;

out vec4 v_Pos; 
out vec2 v_texCoord;
out vec3 v_Nrml;

void main()
{
	//v_Pos = vec4(vertexPos, 1.0);
	v_texCoord = vertexTexCoord;
	v_Nrml = vertexNormals;

	v_Pos = u_transform * vec4(vertexPos, 1.0);
	
	gl_Position = u_transform * vec4(vertexPos, 1.0); // make equal to v_pos? 
}

