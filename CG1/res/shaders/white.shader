#shader VERTEX triangle
#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * position;
};

#shader FRAGMENT color
#version 330 core
layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
};