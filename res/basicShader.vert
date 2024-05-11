#version 120
// called a passthrough shader

attribute vec4 vertexPos; //changed to vec 4 to avoid changing it in main
attribute vec2 vertexTexCoord; //linking from shader class

varying vec2 texCoord0; 
uniform mat4 transform; //linking from shader class

void main()
{
	gl_Position = transform * vertexPos; 
	texCoord0 = vertexTexCoord;
}