#version 330 core

in vec2 v_texCoord;
in vec3 normal;
//in vec3 lightPos;
in vec4 v_Pos;

uniform sampler2D diffuse;

vec4 colorStart = vec4 (1.0, 1.0, 1.0, 1.0 );
vec4 colorEnd = vec4(0.0, 0.0, 1.0, 1.0 );

void main()
{
	// will probably need the eye pos to model variable from fogshader
	float dist = abs(v_Pos.z);

	//vec3 lightDir = vec3(0.5f, 0.5f, 0.5f);
	vec3 lightDir = vec3(0.0f, 0.0f, -1.0f);

	vec4 texture = texture2D(diffuse, v_texCoord); // if you enable transparency alpha, then could avoid repitition
	float intensity = 1 - max(dot(normalize(normal), normalize(lightDir)), 0.0); // inverse of light direction 

	intensity = max(0.0, intensity); //max so the value is not negative
	intensity = pow(intensity, 4.0f); // higher second value - sharper drop in effect

	if (intensity >= 0.75f)
	{
		intensity = 0.0f;
	}

	gl_FragColor = vec4(intensity, intensity, intensity, 0.0) * texture;
}
