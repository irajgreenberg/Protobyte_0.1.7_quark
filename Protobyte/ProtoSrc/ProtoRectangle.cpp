/*!  \brief  ProtoRectangle.h: Rectangle implementation
ProtoRectangle.h
Protobyte Library v02

Created by Ira on 6/25/15.
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

#include "ProtoRectangle.h"


namespace ijg {

	std::ostream& operator<<(std::ostream& out, const ProtoRectangle& ProtoRectangle) {
		out << "pos: " << ProtoRectangle.pos << "\n" <<
			"size: " << ProtoRectangle.size << "\n" <<
			"col4: " << ProtoRectangle.col4;
		return out;
	}
}

using namespace ijg;

/*!
* Default Constructor */
ProtoRectangle::ProtoRectangle(){}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(const Vec2f& pos, const Dim2f& size, const ProtoColor4<float>& col4) :
Geom3(Vec3f(pos.x, pos.y, 0), Vec3f(), size, col4) {
	textureScale = Vec2f(1, 1);
	for (int i = 0; i < 4; ++i){
		col4s.push_back(col4);
	}
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(float x, float y, const Dim2f& size, const ProtoColor4<float>& col4) :
Geom3(Vec3f(x, y, 0), Vec3f(), size, col4) {
	textureScale = Vec2f(1, 1);
	for (int i = 0; i < 4; ++i){
		col4s.push_back(col4);
	}
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(const Vec2f& pos, const Dim2f& size, const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale) :
Geom3(Vec3f(pos.x, pos.y, 0), Vec3f(), size, col4, textureImageURL, textureScale) {
	for (int i = 0; i < 4; ++i){
		col4s.push_back(col4);
	}
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(float x, float y, const Dim2f& size, const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale) :
Geom3(Vec3f(x, y, 0), Vec3f(), size, col4, textureImageURL, textureScale) {
	for (int i = 0; i < 4; ++i){
		col4s.push_back(col4);
	}
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(const Vec2f& pos, const Dim2f& size,
	const std::vector<Col4f>& cols4) :
	Geom3(Vec3f(pos.x, pos.y, 0), Vec3f(), size, cols4) {
	textureScale = Vec2f(1, 1);
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(float x, float y, const Dim2f& size,
	const std::vector<Col4f>& cols4) :
	Geom3(Vec3f(x, y, 0), Vec3f(), size, cols4) {
	textureScale = Vec2f(1, 1);
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(const Vec2f& pos, const Dim2f& size, const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale) :
Geom3(Vec3f(pos.x, pos.y, 0), Vec3f(), size, cols4, textureImageURL, textureScale) {
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(float x, float y, const Dim2f& size, const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale) :
Geom3(Vec3f(x, y, 0), Vec3f(), size, cols4, textureImageURL, textureScale) {
	init();
}

// w, h
/*!
* Constructor */
ProtoRectangle::ProtoRectangle(const Vec2f& pos, float w, float h, const ProtoColor4<float>& col4) :
Geom3(Vec3f(pos.x, pos.y, 0), Vec3f(), Dim3f(w, h, 0), col4) {
	textureScale = Vec2f(1, 1);
	for (int i = 0; i < 4; ++i){
		col4s.push_back(col4);
	}
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(float x, float y, float w, float h, const ProtoColor4<float>& col4) :
Geom3(Vec3f(x, y, 0), Vec3f(), Dim3f(w, h, 0), col4) {
	textureScale = Vec2f(1, 1);
	for (int i = 0; i < 4; ++i){
		col4s.push_back(col4);
	}
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(const Vec2f& pos, float w, float h, const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale) :
Geom3(Vec3f(pos.x, pos.y, 0), Vec3f(), Dim3f(w, h, 0), col4, textureImageURL, textureScale) {
	for (int i = 0; i < 4; ++i){
		col4s.push_back(col4);
	}
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(float x, float y, float w, float h, const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale) :
Geom3(Vec3f(x, y, 0), Vec3f(), Dim3f(w, h, 0), col4, textureImageURL, textureScale) {
	for (int i = 0; i < 4; ++i){
		col4s.push_back(col4);
	}
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(const Vec2f& pos, float w, float h,
	const std::vector<Col4f>& cols4) :
	Geom3(Vec3f(pos.x, pos.y, 0), Vec3f(), Dim3f(w, h, 0), cols4) {
	textureScale = Vec2f(1, 1);
	init();
}
/*!
* Constructor */
ProtoRectangle::ProtoRectangle(float x, float y, float w, float h,
	const std::vector<Col4f>& cols4) :
	Geom3(Vec3f(x, y, 0), Vec3f(), Dim3f(w, h, 0), cols4) {
	textureScale = Vec2f(1, 1);
	init();
}

/*!
* Constructor */
ProtoRectangle::ProtoRectangle(const Vec2f& pos, float w, float h, const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale) :
Geom3(Vec3f(pos.x, pos.y, 0), Vec3f(), Dim3f(w, h, 0), cols4, textureImageURL, textureScale) {
	init();
}
/*!
* Constructor */
ProtoRectangle::ProtoRectangle(float x, float y, float w, float h, const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale) :
Geom3(Vec3f(x, y, 0), Vec3f(), Dim3f(w, h, 0), cols4, textureImageURL, textureScale) {
	init();
}


//Uses uuplicate vertices to allow proper texture mapping

void ProtoRectangle::calcVerts() {
	verts.push_back(ProtoVertex3(Vec3f(-.5, .5, 0), col4, Tup2(0, 0)) );
	verts.push_back(ProtoVertex3(Vec3f(-.5, -.5, 0), col4, Tup2(0, 1)));
	verts.push_back(ProtoVertex3(Vec3f(.5, -.5, 0), col4, Tup2(1, 1)));
	verts.push_back(ProtoVertex3(Vec3f(.5, .5, 0), col4, Tup2(1, 0)));
}

void ProtoRectangle::calcInds() {
	inds.push_back(Tup3i(0, 1, 2));
	inds.push_back(Tup3i(0, 2, 3));
}


