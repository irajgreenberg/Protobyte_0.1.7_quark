/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	strokeWeight(1);
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(0);
	stroke(1, 0, 0, 1);
	for (int i = 0; i < 3000; i++) {
		point(random(-400, 400), random(-400, 400), random(-400, 400));
	}
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