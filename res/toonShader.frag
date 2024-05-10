#version 330 core

in vec3 normal;

uniform mat4 lighting;

void main()
{
	vec3 lightDir = vec3(0.5f, 0.5f, 0.5f);

	float intensity = max(dot(normalize(normal), normalize(lightDir)), 0.0);

	if (intensity <= 0.5f)
	{
		intensity = intensity * 0.4f;
	}

	else if (intensity < 0.75f && intensity > 0.5f)
	{
		intensity = intensity * 0.7f;
	}

	gl_FragColor = vec4(intensity, intensity, intensity, 1.0);
}
