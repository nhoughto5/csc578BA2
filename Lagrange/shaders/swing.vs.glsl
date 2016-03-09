#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColour;
out vec3 colour;
void main()
{
	gl_Position = vec4(vPosition, 1);
	colour = vColour;
}