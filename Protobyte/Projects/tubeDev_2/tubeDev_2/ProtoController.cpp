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
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(.25);
	beginArcBall();
	curveDetail(20);
	stroke(1);
	beginPath();
	for (Vec v : pts) {
		curveVertex(v);
	}
	endPath(CLOSE);
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