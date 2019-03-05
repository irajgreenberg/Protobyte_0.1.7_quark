/*!  \brief  ProtoCylinder.cpp: (add brief description)
 ProtoCylinder.cpp
 Protobyte Library v02

 Created by Ira on 12/23/13.
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

#include "ProtoCylinder.h"

using namespace ijg;

// default cstr
ProtoCylinder::ProtoCylinder() :
	ProtoGeom3(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), "white_tile.jpg", Vec2(1)), detail(12), registration(CENTER) {
	//init();
}

//overloaded cstr's
ProtoCylinder::ProtoCylinder(int detail, Registration reg) :
	ProtoGeom3(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), "white_tile.jpg", Vec2(1)), detail(detail), registration(reg) {
	//setBumpMap("white_tile.jpg");
	init();
}
ProtoCylinder::ProtoCylinder(const Vec3& pos, int detail, Registration reg) :
	ProtoGeom3(pos, Vec3f(), Dim3f(1), Col4f(1), "white_tile.jpg", Vec2(1)), detail(detail), registration(reg) {
	init();
}
ProtoCylinder::ProtoCylinder(const Dim3f& size, int detail, Registration reg) :
	ProtoGeom3(Vec3f(), Vec3f(), size, Col4f(1), "white_tile.jpg", Vec2(1)), detail(detail), registration(reg) {
	init();
}
ProtoCylinder::ProtoCylinder(const Vec3& pos, const Dim3f& size, int detail, Registration reg) :
	ProtoGeom3(pos, Vec3f(), size, Col4f(1), "white_tile.jpg", Vec2(1)), detail(detail), registration(reg) {
	init();
}
ProtoCylinder::ProtoCylinder(int detail, const std::string& textureImageURL, Registration reg) :
	ProtoGeom3(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), textureImageURL, Vec2(1)), detail(detail), registration(reg) {
	init();
}
ProtoCylinder::ProtoCylinder(const Vec3& pos, int detail, const std::string& textureImageURL, Registration reg) :
	ProtoGeom3(pos, Vec3f(), Dim3f(1), Col4f(1), textureImageURL, Vec2(1)), detail(detail), registration(reg) {
	init();
}
ProtoCylinder::ProtoCylinder(const Dim3f& size, int detail, const std::string& textureImageURL, Registration reg) :
	ProtoGeom3(Vec3f(), Vec3f(), size, Col4f(1), textureImageURL, Vec2(1)), detail(detail), registration(reg) {
	init();
}
ProtoCylinder::ProtoCylinder(const Vec3& pos, const Dim3f& size, int detail, const std::string& textureImageURL, Registration reg) :
	ProtoGeom3(pos, Vec3f(), size, Col4f(1), textureImageURL, Vec2(1)), detail(detail), registration(reg) {
	init();
}

ProtoCylinder::ProtoCylinder(const Vec3& pos, const Dim3f& size, int detail, const Col4f& col, const std::string& textureImageURL, Registration reg) :
	ProtoGeom3(pos, Vec3f(), size, Col4f(col), textureImageURL, Vec2(1)), detail(detail), registration(reg) {
	init();
}



void ProtoCylinder::calcVerts() {
	float theta = 0.0f;
	// NOTE:: packs terminals in verts at 0, 1 verts locations
	float x = 0;
	float y = 0;
	float z = 0;


	float len = size.w*PI;

	switch (registration) {
	case TOP:
		// to do
		break;
	case CENTER:
		/*
		| |
		|.|
		| |
		*/
		// top center point
		verts.push_back(ProtoVertex3(Vec3f(0, size.h / 2.0f, 0), col4, ProtoTuple2f(0, 0)));

		// bottem center point
		verts.push_back(ProtoVertex3(Vec3f(0, -size.h / 2.0f, 0), col4, ProtoTuple2f(0, 0)));

		// BEGIN edge points

		// top edge points
		for (int i = 0; i <= detail; ++i) {
			z = cos(theta)*size.d;
			y = size.h / 2.0f;
			x = sin(theta)*size.w;
			verts.push_back(ProtoVertex3(Vec3f(x, y, z), col4, ProtoTuple2f((1.0 / detail*i) * 4, .5f * 3)));
			theta -= TWO_PI / (detail);
		}


		// bottem edge points
		theta = 0; // reset theta
		for (int i = 0; i <= detail; ++i) {
			z = cos(theta)*size.d;
			y = -size.h / 2.0f;
			x = sin(theta)*size.w;
			verts.push_back(ProtoVertex3(Vec3f(x, y, z), col4, ProtoTuple2f((1.0 / detail*i) * 4, -.5f * 3)));
			theta -= TWO_PI / (detail);
		}

	case BOTTEM:
		// to do

		break;

	default:
		/*
		| |
		|.|
		| |
		*/
		// top center point
		verts.push_back(ProtoVertex3(Vec3f(0, size.h / 2.0f, 0), col4, ProtoTuple2f(0, 0)));

		// bottem center point
		verts.push_back(ProtoVertex3(Vec3f(0, -size.h / 2.0f, 0), col4, ProtoTuple2f(0, 0)));

		// BEGIN edge points

		// top edge points
		for (int i = 0; i <= detail; ++i) {
			z = cos(theta)*size.d;
			y = size.h / 2.0f;
			x = sin(theta)*size.w;
			verts.push_back(ProtoVertex3(Vec3f(x, y, z), col4, ProtoTuple2f((1.0 / detail*i) * 4, .5f * 3)));
			theta -= TWO_PI / (detail);
		}


		// bottem edge points
		theta = 0; // reset theta
		for (int i = 0; i <= detail; ++i) {
			z = cos(theta)*size.d;
			y = -size.h / 2.0f;
			x = sin(theta)*size.w;
			verts.push_back(ProtoVertex3(Vec3f(x, y, z), col4, ProtoTuple2f((1.0 / detail*i) * 4, -.5f * 3)));
			theta -= TWO_PI / (detail);
		}
	}

}


void ProtoCylinder::calcInds() {
	// top cap
	for (int i = 0; i < detail; ++i) {
		if (i < detail - 1) {
			//inds.push_back(ProtoTuple3i(i + 2, 0, i + 3));
		}
		else {
			//inds.push_back(ProtoTuple3i(i + 2, 0, 2));
		}
	}

	//bottem cap
	for (int i = 0; i < detail; ++i) {
		if (i < detail - 1) {
			//inds.push_back(ProtoTuple3i(detail + i + 2, 1, detail + i + 3));
		}
		else {
			//inds.push_back(ProtoTuple3i(detail + i + 2, 1, detail + 2));
		}
	}

	//body
	// Don't close
	//int end = detail * 2 + 2 - 1;
	for (int i = 0; i <= detail; ++i) {
		int j = i + 2;

		if (i < detail) {
			inds.push_back(ProtoTuple3i(j, j + 1, j + detail+1)); // (j, j+1, j+detail));
			inds.push_back(ProtoTuple3i(j + 1, j + detail + 2, j + detail+1)); // (j+1, j+detail+1, j+detail));
		}
	}
}
