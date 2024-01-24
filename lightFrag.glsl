#version 430 core

uniform vec4 lightColor;

out vec4 theColor;

void main()
{
	theColor = lightColor;
}