//
//  ProtoTube.cpp
//  Protobyte_iig001
//
//  Created by Ira on 10/17/12.
//
//

#include "ProtoTube.h"
#include "ProtoBlock.h"



namespace ijg {


	std::ostream& operator<<(std::ostream& out, const ProtoTube& tube) {
		out << "\n\tpos = " << tube.pos << "\n" << ""
			"\trot = " << tube.rot << "\n" <<
			"\tsize = " << tube.size << "\n" <<
			"\tcol4 = " << tube.col4 << "\n" <<
			"\tradius = " << tube.radius << "\n" <<
			"\tcrossSectionDetail = " << tube.crossSectionDetail << "\n" <<
			"\tisClosed = " << tube.isClosed << "\n" <<
			"\tfrenetFrameLength = " << tube.frenetFrameLength << "\n" <<
			"\tspd = " << tube.spd << "\n" <<
			"\trotSpd = " << tube.rotSpd << "\n" <<
			"\tisTransformFunction = " << tube.isTransformFunction;

		return out;
	}
}

using namespace ijg;

// default cstr

ProtoTube::ProtoTube() {
	//trace("ProtoTube Default CSTR");
}

// overloaded cstr 1
ProtoTube::ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.3, .3, .3, 1.0)), path(path), radius(radius), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {
	//trace( "ProtoTube CSTR 1 : (Spline3 path, radius, crossSectionDetail, isClosed)" );
	if (radii.size() > 0) radii.clear();
	if (col4s.size() > 0) col4s.clear();

	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
		col4s.push_back(col4);
	}

	init();
}

// overloaded cstr 1-b
ProtoTube::ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed, const std::string& textureImageURL, const Vec2f& textureScale) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.3, .3, .3, 1.0), textureImageURL, textureScale), path(path), radius(radius), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {
	//trace( "ProtoTube CSTR 1-b : (Spline3 path, radius, crossSectionDetail, isClosed, textureImageURL)" );
	if (radii.size() > 0) radii.clear();
	if (col4s.size() > 0) col4s.clear();

	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
		col4s.push_back(col4);
	}

	init();
}

/*!
 * Constructor 02
 * with TransformFunction object*/
ProtoTube::ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.3, .3, .3, 1.0)), path(path), radius(radius), crossSectionDetail(crossSectionDetail), transFuncObj(transFuncObj), isClosed(isClosed) {

	//trace("ProtoTube CSTR 2 : (Spline3 path, radius, crossSectionDetail, Transformfunction, isClosed)");

	if (radii.size() > 0) radii.clear();
	if (col4s.size() > 0) col4s.clear();

	setIsTransformFunction(true);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
		col4s.push_back(col4);
	}
	init();
}

/*!
 * Constructor 02-b
 * with TransformFunction object and texture*/
ProtoTube::ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed, const std::string& textureImageURL, const Vec2f& textureScale) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.3, .3, .3, 1.0), textureImageURL, textureScale), path(path), radius(radius), crossSectionDetail(crossSectionDetail), transFuncObj(transFuncObj), isClosed(isClosed) {

	//trace("ProtoTube CSTR 2 b : (Spline3 path, radius, crossSectionDetail, Transformfunction, isClosed)");

	if (radii.size() > 0) radii.clear();
	if (col4s.size() > 0) col4s.clear();

	setIsTransformFunction(true);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
		col4s.push_back(col4);
	}
	init();
}

// Constructor 03

ProtoTube::ProtoTube(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0)), path(path), radii(radii), crossSectionDetail(crossSectionDetail), transFuncObj(transFuncObj), isClosed(isClosed) {

	if (col4s.size() > 0) col4s.clear();

	// std::cout << "ProtoTube CSTR 3" << std::endl;
	setIsTransformFunction(true);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		//radii.push_back(radius);
		col4s.push_back(col4);
	}
	init();
}

/*!
 * Constructor 04
 * varied thickness*/
ProtoTube::ProtoTube(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0)), path(path), radii(radii), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {

	if (col4s.size() > 0) col4s.clear();

	// std::cout << "ProtoTube CSTR 4" << std::endl;
	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		col4s.push_back(col4);
	}
	init();
}

/*!
 * Constructor 05
 * varied color*/
ProtoTube::ProtoTube(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s), path(path), radius(radius), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {

	if (radii.size() > 0) radii.clear();

	//std::cout << "ProtoTube CSTR 5" << std::endl;
	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
	}
	init();
}

/*!
 * Constructor 06
 * varied color and TransformFunction object*/
ProtoTube::ProtoTube(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s), path(path), radius(radius), crossSectionDetail(crossSectionDetail), transFuncObj(transFuncObj), isClosed(isClosed) {

	if (radii.size() > 0) radii.clear();


	// std::cout << "ProtoTube CSTR 6" << std::endl;
	setIsTransformFunction(true);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
	}
	init();
}

/*!
 * Constructor 07
 * varied thickness and color */
ProtoTube::ProtoTube(const std::vector< ProtoColor4f >& col4s, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed) :
ProtoGeom3(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s), path(path), radii(radii), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {

	// std::cout << "ProtoTube CSTR 7" << std::endl;
	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;
	init();
}

/*!
 * Constructor 08
 * All */
ProtoTube::ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed) :
ProtoGeom3(pos, rot, size, col4), path(path), radius(radius), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {

	if (radii.size() > 0) radii.clear();
	if (col4s.size() > 0) col4s.clear();

	// std::cout << "ProtoTube CSTR 8" << std::endl;
	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
		col4s.push_back(col4);
	}
	init();
}

/*!
 * Constructor 09
 * varied thickness */
ProtoTube::ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed) : // varied thickness
ProtoGeom3(pos, rot, size, col4), path(path), radii(radii), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {


	if (col4s.size() > 0) col4s.clear();

	// std::cout << "ProtoTube CSTR 9" << std::endl;
	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		col4s.push_back(col4);
	}
	init();
}

/*!
 * Constructor 10
 * varied color */
ProtoTube::ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
	const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed) : // varied color
	ProtoGeom3(pos, rot, size, col4s), path(path), radius(radius), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {

	if (radii.size() > 0) radii.clear();

	// std::cout << "ProtoTube CSTR 10" << std::endl;
	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
	}
	init();
}

/*!
 * Constructor 11
 * varied thickness and color */
ProtoTube::ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
	const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, std::vector<float>& radii,
	int crossSectionDetail, bool isClosed) : // varied thickness & color
	ProtoGeom3(pos, rot, size, col4s), path(path), radii(radii), crossSectionDetail(crossSectionDetail), isClosed(isClosed) {

	//  std::cout << "ProtoTube CSTR 11" << std::endl;

	// no transform function
	setIsTransformFunction(false);
	perturbation.x = perturbation.y = perturbation.z = 0.0;
	init();
}

/*!
 * Constructor 12
 * All with TransformFunction obj*/
ProtoTube::ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) : ProtoGeom3(pos, rot, size, col4), path(path), radius(radius), crossSectionDetail(crossSectionDetail), transFuncObj(transFuncObj), isClosed(isClosed) {

	if (radii.size() > 0) radii.clear();
	if (col4s.size() > 0) col4s.clear();

	// std::cout << "ProtoTube CSTR 12" << std::endl;
	setIsTransformFunction(true);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
		col4s.push_back(col4);
	}
	init();
}

/*!
 * Constructor 13
 * all with varied color and TransformFunction obj */
ProtoTube::ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) : ProtoGeom3(pos, rot, size, col4s), path(path), radius(radius), crossSectionDetail(crossSectionDetail), transFuncObj(transFuncObj), isClosed(isClosed) {

	// std::cout << "ProtoTube CSTR 13" << std::endl;
	setIsTransformFunction(true);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	if (radii.size() > 0) radii.clear();


	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
	}
	init();
}

/*!
 * Constructor 14 added 12/27/13
 * all with varied color and TransformFunction obj */
ProtoTube::ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed){

	//  std::cout << "ProtoTube CSTR 14" << std::endl;
	setIsTransformFunction(true);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	init();
}

// NEW
ProtoTube::ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed, const std::string& textureImageURL, const Vec2f& textureScale) : ProtoGeom3(pos, rot, size, col4, textureImageURL, textureScale), path(path), radius(radius), crossSectionDetail(crossSectionDetail), transFuncObj(transFuncObj), isClosed(isClosed)
{
	if (radii.size() > 0) radii.clear();
	if (col4s.size() > 0) col4s.clear();

	// std::cout << "ProtoTube CSTR 12" << std::endl;
	setIsTransformFunction(true);
	perturbation.x = perturbation.y = perturbation.z = 0.0;

	for (int i = 0; i < path.getVertsLength(); i++) {
		radii.push_back(radius);
		col4s.push_back(col4);
	}

	init();
}



ProtoTube::~ProtoTube() {
	//std::cout << "in ProtoTube destructor" << std::endl;
}


void ProtoTube::calcVerts() {


	//trace("path.getVerts().at(0) =", path.getVerts().at(0));
	//trace("path.getVerts().at(1) =", path.getVerts().at(1));
	//trace("path.getVerts().at(path.getVerts().size()-1) =", path.getVerts().at(path.getVerts().size() - 1));
	//trace("path.getVerts().at(path.getVerts().size()-2) =", path.getVerts().at(path.getVerts().size() - 2));

	// NOTE: ff and vecs are not the same size
	ff = path.getFrenetFrames();
	//trace("ff.at(0) =", ff.at(0));
	std::vector<Vec3f> vecs = path.getVerts();
	frenetFrameLength = static_cast<int>(ff.size());
	//std::cout << ff.size() << std::endl;

	// prepare verts vector
	verts.clear();
	//verts.resize(frenetFrameLength * crossSectionDetail + 2);

	// top and bottom vec to enable tube caps
	Vec3f topCapVec, bottomCapVec;
	// std::cout << "frenetFrameLength = " << frenetFrameLength << std::endl;
	//trace("vecs.size() =", vecs.size());
	//trace("frenetFrameLength =", frenetFrameLength);

	//float step = 0;
	Vec3f step_xyz, randomStep_xyz;
	float randomStep_x = 0.0;
	float randomStep_y = 0.0;
	float x = 0.0;
	float y = 0.0;
	float u = 0.0;
	float v = 0.0;
	float phi = 0.0;

	//one additional convenience position vector for VerletProtoSpline
	std::vector<Vec3f> vProtoSplineVecs;


	for (int i = 0; i < frenetFrameLength; i++) {

		// calculate cross-section vertices
		float theta = 0;
		float theta2 = 0;

		// only calculate if necessary
		if (getIsTransformFunction()) {
			//std::cout << "in random getTransformed section" << std::endl;
			step_xyz.x = (transFuncObj.getVectorRange().elem1.x - transFuncObj.getVectorRange().elem0.x) / frenetFrameLength;
			step_xyz.y = (transFuncObj.getVectorRange().elem1.y - transFuncObj.getVectorRange().elem0.y) / frenetFrameLength;

			randomStep_x = random(transFuncObj.getVectorRange().elem0.x, transFuncObj.getVectorRange().elem1.x);
			randomStep_y = random(transFuncObj.getVectorRange().elem0.y, transFuncObj.getVectorRange().elem1.y);

		}


		vProtoSplineVecs.push_back(vecs.at(i));

		// calculating double end points for seam UV coords (0  ->  1)
		for (int j = 0; j < crossSectionDetail; j++) {

			// customize tube based on transform function
			if (getIsTransformFunction()) {

				switch (transFuncObj.getFunctionType()) {
				case ProtoTransformFunction::LINEAR:
					//step_xyz.x = (transFuncObj.getVectorRange().elem1.x - transFuncObj.getVectorRange().elem0.x) / frenetFrameLength;
					//step_xyz.y = (transFuncObj.getVectorRange().elem1.y - transFuncObj.getVectorRange().elem0.y) / frenetFrameLength;
					x = cos(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem0.x + step_xyz.x * i + random(-perturbation.x, perturbation.x));
					y = sin(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem0.y + step_xyz.y * i + random(-perturbation.y, perturbation.y));
					break;
				case ProtoTransformFunction::LINEAR_INVERSE:
					//step_xyz.x = (transFuncObj.getVectorRange().elem1.x - transFuncObj.getVectorRange().elem0.x) / frenetFrameLength;
					//step_xyz.y = (transFuncObj.getVectorRange().elem1.y - transFuncObj.getVectorRange().elem0.y) / frenetFrameLength;
					x = cos(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem1.x - step_xyz.x * i + random(-perturbation.x, perturbation.x));
					y = sin(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem1.y - step_xyz.y * i + random(-perturbation.y, perturbation.y));
					break;
				case ProtoTransformFunction::SINUSOIDAL:
					//step = fabs(sin(phi) * (transFuncObj.getScalerRange().elem1 - transFuncObj.getScalerRange().elem0));
					step_xyz.x = fabs(sin(phi) * (transFuncObj.getVectorRange().elem1.x - transFuncObj.getVectorRange().elem0.x));
					step_xyz.y = fabs(sin(phi) * (transFuncObj.getVectorRange().elem1.y - transFuncObj.getVectorRange().elem0.y));
					//std::cout << "phi = " << phi << std::endl;
					x = cos(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem0.x + step_xyz.x + ijg::random(-perturbation.x, perturbation.x));
					y = sin(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem0.y + step_xyz.y + ijg::random(-perturbation.y, perturbation.y));
					break;
				case ProtoTransformFunction::SINUSOIDAL_INVERSE:
					//step = fabs(sin(phi) * (transFuncObj.getScalerRange().elem1 - transFuncObj.getScalerRange().elem0));
					step_xyz.x = fabs(sin(HALF_PI - phi) * (transFuncObj.getVectorRange().elem1.x - transFuncObj.getVectorRange().elem0.x));
					step_xyz.y = fabs(sin(HALF_PI - phi) * (transFuncObj.getVectorRange().elem1.y - transFuncObj.getVectorRange().elem0.y));
					//std::cout << "phi = " << phi << std::endl;
					x = cos(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem0.x + step_xyz.x + ijg::random(-perturbation.x, perturbation.x));
					y = sin(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem0.y + step_xyz.y + ijg::random(-perturbation.y, perturbation.y));
					break;
					//                    case TransformFunction::SINUSOIDAL_TRANSFORM_RANDOM:
					//                        x = cos(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem0.x + randomStep_x);
					//                        y = sin(theta) * radii.at(i) * (transFuncObj.getVectorRange().elem0.y + randomStep_y);
					//                        break;
					//default:
				};

				// no transform function
			}
			else {
				x = cos(theta) * (radii.at(i) + ijg::random(-perturbation.x, perturbation.x));
				y = sin(theta) * (radii.at(i) + ijg::random(-perturbation.y, perturbation.y));
			}

			// calculate cross section shape
			// TO DO: add param for ribbon asymmetry (radius per axis)
			//float x = cos(theta) * radii.at(i) * step*i; //*10;
			//float y = sin(theta) * radii.at(i) * step*i;
			// std::cout << "radii.at(" << i << ") = " << radii.at(i) << std::endl;


			float z = ijg::random(-perturbation.z, perturbation.z);
			theta += TWO_PI / (float(crossSectionDetail)-random(.98, 1.0)); // added -.99 to avoid seams 7/27

			if (i == 0 && j == 0) {
				//trace("vecs.at(0) =", vecs.at(0));
				//trace("vecs.at(1) =", vecs.at(1));
				//trace("vecs.at(vecs.size()-1) =", vecs.at(vecs.size() - 1));
				//trace("vecs.at(vecs.size()-2) =", vecs.at(vecs.size() - 2));
			}
			// transform to Frenet frame of reference
			float px = vecs.at(i + 1).x + x * ff.at(i).getN().x + y * ff.at(i).getB().x;
			float py = vecs.at(i + 1).y + x * ff.at(i).getN().y + y * ff.at(i).getB().y;
			float pz = vecs.at(i + 1).z + x * ff.at(i).getN().z + y * ff.at(i).getB().z;
			// std::cout <<"ff[i].getB() = " << ff[i].getB() << std::endl;

			//             std::cout << "vecs.at(i + 1) = " << vecs.at(i + 1) << std::endl;
			//             std::cout << " ff.at(i).getN() = " <<  ff.at(i).getN() << std::endl;
			//             std::cout << "ff.at(i).getB() = " << ff.at(i).getB() << std::endl;
			//             std::cout << "Vec3f(px, py, pz).at(" << i << ") = " << Vec3f(px, py, pz) << std::endl;
			//trace("Vec3f(px, py, pz) = " , Vec3f(px, py, pz));
			//verts.at(i * crossSectionDetail + j) = ProtoVertex3(Vec3f(px, py, pz), col4s.at(i));

	
			// set uv coords
			u = theta2 / (TWO_PI*(1.0f / textureScale.x));
			v = (float(i * crossSectionDetail + j) / float(crossSectionDetail*frenetFrameLength))*(1.0f / textureScale.y);
			//trace("u =", u);
			//trace(" theta2*180/PI =", theta2 * 180 / PI);

			verts.push_back(ProtoVertex3(Vec3f(px, py, pz), col4s.at(i), ProtoTuple2f(u, v)));
			//trace("v = ", (i * float(crossSectionDetail) + j) / float(crossSectionDetail*frenetFrameLength) );
			theta2 += TWO_PI / (crossSectionDetail);

			//verts.at(i * crossSectionDetail + j) = ProtoVertex3(Vec3f(px, py, pz), col4s.at(i), ProtoTuple2f(px/size.w, py/size.h));
			//std::cout << "Vec3f(px, py, pz).at(" << i << ") = " << Vec3f(px, py, pz) << std::endl;

			//std::cout << "perturbation = " << perturbation << std::endl;


			// get centroid of top and bottom cross-section for caps
			if (i == 0)
				topCapVec += Vec3f(px, py, pz);
			else if (i == ff.size() - 1)
				bottomCapVec += Vec3f(px, py, pz);

		}

		// only calculate if necessary
		if (getIsTransformFunction()) {
			phi += PI / frenetFrameLength * transFuncObj.getPeriodCount();
		}
	}

	// finish getting top and bottom cap centroid vecs.
	topCapVec /= crossSectionDetail;
	bottomCapVec /= crossSectionDetail;

	// add cap centroids to verts.
	verts.push_back(ProtoVertex3(topCapVec, col4s.at(0)));
	verts.push_back(ProtoVertex3(bottomCapVec, col4s.at(frenetFrameLength - 1)));



	// calculate all cross-section centroids - used by transforamtions such as breath()
	std::vector<Vec3f> centerPts(frenetFrameLength);
	crossSectionCentroids.resize(frenetFrameLength);


	// std::cout << "crossSectionDetail = " << crossSectionDetail << std::endl;

	for (int i = 0; i < frenetFrameLength; i++) {
		float cx = 0, cy = 0, cz = 0;
		for (int j = 0; j < crossSectionDetail; j++) {
			cx += verts.at(i * crossSectionDetail + j).pos.x;
			cy += verts.at(i * crossSectionDetail + j).pos.y;
			cz += verts.at(i * crossSectionDetail + j).pos.z;
			//            std::cout << "cx = " << cx << std::endl;
			//            std::cout << "cy = " << cy << std::endl;
			//            std::cout << "cz = " << cz << std::endl;
		}
		cx /= crossSectionDetail;
		cy /= crossSectionDetail;
		cz /= crossSectionDetail;
		crossSectionCentroids.at(i) = Vec3f(cx, cy, cz);

	}
}

void ProtoTube::calcInds() {
	if (inds.size() > 0) inds.clear();

	// indices
	for (int i = 0; i < frenetFrameLength; i++) {
		for (int j = 0; j < crossSectionDetail; j++) {

			int i0 = i * crossSectionDetail + j;
			int i1 = (i + 1) * crossSectionDetail + j;
			int i2 = i * crossSectionDetail + j + 1;
			int i3 = (i + 1) * crossSectionDetail + j + 1;
			int i4 = j;
			int i5 = i*crossSectionDetail;
			int i6 = crossSectionDetail + j + 1;
			int i7 = (i + 1) * crossSectionDetail;
			int i8 = j + 1;


			if (i < frenetFrameLength - 1) {
				if (j < crossSectionDetail-1) {

					// top cap
					if (i == 0 && isClosed) {
						inds.push_back(ProtoTuple3<int>(i2, i0, static_cast<int>(verts.size()) - 2));
					}

					// tube body
					inds.push_back(ProtoTuple3<int>(i0, i2, i3));
					inds.push_back(ProtoTuple3<int>(i0, i3, i1));
				}
				//// close tube seam
				else {

					// top cap
					if (i == 0 && isClosed) {
						inds.push_back(ProtoTuple3<int>(i5, i0, static_cast<int>(verts.size()) - 2));
					}

					// tube body
					//verts.at(i*crossSectionDetail).setUV(Tup2f(1, verts.at(i*crossSectionDetail).getUV().elem1));
					inds.push_back(ProtoTuple3<int>(i0, i5, i7));
					inds.push_back(ProtoTuple3<int>(i0, i7, i1));
				}
			}
			else if (i == frenetFrameLength - 1 && isClosed) {
				// close bottom cap
				if (j < crossSectionDetail-1) {
					inds.push_back(ProtoTuple3<int>(i0, i2, static_cast<int>(verts.size()) - 1));
				}
				else {
					inds.push_back(ProtoTuple3<int>(i0, i5, static_cast<int>(verts.size()) - 1));
				}
			}
		}
	}
}

void ProtoTube::rotateY() {
	//    glBindBuffer(GL_ARRAY_BUFFER, vboID);
	//    float t = PI / 360.0;
	//    for (int i = 0; i < interleavedPrims.size(); i += 12) {
	//        float x = 0;
	//        //float y = 0;
	//        float z = 0;
	//        float nx = 0;
	//        //float ny = 0;
	//        float nz = 0;
	//
	//        // verts
	//        z = cos(t) * interleavedPrims.at(i + 2) - sin(t) * interleavedPrims.at(i);
	//        x = sin(t) * interleavedPrims.at(i + 2) + cos(t) * interleavedPrims.at(i);
	//        interleavedPrims.at(i + 2) = z;
	//        interleavedPrims.at(i) = x;
	//
	//        //vnorms
	//        nz = cos(t) * interleavedPrims.at(i + 5) - sin(t) * interleavedPrims.at(i + 3);
	//        nx = sin(t) * interleavedPrims.at(i + 5) + cos(t) * interleavedPrims.at(i + 3);
	//        interleavedPrims.at(i + 5) = nz;
	//        interleavedPrims.at(i + 3) = nx;
	//
	//    }
	//    int vertsDataSize = sizeof (float) *interleavedPrims.size();
	//    glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	//    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

