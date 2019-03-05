/*!  \brief  ProtoPath3.h: General path (open or closed) with no guarantee of convexity
Used interanlly by procedural convenience drawing functions.

ProtoPath3.h
Protobyte Library v02

Created by Ira on 9/10/14.
Copyright (c) 2013 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include "ProtoPath3.h"


namespace ijg {

	std::ostream& operator<<(std::ostream& out, const ProtoPath3& path) {
		out << "path size: " << path.pathVecs.size();
		return out;
	}
}


using namespace ijg;

ProtoPath3::ProtoPath3() {
}

ProtoPath3::ProtoPath3(const Col4f& col4, const std::vector<Vec3f>& pathVecs):
col4(col4), pathVecs(pathVecs)
{
	init();
}


void ProtoPath3::init() {
	calcPrimitives();

	// set default material settings
	//materials = Material(Col4f(.7f, .7f, .7f, 1.0f), Col4f(.125f, .125f, .125f, 1.0f), Col4f(.2, .2, .2, 1.0f), Col4f(.0f, .0f, .0f, 1.0f), 8);

	// set material memory locations for GPU
	colorLoc_U = glGetUniformLocation(ProtoShader::getID_2(), "pathColor");


//
//	// initialize glew for Windows
//#if defined(_WIN32) || defined(__linux__)
//	GLenum err = glewInit();
//	if (GLEW_OK != err)
//	{
//		/* Problem: glewInit failed, something is seriously wrong. */
//		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//	}
//	//fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
//#endif

	// Special thanks to:
	// http://stackoverflow.com/questions/8704801/glvertexattribpointer-clarification
	// http://www.swiftless.com/tutorials/opengl4/4-opengl-4-vao.html
	/***************************************/
	/*       Setup VAO/VBO buffers         */
	/***************************************/
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoID); // Create VAO
	glBindVertexArray(vaoID); // Bind VAO (making it active)
	//2. Create and bind VBO
	// a. Vertex attributes
	glGenBuffers(1, &vboID); // Create VBO ID
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind vertex attributes VBO
	int vertsDataSize = sizeof (float)* static_cast<int>(interleavedPrims.size());
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW); // allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data

	// b. Indices  uses ELEMENT_ARRAY_BUFFER
	glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind indices VBO
	int indsDataSize = static_cast<int>(inds.size()) * 3 * sizeof (GL_UNSIGNED_INT);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &indPrims[0]); // upload the data

	for (int i = 0; i < 2; i++) {
		glEnableVertexAttribArray(i);
	}
	// STRIDE is 7: pos(3) + col(4)
	// (x, y, z, r, g, b, a)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(12)); // col

	// Disable VAO
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

void ProtoPath3::calcPrimitives() {
	if (interleavedPrims.size()>0) interleavedPrims.clear();
	if (indPrims.size()>0) indPrims.clear();

	for (int i = 0; i < pathVecs.size(); i++) {

		// fill interleaved primitive arrays
		interleavedPrims.push_back(pathVecs.at(i).x);
		interleavedPrims.push_back(pathVecs.at(i).y);
		interleavedPrims.push_back(pathVecs.at(i).z);

		interleavedPrims.push_back(col4.getR());
		interleavedPrims.push_back(col4.getG());
		interleavedPrims.push_back(col4.getB());
		interleavedPrims.push_back(col4.getA());

		indPrims.push_back(i);

	}
	//// explode inds arrays to primitives
	//for (int i = 0, j = 0; i < inds.size(); i++) {
	//	indPrims.push_back(inds.at(i).elem0);
	//	indPrims.push_back(inds.at(i).elem1);
	//	indPrims.push_back(inds.at(i).elem2);
	//}
}



void ProtoPath3::display(RenderMode render, float pointSize) {


	// update material values in GPU
	glUniform4fv(colorLoc_U, 1, &col4.r);



	switch (render) {
	case POINTS:
		glPointSize(pointSize);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;

	case WIREFRAME:
		glLineWidth(pointSize);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	default:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}

	//sortFaces();
	/* NOTE:: sorting here is not solving self-overlap highlighting with alpha
	possible solution will be doing manual rotations on geometry
	(as coampdre to modelview matrix transformation) and then sorting faces.
	* See note aovbe above delegating this to a world type class.*/


	// VAO manages VBO's
	glBindVertexArray(vaoID);
	if (render == POINTS) {
		glDrawElements(GL_POINTS, static_cast<int>(indPrims.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	}
	else {
		glDrawElements(GL_LINE_STRIP, static_cast<int>(indPrims.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	}
	glBindVertexArray(0);

}

//void ProtoPath3::updateColorBuffer(){
//	glBindBuffer(GL_ARRAY_BUFFER, vboID);
//	//trace("col4s.size() =", col4s.size());
//	//trace("interleavedPrims.size()/12 =", interleavedPrims.size() / 12);
//	for (int i = 0, colCounter = 0; i < interleavedPrims.size(); i += STRIDE) {// transform verts
//		// NOTE:: this needs work!!!
//		if (col4s.size()>0){
//			interleavedPrims.at(i + 6) = col4s.at(colCounter).getR();
//			interleavedPrims.at(i + 7) = col4s.at(colCounter).getG();
//			interleavedPrims.at(i + 8) = col4s.at(colCounter).getB();
//			interleavedPrims.at(i + 9) = col4s.at(colCounter).getA();
//		}
//		else {
//			interleavedPrims.at(i + 6) = col4.getR();
//			interleavedPrims.at(i + 7) = col4.getG();
//			interleavedPrims.at(i + 8) = col4.getB();
//			interleavedPrims.at(i + 9) = col4.getA();
//		}
//
//	}
//	int vertsDataSize = sizeof (float)*interleavedPrims.size();
//	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}



