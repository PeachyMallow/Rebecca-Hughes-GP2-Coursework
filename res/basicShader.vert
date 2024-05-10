#version 120
// called a passthrough shader

attribute vec3 position; //linking from shader class
attribute vec2 texCoord; //linking from shader class

varying vec2 texCoord0; 
uniform mat4 transform; //linking from shader class

void main()
{
	gl_Position = transform * vec4(position, 1.0); 
	texCoord0 = texCoord;
}