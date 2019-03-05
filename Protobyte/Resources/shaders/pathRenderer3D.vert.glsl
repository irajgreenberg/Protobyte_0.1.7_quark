#version 430 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 pathColor;
 

// coord transforms
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;

out vec4 pathCol;


void main(void)
{
    // pass out color to fragment shader
	pathCol = pathColor;

    // Calculate vertex position in view space.
    vec4 P = modelViewMatrix * vec4(vertexPosition, 1.0);


    // Calculate clip coordinates by multiplying our view position by
    // the projection matrix.
    gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}