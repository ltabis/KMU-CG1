#shader VERTEX triangle_vertex
#version 330 core
// location = 0 : glVertexAttribPointer(0
// opengl will translate the attribute (vec2) to a vec4.
layout(location = 0) in vec4 position;
void main()
{
   gl_Position = position;
};

#shader FRAGMENT     red
#version 330 core
layout(location = 0) out vec4 color;
void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
};

#shader FRAGMENT    green
#version 330 core
layout(location = 0) out vec4 color;
void main()
{
	color = vec4(0.0, 1.0, 0.0, 1.0);
};

#shader FRAGMENT    blue
#version 330 core
layout(location = 0) out vec4 color;
void main()
{
	color = vec4(0.0, 0.0, 1.0, 1.0);
};