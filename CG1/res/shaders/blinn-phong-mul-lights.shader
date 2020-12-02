#shader VERTEX triangle
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_mvp;
uniform mat4 u_modelView;
uniform mat3 u_normalMat;

out vec3 Position;
out vec3 Normal;

void main()
{
	Position = vec3(u_modelView * position);
	Normal = normalize(u_normalMat * normal);

	gl_Position = u_mvp * position;
}

#shader FRAGMENT color
#version 330 core
layout(location = 0) out vec4 FragColor;

struct LightInfo {
	vec4 Position;
	vec3 Intensity;
};

uniform LightInfo u_lights[5];

uniform vec3 u_ambiantLightColor;
uniform vec3 u_objectColor;
uniform vec3 u_lightPos;
uniform mat4 u_view;

in vec3 Position;
in vec3 Normal;

float p = 180.0;

void main()
{
	vec3 finalColor = vec3(0.0, 0.0, 0.0);
	vec3 ambiantLightColor = u_lights[0].Intensity * vec3(0.1, 0.1, 0.1);
	vec3 V = normalize(-Position);

	for (int i = 0; i < 5; i++) {
		vec3 L = normalize(vec3(u_view * u_lights[i].Position) - Position);
		vec3 H = V + L;
		vec3 R = reflect(-L, Normal);
		// vec3 H = V + L;

		vec3 diffuseColor = u_lights[i].Intensity * vec3(0.4, 0.4, 0.4) * max(dot(L, Normal), 0.0);
		vec3 specularColor = u_lights[i].Intensity * vec3(0.9, 0.9, 0.9)  * pow(max(dot(V, R), 0.0), p);

		finalColor += diffuseColor + specularColor;
	}

	FragColor = vec4(finalColor + ambiantLightColor, 1.0);
};