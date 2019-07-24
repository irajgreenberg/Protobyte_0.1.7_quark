/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	float w{ 200.0f };
	float gap = w / count;
	for (int i = 0; i < count; i++) {
		float x = -w / 2 + gap * i;
		float y = 0;
		float z = 0;
		if (i == 0 || i == count-1) y = -10;
		pts.push_back(Vec3(x, y, z));
	}
	
	//float theta{ 0.0 };
	//float r{ 60 };
	//float x{ 0.0 };
	//for (int i = 0; i < count; i++) {
	//	x += 5;
	//	float y = sin(theta) * r;
	//	pts.push_back(Vec3(x, y, 0));
	//	theta += TWO_PI/count;
	//}
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
	pts[0].y = pts[count-1].y = mouseY-getHeight()/2;
	s = Spline(pts, 6, false);
}

void ProtoController::mouseDragged() {
}

// Window Events
void ProtoController::onResized() {
}

void ProtoController::onClosed() {
}