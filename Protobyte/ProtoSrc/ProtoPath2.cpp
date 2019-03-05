/*!  \brief  ProtoPath2.cpp: Class for drawing methods, moveTo, lineTo, curveTo...
ProtoPath2.cpp
Protobyte Library v02

Created by Ira on 1/2/15.
Copyright (c) 2015 Ira Greenberg. All rights reserved.

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

#include "ProtoPath2.h"
// forward declared in .h to avoid circular dependency
#include "ProtoBaseApp.h"

using namespace ijg;


ProtoPath2::ProtoPath2() {
}

ProtoPath2::ProtoPath2(ProtoBaseApp* baseApp){
	this->baseApp = baseApp;
	// default style state
	fillCol = Col4f(1);
	strokeCol = Col4f(0);
	isFill = true;
	isStroke = true;
}

ProtoPath2::ProtoPath2(const std::vector<Vec2f>& path) {
}

ProtoPath2::ProtoPath2(const std::vector<Vec2f>& path, const std::vector<Col4f>& cols) {
}

ProtoPath2::~ProtoPath2() {
}


//void ProtoPath2::setShader(const ProtoShader* shader) {
//	this->shader = shader;
//}

void ProtoPath2::init() {


	// 1. Create and bind VAO
	//GLuint vaoID;
	glGenVertexArrays(1, &vaoPathID); // Create VAO
	glBindVertexArray(vaoPathID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	//GLuint vboID;
	glGenBuffers(1, &vboPathID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboPathID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (GLfloat)* pathPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STATIC_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrims[0]); // upload the data

	// indices data
	//GLuint indexVboID;
	glGenBuffers(1, &indexVboPathID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboPathID); // Bind element buffer

	//int indsDataSize = pathDetail * 3 * sizeof(GL_UNSIGNED_INT);
	int indsDataSize = 1 * 3 * sizeof(GL_UNSIGNED_INT); // pathDetail or 1 in this case just a placeholder for now

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &pathInds[0]); // upload data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// draw ellipse
	glBindBuffer(GL_ARRAY_BUFFER, vboPathID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboPathID);

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(2); // color
	// stride is 7: pos(3) + col(4)
	// (x, y, z, r, g, b, a)
	int stride = 7;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof (GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride * sizeof (GLfloat), BUFFER_OFFSET(12)); // col

	//glDisable(GL_LIGHTING);
	//glDrawElements(GL_TRIANGLES, ellipseDetail * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Disable buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//pathPrims.clear();
	//pathInds.clear();

	glLineWidth(2.5);
}

void ProtoPath2::moveTo(float x, float y) {
	pathVecs.clear();
	pathVecs.push_back(Vec2f(x, y));
}
void ProtoPath2::moveTo(const Vec2f& v){
	pathVecs.clear(); 
	pathVecs.push_back(v);

}
void ProtoPath2::lineTo(float x, float y){
	pathVecs.push_back(Vec2f(x, y));
}
void ProtoPath2::lineTo(const Vec2f& v){
	pathVecs.push_back(v);
}
void ProtoPath2::curveTo(float x, float y){

}
void ProtoPath2::curveTo(const Vec2f& v){

}
void ProtoPath2::end(int pathEndState){

	this->pathEndState = pathEndState;

	// process vertices
	for (int i = 0; i < pathVecs.size(); ++i){
		pathPrims.push_back(pathVecs.at(i).x); // x
		pathPrims.push_back(pathVecs.at(i).y); // y
		pathPrims.push_back(0); // z
		pathPrims.push_back(strokeCol.r); // r
		pathPrims.push_back(strokeCol.g); // g
		pathPrims.push_back(strokeCol.b); // b
		pathPrims.push_back(strokeCol.a); // a
	}

	init();
}

void ProtoPath2::fill(const Col4f& col){
	isFill = true; 
	fillCol = col;

	if (pathVecs.size() > 1){
		for (int i = 0; i < pathPrims.size(); i += 7){
			pathPrims.at(i + 3) = fillCol.r; // r
			pathPrims.at(i + 4) = fillCol.g; // g
			pathPrims.at(i + 5) = fillCol.b; // b
			pathPrims.at(i + 6) = fillCol.a; // a
		}
	}
}

void ProtoPath2::fill(float r, float g, float b, float a){
	fill(Col4f(r, g, b, a));
}

void ProtoPath2::fill(float r, float g, float b){
	fill(Col4f(r, g, b, 1.0));
}

void ProtoPath2::fill(const std::vector<Col4f>& cols){
	fillCols = cols;
}

void ProtoPath2::stroke(const Col4f& col){
	isStroke = true;
	strokeCol = col;

	if (pathVecs.size() > 1){
		for (int i = 0; i < pathPrims.size(); i += 7){
			pathPrims.at(i + 3) = strokeCol.r; // r
			pathPrims.at(i + 4) = strokeCol.g; // g
			pathPrims.at(i + 5) = strokeCol.b; // b
			pathPrims.at(i + 6) = strokeCol.a; // a
		}
	}
}

void ProtoPath2::stroke(float r, float g, float b, float a){
	stroke(Col4f(r, g, b, a));
}

void ProtoPath2::stroke(float r, float g, float b){
	stroke(Col4f(r, g, b, 1.0));
}

void ProtoPath2::stroke(const std::vector<Col4f>& cols) {
	strokeCols = cols;
}

void ProtoPath2::noFill() {
	isFill = false;
}

void ProtoPath2::noStroke() {
	isStroke = false;
}

void ProtoPath2::display() {
	glBindBuffer(GL_ARRAY_BUFFER, vboPathID);
	int vertsDataSize = sizeof (GLfloat)* pathPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrims[0]); // upload the data

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboPathID);
	int indsDataSize = sizeof (int)* pathInds.size();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &pathInds[0]); // upload the data

	baseApp->enable2DRendering();
	glBindVertexArray(vaoPathID);
	//glDrawElements(GL_TRIANGLES, pathInds.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_POLYGON, 0, pathVecs.size());
	baseApp->disable2DRendering();

	// Disable VAO
	glBindVertexArray(0);

	// reenable 3D lighting
	baseApp->disable2DRendering();

	// clean up vectors between each frame
	//pathPrims.clear();
	//pathInds.clear();

}

void ProtoPath2::setBaseApp(ProtoBaseApp* baseApp){
	this->baseApp = baseApp;
}