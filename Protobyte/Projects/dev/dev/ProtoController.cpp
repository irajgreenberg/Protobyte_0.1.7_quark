/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	strokeWeight(12);
}

void ProtoController::run() {
}

void ProtoController::display() {
	//background({ .5f, .5f, .5f});
	beginArcBall();
	stroke(1, 0, 0, 1);
	strokeWeight(getFrameCount()*.001);
	for (int i = 0; i < 3000; i++) {
		point(random(-400, 400), random(-400, 400), random(-400, 400));
	}

	stroke(0, .5, .75, 1);
	strokeWeight(.05);
	float t = 0;
	float r = 375;
	int pts = 30;
	for (int i = 0; i < pts; i++) {
		line(cos(t) * r, sin(t) * r,
			cos(t + TWO_PI / (pts / 2)) * r, sin(t + TWO_PI / (pts / 2)) * r);
		t += TWO_PI / pts * 2;
		r -= 25;
	}
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