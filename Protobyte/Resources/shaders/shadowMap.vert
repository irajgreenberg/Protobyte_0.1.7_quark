#version 400

// from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/
// attibutes in memory
layout (location = 0) in vec3 vertexPosition;

// view from lights perspective 
uniform mat4 shadowMapMVPMatrix;

void main(){
	gl_Position =  shadowMapMVPMatrix * vec4(vertexPosition,1);
}