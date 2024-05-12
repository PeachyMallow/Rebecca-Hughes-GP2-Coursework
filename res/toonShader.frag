#version 330 core

in vec2 v_texCoord;
in vec3 normal;
//in vec3 lightPos;

uniform sampler2D diffuse;

void main()
{
	vec3 lightDir = vec3(0.5f, 0.5f, 0.5f);

	vec4 texture = texture2D(diffuse, v_texCoord); // if you enable transparency alpha, then could avoid repitition
	float intensity = max(dot(normalize(normal), normalize(lightDir)), 0.0);

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
