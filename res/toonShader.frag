#version 330 core

in vec3 normal;

void main()
{
	vec3 lightDir = vec3(0.5f, 0.5f, 0.5f);

	float intensity = max(dot(normalize(normal), normalize(lightDir)), 0.0);
    vec4 color = vec4(intensity, intensity, intensity, 1.0);

	gl_FragColor = color;
}
