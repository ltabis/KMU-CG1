#shader VERTEX triangle
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
out vec3 out_Color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view  * u_model * position;
	out_Color = color;
};

#shader FRAGMENT color
#version 330 core
layout(location = 0) out vec4 color;

in vec3 out_Color;

void main()
{
	color = vec4(out_Color, 1.0);
};