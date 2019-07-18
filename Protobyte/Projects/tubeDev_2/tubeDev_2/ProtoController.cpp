/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	pts.push_back({ -400, 0, 0 });
	pts.push_back({ -300, 0, 0 });
	pts.push_back({ 0, 200, 0 });
	pts.push_back({ 300, 0, 0 });
	pts.push_back({ 400, 0, 0 });

	r = ProtoRectangle(0, 0, 1418, 1080, Col4f(0, 0,0, 1 ), "crit_background.jpg") ;
	r.setDiffuseMaterial({ 1.0f, 1, 1 });
	r.setAmbientMaterial(0);
	//r.createBumpMap("crit_background.jpg");
	r.setBumpMap("crit_background_normal.jpg");

	//r.setSpecularMaterial({ 1, 1, 1 });
	//r.setShininess(80);
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(.25);
	beginArcBall();
	//stroke(1, 0, 0);
	/*push();
	translate(getWidth() / 2, getHeight() / 2, 0);*/
	//rect(-960, 540, 1920, 1080);
	/*pop();*/
	//push();
	//scale(1920, 1080, 1);
	r.display();

	//pop();
	
	/*curveDetail(20);
	stroke(1);
	beginPath();
	for (Vec v : pts) {
		curveVertex(v);
	}
	endPath(CLOSE);*/
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