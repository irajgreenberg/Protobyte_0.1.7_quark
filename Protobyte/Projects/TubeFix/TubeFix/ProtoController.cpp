/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	std::vector<Vec> vs;
	float theta{ 0.0f };
	float r{ 100.0f };
	for (int i = 0; i < pts; i++) {
		vs.push_back({ cos(theta) * r, sin(theta) * r, float(-200 + 400 / pts * i) });

		//vs.push_back({ cos(theta) * r, sin(theta) * r, 0 });
		theta += TWO_PI / pts;
	}
	s1 = Spline(vs, 6, false);
	t1 = Tube(s1, 74, 12, false, "lime.jpg");
}

void ProtoController::run() {
}

void ProtoController::display() {
	arcBallBegin();
	t1.display(WIREFRAME);
	t1.display();
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