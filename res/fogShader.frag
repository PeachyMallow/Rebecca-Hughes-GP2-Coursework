#version 400

in vec4 v_Pos; // move to be first?
in vec2 v_texCoord;

// vv uniform 
vec4 fogColour = vec4(0.1f, 0.1f, 0.1f, 1.0f);

// vv uniform 
float maxDist = 7.0f; // object distance from camera where fog will be at max intensity
float minDist = 0.5f; // object distance to camera before fog starts(fog 'thickness')

uniform sampler2D diffuse;

void main() 
{
	float dist = abs(v_Pos.z); 	//surface point to the eye position
	
	float fogFactor = clamp((maxDist - dist) / (maxDist - minDist), 0.0f, 1.0f); // how much the object should be affected by fog 

	vec4 texture = texture2D(diffuse, v_texCoord); // model's texture

	vec4 colour = mix( texture, fogColour, 1 - fogFactor); // interpolate between model's texture & fogColour dependant on objects distance from camera

	gl_FragColor = colour;
}
