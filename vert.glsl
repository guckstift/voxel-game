#version 330 core

in vec2 vert_pos;
out vec4 vert_color;

void main()
{
	gl_Position = vec4(vert_pos, 0, 1);
	vert_color = vec4(0, 1, 0, 1);
}

