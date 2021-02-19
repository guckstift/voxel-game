#version 330 core

uniform mat4 proj;
uniform mat4 view;
in vec2 vert_pos;
out vec4 vert_color;

void main()
{
	gl_Position = proj * view * vec4(vert_pos, 0, 1);
	vert_color = vec4(0, 1, 0, 1);
}

