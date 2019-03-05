/*!  \brief  ProtoPlane.cpp: Simple plane
 ProtoPlane.cpp
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

#include "ProtoPlane.h"
#include "ProtoMath.h"

namespace ijg {

    std::ostream& operator<<(std::ostream& out, const ProtoPlane& plane) {
        out << "Columns: " << plane.columns << ", rows: " << plane.rows <<
			", size.w: " << plane.size.w << ", size.h: " << plane.size.h << ", size.d: " << plane.size.d;
		return out;
    }
}


using namespace ijg;

ProtoPlane::ProtoPlane() {
}

ProtoPlane::ProtoPlane(const Vec3f& pos, const Vec3f& rot, const Dim2f& size,
	const Col4f& col4, int rows, int columns) : Geom3(pos, rot, Dim3f(size.w, 0, size.h), col4), rows(rows), columns(columns)
{
	init();
}


ProtoPlane::ProtoPlane(const Vec3f& pos, const Vec3f& rot, const Dim2f& size,
	const Col4f& col4, int rows, int columns, const std::string& textureImageURL, const Vec2f& textureScale) :
	Geom3(pos, rot, Dim3f(size.w, 0, size.h), col4, textureImageURL, textureScale), rows(rows), columns(columns)
{
	init();
}

ProtoPlane::ProtoPlane(const Vec3f& pos, const Vec3f& rot, const Dim2f& size,
	const Col4f& col4, int rows, int columns, const std::vector<std::string>& textureImageURLs, const Vec2f& textureScale) :
	Geom3(pos, rot, Dim3f(size.w, 0, size.h), col4, textureImageURLs, textureScale), rows(rows), columns(columns)
{
	init();
}
void ProtoPlane::calcVerts() {
	verts.push_back(ProtoVertex3(Vec3f(-.5f, .5f, 0), col4, Tup2f(0, 0))); // LB
	verts.push_back(ProtoVertex3(Vec3f(-.5f, -.5f, 0), col4, Tup2f(0, 1.0f / textureScale.y))); // LF
	verts.push_back(ProtoVertex3(Vec3f(.5f, -.5f, 0), col4, Tup2f(1.0f / textureScale.x, 1.0f / textureScale.y))); // RF
	verts.push_back(ProtoVertex3(Vec3f(.5f, .5f, 0), col4, Tup2f(1.0f / textureScale.x, 0))); // RB
	
}

void ProtoPlane::calcInds() {
	// left face
	inds.push_back(Tup3i(0, 1, 2));
	// right face
	inds.push_back(Tup3i(0, 2, 3));
}



