#version 400

// from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/

// Ouput data
layout(location = 0) out float fragmentDepth;
 
void main(){
    // Not really needed, OpenGL does it anyway ??
    fragmentDepth = gl_FragCoord.z;
}