#version 330 core

in vec2 v_texCoord;
in vec3 normal;
//in vec3 lightPos;

uniform sampler2D diffuse;
uniform vec3 u_lighting;

void main()
{
	//vec3 lightDir = vec3(0.0f, 0.0f, -1.0f);
	//vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);

	vec4 texture = texture2D(diffuse, v_texCoord); // if you enable transparency alpha, then could avoid repitition
	float intensity = max(dot(normalize(normal), normalize(u_lighting)), 0.0);

	if (intensity <= 0.5f)
	{
		intensity = intensity * 0.4f;
	}

	else if (intensity < 0.75f && intensity > 0.5f)
	{
		intensity = intensity * 0.7f;
	}

	gl_FragColor = vec4(intensity, intensity, intensity, 0.0) * texture;
}
