/*!  \brief  ProtoSpline3.cpp: Catmull-Rom spline class implementation
ProtoSpline3.cpp
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

#include "ProtoSpline3.h"
//#include "ProtoQuaternion.h"
#include "ProtoMatrix3.h"


#include <iostream>

using namespace ijg;
//Matrix4 m;;

/**
 * Spline cubic curve class, where curve goes through all points. C
 * <p>
 */


ProtoSpline3::ProtoSpline3() {
}

// requires 4 control points to work
ProtoSpline3::ProtoSpline3(const std::vector<Vec3f>& controlPts, int interpolatedPtsCount,
	bool isCurveClosed, SplineType type) :
	ProtoCurve3(controlPts, interpolatedPtsCount, isCurveClosed), type(type) {
	init();
}


/**
 * Calculate the interpolated curve points populating the uniqueVerts array.
 */
void ProtoSpline3::init() {
	// ensure starting state ok
	controlPts = originalControlPts;
	
	// clear vectors
	if (verts.size() > 0) verts.clear();
	if (controlPtPrims.size() > 0) controlPtPrims.clear();
	if (frenetFrames.size() > 0) frenetFrames.clear();
	if (curveVertsPrims.size() > 0) curveVertsPrims.clear();

	switch (type) {
	case UNIFORM:
		splineAlpha = 0.0f;
		break;
	case CENTRIPETAL:
		splineAlpha = 0.5f;
		break;
	case CHORDAL:
		splineAlpha = 1.0f;
		break;
	default:
		splineAlpha = 0.0f;
	};

	// ensures curve is drawn between all control points
	// maintaining smooth curvature
	if (areTerminalPtsIncluded) {
		std::vector<Vec3f>::iterator it;
		it = controlPts.begin();
		it = controlPts.insert(it, controlPts.at(controlPts.size() - 1));
		it = controlPts.end();
		it = controlPts.insert(it, controlPts.at(0));
		// draw smooth closed curve
		if (isCurveClosed) {
		//	controlPts.push_back(controlPts.at(2));
		//	controlPts.push_back(controlPts.at(3));
		}
	}
	else {
	}


	

	//Convenient interleaved primitives array of original curve control points.
	for (auto i : controlPts) {
		controlPtPrims.push_back(i.x);
		controlPtPrims.push_back(i.y);
		controlPtPrims.push_back(i.z);
		controlPtPrims.push_back(0.0f); //r
		controlPtPrims.push_back(0.0f); //g
		controlPtPrims.push_back(0.0f); //b
		controlPtPrims.push_back(1.0f); //a
	}
	Vec3f p0{};
	Vec3f p1{};
	Vec3f p2{};
	Vec3f p3{};
	for (int i = 0; i < controlPts.size() - 3; i++) {
		p0 = controlPts[i];
		p1 = controlPts[i + 1];
		p2 = controlPts[i + 2];
		p3 = controlPts[i + 3];


		float t0 = 0.0f;
		float t1 = getT(t0, p0, p1);
		float t2 = getT(t1, p1, p2);
		float t3 = getT(t2, p2, p3);
		for (float t = t1; t < t2; t += ((t2 - t1) / interpolatedPtsCount)) {
			Vec3f a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
			Vec3f a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
			Vec3f a3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;

			Vec3f b1 = (t2 - t) / (t2 - t0) * a1 + (t - t0) / (t2 - t0) * a2;
			Vec3f b2 = (t3 - t) / (t3 - t1) * a2 + (t - t1) / (t3 - t1) * a3;

			Vec3f c = (t2 - t) / (t2 - t1) * b1 + (t - t1) / (t2 - t1) * b2;

			verts.push_back(c);
		}
	}

	// add last interpolated point on control point
	verts.push_back(controlPts.at(controlPts.size() - 2));

	// create frenet frames for each curve knot
	//if (frenetFrames.size() > 1) frenetFrames.clear();

	initFrenetFrames();

	// don't need these any longer
	//controlPts.clear();

	/* ensure tube section doesn't flip */
	parallelTransport();

	//curveVertsPrims.clear();
		// create convenient interleaved primitives array of vertices for shader based curve rendering
	for (auto i : verts) {
		curveVertsPrims.push_back(i.x);
		curveVertsPrims.push_back(i.y);
		curveVertsPrims.push_back(i.z);
		curveVertsPrims.push_back(.3); //r
		curveVertsPrims.push_back(.6); //g
		curveVertsPrims.push_back(.2); //b
		curveVertsPrims.push_back(.85); //a
	}
}

void ProtoSpline3::initFrenetFrames() {
	for (int i = 1; i < verts.size() - 1; i++) {
		frenetFrames.push_back(FrenetFrame(verts.at(i - 1), verts.at(i), verts.at(i + 1)));
	}
	//trace("verts.size =", verts.size());
	//trace("renetFrames.size =", frenetFrames.size());
}


// Calculates interpolated knots along curve, between control points
float ProtoSpline3::getT(float t, Vec3f p0, Vec3f p1) {
	float a = pow((p1.x - p0.x), 2.0f) + pow((p1.y - p0.y), 2.0f) + pow((p1.z - p0.z), 2.0f);
	float b = pow(a, 0.5f);
	float c = pow(b, splineAlpha);
	return (c + t);
}

/**
 * Draw the curve.
 *
 */
void ProtoSpline3::display(float strokeWeight, Col4 strokeCol) {

	for (int i = 0; i < curveVertsPrims.size(); i += stride) {
		curveVertsPrims.at(i + 3) = strokeCol.getR();
		curveVertsPrims.at(i + 4) = strokeCol.getG();
		curveVertsPrims.at(i + 5) = strokeCol.getB();
		curveVertsPrims.at(i + 6) = strokeCol.getA();
	}

	//enable2DRendering();
	glBindVertexArray(vaoVertsID);
	// NOTE::this may not be most efficient - eventually refactor
	glBindBuffer(GL_ARRAY_BUFFER, vboVertsID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * curveVertsPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &curveVertsPrims[0]); // upload the data

	glLineWidth(strokeWeight);
	// closed path
	//if (pathRenderMode){
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glDrawArrays(GL_LINE_LOOP, 0, pathPrims.size() / stride);
	//}
	//// open path
	//else {
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glDrawArrays(GL_LINE_STRIP, 0, pathPrims.size() / stride);
	//}
	// turn off lighting
	Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_LINE_STRIP, 0, curveVertsPrims.size() / stride);

	//turn on lighting
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	//disable2DRendering();

	// Disable VAO
	glBindVertexArray(0);
}

/**
 * Draw the control points.
 *
 */
void ProtoSpline3::displayControlPts(float pointSize, Col4 strokeCol) {
	for (int i = 0; i < controlPtPrims.size(); i += stride) {
		if (i == 0) {
			controlPtPrims.at(i + 3) = 0.0f;
			controlPtPrims.at(i + 4) = 1.0f;
			controlPtPrims.at(i + 5) = 0.25f;
			controlPtPrims.at(i + 6) = 1.0f;
		}
		else if (i == controlPtPrims.size()-7) {
			controlPtPrims.at(i + 3) = 1.0f;
			controlPtPrims.at(i + 4) = 0.5f;
			controlPtPrims.at(i + 5) = 0.0f;
			controlPtPrims.at(i + 6) = 1.0f;
		}
		else {
			controlPtPrims.at(i + 3) = strokeCol.getR();
			controlPtPrims.at(i + 4) = strokeCol.getG();
			controlPtPrims.at(i + 5) = strokeCol.getB();
			controlPtPrims.at(i + 6) = strokeCol.getA();
		}
	}
	glBindVertexArray(vaoVertsID);
	// NOTE::this may not be most efficient - eventually refactor
	glBindBuffer(GL_ARRAY_BUFFER, vboVertsID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * controlPtPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &controlPtPrims[0]); // upload the data

	glPointSize(pointSize);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // do I need this anymore?

	// turn off lighting
	Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glDrawArrays(GL_POINTS, 0, controlPtPrims.size() / stride);

	//turn on lighting
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	// Disable VAO
	glBindVertexArray(0);
}

/**
 * Draw the interpolated points.
 *
 */
void ProtoSpline3::displayInterpolatedPts(float pointSize, Col4 strokeCol) {
	for (int i = 0; i < curveVertsPrims.size(); i += stride) {
		curveVertsPrims.at(i + 3) = strokeCol.getR();
		curveVertsPrims.at(i + 4) = strokeCol.getG();
		curveVertsPrims.at(i + 5) = strokeCol.getB();
		curveVertsPrims.at(i + 6) = strokeCol.getA();
	}
	glBindVertexArray(vaoVertsID);
	// NOTE::this may not be most efficient - eventually refactor
	glBindBuffer(GL_ARRAY_BUFFER, vboVertsID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * curveVertsPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &curveVertsPrims[0]); // upload the data

	glPointSize(pointSize);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // do I need this anymore?

	// turn off lighting
	Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glDrawArrays(GL_POINTS, 0, curveVertsPrims.size() / stride);

	//turn on lighting
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	// Disable VAO
	glBindVertexArray(0);
}

/**
 * Draw the Frenet Frames.
 *
 */
 // float length, float strokeWeight, Col4f TCol, Col4f NCol, Col4f BCol
void ProtoSpline3::displayFrenetFrames(float length, float strokeWeight, Col4f TCol, Col4f NCol, Col4f BCol) {
	//	trace("frenetFrames.size() =", frenetFrames.size());
	//	trace("verts.size() =", verts.size());
	for (int i = 0; i < frenetFrames.size()-5; i++) {
		frenetFrames.at(i).display(length, strokeWeight, TCol, NCol, BCol);
	}
}

///**
// * Draw cross-section extruded along the spline path.
// * Default cross-section is an ellipse
// */
//void ProtoSpline3::drawCrossSections() {
//	for (int i = 0; i < frenetFrames.size(); i++) {
//		// draw cross-section ellipse
//		glColor3f(1, 1, 1);
//		glBegin(GL_POLYGON);
//		float th = 0;
//		for (int j = 0; j < 6; j++) {
//			float x = cos(th) * 10;
//			float y = sin(th) * 10;
//			//float z = 0;
//			float px = verts.at(i + 1).x + x * frenetFrames.at(i).getN().x + y * frenetFrames.at(i).getB().x;
//			float py = verts.at(i + 1).y + x * frenetFrames.at(i).getN().y + y * frenetFrames.at(i).getB().y;
//			float pz = verts.at(i + 1).z + x * frenetFrames.at(i).getN().z + y * frenetFrames.at(i).getB().z;
//			glVertex3f(px, py, pz);
//			th += PI * 2.0 / 6.0;
//		}
//		glEnd();
//	}
//
//	glPointSize(4);
//	for (int i = 0; i < frenetFrames.size(); i++) {
//		// draw cross-section ellipse
//		glBegin(GL_POINTS);
//		float th = 0;
//		for (int j = 0; j < 6; j++) {
//			float x = cos(th) * 10;
//			float y = sin(th) * 10;
//			//float z = 0;
//			float px = verts.at(i + 1).x + x * frenetFrames.at(i).getN().x + y * frenetFrames.at(i).getB().x;
//			float py = verts.at(i + 1).y + x * frenetFrames.at(i).getN().y + y * frenetFrames.at(i).getB().y;
//			float pz = verts.at(i + 1).z + x * frenetFrames.at(i).getN().z + y * frenetFrames.at(i).getB().z;
//			glColor3f(0, 1 - 1 / (j + 1), 1 / (j + 1));
//			glVertex3f(px, py, pz);
//			th += PI * 2 / 6;
//		}
//		glEnd();
//	}
//}


void ProtoSpline3::parallelTransport() {
	//// double up first and last verts
	////verts.insert(verts.begin(), verts.at(0));
	////verts.push_back(verts.at(verts.size() - 1));

	////frenetFrames.push_back(FrenetFrame(verts.at(0), Vec3f(1,0,0), Vec3f(0,-1,0), Vec3f(0,0,-1))); // add first vert
	//// std::cout << "in createFrenetFrame():  verts.size() = " << verts.size() << std::endl;
	//std::vector<Vec3f> tans;
	//float theta = 0.0;
	//Vec3f cp0, cp1, cp2;
	//Vec3f tan, biNorm, norm, nextBiNorm, nextNorm;


	//for (int i = 0; i < verts.size(); i++) {
	//	// special case if at first point
	//	if (i == 0) {
	//		//cp0 = verts[verts.size() - 1];
	//		cp0 = verts.at(i);
	//		cp1 = verts.at(i);
	//		cp2 = verts.at(i + 1);

	//	}
	//	// special case if at last point
	//	else if (i == verts.size() - 1) {
	//		cp0 = verts.at(i - 1);
	//		cp1 = verts.at(i);
	//		cp2 = verts.at(i); // 0, circled back here? changed to i

	//	}
	//	else {
	//		cp0 = verts.at(i - 1);
	//		cp1 = verts.at(i);
	//		cp2 = verts.at(i + 1);

	//		//std::cout << "i = = " << i << std::endl;
	//		//            std::cout << "cp0 " << cp0 << std::endl;

	//		//            std::cout << "cp1 " << cp1 << std::endl;
	//		//            std::cout << "cp2 " << cp2 << std::endl;
	//		//            std::cout << "cross(cp1, cp2) " << cross(cp1, cp2) << std::endl;
	//		//std::cout << "cp2 " << cp2 << std::endl;
	//	}
	//	// fill tangents
	//	tan = cp2 - cp0;
	//	tan.normalize();
	//	tans.push_back(tan);

	//	// collect initial frame
	//	if (i == 1) {
	//		// fix biNorm for parralel vectors
	//		biNorm = cp1.cross(cp2);

	//		// uh-oh parallel vecs
	//		// ! HACK ! avoids problems with orthonormal tubes.
	//		if (biNorm.mag() == 0) {

	//			if (cp1.x != 0 && cp2.x != 0) {
	//				biNorm = Vec3f(0, 1, 0);
	//			}
	//			if (cp1.y != 0 && cp2.y != 0) {
	//				biNorm = Vec3f(0, 0, -1);
	//			}
	//			if (cp1.z != 0 && cp2.z != 0) {
	//				biNorm = Vec3f(1, 0, 0);
	//			}

	//		}
	//		//std::cout << "biNorm pre = " << biNorm << std::endl;
	//		//std::cout << "biNorm.mag() = " << biNorm.mag() << std::endl;
	//		biNorm.normalize();
	//		//            biNorm.x = 1;
	//		//            biNorm.y = 0;
	//		//            biNorm.z = 0;
	//		//            std::cout << "cp1 " << cp1 << std::endl;
	//		//            std::cout << "cp2 " << cp2 << std::endl;
	//		//            std::cout << "biNorm post = " << biNorm << std::endl;

	//		norm = biNorm.cross(tan);
	//		norm.normalize();
	//	}
	//}
	//// rotate frame

	////  std::cout << "tans.size() = " << tans.size() << std::endl;
	//for (int i = 0; i < tans.size() - 1; i++) {


	//	if (biNorm.mag() == 0) {
	//		nextNorm = norm;
	//		//frenetFrames.push_back(FrenetFrame(verts.at(i), Vec3f(1,1,1), Vec3f(1,1,1), Vec3f(1,1,1)));
	//		// std::cout << "norm = " << norm << std::endl;
	//	}
	//	else {
	//		theta = acos(tans.at(i).dot(tans.at(i + 1)));
	//		Vec3f axis = tans.at(i);
	//		//std::cout << "tans.at(i + 1) = " << tans.at(i + 1) << std::endl;
	//		//std::cout << i << std::endl;
	//		axis = axis.cross(tans.at(i + 1));
	//		//std::cout << "axis = " << axis << std::endl;
	//		axis.normalize();



	//		ProtoMatrix3f m;
	//		nextNorm = m.getRotate(theta, axis, norm);
	//		//std::cout << "axis = " << axis << std::endl;

	//		nextBiNorm = tans.at(i + 1);
	//		nextBiNorm = nextBiNorm.cross(nextNorm);



	//		// std::cout << "nextNorm = " << nextNorm << std::endl;
	//		// std::cout << "norm = " << norm << std::endl;

	//	}

	//	//biNorm.normalize();
	//	//norm.normalize();
	//	//        std::cout <<i<<std::endl;
	//	//        std::cout << "tans.at(i) = " << tans.at(i) << std::endl;
	//	//        std::cout << "biNorm = " << biNorm << std::endl;
	//	//        std::cout << "norm = " << norm << std::endl;
	//	frenetFrames.push_back(ProtoFrenetFrame(verts.at(i), tans.at(i), biNorm, norm));
	//	norm = nextNorm;
	//	biNorm = nextBiNorm;

	//	//std::cout << "verts = " << verts.at(i) << std::endl;
	//}
	//std::cout << "in createFrenetFrame():  frenetFrames.size() = " << frenetFrames.size() << std::endl;

}