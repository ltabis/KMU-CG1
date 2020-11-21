#shader VERTEX triangle
#version 330 core
layout(location = 0) in vec4 position;

out vec3 out_Color;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * position;
	out_Color = vec3(0.4, 0.3, 1.0);
};

#shader FRAGMENT color
#version 330 core
layout(location = 0) out vec4 color;

in vec3 out_Color;

void main()
{
	color = vec4(out_Color, 1.0);
};