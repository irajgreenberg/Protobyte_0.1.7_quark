/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	for(int i = 0; i < count; i++) {
		pts.push_back(Vec(random(-200, 200), random(-200, 200), random(-200, 200)));

	}
	s = Spline(pts, 12, 1);

	t = Tube(s, 30, 8, 0, "multiple-myeloma.jpg");
	t.setTextureScale({ 1,.06 });
	t.createBumpMap("multiple-myeloma.jpg");
}

void ProtoController::run() {}


void ProtoController::display() {
	background(1);
	arcBallBegin();
	strokeWeight(6);
	stroke(.3, .4, .8, 1);
	for (Vec v : pts) { 
		point(v);
	}
	strokeWeight(20);
	s.display(20);
	t.display();
	arcBallEnd();
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