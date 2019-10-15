/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	noFill();
	strokeWeight(.25f);
	stroke({ 0.0, 1.0 });

	for (int i = 0; i < pts; i++) {
		vecs.push_back(Vec3(
			random(-getWidth(), getWidth()),
			random(-getHeight(), getHeight()),
			0));
	}
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(1.0);

	beginArcBall();
	{
		beginPath();
		for (auto v : vecs) {
			curveVertex(v.x, v.y, -600);
		}
		endPath(true);
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
	save("Augmented Drawing 01", 8);
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