#shader VERTEX triangle
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 FragColor;

uniform mat4 u_mvp;
uniform mat4 u_model;

uniform vec3 u_ambiantLightColor;
uniform vec3 u_ambiantObjectColor;
uniform vec3 u_lightPos;

void main()
{
	// to transform into uniforms.
	vec3 diffuseLightColor = vec3(1.0, 1.0, 1.0);
	vec3 diffuseObjectColor = vec3(1.0, 1.0, 1.0);

	vec4 pos = u_model * position;
	vec3 N = normalize((u_model * vec4(normal, 0.0)).xyz);
	vec3 L = normalize(u_lightPos - pos.xyz);

	vec3 ambiantColor = u_ambiantLightColor * u_ambiantObjectColor;
	vec3 diffuseColor = diffuseLightColor * diffuseObjectColor * max(0.0, dot(L, N));

	FragColor = ambiantColor * diffuseColor;
	gl_Position = u_mvp * position;
}

#shader FRAGMENT color
#version 330 core
layout(location = 0) out vec4 color;

in vec3 FragColor;

void main()
{
	color = vec4(FragColor, 1.0);
};