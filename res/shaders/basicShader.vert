#version 120
// called a passthrough shader

attribute vec4 vertexPos; //changed to vec 4 to avoid changing it in main
attribute vec2 vertexTexCoord; //linking from shader class

varying vec2 texCoord0; 
uniform mat4 u_transform; //linking from shader class
uniform vec3 u_lighting;

void main()
{
	gl_Position = u_transform * vertexPos; 
	texCoord0 = vertexTexCoord;
}