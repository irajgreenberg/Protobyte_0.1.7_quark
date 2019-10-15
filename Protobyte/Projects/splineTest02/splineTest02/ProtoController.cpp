/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

//https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
#include "ProtoController.h"

//void ProtoController::catmulRom() {
//	//newPts.clear();
//	Vec3f p0{};
//	Vec3f p1{};
//	Vec3f p2{};
//	Vec3f p3{};
//	for (int i = 0; i < pts.size()-3; i++) {
//	/*	if (isClosed) {
//		}
//		else {
//		}*/
//		p0 = pts[i];
//		p1 = pts[i + 1];
//		p2 = pts[i + 2];
//		p3 = pts[i + 3];
//
//
//		float t0 = 0.0f;
//		float t1 = getT(t0, p0, p1);
//		float t2 = getT(t1, p1, p2);
//		float t3 = getT(t2, p2, p3);
//
//		for (float t = t1; t < t2; t += ((t2 - t1) / ptCount)) {
//			Vec3f a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
//			Vec3f a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
//			Vec3f a3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;
//
//			Vec3f b1 = (t2 - t) / (t2 - t0) * a1 + (t - t0) / (t2 - t0) * a2;
//			Vec3f b2 = (t3 - t) / (t3 - t1) * a2 + (t - t1) / (t3 - t1) * a3;
//
//			Vec3f c = (t2 - t) / (t2 - t1) * b1 + (t - t1) / (t2 - t1) * b2;
//
//			newPts.push_back(c);
//		}
//	}
//}
//
//float ProtoController::getT(float t, Vec3f p0, Vec3f p1) {
//	float a = pow((p1.x - p0.x), 2.0f) + pow((p1.y - p0.y), 2.0f) + pow((p1.z - p0.z), 2.0f);
//	float b = pow(a, 0.5f);
//	float c = pow(b, alpha);
//
//	return (c + t);
//}



void ProtoController::init() {

	Col4f c;
	c[0] = .3f;
	// Closed loop test 1
	float circleRadius{ 200.0f };
	float theta{ 0.0f };
	for (int i{ 0 }; i < ptCount; ++i) {
		float x = cos(theta) * circleRadius;
		float y = sin(theta) * circleRadius;
		float z = -ptCount*40/2 + i*40;
		vecs.push_back({x, y, z});
		theta += TWO_PI / (ptCount/4);
	}
	
	// Closed loop test 2
	//for (int i = 0; i < ptCount; ++i) {
	//	vecs.push_back({ random(-400, 400),
	//		random(-300, 300),
	//		random(-400, 400) });
	//}

	s = Spline3(vecs, 5, 0, ProtoSpline3::UNIFORM);
	s.setAreTerminalPtsIncluded(0);
	//trace("s.getAreTerminalPtsIncluded() =",s.getAreTerminalPtsIncluded());
	//s2 = Spline3(vecs, 5, 1, ProtoSpline3::CENTRIPETAL);
	//s3 = Spline3(vecs, 5, 1, ProtoSpline3::CHORDAL);
	//s.set
	tendril = Tube(s, 4, 23, ProtoTransformFunction(ProtoTransformFunction::LINEAR, Tup2(20, 20), 1), true, "corroded_red.jpg");
	tendril.setDiffuseMaterial({ 1.0f, 1, 1 });
	tendril.setAmbientMaterial(0.05f);
	tendril.setBumpMap("corroded_red.jpg", 1.0f);
	////tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tendril.setTextureScale({ 1.1, .1f });

	tendril.setSpecularMaterial({ 1, 1, 1 });
	tendril.setShininess(12);

	// Enables curves to be drawn to terminasl and closed
	// default is terminal drawing
	//if (areTerminalsReached) {
	//	pts.push_back(pts.at(0));
	//	pts.push_back(pts.at(1));
	//	// draw smooth closed curve
	//	if (isCurveClosed) {
	//		pts.push_back(pts.at(2));
	//	}
	//}

	//catmulRom();

	// print pts
	/*for (Vec3f v : newPts) {
		trace("v = ", v);
	}*/
	//for (int i = 0; i < s.getFrenetFrames().size(); ++i) {
	//	trace(s.getFrenetFrames().at(i).getT());
	//	trace(s.getFrenetFrames().at(i).getN());
	//	trace(s.getFrenetFrames().at(i).getB());
	//}
}

void ProtoController::run() {
}

void ProtoController::display() {
	/*scale(.5);
	beginArcBall();
	fill(0);
	strokeWeight(6);
	for (Vec3f v : newPts) {
		point(v.x, v.y, v.z);
	}
	fill(1, .5, 0, 1);
	strokeWeight(7);
	int i = 0;
	for (Vec3f v : pts) {
		if (i == 0) {
			strokeWeight(16);
			fill(0, 0, 1, 1);
		} 
		else if (i == pts.size()-1) {
			strokeWeight(16);
			fill(1, 0, 0, 1);
		}
		else {
			strokeWeight(9);
			fill(1, .5, 0, 1);
		}
		point(v.x, v.y, v.z);
		i++;
	}
	endArcBall();*/
	scale(.55);
	beginArcBall(); 
	s.display(2);
	s.displayControlPts();
	//s.displayInterpolatedPts(6);
	s.displayFrenetFrames();

	//translate(100, 0, 0);
	//s2.display(2);
	//s2.displayInterpolatedPts(6);

	////translate(100, 0, 0);
	//s3.display(2);
	//s3.displayInterpolatedPts(6);
	//tendril.display(WIREFRAME);
	tendril.display();
	endArcBall();
}

// Key and Mouse Events
void ProtoController::keyPressed() {
}

void ProtoController::mousePressed() {
}

void ProtoController::mouseRightPressed() {
}

void ProtoController::mouseReleased() {
}

void ProtoController::mouseRightReleased() {
}

void ProtoController::mouseMoved() {
}

void ProtoController::mouseDragged() {
}

// Window Events
void ProtoController::onResized() {
}

void ProtoController::onClosed() {
}