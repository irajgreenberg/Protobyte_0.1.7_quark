/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	float t = 0.0f;
	float r = 100.0f;
	for (int i = 0; i < count; ++i) {
		cols.push_back(Col4(random(1), random(1), random(1), random(1)));
		pts.push_back(
			Vec( random(-200, 200),
			random(-200, 200),
			random(-200, 200) )
		);
	}
	//for (int i = 0; i <count; ++i) {
	//	cols.push_back(Col4(random(1), random(1), random(1), 1.0));
	//	pts.push_back(
	//		Vec(cos(t)*r, sin(t)*r, 0)
	//	);
	//	t += TWO_PI / count;
	//}

	
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(1);
	noFill();
	stroke(.8, .1, .8, .35);
	strokeWeight(1);
	beginArcBall();
	
	push();
	//translate(-100, 0, 0);
	curveDetail(30);
	curveBias(0);
	beginPath();

	int i{ 0 };
	for (Vec v : pts) {
		stroke(cols.at(i));
		curveVertex(v);
		i++;
	}
	endPath(CLOSE_SMOOTH);
	pop();

	/*translate(200, 0, 0);
	beginArcBall();
	curveDetail(0);
	curveBias(100);
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