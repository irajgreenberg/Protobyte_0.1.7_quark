/*!  \brief  ProtoTessellator.cpp: Basedon GLUTessellator
ProtoTessellator.cpp
Protobyte Library v02

Created by Ira on 12/14/14.
Copyright (c) 2014 Ira Greenberg. All rights reserved.

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

#include "ProtoTessellator.h"

std::vector<GLdouble> tessellatedPrims;


ProtoTessellator::ProtoTessellator() {
	init();
}


ProtoTessellator::~ProtoTessellator() {
}


int ProtoTessellator::init() {
	// Create a new tessellation object 
	tesselator = gluNewTess();
	if (!tesselator) return 0;

	// Set callback functions
	gluTessCallback(tesselator, GLU_TESS_VERTEX, (GLvoid(__stdcall *)()) &vertexCallback);
	gluTessCallback(tesselator, GLU_TESS_BEGIN, (GLvoid(__stdcall *)()) &testMeBegin);
	gluTessCallback(tesselator, GLU_TESS_END, (GLvoid(__stdcall *)()) &testMeEnd);
	gluTessCallback(tesselator, GLU_TESS_COMBINE, (GLvoid(__stdcall *)()) &combineCallback);
	gluTessCallback(tesselator, GLU_TESS_ERROR, (GLvoid(__stdcall *)()) &tesellationError);

	//gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
	//gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
	//gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
	//gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);

	//gluTessCallback(tesselator, GLU_TESS_BEGIN, (GLvoid(CALLBACK *)()) ProtoTessellator::begin);
	//gluTessCallback(tesselator, GLU_TESS_EDGE_FLAG, (GLvoid(CALLBACK *)()) ProtoTessellator::edgeFlag);
	//gluTessCallback(tesselator, GLU_TESS_END, (GLvoid(CALLBACK *)()) ProtoTessellator::end);
	//gluTessCallback(tesselator, GLU_TESS_VERTEX_DATA, (GLvoid(CALLBACK *)()) ProtoTessellator::vertexData);
	//gluTessCallback(tesselator, GLU_TESS_COMBINE_DATA, (GLvoid(CALLBACK *)()) ProtoTessellator::combineData);
	//gluTessNormal(tesselator, 0.0, 0.0, 1.0);

	return 1;
}

void ProtoTessellator::setWindingRule(GLenum windingRule) {
	gluTessProperty(tesselator, GLU_TESS_WINDING_RULE, windingRule);
}

void ProtoTessellator::beginPolygon() {
	//tessellatedPrims = tessPrims;
	
	gluTessBeginPolygon(tesselator, NULL);
}

void ProtoTessellator::beginContour() {
	
	gluTessBeginContour(tesselator);
}

void ProtoTessellator::countourVertex(std::vector<GLdouble> data) {
	std::cout << "data.size() = " << data.size() << std::endl;

	//loop through the vertices
	for (int i = 0; i < data.size()-7; i+=7){
		//std::cout << "data = " << data[i] << std::endl;
		GLdouble tempVals[] = { data.at(i), data.at(i + 1), data.at(i + 2), data.at(i + 3), data.at(i + 4), data.at(i + 5), data.at(i + 6) };
		gluTessVertex(tesselator, tempVals, (void*)tempVals); //store the vertex
	}
}

void ProtoTessellator::addContourVertex(GLdouble obj_data[][6], int num_vertices) {
	std::cout << "in addContourVertex"  << std::endl;
	//loop through the vertices
	for (int i = 0; i < num_vertices; ++i){
		gluTessVertex(tesselator, obj_data[i], obj_data[i]); //store the vertex
	}
}

void ProtoTessellator::endContour() {
	gluTessEndContour(tesselator);
}

void ProtoTessellator::endPolygon() {
	gluTessEndPolygon(tesselator);


}



void ProtoTessellator::end() {
	std::cout << "here" << std::endl;
	gluDeleteTess(tesselator);
}



void CALLBACK ProtoTessellator::testMeBegin(GLenum triangleMode) {
	std::cout << "in testMeBegin callback, triangleMode = " << triangleMode << std::endl;
	//std::cout << "in testMeBegin callback" << std::endl;
}



void CALLBACK ProtoTessellator::vertexCallback(GLvoid *vertex) {
	std::cout << "in vertex callback" << std::endl;
}


void CALLBACK ProtoTessellator::testMeEnd() {
	std::cout << "in testMeEnd callback" << std::endl;
}

void CALLBACK ProtoTessellator::tesellationError(GLenum errorCode) {
	const GLubyte *estring;

	estring = gluErrorString(errorCode);
	fprintf(stderr, "Tessellation Error: %s\n", estring);
	//exit(0);
}

//void CALLBACK ProtoTessellator::combineCallback(GLdouble coords[3], void* vertex_data[4], GLfloat weight[4], void** outData) {
//
//	double *vertex;
//
//	vertex = new GLdouble[3];
//
//	vertex[0] = coords[0];
//	vertex[1] = coords[1];
//	vertex[2] = coords[2];
//
//	outData = { 3.4, 5.6, 3.4, 5.6, 3.4, 5.6 };
//
//		//*outData = new double;
//	//*outData = vertex;
//}


void CALLBACK ProtoTessellator::combineCallback(GLdouble coords[3],
	GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut) {
	GLdouble *vertex;
	int i;

	vertex = (GLdouble *)malloc(6 * sizeof(GLdouble));
	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];
	for (i = 3; i < 6; i++)
		vertex[i] = weight[0] * vertex_data[0][i]
		+ weight[1] * vertex_data[1][i]
		+ weight[2] * vertex_data[2][i]
		+ weight[3] * vertex_data[3][i];
	*dataOut = vertex;
}



// calculate new verts whne intersection detected
//void CALLBACK ProtoTessellator::combineCallback(GLdouble coords[3], GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut){
//	GLdouble *vertex;
//	//std::cout << weight[0] << std::endl;
//	//std::cout << weight[1] << std::endl;
//	//std::cout << weight[2] << std::endl;
//	//std::cout << weight[3] << std::endl;
//
//	vertex = (GLdouble *)malloc(6 * sizeof(GLdouble));
//	vertex[0] = coords[0];
//	vertex[1] = coords[1];
//	vertex[2] = coords[2];
//
//	for (int i = 3; i < 6; i++)
//	{
//		vertex[i] = weight[0] * vertex_data[0][i] +
//			weight[1] * vertex_data[1][i] +
//			weight[2] * vertex_data[2][i] +
//			weight[3] * vertex_data[3][i];
//	}
//
//	/* *dataOut = vertex; */
//}

// write to passed in vector for non-immediate drawing using VAO/VBO/GLSL
//void CALLBACK vertexCallback(GLvoid *vertex) {
//	
//	std::cout << "in vertex callback" << std::endl;
//	GLdouble* ptr;
//	//ptr = (GLdouble *)vertex;
//	//glVertex3dv((GLdouble *)ptr);
//	//glColor3dv((GLdouble *)ptr + 3);
//
//	//tessellatedPrims.push_back((GLdouble*)vertex);
//	//tessellatedPrims.push_back((GLdouble*)vertex+1);
//	//tessellatedPrims.push_back((GLdouble*)vertex+2);
//	//tessellatedPrims.push_back((GLdouble*)vertex+3);
//	//tessellatedPrims.push_back((GLdouble*)vertex+4);
//	//tessellatedPrims.push_back((GLdouble*)vertex+5);
//	//tessellatedPrims.push_back((GLdouble*)vertex+6);
//
//}

