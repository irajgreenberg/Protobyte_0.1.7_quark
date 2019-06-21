/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	background(0.0);
	strokeWeight(5);
	//noStroke();
	fill( 1.0f, 0.0f, 0.0f, 1.0f );
	//noFill();
	stroke({ 1.0f, 0.5f, 0.0f, 1.0f });

	float theta = 0.0;
	for (int i = 0; i < pts; i++) {
		if (i % 2 == 0) {
			vecs.push_back(Vec3(cos(theta) * 100, sin(theta) * 100, 0));
			theta += TWO_PI / pts;
		}
		else {
			const static int PTS = 14;
			vecs.push_back(Vec3(cos(theta) * 200, sin(theta) * 200, 0));
			theta += TWO_PI / pts;
		}

		// y-rot
		//c-s
		//s+c
		float _z = cos(PI / 3) * vecs.at(i).z - sin(PI / 3) * vecs.at(i).x;
		float _y = vecs[i].y;
		float _x = sin(PI / 3) * vecs.at(i).z + cos(PI / 3) * vecs.at(i).x;
		vecs.push_back(Vec3(_x, _y, _z));


	}


	//beginPath();
	//for (int i = 0; i < pts; i++) {
	//	vertex(vecs.at(i));
	//	//	curveVertex(vecs.at(i).x, vecs.at(i).y, -pts*80/2+ i*80);
	//}
	//endPath();
}

void ProtoController::run() {
}

void ProtoController::display() {
	//stroke({ 1.0f, 0.5f, 0.0f, 1.0f });
	fill({ 1.0f, 0.5f, 0.0f, 1.0f });
	strokeWeight(5);
	//noStroke();
	//fill(1.0, 0.0f, 0.0f);
	//noFill();
	stroke({ 1.0f, 0.5f, 1.0f, 1.0f });
	beginArcBall();
	{
		//beginPath();
		for (int i = 0; i < pts; i++) {
			point(vecs.at(i).x, vecs.at(i).y);
			//	curveVertex(vecs.at(i).x, vecs.at(i).y, -pts*80/2+ i*80);
		}
		//endPath();
		noFill();
		strokeWeight(.5f);
		translate( 0, -200 );
		beginPath();
		for (int i = 0; i < pts; i++) {
			//vertex(vecs.at(i));
		 curveVertex(vecs.at(i).x, vecs.at(i).y, -pts*80/2+ i*80);
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
	save("MyTest", 8);
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