#shader VERTEX triangle
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 FragColor;

uniform mat4 u_mvp;
uniform mat4 u_view;
uniform mat4 u_modelView;
uniform mat3 u_normalMat;

uniform vec3 u_ambiantLightColor;
uniform vec3 u_objectColor;
uniform vec3 u_lightPos;

float p = 32.0;

void main()
{
	// to transform into uniforms.
	vec3 diffuseLightColor = vec3(1.0, 1.0, 1.0);
	vec3 specularLightColor = vec3(0.0, 1.0, 1.0);

	vec3 pos = vec3(u_modelView * position);
	vec3 N = u_normalMat * normal;
	vec3 L = normalize(vec3(u_view * vec4(u_lightPos, 1.0)) - pos);
	vec3 V = normalize(-pos);
	vec3 R = reflect(-L, N);

	vec3 diffuseColor = diffuseLightColor * max(dot(N, L), 0.0);
	vec3 specularColor = 0.5 * specularLightColor * pow(max(dot(V, R), 0.0), p);

	FragColor = (u_ambiantLightColor + diffuseColor + specularColor) * u_objectColor;
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