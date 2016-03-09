#version 330 core
in vec3 colour;
out vec4 fColor;

void main()
{
	fColor = vec4(colour, 1);
}