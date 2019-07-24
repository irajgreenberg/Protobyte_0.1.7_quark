/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	float theta{ 0.0 };
	float r{ 60 };
	float x{ 0.0 };
	for (int i = 0; i < count; i++) {
		x += 5;
		float y = sin(theta) * r;
		pts.push_back(Vec3(x, y, 0));
		theta += TWO_PI/count;
	}
	s = Spline(pts, 6, false);

}

void ProtoController::run() {
}

void ProtoController::display() {
	background(127);
	
	push();
	scale(5);
	s.displayControlPts();
	s.display();
	pop();

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