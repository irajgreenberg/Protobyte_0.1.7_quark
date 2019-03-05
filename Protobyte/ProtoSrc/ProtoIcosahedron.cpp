/*!  \brief  ProtoIcosahedron.cpp: Icosahedron implementation
ProtoIcosahedron.h
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

#include "ProtoIcosahedron.h"


using namespace ijg;

ProtoIcosahedron::ProtoIcosahedron() {
}

ProtoIcosahedron::ProtoIcosahedron(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4) :
	ProtoGeom3(pos, rot, size, col4) {
	init();
}

ProtoIcosahedron::ProtoIcosahedron(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size,
	const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale) :
	ProtoGeom3(pos, rot, size, col4, textureImageURL, textureScale) {
	init();
}


void ProtoIcosahedron::calcVerts() {

	// vertex position and color information for icosahedron
	float vals[] = { 
			-0.26286500f, 0.0000000f, 0.42532500f,
			0.26286500f, 0.0000000f, 0.42532500f,
			-0.26286500f, 0.0000000f, -0.42532500f,
			0.26286500f, 0.0000000f, -0.42532500f,
			0.0000000f, 0.42532500f, 0.26286500f,
			0.0000000f, 0.42532500f, -0.26286500f,
			0.0000000f, -0.42532500f, 0.26286500f,
			0.0000000f, -0.42532500f, -0.26286500f,
			0.42532500f, 0.26286500f, 0.0000000f,
			-0.42532500f, 0.26286500f, 0.0000000f,
			0.42532500f, -0.26286500f, 0.0000000f,
			-0.42532500f, -0.26286500f, 0.0000000f
	};


	for (int i = 0; i < 36; i+=3) {
		verts.push_back(ProtoVertex3(Vec3f(vals[i+2]*size.w / 2, vals[i+1] * size.h / 2, vals[i] * size.d / 2), Col4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(vals[i + 1]/ vals[i + 2], vals[i]/ vals[i + 2])));
	}
}


void ProtoIcosahedron::calcInds() {
	inds.push_back(ProtoTuple3i(0, 6, 1));
	inds.push_back(ProtoTuple3i(0, 11, 6));
	inds.push_back(ProtoTuple3i(1, 4, 0));
	inds.push_back(ProtoTuple3i(1, 8, 4));
	inds.push_back(ProtoTuple3i(1, 10, 8));
	inds.push_back(ProtoTuple3i(2, 5, 3));
	inds.push_back(ProtoTuple3i(2, 9, 5));
	inds.push_back(ProtoTuple3i(2, 11, 9));
	inds.push_back(ProtoTuple3i(3, 7, 2));
	inds.push_back(ProtoTuple3i(3, 10, 7));
	inds.push_back(ProtoTuple3i(4, 8, 5));
	inds.push_back(ProtoTuple3i(4, 9, 0));
	inds.push_back(ProtoTuple3i(5, 8, 3));
	inds.push_back(ProtoTuple3i(5, 9, 4));
	inds.push_back(ProtoTuple3i(6, 10, 1));
	inds.push_back(ProtoTuple3i(6, 11, 7));
	inds.push_back(ProtoTuple3i(7, 10, 6));
	inds.push_back(ProtoTuple3i(7, 11, 2));
	inds.push_back(ProtoTuple3i(8, 10, 3));
	inds.push_back(ProtoTuple3i(9, 11, 0));
}