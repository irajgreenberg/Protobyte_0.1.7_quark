
/*!  \brief  ProtoTessellator.h: Basedon GLUTessellator
ProtoTessellator.h
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

Based on tutorials:
http://www.songho.ca/opengl/gl_tessellation.html
// calss design
http://www.flipcode.com/archives/Polygon_Tessellation_In_OpenGL.shtml

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#ifndef PROTO_TESSELLATOR_H
#define	PROTO_TESSELLATOR_H

#include <vector>
#include <iostream>

//#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
//#define GLEW_STATIC
//#include <GL/glew.h>
//#endif

#include "glad/glad.h"

// from OF documentation
// OSX link with " " instead of < > to avoid putting in defualt include path
#if defined(_WIN32) || defined(_WIN64)
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#else
#include "GLFW/glfw3.h"
#endif

#ifndef CALLBACK
#define CALLBACK
#endif


class ProtoTessellator {

public:
	ProtoTessellator();
	virtual ~ProtoTessellator();

	int init();
	void setWindingRule(GLenum windingRule);
	void beginPolygon();
	void beginContour();
	void countourVertex(std::vector<GLdouble> data);
	void addContourVertex(GLdouble obj_data[][6], int num_vertices);
	//void countourVertex(GLdouble data[][7], int vertexCount);
	void endContour();
	void endPolygon();
	void end();

protected:
	GLUtesselator* tesselator;

	static void CALLBACK vertexCallback(GLvoid *vertex);
	static void CALLBACK combineCallback(GLdouble coords[3], GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut);
	static void CALLBACK tesellationError(GLenum errorCode);
	static void CALLBACK testMeBegin(GLenum triangleMode);
	static void CALLBACK testMeEnd();


	
};

#endif	// PROTO_TESSELLATOR
