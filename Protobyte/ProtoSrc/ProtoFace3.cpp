/*!  \brief  ProtoFace3.cpp: 3 sided polygon class
 ProtoFace3.cpp
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
 This class is part of the group common (update)
 \sa NO LINK
 */

#include "ProtoFace3.h"


namespace ijg {
	// overloaded << operator for outputting field values in objects

	std::ostream& operator<<(std::ostream& output, const ProtoFace3& face3) {
		output << "V0: " << *(face3.v0_p) << "\nV1: " << *(face3.v1_p) << "\nV2: " << *(face3.v2_p);
		return output;
	}
}

using namespace ijg;

// default cstr
ProtoFace3::ProtoFace3() {}

// overloaded cstr
ProtoFace3::ProtoFace3(ProtoVertex3* v0_p, ProtoVertex3* v1_p, ProtoVertex3* v2_p) {
	// get vertex addresses
	this->v0_p = v0_p;
	this->v1_p = v1_p;
	this->v2_p = v2_p;

	init();
}

void ProtoFace3::init() {
	// initialize centroid and normal
	calcCentroid();
	calcNorm();

	// store positional data by value
	v0 = v0_p->pos;
	v1 = v1_p->pos;
	v2 = v2_p->pos;
}

void ProtoFace3::display() {
	// flat shading
	/*glBegin(GL_TRIANGLES);
	glColor3f(.2, .3, 1.0); // for face normals
	glNormal3f(norm.x, norm.y, norm.z);
	glProtoVertex33f(v0_p->pos.x, v0_p->pos.y, v0_p->pos.z);
	glColor3f(.2, .3, 1.0);
	//glNormal3f(v1_p->getNormal().x, v1_p->getNormal().y, v1_p->getNormal().z);
	glProtoVertex33f(v1_p->pos.x, v1_p->pos.y, v1_p->pos.z);
	glColor3f(.2, .3, 1.0);
	//glNormal3f(v2_p->getNormal().x, v2_p->getNormal().y, v2_p->getNormal().z);
	glProtoVertex33f(v2_p->pos.x, v2_p->pos.y, v2_p->pos.z);
	glEnd();*/


	// smooth shading
	glBegin(GL_TRIANGLES);
	glColor3f(.2, .3, 1.0); // for face normals
	glNormal3f(v0_p->getNormal().x, v0_p->getNormal().y, v0_p->getNormal().z);
	glVertex3f(v0_p->pos.x, v0_p->pos.y, v0_p->pos.z);
	glColor3f(.2, .3, 1.0);
	glNormal3f(v1_p->getNormal().x, v1_p->getNormal().y, v1_p->getNormal().z);
	glVertex3f(v1_p->pos.x, v1_p->pos.y, v1_p->pos.z);
	glColor3f(.2, .3, 1.0);
	glNormal3f(v2_p->getNormal().x, v2_p->getNormal().y, v2_p->getNormal().z);
	glVertex3f(v2_p->pos.x, v2_p->pos.y, v2_p->pos.z);
	glEnd();
}

void ProtoFace3::calcCentroid() {
	//std::cout << "centroid before = " << centroid << std::endl;
	centroid += v0_p->pos;
	centroid += v1_p->pos;
	centroid += v2_p->pos;
	centroid /= 3;
	//std::cout << "centroid after = " << centroid << std::endl;
}

void ProtoFace3::calcNorm() {
	Vec3f v0 = v1_p->pos - v0_p->pos;
	Vec3f v1 = v2_p->pos - v0_p->pos;
	norm = v0.cross(v1); //normal points to camera
	//norm = v1.cross(v0);
	norm.normalize();
	//trace(*this);
	//trace("norm =", norm);
}

// calculates tangent for bump mapping based
// on normal and uv coords
Vec3f ProtoFace3::getTangentBM(){

	Vec3f v0 = v1_p->pos - v0_p->pos;
	Vec3f v1 = v2_p->pos - v0_p->pos;

	Vec2f uv0_p = Vec2f(v0_p->getUV().elem0, v0_p->getUV().elem1);
	Vec2f uv1_p = Vec2f(v1_p->getUV().elem0, v1_p->getUV().elem1);
	Vec2f uv2_p = Vec2f(v2_p->getUV().elem0, v2_p->getUV().elem1);

	Vec2f uv0 = uv1_p - uv0_p;
	Vec2f uv1 = uv2_p - uv0_p;


	float r = 1.0f / (uv0.x * uv1.y - uv0.y *uv1.x);
	Vec3f tangent = (v0 * uv1.y - v1 * uv0.y)*r;
	//trace("tangent", tangent);
	return tangent;
}


const ProtoVertex3* ProtoFace3::operator[](int index) {
	switch (index) {
	case 0:
		return v0_p;
		break;
	case 1:
		return v1_p;
		break;
	case 2:
		return v2_p;
		break;
	}
	return v0_p;
}


