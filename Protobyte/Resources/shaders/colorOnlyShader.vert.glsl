#version 430 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec4 vertexColor;

out vec4 col;

// coord transforms
uniform mat4 modelViewProjectionMatrix;


void main(void)
{
	col = vertexColor;
    gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}
