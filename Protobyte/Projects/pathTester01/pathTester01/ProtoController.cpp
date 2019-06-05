/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	int ptCount = 10;
	
	float splineLength = 400;
	float step = splineLength / ptCount;
	for (int i = 0; i < ptCount; ++i) {
		pts.push_back({0, -splineLength/2+step*(i+1), 0});
	}

	spline = Spline3(pts, 2, false, .65);
	tube = Tube(spline, 100, 18, false, "humanSkin02.jpg");
	tube.setDiffuseMaterial({ 1.0f, 1, 1 });
	tube.setAmbientMaterial(0.05f);
	tube.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_15-normal.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tube.setTextureScale({ 1.1, .1f });

	tube.setSpecularMaterial({ 1, 1, 1 });
	tube.setShininess(40);

	strokeWeight(5);
}

void ProtoController::run() {
}

void ProtoController::display() {
	//background({ 1 });

	//beginArcBall(); 
	//translate(0, 0, -200);
	//
	//// draw spline data
	//stroke(1, 1, 0, 1);
	//fill(0);
	////spline.display(4);
	//push();
	tube.display(WIREFRAME, 5);
	//tube.display();
	//translate(-100, 0, 0);
	//spline.displayControlPts();

	//pop();

	//spline.displayInterpPts(13);
	//strokeWeight(5);
	//
	//push();
	//translate(100, 0, 0);
	//// draw original control points
	//for (int i = 0; i < pts.size(); ++i) {
	//	point(pts.at(i).x, pts.at(i).y);
	//}
	//pop();


	//endArcBall();
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