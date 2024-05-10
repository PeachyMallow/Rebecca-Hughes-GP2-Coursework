#version 120
// called a passthrough shader

attribute vec4 v_pos; //changed to vec 4 to avoid changing it in main
attribute vec2 v_texCoord; //linking from shader class

varying vec2 texCoord0; 
uniform mat4 transform; //linking from shader class

void main()
{
	gl_Position = transform * v_pos; 
	texCoord0 = v_texCoord;
}