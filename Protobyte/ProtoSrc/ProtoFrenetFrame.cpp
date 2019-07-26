/*!  \brief  ProtoFrenetFrame.cpp: Frenet frame class for parallel transport correction
 ProtoFrenetFrame.cpp
 Protobyte Library v02

 Created by Ira on 7/23/13.
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
 This class is templated to allow for varied single collection types
 This class is part of the group common (update)
 \sa NO LINK
 */


#include "ProtoFrenetFrame.h"
#include <iostream>



namespace ijg {

	std::ostream& operator<<(std::ostream& out, const ProtoFrenetFrame& frame) {
		std::cout << "T = " << frame.getT() << ", B = " << frame.getB() << ", N = " << frame.getN();
		return out;
	}
}

using namespace ijg;

ProtoFrenetFrame::ProtoFrenetFrame() {
}

ProtoFrenetFrame::ProtoFrenetFrame(const Vec3f& v1, const Vec3f& T, const Vec3f& N, const Vec3f& B) : v1(v1) {
	this->TNB[0] = T;
	this->TNB[1] = N;
	this->TNB[2] = B;

	initBuffers();
}

//ProtoFrenetFrame::ProtoFrenetFrame(const Vec3f& v1, const Vec3f& T, const Vec3f& N, const Vec3f& B): {
//	this->TNB[0] = TNB[0];
//	this->TNB[1] = TNB[1];
//	this->TNB[2] = TNB[2];
//	this->v1 = v1;
//
//	initBuffers();
//}

//ProtoFrenetFrame::ProtoFrenetFrame(const Vec3f& T, const Vec3f& N, const Vec3f& B) {
//	this->TNB[0] = T;
//	this->TNB[1] = N;
//	this->TNB[2] = B;
//}


ProtoFrenetFrame::ProtoFrenetFrame(Vec3f v0, Vec3f v1, Vec3f v2) :
	v0(v0), v1(v1), v2(v2) {
	init();

	initBuffers();
}

void ProtoFrenetFrame::init() {
	// calulate frame and define vector TNB

	// Used for 1st deriviatve 
	Vec3f vel = v1 - v0;
	//trace("vel = ", vel);
	vel.normalize();

	TNB.resize(3);

	// Used for 2nd deriviatve to calculate Tangent vector
	TNB.at(0) = v2 - v0;
	TNB.at(0).normalize();

	// (v' x v'')cross product to calculate Binormal vector
	TNB.at(2) = TNB.at(0).cross(vel);
	TNB.at(2).normalize();


	// (T x B)cross product to calculate Normal vector
	TNB.at(1) = TNB.at(2).cross(TNB.at(0));
	TNB.at(1).normalize();
}

void ProtoFrenetFrame::initBuffers() {
	// clear junk out of FrentFrameprimitives
	if (frenetPrims.size()>0) frenetPrims.clear();

	// 3 axes to draw in each frame, with 2 points each axis(terminials)
	// Also need to include 4 color complenents
	for (int i = 0; i < 3 * 2 * stride; i++) {
		frenetPrims.push_back(0.0f);
	}
	//trace("frenetPrims. length =", frenetPrims.size());

	// prepare shader handles to verts data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoFrameID); // Create VAO
	glBindVertexArray(vaoFrameID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	glGenBuffers(1, &vboFrameID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboFrameID); // Bind the buffer (vertex array data)
	int vertsDataSize = 0;// sizeof (GLfloat)* pathPrims.size();
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);// allocate space
	//glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrims[0]); // upload the data

	// fill state is true - need to create this
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(2); // color

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), BUFFER_OFFSET(12)); // col

	// Disable buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// used to disable/enable lighting in shader
	// passed to shader in display functions
	lightRenderingFactors_U = glGetUniformLocation(ProtoShader::getID_2(), "lightRenderingFactors");
}

void ProtoFrenetFrame::display(float length, float strokeWeight, Col4f TCol, Col4f NCol, Col4f BCol) {
	//frenetPrims.at(0) = (v1.x);
	//frenetPrims.at(1) = (v1.y);
	//frenetPrims.at(2) = (v1.z);
	//frenetPrims.at(3) = TCol.r;
	//frenetPrims.at(4) = TCol.g;
	//frenetPrims.at(5) = TCol.b;
	//frenetPrims.at(6) = TCol.a;

	//frenetPrims.at(7) = (v1.x + TNB.at(0).x * length);
	//frenetPrims.at(8) = (v1.y + TNB.at(0).y * length);
	//frenetPrims.at(9) = (v1.z + TNB.at(0).z * length);
	//frenetPrims.at(10) = TCol.r;
	//frenetPrims.at(11) = TCol.g;
	//frenetPrims.at(12) = TCol.b;
	//frenetPrims.at(13) = TCol.a;

	//frenetPrims.at(14) = (v1.x);
	//frenetPrims.at(15) = (v1.y);
	//frenetPrims.at(16) = (v1.z);
	//frenetPrims.at(17) = NCol.r;
	//frenetPrims.at(18) = NCol.g;
	//frenetPrims.at(19) = NCol.b;
	//frenetPrims.at(20) = NCol.a;

	//frenetPrims.at(21) = (v1.x + TNB.at(1).x * length);
	//frenetPrims.at(22) = (v1.y + TNB.at(1).y * length);
	//frenetPrims.at(23) = (v1.z + TNB.at(1).z * length);
	//frenetPrims.at(24) = NCol.r;
	//frenetPrims.at(25) = NCol.g;
	//frenetPrims.at(26) = NCol.b;
	//frenetPrims.at(27) = NCol.a;


	//populate Frenet Frame prims
	Col4f cols[] = { TCol, NCol, BCol };
	for (int i = 0; i < 3; i++) {
		// draw frenet frame axis from each knot
		frenetPrims.at(14 * i) = (v1.x);
		frenetPrims.at(14 * i + 1) = (v1.y);
		frenetPrims.at(14 * i + 2) = (v1.z);
		frenetPrims.at(14 * i + 3) = (cols[i].r);
		frenetPrims.at(14 * i + 4) = (cols[i].g);
		frenetPrims.at(14 * i + 5) = (cols[i].b);
		frenetPrims.at(14 * i + 6) = (cols[i].a);

		frenetPrims.at(14 * i + 7) = (v1.x + TNB.at(i).x * length);
		frenetPrims.at(14 * i + 8) = (v1.y + TNB.at(i).y * length);
		frenetPrims.at(14 * i + 9) = (v1.z + TNB.at(i).z * length);
		frenetPrims.at(14 * i + 10) = (cols[i].r);
		frenetPrims.at(14 * i + 11) = (cols[i].g);
		frenetPrims.at(14 * i + 12) = (cols[i].b);
		frenetPrims.at(14 * i + 13) = (cols[i].a);
	}

	//enable2DRendering();
	glBindVertexArray(vaoFrameID);
	// NOTE::this may not be most efficient - eventually refactor
	glBindBuffer(GL_ARRAY_BUFFER, vboFrameID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * frenetPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &frenetPrims[0]); // upload the data
	glLineWidth(strokeWeight);
	// turn off lighting
	Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_LINES, 0, frenetPrims.size() / stride);

	//turn on lighting
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	//disable2DRendering();

	// Disable VAO
	glBindVertexArray(0);
}