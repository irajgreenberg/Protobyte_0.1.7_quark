/*!  \brief  ProtoToroid.cpp: Toroid implementation
 ProtoToroid.h
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

#include "ProtoToroid.h"


using namespace ijg;

ProtoToroid::ProtoToroid():
	ProtoGeom3(Vec3f(), Vec3f(), Dim3f(1, 1, 1), Col4f(0, 0, 0, 1)), ringCount(12), ringDetail(12), ringRadius(1), ringThickness(.65f) {
}

ProtoToroid::ProtoToroid(int ringCount, int ringDetail, float ringRadius, float ringThickness) :
ProtoGeom3(Vec3f(), Vec3f(), Dim3f(1, 1, 1), Col4f(0, 0, 0, 1)), ringCount(ringCount), ringDetail(ringDetail), ringRadius(ringRadius), ringThickness(ringThickness) {
	init();
}

ProtoToroid::ProtoToroid(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, int ringCount, int ringDetail, float ringRadius, float ringThickness):
ProtoGeom3(pos, rot, size, col4), ringCount(ringCount), ringDetail(ringDetail), ringRadius(ringRadius), ringThickness(ringThickness) {
    init();
}

ProtoToroid::ProtoToroid(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4,
	int ringCount, int ringDetail, float ringRadius, float ringThickness, const std::string& textureImageURL, const Vec2f& textureScale) :
ProtoGeom3(pos, rot, size, col4, textureImageURL, textureScale), ringCount(ringCount), ringDetail(ringDetail), ringRadius(ringRadius), ringThickness(ringThickness) {
    init();
}

// TEST to allow declared Toroid var to be used without invoking assignment op
void ProtoToroid::update() {
	if (verts.size() > 1 && inds.size()>1) {
		verts.clear();
		inds.clear();
	}
	init();
}


void ProtoToroid::calcVerts() {
	//  http://www.siggraph.org/education/materials/HyperGraph/mapping/torustx.htm
	// vertices
	float x, y, z, u, v;
	float phi = 0; // ring rotations
	for (int i = 0/*, k=0*/; i < ringCount; i++) {
		float theta = 0;
		// START CALCULATE VERTICES
		for (int j = 0; j < ringDetail; j++) {

			x = (ringRadius + ringThickness*cos(theta))*cos(phi);
			y = ringThickness*sin(theta);
			z = (ringRadius + ringThickness*cos(theta))*sin(phi);

			v = acos(y / ringRadius) / 2 * PI;
			u = (acos(x / (ringRadius + ringThickness*cos(theta)))) * 2 * PI;
		
			// fill vertices with floats
			// Note:: invert scale to make API more intuitive
			verts.push_back(ProtoVertex3(Vec3f(x, y, z),
				ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(v / ringThickness*(1/textureScale.y), u / ringRadius*(1/textureScale.x))));

			theta += float(PI * 2 / ringDetail);
		}
		phi += float(PI * 2 / ringCount);
	}
}


void ProtoToroid::calcInds() {
    // indices
    for (int i = 0; i < ringCount; i++) {
        for (int j = 0; j < ringDetail; j++) {

            int i0 = i * ringDetail + j;
            int i1 = (i + 1) * ringDetail + j;
            int i2 = i * ringDetail + j + 1;
            int i3 = (i + 1) * ringDetail + j + 1;
            int i4 = j;
            int i5 = i*ringDetail;
            //int i6 = ringDetail + j + 1; // not used
            int i7 = (i + 1) * ringDetail;
            int i8 = j + 1;

			if (i < ringCount - 1) {
				if (j < ringDetail - 1) {
					inds.push_back(ProtoTuple3i(i0, i2, i3));
					inds.push_back(ProtoTuple3i(i0, i3, i1));

				}
				else {
					// j+1 = 0
					inds.push_back(ProtoTuple3i(i0, i5, i7));
					inds.push_back(ProtoTuple3i(i0, i7, i1));
				}
			}
			else {
				if (j < ringDetail - 1) {
					//i+1 = 0// HERE
					inds.push_back(ProtoTuple3i(i0, i2, i8));
					inds.push_back(ProtoTuple3i(i0, i8, i4));

				}
				else {
					//i+1 =0, j+1 = 0
					inds.push_back(ProtoTuple3i(i0, i5, 0));
					inds.push_back(ProtoTuple3i(i0, 0, i4));
				}
			}
        }
    }
}


