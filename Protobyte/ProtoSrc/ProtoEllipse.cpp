#include "ProtoEllipse.h"

using namespace ijg;

ProtoEllipse::ProtoEllipse()
{
}
ProtoEllipse::ProtoEllipse(const Vec3f& pos, const Vec3f& rot, const Dim2f& size,
	const Col4f& col4, int detail) :
	ProtoGeom3(pos, rot, size, col4), detail(detail)
{
	init();
}

void ProtoEllipse::calcVerts(){
	// centroid
	verts.push_back(ProtoVertex3(Vec3f(),
		ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
	float theta = 0.0;
	for (int i = 0; i < detail; i++) {
		// unit size
		verts.push_back(ProtoVertex3(Vec3f(cos(theta), sin(theta), 0),
			ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(cos(theta), sin(theta))));
		theta += TWO_PI / detail;
	}


}

void ProtoEllipse::calcInds(){
	int sz = verts.size();
	for (int i = 1; i <sz; ++i) {

		// body
		if (i < sz - 1){
			inds.push_back(ProtoTuple3i(i+1, 0, i));
		}
		// seam
		else {
			inds.push_back(ProtoTuple3i(1, 0, i));
		}

	}
}