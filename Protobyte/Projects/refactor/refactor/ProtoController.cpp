/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	float theta = 0.0f;
	float theta2 = 0.0f;
	float theta3 = 0.0f;
	float r = 200.0f;

	for (int i = 0; i < pts; i++) {
		float x = cos(theta) * r;
		float y = sin(theta2) * r;
		float z = cos(theta-theta2) * r;
		float x1 = cos(theta3)*z + sin(theta3)*x;
		float y1 = y;
		float z1 = sin(theta3) * z - cos(theta3) * x;

		vecs.push_back(Vec3(x1, y1, z1));
		theta += TWO_PI / pts;
		theta2 += theta;
		theta3 += PI*4 / pts;


	}
	s = Spline3(vecs, 8, false);

	t = Tube(s, 20, 18, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL,
		Tup2(.25, 29.5), 60), false, "humanSkin02.jpg");

	t.setDiffuseMaterial({ 1.0f, 1, 1 });
	t.setAmbientMaterial(0.05f);
	t.setBumpMap("humanSkin02.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	t.setTextureScale({ 1, 0.03f });
	t.setSpecularMaterial({ 1, 1, 1 });
	t.setShininess(30);
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(1);
	scale(.65f);
	arcBallBegin();
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
	save("geomOrgan", 8);
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